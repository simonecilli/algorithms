#include<stdio.h>

#define DEBUG 0

void heapsort(int a[],int n);
void maxHeapify(int a[], int p, int n);
void printArray(int[],int);

int main()
{
	int a[6][10]= {
		{ 1 },
		{ 1, 2 },
		{ 2, 1 },
		{ 3, 2, 1 },
		{ 2, 3, 1 },
		{ 17, 14, 6, 13, 10, 1, 5, 7, 12 }
	};
	int n[6] = { 1, 2, 2, 3, 3, 9 };
	for (int i=0;i<6;i++)
	{
		printf("START \t");printArray(a[i],n[i]);
		heapsort(a[i],n[i]);
		printf("END   \t");printArray(a[i],n[i]);
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
// HEAP SORT - O(n lg n) //////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void heapsort(int a[],int n)
{
	int i, max;
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
		max = a[0];
		a[0] = a[i];
		a[i] = max;
		maxHeapify(a, 0, i);
	}
#if DEBUG
	printf("heapsort(%d) - ",__LINE__); printArray(a,n);
#endif
}

void maxHeapify(int a[], int p, int n)
{
	// p: Parent
	int l = 2*(p+1)-1; // Left children
	int r = 2*(p+1);   // Right children
	int max, t;
	max = (l<n && a[l]>a[p])?   l : p;   // Compare parent with left (if left is inside array)
	max = (r<n && a[r]>a[max])? r : max; // Compare current max with right (is it is inside array)
#if DEBUG
	printf("maxHeapify(%d) - (n:%d,p:%d,l:%d,r:%d,max:%d,FIX:%d) - ",__LINE__,n,p,l,r,max,(max!=p)); printArray(a,n);
#endif
	if (max != p) // If max is not parent, max-heap property is violated. Fix it
	{
		t = a[p];
		a[p] = a[max];
		a[max] = t;
		maxHeapify(a,max,n);
	}
}

///////////////////////////////////////////////////////////////////////////////
// QUICK SORT - worst case O(n^2) - expected O(n lg n) ////////////////////////
///////////////////////////////////////////////////////////////////////////////

void quicksort(int a[],int n)
{
	//
}

///////////////////////////////////////////////////////////////////////////////
// UTILITY ////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void printArray(int a[],int n)
{
	int sorted = 1;
	for (int i=0;i<n;i++)
	{
		printf("\t%d",a[i]);
		if (i<n-1 && a[i]>a[i+1]) sorted = 0;
	}
	printf(" (sort:%d)\n", sorted);
}