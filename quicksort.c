#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int arr[], int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}


int partition(int start,int end,int *array){
    int pivot=array[start];
    int i=start+1;
    int j= end;
    while(i<=j){
        if(array[i]<=pivot){
            i++;
        }
        else if(array[j]>=pivot){
            j--;
        }
        else{
            swap(array,i,j);
            i++;
            j--;
        }
    }
    swap(array,start,j);
    return j;
}


void quicksort(int start, int end,int *array) {
    if (start < end) {
        int pi = partition(start, end,array);
        quicksort(start, pi - 1,array);
        quicksort(pi + 1, end,array);
    }
}


void array_print(int *array,int sz){
    for(int i=0;i<sz;i++){
        printf("%d, ",array[i]);
    }
    printf("\n");
}

void array_copy(int *array,int *new_array, int sz){
    for(int i=0;i<sz;i++){
        new_array[i]=array[i];
    }
}

int main(int argc,char *argv[])
{
    if(argc==2){
        clock_t start,end;
        double time_taken=0;
        int i,ans; 
        int size=atoi(argv[1]);
        printf("%d\n",size);
        int *array = (int*)malloc( size* sizeof(int));
        if (array == NULL) {
            printf("Memory allocation failed\n");
            return 1;
        }
        for(i=0;i<size;i++){
            array[i]=rand();
        }
        start = (double)clock();
        quicksort(0,size,array);
        end = (double)clock();
        time_taken+= (((double) (end - start)) / CLOCKS_PER_SEC);
        printf(" time taken  %f",time_taken);
        free(array);
    }
}