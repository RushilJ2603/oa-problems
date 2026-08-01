# Statistics & Data Analysis

::: definition
**Core Statistical Measures & Formulas**

- **Mean/Median/Mode:** Mean is the average, sensitive to outliers. Median is the middle value, **robust** to outliers (skewed data). Mode is the most frequent value.
- **Variance & SD:** Variance $\sigma^2 = E[X^2] - (E[X])^2$. Standard deviation (SD) is $\sigma = \sqrt{\text{Variance}}$.
- **Linear Transformation:** If $Y = aX + b$, then $E[Y] = aE[X] + b$, and $\text{Var}(Y) = a^2 \text{Var}(X)$. The SD becomes $|a|\sigma_X$. (Adding a constant shifts the mean but does *not* change variance).
- **Covariance & Correlation:** $\text{Cov}(X,Y) = E[XY] - E[X]E[Y]$. Correlation $\rho = \frac{\text{Cov}(X,Y)}{\sigma_X \sigma_Y}$, where $-1 \le \rho \le 1$. $\rho$ measures linear relationship strength.
- **Normal Distribution:** The $68\text{-}95\text{-}99.7$ rule states $\approx 68\%$ of data falls within $\mu \pm 1\sigma$, $95\%$ within $\mu \pm 2\sigma$, and $99.7\%$ within $\mu \pm 3\sigma$.
- **Bayes' Theorem (Diagnostics):** $P(\text{Disease} \mid \text{Positive}) = \frac{P(\text{Pos} \mid \text{Dis})P(\text{Dis})}{P(\text{Pos})}$.
- **Binomial Distribution:** $n$ trials, probability $p$. Mean $= np$, Variance $= np(1-p)$.

:::

::: interview
In analyst and quant rounds, interviewers care less about your ability to memorize the PDF of a normal distribution and more about your **intuition**. They will ask you to estimate values on the fly, explain why a metric is misleading, or quickly compute a Bayes base-rate problem out loud. Expect them to probe whether you understand *what* the math means.

:::

## 1. Descriptive stats

**Q1.** A dataset of $10$ numbers has a mean of $40$. If the number $62$ is added to the dataset, what is the new mean?

(a) $40.5$ (b) $42$ (c) $44$ (d) $51$

**Solution:** The original sum is $10 \times 40 = 400$. The new sum is $400 + 62 = 462$. The new number of observations is $11$. The new mean is $\frac{462}{11} = 42$.

**Answer:** $42$ (b)

**Q2.** The average salary of $20$ men in a company is $60000$ dollars, and the average salary of $30$ women is $50000$ dollars. What is the average salary of all $50$ employees?

(a) $54000$ dollars (b) $55000$ dollars (c) $56000$ dollars (d) $58000$ dollars

**Solution:** Use a weighted average. The total salary for men is $20 \times 60000 = 1200000$. For women, $30 \times 50000 = 1500000$. Total salary is $2700000$. The overall mean is $\frac{2700000}{50} = 54000$.

**Answer:** $54000$ dollars (a)

::: keypoint
For weighted averages, you can also use deviations. The baseline is $50000$. The $20$ men make $10000$ more. The total "excess" is $20 \times 10000 = 200000$. Spread this across all $50$ employees: $\frac{200000}{50} = 4000$. Thus, $50000 + 4000 = 54000$.

:::

**Q3.** A class's test scores have a mean of $60$ and a standard deviation of $8$. The teacher decides to curve the grades by multiplying every score by $1.2$ and then adding $5$ bonus points. What are the new mean and standard deviation?

(a) Mean $77$, SD $8$ (b) Mean $77$, SD $9.6$ (c) Mean $77$, SD $14.6$ (d) Mean $72$, SD $9.6$

**Solution:** For a transformation $Y = aX + b$, the new mean is $aE[X] + b$ and the new SD is $|a|\sigma_X$.
New mean: $1.2(60) + 5 = 72 + 5 = 77$.
New SD: $1.2(8) = 9.6$. (The addition of $5$ does not affect the spread).

**Answer:** Mean $77$, SD $9.6$ (b)

**Q4.** An analyst notices that for a certain highly skewed metric, the median is $15$ while the mean is $45$. Which of the following is most likely true about the distribution?

(a) It is symmetric (b) It is negatively skewed (left-tailed) (c) It is positively skewed (right-tailed) (d) The variance is zero

**Solution:** When the mean is significantly greater than the median, it implies there are large outlier values pulling the average to the right. This is the definition of a right-skewed (positively skewed) distribution.

**Answer:** It is positively skewed (right-tailed) (c)

## 2. Variance, SD & combining data

**Q5.** For a random variable $X$, you are given that $E[X] = 4$ and $E[X^2] = 25$. What is the standard deviation of $X$?

(a) $3$ (b) $9$ (c) $16$ (d) $21$

**Solution:** Use the formula $\text{Var}(X) = E[X^2] - (E[X])^2$.
$\text{Var}(X) = 25 - (4)^2 = 25 - 16 = 9$.
The standard deviation is $\sigma = \sqrt{9} = 3$.

**Answer:** $3$ (a)

::: trap
Do not confuse variance and standard deviation. Variance is in squared units (e.g., dollars squared). Standard deviation is in the original units (dollars) and is what we typically interpret. Always remember to take the square root of variance to get SD.

:::

**Q6.** Group A has $10$ observations with mean $5$ and variance $0$. Group B has $10$ observations with mean $15$ and variance $0$. What is the variance of the combined group of $20$ observations?

(a) $0$ (b) $5$ (c) $25$ (d) $50$

**Solution:** Since the variances are $0$, Group A is exactly ten $5$s, and Group B is exactly ten $15$s.
The combined mean is $\frac{10(5) + 10(15)}{20} = 10$.
Now find the variance using $E[X^2] - (E[X])^2$.
$E[X^2]$ for the combined group is $\frac{10(5^2) + 10(15^2)}{20} = \frac{250 + 2250}{20} = \frac{2500}{20} = 125$.
Combined variance $= 125 - (10)^2 = 125 - 100 = 25$.

**Answer:** $25$ (c)

**Q7.** An observation $x = 85$ is drawn from a normal distribution with mean $\mu = 70$ and standard deviation $\sigma = 5$. What is the z-score of this observation?

(a) $1.5$ (b) $2.0$ (c) $2.5$ (d) $3.0$

**Solution:** The z-score standardizes the value: $z = \frac{x - \mu}{\sigma}$.
$z = \frac{85 - 70}{5} = \frac{15}{5} = 3.0$.

**Answer:** $3.0$ (d)

## 3. Distributions

**Q8.** A biased coin has a $0.6$ probability of landing heads. If the coin is flipped $5$ times, what is the exact probability of getting exactly $3$ heads?

(a) $0.2304$ (b) $0.3456$ (c) $0.4320$ (d) $0.6000$

**Solution:** Use the binomial probability formula: $P(X=k) = \binom{n}{k} p^k (1-p)^{n-k}$.
$P(X=3) = \binom{5}{3} (0.6)^3 (0.4)^2 = 10 \times 0.216 \times 0.16 = 10 \times 0.03456 = 0.3456$.

**Answer:** $0.3456$ (b)

**Q9.** An ad campaign has a $2\%$ click-through rate. If $400$ users see the ad, what are the expected value and the variance of the number of clicks?

(a) Mean $8$, Variance $8$ (b) Mean $8$, Variance $7.84$ (c) Mean $8$, Variance $7.68$ (d) Mean $4$, Variance $3.92$

**Solution:** This is a binomial distribution with $n = 400$ and $p = 0.02$.
Mean $= np = 400 \times 0.02 = 8$.
Variance $= np(1-p) = 8 \times 0.98 = 7.84$.

**Answer:** Mean $8$, Variance $7.84$ (b)

**Q10.** A web server receives an average of $\lambda = 3$ requests per minute. Assuming a Poisson distribution, what is the probability of receiving exactly $0$ requests in a given minute?

(a) $0$ (b) $e^{-3}$ (c) $3e^{-3}$ (d) $1 - e^{-3}$

**Solution:** The Poisson probability mass function is $P(X=k) = \frac{\lambda^k e^{-\lambda}}{k!}$.
For $k=0$, $P(X=0) = \frac{3^0 e^{-3}}{0!} = e^{-3}$.

**Answer:** $e^{-3}$ (b)

**Q11.** The heights of a population are normally distributed with a mean of $170\text{ cm}$ and a standard deviation of $10\text{ cm}$. Approximately what percentage of the population has a height between $160\text{ cm}$ and $190\text{ cm}$?

(a) $68\%$ (b) $81.5\%$ (c) $95\%$ (d) $97.5\%$

**Solution:** Use the $68\text{-}95\text{-}99.7$ empirical rule.
$160\text{ cm}$ is $\mu - 1\sigma$. $190\text{ cm}$ is $\mu + 2\sigma$.
The area between $\mu - 1\sigma$ and $\mu$ is $\frac{68\%}{2} = 34\%$.
The area between $\mu$ and $\mu + 2\sigma$ is $\frac{95\%}{2} = 47.5\%$.
Total percentage $= 34\% + 47.5\% = 81.5\%$.

**Answer:** $81.5\%$ (b)

**Q12.** In a normal distribution, what percentage of the data lies strictly above a z-score of $2$?

(a) $2.5\%$ (b) $5\%$ (c) $16\%$ (d) $97.5\%$

**Solution:** The empirical rule states $95\%$ of the data lies between $z = -2$ and $z = 2$.
The remaining $5\%$ is split equally between the two tails.
Therefore, the percentage above $z = 2$ is $\frac{5\%}{2} = 2.5\%$.

**Answer:** $2.5\%$ (a)

## 4. Correlation & regression intuition

**Q13.** Which of the following correlation coefficients ($\rho$) indicates the strongest linear relationship between two variables?

(a) $0.75$ (b) $0.10$ (c) $-0.85$ (d) $0.00$

**Solution:** The strength of a linear relationship is determined by the absolute value of the correlation coefficient, $|\rho|$.
$|-0.85| = 0.85$, which is larger than $|0.75| = 0.75$. The negative sign merely indicates an inverse relationship, not a weaker one.

**Answer:** $-0.85$ (c)

**Q14.** A data scientist notes a strong positive correlation between ice cream sales and shark attacks. What is the most statistically sound conclusion?

(a) Eating ice cream attracts sharks. (b) Fear of sharks drives people to eat ice cream. (c) A lurking confounding variable, like summer weather, causes both to increase. (d) Ice cream sales linearly predict shark biology.

**Solution:** Correlation does not imply causation. Two highly correlated variables often share a common cause (a confounding variable). In this classic example, warmer temperatures and summer holidays cause both ice cream consumption and beach attendance (leading to shark attacks) to rise.

**Answer:** A lurking confounding variable, like summer weather, causes both to increase. (c)

**Q15.** A manager observes that employees who score the absolute lowest on their first performance review tend to show significant improvement on their second review, even without intervention. What statistical phenomenon best explains this?

(a) The law of large numbers (b) Survivorship bias (c) Regression to the mean (d) Central limit theorem

**Solution:** Regression to the mean dictates that extreme measurements on a first trial are likely to be closer to the average on a second trial, purely due to random variance (luck) balancing out. The worst performers were likely unluckier than average the first time.

**Answer:** Regression to the mean (c)

## 5. Bayesian / conditional reasoning

**Q16.** A rare disease affects $1\%$ of the population. A diagnostic test for the disease is $90\%$ sensitive (true positive rate) and has a $10\%$ false positive rate. If a patient tests positive, what is the probability they actually have the disease?

(a) $9\%$ (b) $8.3\%$ (c) $50\%$ (d) $90\%$

**Solution:** This is the classic Bayes' theorem base-rate problem.
Let $D$ be having the disease, $P(D) = 0.01$. $P(\neg D) = 0.99$.
Let $+$ be a positive test. $P(+ \mid D) = 0.90$. $P(+ \mid \neg D) = 0.10$.
We want $P(D \mid +) = \frac{P(+ \mid D)P(D)}{P(+ \mid D)P(D) + P(+ \mid \neg D)P(\neg D)}$.
$P(D \mid +) = \frac{0.90 \times 0.01}{(0.90 \times 0.01) + (0.10 \times 0.99)} = \frac{0.009}{0.009 + 0.099} = \frac{0.009}{0.108} = \frac{9}{108} = \frac{1}{12} \approx 8.3\%$.

**Answer:** $8.3\%$ (b)

::: trap
**Base-rate neglect** is the most common pitfall in probability interviews. Even with a $90\%$ accurate test, a positive result only means an $8.3\%$ chance of having the disease. Why? Because the disease is so rare ($1\%$) that the sheer volume of false positives from the healthy $99\%$ swamps the true positives.

:::

**Q17.** In a spam filter, $20\%$ of all emails are spam. The word "viagra" appears in $50\%$ of spam emails and $1\%$ of non-spam emails. Given that an email contains the word "viagra", what is the probability it is spam?

(a) $50\%$ (b) $86.5\%$ (c) $92.6\%$ (d) $99\%$

**Solution:** Use Bayes' theorem.
$P(\text{Spam}) = 0.20$, $P(\text{Not Spam}) = 0.80$.
$P(V \mid \text{Spam}) = 0.50$, $P(V \mid \text{Not Spam}) = 0.01$.
$P(\text{Spam} \mid V) = \frac{0.50 \times 0.20}{(0.50 \times 0.20) + (0.01 \times 0.80)} = \frac{0.10}{0.10 + 0.008} = \frac{0.10}{0.108} = \frac{100}{108} = \frac{25}{27} \approx 92.6\%$.

**Answer:** $92.6\%$ (c)

## 6. Sampling & estimation intuition

**Q18.** A population has a mean $\mu = 100$ and a standard deviation $\sigma = 20$. If you draw a random sample of size $n = 25$, what is the standard error of the sample mean?

(a) $0.8$ (b) $4$ (c) $5$ (d) $20$

**Solution:** The standard error (SE) of the sample mean is the standard deviation of the sampling distribution, given by $\text{SE} = \frac{\sigma}{\sqrt{n}}$.
$\text{SE} = \frac{20}{\sqrt{25}} = \frac{20}{5} = 4$.

**Answer:** $4$ (b)

**Q19.** An analyst rolls a fair six-sided die $10$ times and gets an average of $4.5$. They then roll it $10000$ times and get an average of $3.51$. Which statistical principle explains why the second average is much closer to the theoretical expected value of $3.5$?

(a) Central Limit Theorem (b) Law of Large Numbers (c) Regression to the mean (d) Bayes' Theorem

**Solution:** The Law of Large Numbers (LLN) states that as the sample size $n$ increases, the sample mean converges to the true population expected value. (The Central Limit Theorem describes the *shape* of the distribution of the sample mean, while LLN describes its *location*).

**Answer:** Law of Large Numbers (b)

**Q20.** A $95\%$ confidence interval for the average wait time on a website is calculated as $[1.2\text{ s}, 2.8\text{ s}]$. What is the strictly correct statistical interpretation of this interval?

(a) There is a $95\%$ probability that the true average wait time falls between $1.2\text{ s}$ and $2.8\text{ s}$.
(b) $95\%$ of all users experience a wait time between $1.2\text{ s}$ and $2.8\text{ s}$.
(c) If we repeated this sampling process infinitely many times, $95\%$ of the calculated confidence intervals would contain the true population mean.
(d) The sample mean has a $95\%$ chance of being correct.

**Solution:** In frequentist statistics, the population mean is a fixed, non-random value—it is either in the interval or it isn't, so saying "there is a $95\%$ probability" (option a) is technically incorrect. The $95\%$ refers to the long-run success rate of the *procedure* used to generate the interval.

**Answer:** If we repeated this sampling process infinitely many times... (c)

## Sources

- InterviewQuery — https://www.interviewquery.com/ (Statistics and A/B Testing questions)
- QuantQuestions — https://www.quantquestions.com/ (Probability, expected value, and Bayes base-rate puzzles)
- QuantGuide — https://www.quantguide.io/ (Standard normal distributions and variance rules)
- TraderMath — https://www.tradermath.org/ (Mental math and descriptive stats properties)
