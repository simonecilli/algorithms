# Algorithms

## Sorting Algorithms

* Heap Sort

### Heap Sort

* Complexity: O(n lg n)
* Heap structure
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
* Divide-and-conquer paradigm

## References

[] Thomas H Cormen, Charles E Leiserson, Ronald L Rivest, Clifford Stein. Introduction to Algorithms. SBN 10: 0262033844 / ISBN 13: 9780262033848