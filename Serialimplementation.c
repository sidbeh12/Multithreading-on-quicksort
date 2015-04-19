/*
 ============================================================================
 Kernel Name : quicksort_serial.c
 Author      : Sidhartha Behura
 Version     : Serial V1.0
 Contact     : sidbeh12@ufl.edu
 Description : Serial code for Quicksort without using any optimised library.
 ============================================================================
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
void quickSort(double arr[], int left, int right)
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
            quickSort(arr, left, j);
      if (i < right)
            quickSort(arr, i, right);
}
double timerval()
{
struct timeval st;
gettimeofday(&st,NULL);
return st.tv_sec + st.tv_usec*1e-6;
}
int main()
{  
   clock_t begin, end;
   double time_spent;
   double st,et,time;
   int n,i=0,j=0;
   double *value;
   FILE *outputfileserial;
   long int N;
   int kstart=2;
   int kstop=8;
   int m=0;
   double seconds[kstop];


// printf("enter the number of elements");
// scanf("%d",&n);
   for(j = kstart;j <= kstop; j++)
   {
   N = pow(2,j);
   value=(double *)malloc(N* sizeof(double)); 
   if(value== 0)
   {
	printf("Error: out of memory\n");
	return 1;
   }
  
// printf("Enter %d elements to be sorted \n",n);
   for( i = 0 ; i < N;++i) 
   {    value[i]=rand();
   }
   
/* printf("Before sorting the list is: \n");
   for( i = 0 ; i < n; i++ ) 
   {
      printf("%lf \n", value[i]);
   }
*/   
   st=timerval();
   for(i = 0; i<1000; i++)
   quickSort(value,0,N-1);
   et=timerval();   
   seconds[m++]=(et-st)/1000;
 /*  printf("\n Sorted List: \n");
   for( i = 0 ; i < N; i++ )
   {
      printf("%lf \n", value[i]);
   }

printf("\n time from timerval = %f",(et-st)/1000);
*/
//fprintf(output,"Time taken for N = %ld is %lf\n", N, (et-st)/1000);
free(value);
}
// File used to store timing of the Quicksort.
outputfileserial = fopen("outputfileserial.csv","a+");

if(outputfileserial==NULL)
{
printf("Could not open file \n");
return EXIT_FAILURE;
}
fprintf(outputfileserial,"N, Timetaken\n");
for(i=0;i<m;i++)
fprintf(outputfileserial,"%lf,%lf\n",pow(2,(i+kstart)), seconds[i]);
fclose(outputfileserial);
 //Closing the file
return EXIT_SUCCESS;
//fclose(outputfileserial);
return(0); 
}