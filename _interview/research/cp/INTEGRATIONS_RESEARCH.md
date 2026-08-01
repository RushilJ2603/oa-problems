# CP Integrations — stats dashboard + contest tracker (my research)

All fetches are **server-side** (Flask). Browsers can't hit these APIs directly (CORS); the server fetches,
caches in SQLite with a TTL, and serves the app. Keeps Fly scale-to-zero + avoids rate limits. No secrets
except an optional clist key (gitignored like the others).

## Per-user stats — each user links their handles, we show one dashboard
| Site | Source | Endpoint / method | Key? | Gives |
|------|--------|-------------------|------|-------|
| **Codeforces** | official API | `GET api/user.info?handles=H` + `api/user.rating?handle=H` | none | rating, maxRating, rank, full rating history |
| **AtCoder** | public JSON | `GET atcoder.jp/users/H/history/json` | none | per-contest rating history → current + max. Problem stats via kenkoooo `atcoder-problems` API |
| **LeetCode** | unofficial GraphQL | `POST leetcode.com/graphql` (matchedUser {submitStats}, userContestRanking) | none | solved by difficulty, contest rating. Wrapper reference: alfa-leetcode-api |
| **CodeChef** | scrape profile HTML | `GET codechef.com/users/H` → parse `rating-number` / stars | none | current rating, stars, global/country rank (flaky; cache hard, degrade gracefully) |

Design: one `user_cp_handles` table (user_id, site, handle) + `user_cp_stats` cache (user_id, site, json, fetched_at).
Refresh on-demand ("Refresh" button) + lazily when cache older than ~6h. Any single site failing must not break
the dashboard — show last-known + a stale badge.

## Contest tracker (multi-site) — one panel, all judges
- **Primary: clist.by API v4** — `GET clist.by/api/v4/contest/?upcoming=true&order_by=start&username=U&api_key=K`
  aggregates CF, CodeChef, AtCoder, LeetCode, TopCoder, etc. Free account → username+key. **Limit 10 req/min**
  → fetch once/hour server-side, cache in SQLite; never per-user-request. (RSS/Atom also available.)
- **No-key fallback for CF alone:** `api/contest.list` (phase=BEFORE) — always works even without a clist key.
- Store upcoming contests in `contests` table (site, name, url, start, duration). Serve from cache.
- Per-user reminders: a downloadable **`.ics`** (generated from cached contests, filtered to the sites the user
  cares about) they import once → recurring calendar entries. Zero new infra, no email dependency.
  (Optional later: Google Calendar / Gmail push — needs those connectors authorized; skip for v1.)

## Cost
Two tiny periodic/on-demand fetches + a few small SQLite tables. No new always-on process. Fly stays ~$0.

## Sources
- Codeforces API: https://codeforces.com/apiHelp/methods
- clist.by API v4 doc: https://clist.by/api/v4/doc/
- AtCoder history json: https://atcoder.jp/users/{handle}/history/json
- LeetCode GraphQL wrappers: alfa-leetcode-api (github.com/alfaarghya/alfa-leetcode-api), leetcode-query (npm)
- CodeChef scrape patterns: github.com/topics/codechef-api
