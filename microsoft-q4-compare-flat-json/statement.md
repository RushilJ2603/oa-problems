# Compare Flat JSON Objects

You are given two strings, `json1` and `json2`, each representing a valid **flat** JSON object. Every
key and value is a string enclosed in double quotes (`"`). The objects have no nested objects or
arrays.

Return all keys that are present in **both** objects but are associated with **different** values.

> You must implement your own parsing — do not rely on a JSON library. (This is a self-hosted judge,
> so there's nothing stopping you, but the intended exercise is the parser.)

## Input

```
json1
json2
```

- Line 1: the string `json1`.
- Line 2: the string `json2`.

## Output

The keys that exist in both objects with differing values, **sorted in ascending order, one per
line**. If there are no such keys, print nothing.

## Constraints

- `1 ≤ |json1|, |json2| ≤ 100000`
- The JSON strings contain no whitespace.
- The objects are flat (no nested objects or arrays).
- Keys are unique within a single object.
- All keys and values are non-empty and contain no double-quote character (`"`). Any other
  character (including `:` `,` `{` `}`) may appear inside a key or value.
- Both inputs are valid flat JSON objects (possibly empty, i.e. `{}`).

## Example 1

**Input**
```
{"key1":"value1","key2":"value2","key3":"value3"}
{"key1":"value1","key2":"new_value","key3":"value3","key4":"value4"}
```
**Output**
```
key2
```

`key2` is present in both objects with different values. The other common keys (`key1`, `key3`) have
identical values, and `key4` exists only in the second object.
