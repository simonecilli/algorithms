#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()
#define DEBUG 0

void heapsort(int a[],int n);
void quicksort(int a[], int s, int e, int partAlgo);

void exchange(int a[], int i, int j);
void printArray(int[],int);
int verifySort(int[],int);

int main()
{
	clock_t begin, end;
	int a[50000];
	int b[50000];
	int n = 50000;
	srand(time(0));
	for (int i=0;i<10;i++)
	{
		for (int j=0;j<n;j++) a[j]=(rand() % 100) + 1;

		memcpy(b, a, n*sizeof(int));
		begin = clock();
		heapsort(b, n);
		end = clock();
		printf("%d) HEAP SORT         \t", i); //printArray(b,n);
		printf(" (sorted:%d,time:%f)\n", verifySort(b,n), ((double)(end - begin) / CLOCKS_PER_SEC));
		
		memcpy(b, a, n*sizeof(int));
		begin = clock();
		quicksort(b, 0, n-1, 1);
		end = clock();
		printf("%d) QUICK SORT        \t", i); //printArray(b,n);
		printf(" (sorted:%d,time:%f)\n", verifySort(b,n), ((double)(end - begin) / CLOCKS_PER_SEC));
		
		memcpy(b, a, n*sizeof(int));
		begin = clock();
		quicksort(b, 0, n-1, 2);
		end = clock();
		printf("%d) QUICK SORT (HOARE)\t", i); //printArray(b,n);
		printf(" (sorted:%d,time:%f)\n", verifySort(b,n), ((double)(end - begin) / CLOCKS_PER_SEC));
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
// HEAP SORT - O(n lg n) //////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void maxHeapify(int a[], int p, int n)
{
	// p: Parent
	int l = 2*(p+1)-1; // Left children
	int r = 2*(p+1);   // Right children
	int max = (l<n && a[l]>a[p])?   l : p; // Compare parent with left (if left is inside array)
	max = (r<n && a[r]>a[max])? r : max;   // Compare current max with right (is it is inside array)
#if DEBUG
	printf("maxHeapify(%d) - (n:%d,p:%d,l:%d,r:%d,max:%d,FIX:%d) - ",__LINE__,n,p,l,r,max,(max!=p)); printArray(a,n);
#endif
	if (max != p) // If max is not parent, max-heap property is violated. Fix it
	{
		exchange(a, p, max);
		maxHeapify(a,max,n);
	}
}

void heapsort(int a[],int n)
{
	int i;
	// BUILD MAX HEAP
	// Create HEAP structure verifying max-heap property (A[PARENT(i)] >= A[i])
	for(i=n-1; i>=0; i--)
		maxHeapify(a, i, n);
#if DEBUG
	printf("heapsort(%d) - ",__LINE__); printArray(a,n);
#endif
	// SORT MIN MAX
	// Order in place using this rule: 0th element is the largest
	// 1 - Put 0th element on the queue and work on n-1 element array
	// 2 - Adjust heap structure verifying max-heap property
	for(i=n-1; i>=1; i--)
	{
		exchange(a, 0, i);
		maxHeapify(a, 0, i);
	}
#if DEBUG
	printf("heapsort(%d) - ",__LINE__); printArray(a,n);
#endif
}

///////////////////////////////////////////////////////////////////////////////
// QUICK SORT - worst case O(n^2) - expected O(n lg n) ////////////////////////
///////////////////////////////////////////////////////////////////////////////

// Consider last element of array as a pivot to split array in two section a1 and a2
// At the end of partition function:
// Foreach i -> i<pivot => a[i] <= a[pivot]
//           -> i>pivot => a[i] >= a[pivot
int partition(int a[], int s, int e)
{
	// s: Star index
	// e: End index
	int pivot = a[e]; // pivot element
	int i = s - 1;    // last elemennt of a1
	for (int j=s;j<e;j++)
	{
		if (a[j]<=pivot)
		{
			i++;               // Add one element to a1
			exchange(a, i, j); // Move jth element inside a1 (previous ith element is bigger than pivot)
		}
	}
	exchange(a, i+1, e); // Move pivot between a1 and a2
#if DEBUG
	printf("partition(%d) (s:%d,q:%d,e:%d) - ", __LINE__, s, i+1, e); printArray(a,e-s+1);
#endif
	return i+1;          // Return pivot position
}
int hoarePartition(int a[], int s, int e)
{
	int pivot = a[s];
	int i = s-1;
	int j = e+1;
	while(1)
	{
		do { j--; } while(a[j]>pivot);
		do { i++; } while(a[i]<pivot);
		if (i<j)
		{
			exchange(a, i, j);
		}
		else
		{
			exchange(a, s, j);
#if DEBUG
			printf("partition(%d) (s:%d,q:%d,pivot:%d,e:%d) - ", __LINE__,s,j,a[j],e); printArray(a,e-s+1);
#endif
			return j;
		}
	}
}

void quicksort(int a[], int s, int e, int partAlgo)
{
	int q;
#if DEBUG
	printf("quicksort(%d) (s:%d,e:%d) - ", __LINE__, s, e); printArray(a,e-s+1);
#endif
	if (s<e)
	{
		switch(partAlgo)
		{
			case 1:
				q = partition(a, s, e);
				quicksort(a, s, q-1, partAlgo);
				quicksort(a, q+1, e, partAlgo);
				break;
			case 2:
				q = hoarePartition(a, s, e);
				quicksort(a, s, q, partAlgo);
				quicksort(a, q+1, e, partAlgo);
				break;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// UTILITY ////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void exchange(int a[], int i, int j)
{
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}
void printArray(int a[],int n)
{
	if (n>0)
	{
		for (int i=0;i<n;i++) printf("\t%d",a[i]);
		printf("\n");
	}
	else
	{
		printf("\tempty\n");
	}
}
int verifySort(int a[],int n)
{
	int sorted = 1;
	for (int i=0;i<n-1;i++)
		if (a[i]>a[i+1])
			sorted = 0;
	return sorted;
}