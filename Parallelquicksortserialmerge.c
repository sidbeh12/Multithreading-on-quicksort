 /*
 ============================================================================
 Kernel Name : quicksort_parallel.c
 Author      : Sidhartha Behura
 Version     : Parallel openmp parallel with serial merge
 Contact     : sidbeh12@ufl.edu
 Description : Parallel code for Quicksort without using any optimised library.
 
 ============================================================================
 */
#include<omp.h>
//#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include <sys/time.h>
#include<math.h>

double timerval ()
{
	struct timeval st;
	gettimeofday (&st, NULL);
	return st. tv_sec + st. tv_usec * 1e-6;
}

/* Merge sorted lists A and B into list A.  A must have dim >= m+n */
void merge(int A[], int B[], int m, int n) 
{
	int i=0, j=0, k=0,p=0;
	int size = m+n;
	int *C = (int *)malloc(size*sizeof(int));
	while (i < m && j < n) {
            if (A[i] <= B[j]) C[k] = A[i++];
            else C[k] = B[j++];
            k++;
	}
	if (i < m) 
        for (p = i; p < m; p++,k++) C[k] = A[p];
	else for (p = j; p < n; p++,k++) C[k] = B[p];
	for( i=0; i<size; i++ ) A[i] = C[i];
	free(C);
}


void arraymerge(int *a, int size, int *index, int N)
{  int i;
	 for( i=0; i<N-1; i++ )
		{
		merge(a+index[0],a+index[i+1],index[i+1]-index[0],index[i+2]-index[i+1]);
		}
}

void quicksort(int *arr, int left, int right)
{
      int i = left, j = right;
      int tmp;
      int pivot = arr[(left + right) / 2];
 
      /* partition */
      while (i <= j) 
      {
            while (arr[i] < pivot)
                  i++;
            while (arr[j] > pivot)
                  j--;
            if (i <= j)
	    {
                  tmp = arr[i];
                  arr[i] = arr[j];
                  arr[j] = tmp;
                  i++;
                  j--;
            }
      };
 
      /* recursion */
      if (left < j)
            quicksort(arr, left, j);
      if (i < right)
            quicksort(arr, i, right);
}

int main()
{
double start_time, end_time;
FILE *outputfile;

int size,m=0;
int i,*a,j;
int kstart=2;
int kstop=5;
double seconds[kstop];
for(j=kstart;j<=kstop;j++)
{
size=pow(2,j);
a=(int *)malloc(size*sizeof(int));

for(i=0;i<size;i++)
a[i]=rand();

/*printf("Unsorted list:");
for(i=0;i<size;i++)
printf("\n%d\t",a[i]);
*/
omp_set_num_threads(5);
int threads=omp_get_max_threads();

omp_set_num_threads(threads);
int *index = (int *)malloc((threads+1)*sizeof(int));

for(i=0; i<threads; i++) 
index[i]=i*size/threads; 
index[threads]=size;

start_time=timerval();
for(i=0;i<1000;i++)
{
#pragma omp parallel for private(i)
for(i=0;i<threads;i++)
quicksort(a,index[i],index[i+1]-1);


arraymerge(a,size,index,threads);
}

end_time=timerval();
seconds[m++]=(end_time-start_time)/1000;
/*printf("\n***********Sorted**************");
for(i=0;i<size;i++)
printf("\n%d \t",a[i]);
*/
free(a);
}
outputfile=fopen("outputfile.csv","a+");
if(outputfile==NULL)
{
printf("Could not open file \n");
return EXIT_FAILURE;
}
fprintf(outputfile,"N, Timetaken\n");
for(i=0;i<m;i++)
fprintf(outputfile,"%lf,%lf\n",pow(2,(i+kstart)), seconds[i]);
fclose(outputfile);
 //Closing the file
return EXIT_SUCCESS;
//return 0;
}