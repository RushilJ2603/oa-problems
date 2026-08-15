## Anti-Clockwise Spiral Print

A graphics software company is implementing a new image transformation feature that extracts pixels in an anti-clockwise spiral order. You are given a grid of dimensions $R \times C$ representing the pixel values of an image. 

Your task is to write a function that returns an array of the pixel values collected by starting from the top-left corner and traversing the outer boundary in an anti-clockwise direction (down, right, up, left), then moving inwards to the next unvisited boundary, and so on until all pixels are visited.

### Input Format
- The first line contains two integers $R$ and $C$ representing the number of rows and columns.
- The next $R$ lines each contain $C$ integers representing the grid.

### Output Format
- Print the space-separated pixel values in the anti-clockwise spiral order.

### Constraints
- $1 \le R, C \le 500$
- $-10^4 \le \text{grid}[i][j] \le 10^4$

### Example 1
**Input:**
```
4 4
1 2 3 4
5 6 7 8
9 10 11 12
13 14 15 16
```
**Output:**
```
1 5 9 13 14 15 16 12 8 4 3 2 6 10 11 7
```

### Example 2
**Input:**
```
3 6
1 2 3 4 5 6
7 8 9 10 11 12
13 14 15 16 17 18
```
**Output:**
```
1 7 13 14 15 16 17 18 12 6 5 4 3 2 8 9 10 11
```
