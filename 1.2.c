#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

typedef struct Ocean
{
    int month, day, year;
    float temp, phos, silic, nitrite, nitrate, sal, oxyg;
    
}OCEAN;

typedef struct Ocean2
{
    int year,month,day;
    int phos;
}OCEAN2;

int FileCounter(FILE* fp);
int Find_Max(OCEAN2* arr,int size);
void PrintArray(OCEAN* array,int size);
void PrintArray2(OCEAN2* arr, int size);
void CountingSort(OCEAN2* A, OCEAN2* B, int first, int last);
void SwapFloat(float *a, float *b);
void SwapInt(int *a, int *b);
void Heapify(OCEAN* arr, int n, int i);
void HeapSort(OCEAN* arr, int n);

int main(){
    FILE *fp;
    fp = fopen("ocean.csv","r+");
    if (fp == NULL) {exit(1);}

    int count=FileCounter(fp);
    printf("Count is: %d \n",count);
    fp = fopen("ocean.csv","r+");

    OCEAN OceanArray[count];
    OCEAN2 OceanArray2[count];
    OCEAN2 OceanArray3[count];
    int i=0;
    int month, day, year;
    month=day=year=0;
    float temp, phos, silic, nitrite, nitrate, sal, oxyg;
    temp=phos=silic=nitrite=nitrate=sal=oxyg=0.0;
    char c;

    for (c = fgetc(fp); c != '\n' && c != EOF; c=fgetc(fp)){};

    while (c!=EOF) 
    {
        fscanf(fp, "%d/%d/%d, %f, %f, %f, %f, %f, %f, %f", &month, &day, &year, &temp, &phos, &silic, &nitrite, &nitrate, &sal, &oxyg);
        OceanArray[i].month=month;
        OceanArray[i].day=day;
        OceanArray[i].year=year;
        OceanArray[i].temp=temp;
        OceanArray[i].phos=phos;
        OceanArray[i].silic=silic;
        OceanArray[i].nitrite=nitrite;
        OceanArray[i].nitrate=nitrate;
        OceanArray[i].sal=sal;
        OceanArray[i].oxyg=oxyg;

        OceanArray2[i].month=month;
        OceanArray2[i].year=year;
        OceanArray2[i].day=day;
        OceanArray2[i].phos=(int)(round(phos));
        c=getc(fp);
        if (c == '\n') {i++;}
    }
    //PrintArray(OceanArray,count);
    clock_t t;
    t = clock();
    HeapSort(OceanArray,count);
    t = clock() - t;
    double total = ((double)t)/CLOCKS_PER_SEC;
    printf("\n");
    printf("After Heap Sort...\n\n");
    printf("Time Elapsed: %lf \n\n", (total));
    PrintArray(OceanArray,count);
    int max = Find_Max(OceanArray2, count);
    clock_t cl;
    cl = clock();
    CountingSort(OceanArray3, OceanArray2, max, count);
    cl = clock() - cl;
    total = ((double)cl)/CLOCKS_PER_SEC;
    printf("\n");
    printf("After Counting Sort...\n\n");
    printf("Time Elapsed: %lf \n\n", (total));
    PrintArray2(OceanArray3,count-1);
}

int FileCounter (FILE* fp)
{
    int counter = 0;
    char c;
    for (c = fgetc(fp); c != '\n' && c != EOF; c=fgetc(fp)){};
    for (c=fgetc(fp); c!=EOF; c=fgetc(fp))
    {
        if (c == '\n')
        {
            counter++;
        }
    }
    counter++;
    return counter;
}

void PrintArray(OCEAN* array, int size)
{
    int i;
    for(i=0;i<size;i++)
    {
        printf("%d/%d/%d, %.2f\n",array[i].month,array[i].day,array[i].year,array[i].phos);
    }
    printf("\n");
    return;
}

void PrintArray2(OCEAN2* arr, int size)
{
    int i;
    for(i=0;i<size;i++)
    {
        printf("%d/%d/%d, %d\n",arr[i].month,arr[i].day,arr[i].year,arr[i].phos);
    }
    return;
}

void CountingSort(OCEAN2* B, OCEAN2* A, int max, int size){
    int C[max+1];
    int i,j;

    for(i=0;i<=max;i++){C[i]=0;}

    for(j=1;j<size;j++)
    {
        C[A[j].phos]+=1;
    }

    for(i=1;i<=max;i++)
    {
        C[i]+=C[i-1];
    }

    for(j=size-1;j>=0;j--)
    {
        B[C[A[j].phos]-1].phos=A[j].phos;
        B[C[A[j].phos]-1].year=A[j].year;
        B[C[A[j].phos]-1].month=A[j].month;
        B[C[A[j].phos]-1].day=A[j].day;
        C[A[j].phos]--;
    }
}

int Find_Max(OCEAN2* arr, int size)
{
    int i;
    int max;
    max=arr[0].phos;
    for(i=0;i<size;i++)
    {
        if(arr[i].phos>max){max=arr[i].phos;}
    }
    return max;
}

void SwapFloat(float *a, float *b)
{
    float temp = *a;
    *a = *b;
    *b = temp;
}

void SwapInt(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
  
void Heapify(OCEAN* arr, int n, int i) 
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].phos > arr[largest].phos) {largest = left;}

    if (right < n && arr[right].phos > arr[largest].phos) {largest = right;}

    if (largest != i) 
    {
        SwapFloat(&arr[i].phos, &arr[largest].phos);
        SwapInt(&arr[i].month, &arr[largest].month);
        SwapInt(&arr[i].day, &arr[largest].day);
        SwapInt(&arr[i].year, &arr[largest].year);
        Heapify(arr, n, largest);
    }
}

void HeapSort(OCEAN* arr, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--) {Heapify(arr, n, i);}

    for (int i = n - 1; i >= 0; i--) 
    {
        SwapFloat(&arr[0].phos, &arr[i].phos);
        SwapInt(&arr[0].month, &arr[i].month);
        SwapInt(&arr[0].day, &arr[i].day);
        SwapInt(&arr[0].year, &arr[i].year);
        Heapify(arr, i, 0);
    }
}