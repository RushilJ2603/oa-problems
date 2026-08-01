# Estimation, Guesstimates & Market Sizing

::: keypoint
**The Fermi Method:** 

1. Break the target quantity into a product (or sum) of factors you can each estimate.
2. Anchor on known population figures or round numbers.
3. Estimate each factor to one significant figure.
4. Multiply through.
5. Sanity-check the order of magnitude and units. State your assumptions explicitly at each step.

:::

::: interview
In consulting, PM, and quant interviews, they grade the *structure and assumptions*, not the exact final number. Think out loud, state each assumption clearly, and proactively point out where your model might be overestimating or underestimating.

:::

## Classic Fermi

**Q1.** How many piano tuners are there in Chicago?
**Approach:** Break the problem into total pianos divided by pianos tuned per tuner.

- Population of Chicago: ~$3$ million.
- Persons per household: ~$3$.
- Households in Chicago: $1$ million.
- Fraction of households with a tuned piano: $10\%$ (or $1/10$).
- Total pianos in Chicago: $100,000$.
- Pianos tuned per year: Assumed once a year, so $100,000$ tunings per year.
- Tuner capacity: $4$ pianos per day $\times$ $250$ workdays per year = $1,000$ tunings per year per tuner.
- Tuners needed: $100,000 / 1,000 = 100$.

**Estimate:** $100$ piano tuners. (Sanity: In a major city, finding $100$ specialists in the phonebook feels right, order of magnitude $10^2$).

**Q2.** How many golf balls can fit in a standard school bus?
**Approach:** Volume of bus divided by volume of a golf ball, multiplied by a packing fraction.

- Bus dimensions: $40$ feet long $\times$ $8$ feet wide $\times$ $6$ feet high $\approx 2,000$ cubic feet.
- Convert to inches: $1$ cubic foot = $12^3 \approx 1,700$ cubic inches.
- Total empty bus volume: $2,000 \times 1,700 \approx 3.4 \times 10^6$ cubic inches.
- Golf ball volume: Sphere with radius ~$0.75$ inches. Volume $= \frac{4}{3} \pi r^3 \approx 4 \times (0.75)^3 \approx 1.7$ cubic inches (let's round to $1.5$ for ease).
- Packing fraction for spheres (random close packing): ~$0.66$ (or $2/3$).
- Empty space (seats, etc.): Assume the bus is completely empty for the baseline math.
- Total balls: $(3.4 \times 10^6 / 1.5) \times 0.66 \approx 2.2 \times 10^6 \times 0.66 \approx 1.5 \times 10^6$.

**Estimate:** $1.5 \times 10^6$ golf balls. (Sanity: A million small balls in a large vehicle is the standard order of magnitude expected for this classic problem).

**Q3.** What is the weight of a commercial aeroplane (e.g., a Boeing 747)?
**Approach:** Break down into major components: fuselage, wings, engines, fuel, passengers, and cargo.

- Fuselage: Cylinder ~$70$ m long, $6$ m diameter. Surface area $\approx \pi \times 6 \times 70 \approx 1,300 \text{ m}^2$. Assume aluminium thickness of $0.01$ m, volume is $13 \text{ m}^3$. Density of aluminium $\approx 2,700 \text{ kg/m}^3$. Weight $\approx 35,000 \text{ kg}$.
- Wings and Tail: Roughly equal to fuselage surface, add another $35,000 \text{ kg}$.
- Engines: $4$ engines $\times$ $5,000 \text{ kg} = 20,000 \text{ kg}$.
- Interior/Avionics: ~$30,000 \text{ kg}$.
- Empty weight sum: ~$120,000 \text{ kg}$.
- Fuel: ~$150,000$ kg for a long-haul flight.
- Passengers: $400$ pax $\times$ $100 \text{ kg}$ (with bags) = $40,000 \text{ kg}$.

**Estimate:** Empty weight ~$120,000 \text{ kg}$, max takeoff weight ~$310,000 \text{ kg}$. (Sanity: ~$300$ metric tonnes for a jumbo jet aligns with runway structural limits).

**Q4.** How many hairs are on a typical human head?
**Approach:** Area of the scalp multiplied by hair density.

- Scalp area: Treat as half a sphere. Radius of head ~$10 \text{ cm}$. Area $= \frac{1}{2} \times 4 \pi r^2 = 2 \pi (100) \approx 600 \text{ cm}^2$.
- Hair density: Look at $1 \text{ cm}^2$. Assume hairs are spaced $0.5 \text{ mm}$ apart. A $1 \text{ cm} \times 1 \text{ cm}$ square has $20 \times 20 = 400$ hairs per $\text{cm}^2$.
- Hair thickness and spacing varies, so let's adjust the average to $150$ to $200$ hairs per $\text{cm}^2$.
- Total hairs: $600 \text{ cm}^2 \times 200 \text{ hairs/cm}^2 = 120,000$.

::: keypoint
When estimating surface area, treating the human head as a simple geometric shape (a hemisphere or a cylinder) is a standard Fermi technique. Precision is less important than the logic of `Area` $\times$ `Density`.

:::

**Estimate:** $120,000$ hairs. (Sanity: $10^5$ is the biologically accepted average).

## Market Sizing

**Q5.** How many cups of coffee are consumed per day in New York City?
**Approach:** Segment the population by age and drinking habit.

- NYC Population: ~$8$ million.
- Age breakdown: $20\%$ children (no coffee), $80\%$ adults ($6.4$ million).
- Coffee drinkers: Assume $75\%$ of adults drink coffee ($4.8$ million).
- Consumption rate: Heavy drinkers ($25\%$ of drinkers, $3$ cups/day), average ($50\%$, $1.5$ cups/day), light ($25\%$, $1$ cup/day).
- Weighted average: $0.25(3) + 0.5(1.5) + 0.25(1) = 0.75 + 0.75 + 0.25 = 1.75$ cups per day per drinker.
- Total daily cups: $4.8 \text{ million} \times 1.75 \approx 8.4 \text{ million}$.

::: trap
A common mistake in market sizing is forgetting to segment the population. Estimating "everyone drinks $1$ cup" wildly overestimates. Always strip out children, non-consumers, and segment by heavy/light usage.

:::

**Estimate:** $8.4$ million cups per day. (Sanity: roughly $1$ cup per capita per day).

**Q6.** How many smartphones are sold annually in India?
**Approach:** Addressable population multiplied by penetration, divided by replacement cycle.

- India population: ~$1.4$ billion.
- Addressable market (teens and adults, factoring out extreme poverty/elderly): ~$70\% \approx 1$ billion.
- Smartphone penetration in this segment: ~$70\% \approx 700$ million smartphone users.
- Replacement cycle: Average person upgrades every $3.5$ years.
- Annual replacement sales: $700 \text{ million} / 3.5 = 200$ million.
- First-time buyers: Assume $5\%$ market growth per year $= 35$ million.
- Total annual sales: $200 + 35 = 235$ million.

**Estimate:** $235$ million smartphones per year. (Sanity: For a billion-user market upgrading every $3$ to $4$ years, $200$ million is exactly the right order of magnitude).

**Q7.** How many ride-hailing trips (e.g., Uber/Ola) occur daily in a major city like London?
**Approach:** Top-down via the supply side (number of active drivers) multiplied by trips per driver.

- London population: ~$9$ million.
- Registered drivers: Assume $1\%$ of the working-age population drives for a ride-hail app = $\sim 50,000$ to $100,000$ drivers. Let's assume $100,000$ licensed private hire drivers.
- Active drivers per day: $50\%$ are working on a given day = $50,000$.
- Trips per driver per shift: A $8$-hour shift, $2.5$ trips per hour = $20$ trips per day.
- Total trips: $50,000 \times 20 = 1,000,000$.

**Estimate:** $1$ million trips per day. (Sanity: $\sim 10\%$ of the population taking a ride each day; aligns with public transport and taxi stats).

**Q8.** What is the annual revenue of a standalone McDonald's store?
**Approach:** Hours of operation $\times$ customers per hour $\times$ average order value.

- Operating hours: Assume $16$ hours per day ($6$ AM to $10$ PM).
- Peak vs Off-peak:
  - Peak ($4$ hours: lunch and dinner): $2$ registers $+ 2$ drive-thru lanes. Assume $1$ order per minute per point of sale (POS). $4 \text{ POS} \times 60 \text{ mins} = 240 \text{ orders/hour}$.
  - Off-peak ($12$ hours): $1$ register $+ 1$ drive-thru. Assume $1$ order every $3$ mins per POS = $40 \text{ orders/hour}$.
- Total daily orders: $(4 \times 240) + (12 \times 40) = 960 + 480 = 1,440$ orders per day.
- Average order value (AOV): $\approx 10$ dollars.
- Daily revenue: $1,440 \times 10 = 14,400$ dollars.
- Annual revenue: $14,400 \times 365 \approx 14,400 \times 400 \approx 5.5$ million dollars. Refined: $14.4 \times 365 = 5.25$ million dollars.

**Estimate:** $5.25$ million dollars per year. (Sanity: Typical fast-food franchise revenues are in the $2$ to $5$ million dollar range, making this reasonable for a high-traffic standalone store).

## Systems & Throughput

**Q9.** How much data is generated globally by YouTube video uploads per day?
**Approach:** Hours uploaded per minute $\times$ size per hour $\times$ replication factor.

- Upload rate: Assume $500$ hours of video uploaded per minute globally.
- Daily upload hours: $500 \times 60 \times 24 = 720,000$ hours per day.
- Video size: Assume average quality is 1080p. $1080\text{p}$ video is about $1 \text{ GB}$ per hour (compressed).
- Base data: $720,000 \text{ hours} \times 1 \text{ GB/hour} = 720,000 \text{ GB} = 720 \text{ TB}$.
- Replication & Transcoding: YouTube transcodes to multiple resolutions (480p, 720p, 4K) and replicates data across data centres. Assume this creates a $5\times$ storage multiplier.
- Total storage per day: $720 \text{ TB} \times 5 = 3,600 \text{ TB} = 3.6 \text{ PB}$.

**Estimate:** $3.6 \text{ Petabytes}$ per day. (Sanity: Petabyte scale per day is standard for hyperscale user-generated content).

**Q10.** Estimate the peak queries per second (QPS) for Google Search.
**Approach:** Global internet users $\times$ daily searches $\div$ seconds in a day $\times$ peak multiplier.

- Internet users: ~$5$ billion.
- Searches per user per day: Assume $3$ searches.
- Total daily searches: $15$ billion.

::: keypoint
For system design and throughput estimates, memorize this anchor: $1$ day $\approx 86,400$ seconds $\approx 10^5$ seconds. To convert daily traffic to average QPS, simply divide by $10^5$.

:::

- Average QPS: $15,000,000,000 / 100,000 = 150,000$ QPS average.
- Peak multiplier: Global traffic follows time zones, but peak vs average is roughly $2\times$.
- Peak QPS: $150,000 \times 2 = 300,000$.

**Estimate:** $300,000 \text{ QPS}$. (Sanity: Big Tech global services usually operate in the $10^5$ to $10^6$ QPS range).

**Q11.** What is the total storage required to host profile pictures for $2$ billion WhatsApp users?
**Approach:** Users $\times$ active profiles $\times$ average image size $\times$ replication factor.

- Total users: $2$ billion.
- Profile picture adoption: $90\%$ of users have a picture = $1.8$ billion pictures.
- Image size: A compressed profile picture (thumbnail + full screen mobile) is around $100 \text{ KB}$.
- Total raw storage: $1.8 \times 10^9 \times 100 \times 10^3 \text{ bytes} = 1.8 \times 10^{14} \text{ bytes} = 180 \text{ TB}$.
- Replication factor: Data is typically replicated across $3$ data centres for fault tolerance.
- Total storage: $180 \text{ TB} \times 3 = 540 \text{ TB}$.

**Estimate:** $540 \text{ Terabytes}$. (Sanity: Profile pictures are tiny, so under $1 \text{ PB}$ for a global userbase is expected).

**Q12.** Estimate the bandwidth required to stream a live sporting event to $1$ million concurrent viewers.
**Approach:** Viewers $\times$ average bitrate per viewer.

- Concurrent viewers: $1,000,000$.
- Resolution distribution:
  - $20\%$ on 4K ($15 \text{ Mbps}$)
  - $50\%$ on 1080p ($5 \text{ Mbps}$)
  - $30\%$ on Mobile/720p ($2 \text{ Mbps}$)
- Average bitrate: $(0.2 \times 15) + (0.5 \times 5) + (0.3 \times 2) = 3 + 2.5 + 0.6 = 6.1 \text{ Mbps}$.
- Total bandwidth: $1,000,000 \times 6.1 \text{ Mbps} = 6.1 \text{ million Mbps} = 6.1 \text{ Tbps}$ (Terabits per second).

**Estimate:** $6 \text{ Tbps}$. (Sanity: Major CDNs handle over $100 \text{ Tbps}$, so $6 \text{ Tbps}$ for a huge live event is plausible and requires aggressive CDN offloading).

## Everyday Counting Estimates

**Q13.** How many petrol stations are there in the United States?
**Approach:** Number of cars $\times$ fill-ups per week $\div$ station throughput.

- US Population: $330$ million.
- Cars: $\sim 1$ car per driving adult $\approx 250$ million cars.
- Refuelling frequency: Once a week per car = $250$ million fill-ups per week.
- Station capacity:
  - Average station has $8$ pumps.
  - Fill-up takes $5$ minutes = $12$ cars per hour per pump.
  - Assume station is effectively busy $10$ hours a day.
  - Cars per day per station = $8 \times 12 \times 10 = 960$ cars per day $\approx 1,000$.
  - Fill-ups per week per station = $7,000$ maximum capacity.
  - Utilisation: Assume they run at $30\%$ capacity over the week = $2,000$ fill-ups per week.
- Total stations: $250,000,000 / 2,000 = 125,000$.

**Estimate:** $125,000$ stations. (Sanity: Roughly $1$ station per $2,500$ people. In a town of $10,000$, there are $\sim 4$ stations. This checks out).

**Q14.** How many passenger elevators are there in Manhattan?
**Approach:** Number of buildings $\times$ elevators per building.

- Manhattan area: $\sim 20$ to $25$ square miles.
- City blocks: $\sim 200$ north-south streets, $\sim 15$ avenues. $200 \times 15 = 3,000$ blocks.
- Buildings per block: Average $20$ buildings. Total buildings = $60,000$.
- Building types (by height):
  - Low-rise (1-4 floors): $50\%$ ($30,000$ buildings). $0$ elevators.
  - Mid-rise (5-15 floors): $40\%$ ($24,000$ buildings). Average $2$ elevators.
  - High-rise (16-40 floors): $8\%$ ($4,800$ buildings). Average $6$ elevators.
  - Skyscrapers (41+ floors): $2\%$ ($1,200$ buildings). Average $20$ elevators.
- Total elevators: $(30,000 \times 0) + (24,000 \times 2) + (4,800 \times 6) + (1,200 \times 20) = 0 + 48,000 + 28,800 + 24,000 = 100,800$.

**Estimate:** $100,000$ elevators. (Sanity: $100,000$ elevators for $\sim 2$ million residents and massive commercial space feels correct).

**Q15.** How many windows are in a typical major city (e.g., Seattle)?
**Approach:** Segregate into residential, commercial, and vehicles.

- Seattle Population: ~$750,000$ (city proper). Let's use $1$ million for easy math.
- Residential windows:
  - Assume $2$ people per household = $500,000$ homes.
  - Average home has $10$ windows (living room, bedrooms, kitchen, etc.).
  - Total residential windows = $5 \text{ million}$.
- Commercial/Office windows:
  - Assume $50\%$ of the population works in offices/shops ($500,000$ workers).
  - Modern offices are glass-fronted. Let's estimate $2$ window-equivalents per worker.
  - Total commercial windows = $1 \text{ million}$.
- Vehicles/Transit: $500,000$ cars $\times$ $6$ windows = $3 \text{ million}$.
- Total: $5 \text{ million} + 1 \text{ million} + 3 \text{ million} = 9 \text{ million}$.

**Estimate:** $9 \text{ million}$ windows. (Sanity: $\sim 10$ windows per capita across all domains is a very solid Fermi anchor).

**Q16.** How many footballs (soccer balls) are manufactured globally each year?
**Approach:** Global players $\rightarrow$ ball ownership $\rightarrow$ replacement rate.

- Global population: $8$ billion.
- Football fans/players: It's the most popular sport. Assume $10\%$ of the population plays it actively or recreationally = $800$ million people.
- Ball ownership: In developing nations, $10$ kids might share $1$ ball. In developed nations, $1$ kid might have $2$ balls. Let's assume an average of $1$ ball per $5$ players.
- Total balls in circulation: $800 \text{ million} / 5 = 160$ million balls.
- Replacement rate: Due to wear and tear, punctures, or getting lost, a ball lasts about $2$ years.
- Annual replacement: $160 \text{ million} / 2 = 80$ million balls.
- Unused/Promo balls: Add $20\%$ for retail inventory, promotional items, and display.
- Total manufactured: $80 \times 1.2 \approx 100$ million.

**Estimate:** $100$ million footballs per year. (Sanity: $10^8$ consumer sporting items for an $8$ billion population is highly reasonable).

## Sources

- PrepInsta — https://prepinsta.com/ (Company-specific OA guesstimates)
- InterviewQuery — https://www.interviewquery.com/ (Market sizing and volume estimation frameworks)
- Brainstellar — https://brainstellar.com/ (Classic quant and Fermi puzzles)
- "Heard on the Street" (Timothy Crack) — (Fermi method and brain-teaser types)
