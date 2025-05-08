
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void swap(int arr[], int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int partition(int start,int end,int array[]){
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

int quick_select(int array[], int k, int length){
    srand(time(NULL));
    int pivot=-1;
    int rand_num;
    int s=0;
    int e=length-1;
    while(pivot!=k){
        rand_num =s + rand() % (e-s+1);
        swap(array,s,rand_num);
        pivot=partition(s,e,array);
        if (pivot<k){
            s=pivot+1;
        }
        else{
            e=pivot-1;
        }
    }
    return array[pivot];
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
        int i,k,ans; 
        int size=atoi(argv[1]);
        printf("%d\n",size);
        int *array = (int*)malloc( size* sizeof(int));
        int *new_array = (int*)malloc( size* sizeof(int));
        if (array == NULL || new_array==NULL) {
            printf("Memory allocation failed\n");
            return 1;
        }
        for(i=0;i<size;i++){
            array[i]=rand();
        }
        for( i=0;i<100;i++){
            k=rand()%size;
            array_copy(array,new_array,size);
            start = (double)clock();
            ans=quick_select(new_array,k,size);

            end =  (double)clock();
            time_taken+= (((double) (end - start)) / CLOCKS_PER_SEC);
        }
        printf("avg time taken  %f",time_taken/100);
        free(array);
        free(new_array);
    }
}