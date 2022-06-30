/*This is a program that reads the .csv file and saves the values into a struct. After that it runs a Quicksort and an Insertion Sort Algorithm comparing the runtimes as well*/
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

int FileCounter(FILE* fp); //A function to count how many lines does the file contains
void PrintArray(OCEAN* array, int size); //A function used to print the Struct
void InsertionSort(OCEAN* arr, int n); //InsertionSort Function
void Quicksort(OCEAN* arr, int first, int last); //QuickSort Function

int main(){
    FILE *fp;
    fp = fopen("ocean.csv","r+");
    if (fp == NULL) {exit(1);} //If the file is empty exit the program

    int count = FileCounter(fp);
    printf("Count is: %d \n", count);
    fp = fopen("ocean.csv","r+");

    OCEAN OceanArray[count]; //Initialization of the Struct OceanArray which is our main struct
    int i = 0;
    int month, day, year;
    month = day = year = 0;
    float temp, phos, silic, nitrite, nitrate, sal, oxyg;
    temp = phos = silic = nitrite = nitrate = sal = oxyg = 0.0;
    char c;
    for (c = fgetc(fp); c != '\n' && c != EOF; c = fgetc(fp)){}; 

    while (c!=EOF)
    { //Passing the data from the file to the OceanArray Struct. With this method we can get the Date in three different variables.
        fscanf(fp, "%d/%d/%d, %f, %f, %f, %f, %f, %f, %f", &month, &day, &year, &temp, &phos, &silic, &nitrite, &nitrate, &sal, &oxyg);
        OceanArray[i].month = month;
        OceanArray[i].day = day;
        OceanArray[i].year = year;
        OceanArray[i].temp = temp;
        OceanArray[i].phos = phos;
        OceanArray[i].silic = silic;
        OceanArray[i].nitrite = nitrite;
        OceanArray[i].nitrate = nitrate;
        OceanArray[i].sal = sal;
        OceanArray[i].oxyg = oxyg;
        c = getc(fp);
        if (c == '\n') {i++;}
    }
    //PrintArray(OceanArray,count);
    clock_t t; //Initializing a variable in order to count the clocks between the completions of the algorithms
    t = clock();
    InsertionSort(OceanArray, count); //Insertion Sort algorithm
    t = clock() - t;
    double total = ((double)t) / CLOCKS_PER_SEC;
    printf("\n");
    printf("After Insertion Sort...\n\n");
    printf("Time Elapsed: %lf \n\n", total);
    clock_t cl;
    cl = clock();
    Quicksort(OceanArray, 0, count-1); //QuickSort algorithm
    cl = clock() - cl;
    total = ((double)cl) / CLOCKS_PER_SEC;
    printf("\n");
    printf("After Quick Sort...\n\n");
    printf("Time Elapsed: %lf \n\n", total);
    //PrintArray(OceanArray,count);
}

int FileCounter (FILE* fp)
{
    int counter = 0;
    char c;
    for (c = fgetc(fp); c != '\n' && c != EOF; c = fgetc(fp)){};
    for (c = fgetc(fp); c != EOF; c = fgetc(fp))
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
    for(i = 0; i < size; i++)
    {
        printf("%d/%d/%d, %.2f\n", array[i].month, array[i].day, array[i].year, array[i].temp);
    }
    printf("\n");
    return;
}

void InsertionSort(OCEAN* arr, int n)
{
    int i, j, keym, keyd, keyy;
    float keyt;
    for (i = 1; i < n; i++) 
    {
        keyt = arr[i].temp;
        keym = arr[i].month;
        keyd = arr[i].day;
        keyy = arr[i].year;
        j = i - 1;
 
        while (j >= 0 && arr[j].temp > keyt) 
        {
            arr[j + 1].temp = arr[j].temp;
            arr[j + 1].month = arr[j].month;
            arr[j + 1].day = arr[j].day;
            arr[j + 1].year = arr[j].year;
            j = j - 1;
        }
        arr[j + 1].temp = keyt;
        arr[j + 1].month = keym;
        arr[j + 1].day = keyd;
        arr[j + 1].year = keyy;
    }
}

void Quicksort(OCEAN* arra, int first, int last)
{
    int i, j, pivot, tempm, tempd, tempy;
    float temp;
    if(first < last)
    {
        pivot = first;
        i = first;
        j = last;
        while(i < j)
        {
            while(arra[i].temp <= arra[pivot].temp && i < last) {i++;}
            while(arra[j].temp > arra[pivot].temp) {j--;}
            if(i < j)
            {
                temp = arra[i].temp;
                tempm = arra[i].month;
                tempd = arra[i].day;
                tempy = arra[i].year;
                arra[i].temp = arra[j].temp;
                arra[i].month = arra[j].month;
                arra[i].day = arra[j].day;
                arra[i].year = arra[j].year;
                arra[j].temp = temp;
                arra[j].month = tempm;
                arra[j].day = tempd;
                arra[j].year = tempy;
            }
        }
            temp = arra[pivot].temp;
            tempm = arra[pivot].month;
            tempd = arra[pivot].day;
            tempy = arra[pivot].year;
            arra[pivot].temp = arra[j].temp;
            arra[pivot].month = arra[j].month;
            arra[pivot].day = arra[j].day;
            arra[pivot].year = arra[j].year;
            arra[j].temp = temp;
            arra[j].month = tempm;
            arra[j].day = tempd;
            arra[j].year = tempy;
            Quicksort(arra, first, j-1);
            Quicksort(arra, j+1, last);
    }
}