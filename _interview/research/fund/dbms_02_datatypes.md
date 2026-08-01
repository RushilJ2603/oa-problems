# 2. Exhaustive Data Types

While the ISO/IEC 9075 SQL standard defines a core set of data types, the reality of database engineering is that every major RDBMS implements them slightly differently [1]. To survive a deep technical grilling, you must know not just the standard types, but the *nuances* and traps of how PostgreSQL actually stores data.

## 2.1 Numeric Types — Complete Reference

### Exact Numerics (Integers)

Integers are whole numbers without a fractional part. They are the simplest and most efficient way to store counts, identifiers, or mathematical whole values. Think of them as physical tally marks—you can have 1, 2, or 3 apples, but never 2.5. 

PostgreSQL offers three main integer types, chosen based on the maximum value you expect to store [3]:

| Type | Bytes | Range | Use Case |
|---|---|---|---|
| `SMALLINT` | 2 | -32,768 to 32,767 | Legacy systems, strict memory constraints |
| `INTEGER` | 4 | -2.1 billion to 2.1 billion | Default choice for most general numbers and identifiers |
| `BIGINT` | 8 | -9.2 quintillion to 9.2 quintillion | Extremely large identifiers, high-volume metrics |

In SQL, to define a column as an integer, you use the type name directly. 

When you need an integer that automatically increments with each new row (which is standard for creating unique identifiers, or Primary Keys), PostgreSQL uses a special keyword construct: `GENERATED ALWAYS AS IDENTITY`. This tells the database engine to automatically calculate and assign the next available integer whenever a new row is added, guaranteeing uniqueness without you having to track the previous highest number.

```sql
-- Creating a table (a collection of rows) with an auto-incrementing integer column
CREATE TABLE users (
    user_id INTEGER GENERATED ALWAYS AS IDENTITY,
    age SMALLINT
);
```

*First-use glosses:*

- `CREATE TABLE`: A command that defines a new empty structure to hold data rows, specifying its columns and their data types.
- `NULL`: In SQL, `NULL` represents a completely missing or unknown value. It is not zero; it is not an empty string. It means "absence of data." If you try to add an integer to `NULL`, the result is `NULL`.

*Failure case:* If you define an identifier column as `SMALLINT` and your system creates its 32,768th user, the database will throw an overflow error and completely halt new registrations. Always default to `INTEGER` or `BIGINT` for identifiers unless you have a proven, extreme memory constraint.

### Exact Numerics (Fixed-Point Decimals)

::: heavy
**Heavy Concept: Fixed-Point Decimals (`DECIMAL` / `NUMERIC`)**
:::

**Analogy:** Think of a standard integer like counting whole apples (1, 2, 3). Think of floating-point math like guessing the weight of those apples on a loose spring scale—it's fast and close enough, but imprecise. Fixed-point decimal types are like an accountant's physical ledger book: every single cent is perfectly tracked in its own rigid column, and rounding never happens unless you explicitly ask for it.

**Diagram-in-words:** Imagine a rigid grid with exactly 10 slots for digits, and a permanent decimal point bolted firmly in place after the 8th slot. You have exactly 8 digits for the dollars, and exactly 2 digits for the cents. The decimal point never "floats" or moves.

**Concrete Example:** If an item costs $12.34, you want it stored exactly as 12.34. If you used a floating-point type instead, the computer's base-2 memory might store it as 12.340000000000001 or 12.339999999999999. Over millions of transactions, these microscopic errors compound into real missing money.

**Plain-English:** A fixed-point decimal type guarantees that the exact fractional number you insert is exactly the number you read back. It trades computational speed and storage space to ensure absolute mathematical precision. 

**Technical:** In PostgreSQL, `DECIMAL` and `NUMERIC` are perfectly equivalent. You define them using the syntax `NUMERIC(p, s)`. 

- **Precision (`p`):** The total maximum number of significant digits across the entire number (both left and right of the decimal).
- **Scale (`s`):** The exact number of digits to the right of the decimal point.

For example, `NUMERIC(5, 2)` can store any value from -999.99 to 999.99.

| Type | Syntax | Use Case |
|---|---|---|
| `DECIMAL(p,s)` | `DECIMAL(10,2)` | Currency, financial data, exact scientific measurements |
| `NUMERIC(p,s)` | `NUMERIC(5,3)` | Identical to DECIMAL |

*Why it matters here:* Financial applications mandate exact math. 

::: trap
**Trap: Using FLOAT for Currency**
A classic beginner mistake is storing money as a floating-point number [2]. 
*Failure case:* This breaks when you sum thousands of financial transactions and find your balance sheet is off by a few cents due to floating-point representation limits in binary memory. Always use `DECIMAL` or `NUMERIC` for currency.
:::

### Approximate Numerics (Floating-Point)

Unlike fixed-point decimals, floating-point types allow the decimal point to "float" dynamically based on the size of the number. They trade absolute precision for the ability to represent an astronomically wide range of values in a very small amount of memory.

| Type | Bytes | Precision | When to Use |
|---|---|---|---|
| `REAL` | 4 | ~6 decimal digits | Scientific data, sensor readings |
| `DOUBLE PRECISION` | 8 | ~15 decimal digits | Complex scientific computations |

*Failure case:* If you store `123456789.12` in a 4-byte `REAL` column, it may read back as `123456792.00` because you exceeded its ~6 digits of guaranteed precision.

## 2.2 Character Strings — Complete Reference

Text data in SQL is referred to as a "character string" or just "string". PostgreSQL provides different ways to store text depending on whether the length is predictable.

::: heavy
**Heavy Concept: Variable vs. Fixed-Length Strings**
:::

**Analogy:** A fixed-length string (`CHAR`) is like a physical hotel registration book where every name gets exactly a 50-character wide box. If a guest's name is "Bob" (3 letters), the hotel clerk fills the remaining 47 spaces with blank whiteout. A variable-length string (`VARCHAR` or `TEXT`) is like a dynamic digital sticky note: it only takes up exactly as much space as the letters written on it, plus a tiny tag recording how long the word is.

**Concrete Example:** If you store the state code 'CA' in a `CHAR(2)` column, it takes exactly 2 characters of space. If you store 'CA' in a `CHAR(10)` column, PostgreSQL pads it with 8 invisible spaces to make it exactly 10 characters long ('CA        ').

**Plain-English:** Fixed-length types force every entry to be exactly the same size, padding shorter entries with spaces. Variable-length types adapt to the data, storing only the characters provided. 

**Technical:** PostgreSQL natively stores all text using UTF-8 encoding. You define string columns using:

| Type | Behavior | Max Length | Trailing Spaces |
|---|---|---|---|
| `CHAR(n)` | Fixed-length, space-padded | 10,485,760 bytes | Padded with spaces |
| `VARCHAR(n)` | Variable-length with a strict limit | 10,485,760 bytes | Not padded |
| `TEXT` | Unlimited variable-length | ~1 GB | Not padded |

```sql
-- Creating a table with different character string types
CREATE TABLE user_profiles (
    state_code  CHAR(2),        -- Always exactly 2 chars. Good for US states ('CA', 'NY').
    username    VARCHAR(50),    -- Variable length, but strictly capped at 50 chars.
    biography   TEXT            -- Variable length, functionally unlimited. Good for essays.
);
```

*Alternative rejected:* Why not use `CHAR(n)` for everything to keep rows uniform? Because space-padding wastes massive amounts of disk space for data that varies in length (like names or emails), and it requires you to actively trim off the trailing spaces later when querying the data.

*Failure case:* If you store an email address in a `CHAR(255)` column, searching for `'user@example.com'` might fail unless you account for the 239 invisible spaces padded at the end. In PostgreSQL, always default to `TEXT` or `VARCHAR` unless the data has a globally standardized fixed length (like a 2-letter country code).

## 2.3 Date, Time, Timestamp, and Interval — Complete Reference

Storing temporal (time-based) data correctly is one of the hardest parts of database design because of timezones, leap years, and daylight saving time.

| Type | Behavior | Example Format |
|---|---|---|
| `DATE` | A calendar date with no time of day | '2025-06-27' |
| `TIME` | A time of day with no date attached | '17:30:00' |
| `TIMESTAMP` | Date and time, *without* timezone awareness | '2025-06-27 17:30:00' |
| `TIMESTAMPTZ` | Date and time, *with* timezone awareness | '2025-06-27 17:30:00+05:30' |
| `INTERVAL` | A span of time, not tied to a specific calendar date | '3 days 2 hours' |

In SQL, a literal time value is written as a string inside single quotes, prefixed by the keyword of its data type.

```sql
-- Date and time literals (how you write them explicitly in a query)
SELECT DATE '2025-06-27';
SELECT TIME '17:30:00';
SELECT TIMESTAMP '2025-06-27 17:30:00';
SELECT TIMESTAMPTZ '2025-06-27 17:30:00+05:30'; 
SELECT INTERVAL '3 days 2 hours';

-- Date arithmetic: You can add an INTERVAL to a DATE to get a new date in the future
SELECT CURRENT_DATE + INTERVAL '30 days'; 
```

*First-use gloss:* `SELECT`: The fundamental SQL command used to ask the database to return data to you. When used without a table, it simply evaluates and returns the expression provided.

::: heavy
**Heavy Concept: Timezone Awareness (`TIMESTAMPTZ`)**
:::

**Analogy:** If you tell a friend "Let's talk at 3:00 PM," that works if you are in the same room. But if they fly to Tokyo and you stay in New York, "3:00 PM" becomes dangerously ambiguous. You need an absolute, globally agreed-upon anchor, like "3:00 PM New York Time."

**Concrete Example:** A user clicks a button at exactly 17:30:00 in India (UTC+05:30). If you store this in a plain `TIMESTAMP` column as just `2025-06-27 17:30:00`, the database has no idea where on Earth that happened. When an analyst in New York queries that data, they might falsely assume it happened at 17:30 New York time.

**Plain-English:** The `TIMESTAMPTZ` (Timestamp with Time Zone) type converts the incoming time to UTC (Coordinated Universal Time) for storage. When you ask the database for that value later, it automatically translates the stored UTC time back into your local timezone. It represents a specific, absolute moment in the history of the universe.

**Technical:** `TIMESTAMPTZ` does not actually store the original timezone string you provide. It reads your timezone offset (`+05:30`), calculates what the equivalent UTC time is, stores *that* UTC integer on disk, and discards your original timezone label.

::: trap
**Trap: Timezone Ignorance**
Storing a real-world event in a plain `TIMESTAMP` without knowing the application's timezone means you permanently lose the absolute point in time. 
*Alternative rejected:* Just storing a Unix epoch (an integer counting seconds since 1970) avoids timezone bugs, but makes querying for "all events that happened on a Tuesday" computationally expensive because the database has to convert millions of integers back to calendar days on the fly. Use `TIMESTAMPTZ` for events.
:::

## 2.4 Binary and Boolean Types

### Boolean
A boolean represents a simple truth value. 

| Type | Behavior | Valid Inputs |
|---|---|---|
| `BOOLEAN` | Represents truth states | `TRUE`, `FALSE`, `NULL` |

In PostgreSQL, the `BOOLEAN` (or `BOOL`) type is deeply integrated [3]. Unlike some other dialects that fake booleans using integers (where 1 is true and 0 is false), PostgreSQL treats true and false as native, distinct concepts.

### Binary Data (`BYTEA`)
Sometimes you need to store raw, unformatted computer data—like a compiled executable, a compressed ZIP file, or an encrypted password hash—where text encoding rules like UTF-8 would corrupt the bytes.

| Type | Use Case |
|---|---|
| `BYTEA` | Raw binary data (images, encrypted blobs, file contents) |

*Why it matters here:* If you try to store a raw JPEG image in a `TEXT` column, PostgreSQL will attempt to validate it as UTF-8 text, fail, and reject the data. `BYTEA` tells the database to store the exact binary zeroes and ones without trying to understand them.

## 2.5 Advanced Types (JSON, Arrays, UUID, Enum, XML, Range)

PostgreSQL shines in its support for complex, non-traditional relational data types.

::: heavy
**Heavy Concept: JSON vs JSONB**
:::

**Analogy:** Storing plain `JSON` is like keeping a paper document in a filing cabinet; if you want to find a specific word on page 3, you have to pull out the whole document and read it from top to bottom every time. Storing `JSONB` (Binary JSON) is like scanning that document into a searchable database; the initial scan takes a bit longer, but finding that word later is instantaneous.

**Concrete Example:** You receive a large JSON payload from an external API: `{"user": "alice", "clicks": 42}`. 

**Plain-English:** The `JSON` type stores exactly the text string you gave it, including all spaces and duplicate keys. To query it, the database must parse the text on every single query. The `JSONB` type parses the text *once* when you insert it, removing unnecessary spaces and deduplicating keys, and stores it in a custom binary format [4]. 

**Technical:** `JSONB` supports advanced indexing (like GIN indexes), which allows PostgreSQL to look deep inside the nested JSON structure instantly, without scanning the whole table. Always use `JSONB` unless you have a strict legal requirement to preserve the exact whitespace of an incoming text payload.

```sql
-- Creating a table with a JSONB column
CREATE TABLE web_events (
    event_id INTEGER GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    event_payload JSONB
);

-- Querying deep inside the JSONB structure using specialized operators
-- The ->> operator extracts a nested JSON value as plain SQL text
SELECT event_payload->>'user_name' FROM web_events;

-- The @> operator checks if the left JSON payload contains the right JSON payload
SELECT * FROM web_events WHERE event_payload @> '{"action": "click"}';
```

### Arrays
Relational databases traditionally require you to put multiple values into a separate, linked table. PostgreSQL allows you to store an array (a list) of values directly inside a single column.

```sql
CREATE TABLE survey_responses (
    response_id INTEGER PRIMARY KEY,
    selected_tags TEXT[],       -- An array containing multiple TEXT values
    quiz_scores INTEGER[]       -- An array containing multiple INTEGER values
);

-- The ARRAY keyword defines the list of items
INSERT INTO survey_responses (response_id, selected_tags, quiz_scores) 
VALUES (1, ARRAY['sql', 'databases'], ARRAY[85, 92, 78]);

-- The ANY() operator checks if a specific value exists anywhere inside the array
SELECT * FROM survey_responses WHERE 'sql' = ANY(selected_tags);
```

*Alternative rejected:* Arrays violate the strict rules of database normalization (specifically First Normal Form, which dictates atomic values). However, for simple lists like "tags" where you never need to join the tags to another table, arrays offer immense performance benefits over creating complex join structures.

### UUID (Universally Unique Identifier)
A UUID is a 128-bit number formatted as a 36-character string (e.g., `550e8400-e29b-41d4-a716-446655440000`). It is used when you need to generate a unique identifier without relying on a central database counter.

```sql
CREATE TABLE distributed_nodes (
    -- gen_random_uuid() is a built-in function that creates a secure, random UUID
    node_id UUID DEFAULT gen_random_uuid() PRIMARY KEY,
    location VARCHAR(100)
);
```

### Enum Types
An Enum (Enumeration) is a static, ordered set of specific text values. It acts as a strict whitelist.

```sql
-- First, define the new custom type and its allowed values
CREATE TYPE shirt_size AS ENUM ('XS', 'S', 'M', 'L', 'XL', 'XXL');

-- Then use it in a table
CREATE TABLE products (
    product_id INTEGER,
    size shirt_size
);

-- This succeeds because 'M' is in the whitelist
INSERT INTO products VALUES (1, 'M');    

-- This fails instantly and protects your data integrity
INSERT INTO products VALUES (2, 'XXXL'); 
```

### Range Types
Range types represent an upper and lower bound of values in a single column. They are incredibly powerful for scheduling systems.

```sql
CREATE TABLE meeting_rooms (
    room_number INTEGER,
    -- TSTZRANGE means Timestamp with Time Zone Range (a start and end time)
    booked_during TSTZRANGE
);

-- The @> operator checks if a specific moment falls within the stored range
SELECT * FROM meeting_rooms 
WHERE booked_during @> TIMESTAMPTZ '2025-06-27 15:00+05:30';
```

### XML
For legacy enterprise systems, PostgreSQL provides an `XML` type that checks if the incoming text is well-formed XML and provides functions (like `xpath()`) to query nodes inside it.

```sql
CREATE TABLE configuration_files (
    config_id INTEGER,
    settings XML
);
```

## 2.6 Data Type Selection Cheat Sheet

| Data | Correct Type | Wrong Type | Why |
|---|---|---|---|
| Currency | `NUMERIC` / `DECIMAL` | `REAL`, `DOUBLE PRECISION` | Floating-point rounding destroys financial accuracy. |
| Email Address | `VARCHAR(255)` / `TEXT` | `CHAR(255)` | Wastes disk space with invisible spaces. |
| Unique ID | `UUID` / `BIGINT` | `VARCHAR(36)` | Storing a UUID as plain text wastes space and slows down index lookups. |
| Yes/No Flag | `BOOLEAN` | `VARCHAR(3)` ('yes'/'no') | Semantic clarity and minimal storage footprint. |
| Real-World Events | `TIMESTAMPTZ` | `TIMESTAMP`, `BIGINT` | Prevents permanent loss of timezone context. |
| Network IP | `INET` (Postgres specific) | `VARCHAR(45)` | Built-in network types validate the IP and allow subnet querying. |
| Country Code | `CHAR(2)` | `VARCHAR(100)` | Enforces fixed length for standardized ISO 3166 codes. |
| Article Body | `TEXT` | `VARCHAR(8000)` | Arbitrary length caps lead to broken, truncated data. |

### References
1. Data Type Standards - GeeksForGeeks - https://www.geeksforgeeks.org/sql-data-types/
2. Why not use Double or Float to represent currency? - StackOverflow - https://stackoverflow.com/questions/3730019/why-not-use-double-or-float-to-represent-currency
3. PostgreSQL Data Types - Postgres Docs - https://www.postgresql.org/docs/current/datatype.html
4. PostgreSQL JSON Types - Postgres Docs - https://www.postgresql.org/docs/current/datatype-json.html
