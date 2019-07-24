# Algorithms

## Sorting Algorithms

* Heap Sort
* Quick Sort

### Heap Sort

* Complexity: O(n lg n)
* Comparison sort
* Use Heap structure
* Operations:
 * PARENT(i)  - return i/2
 * LEFT(i)    - return 2i
 * RIGHT(i)   - return 2i+1
 * HEIGHT h   - lg(n)
 * #element n - 2^h-1
* Properties:
 * max-heap property - A[PARENT(i)] >= A[i]
 * min-heap property - A[PARENT(i)] <= A[i]

### Quick Sort

* Complexity: O(n^2) - Expected O(n lg n) - Efficient in average
* Comparison sort
* Divide-and-conquer paradigm
* Based on partition algorithm to split origina arrays in two based on a pivot value (see also Hoare algorithm)

## References

[] Thomas H Cormen, Charles E Leiserson, Ronald L Rivest, Clifford Stein. Introduction to Algorithms. SBN 10: 0262033844 / ISBN 13: 9780262033848