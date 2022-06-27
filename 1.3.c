#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

typedef struct Ocean
{
    long int date;
    float temp, phos, silic, nitrite, nitrate, sal, oxyg;
}Ocean;

float BinarySearch(Ocean* array, int left, int right, int date);
float InterpolationSearch(Ocean* OceanArray, int low, int high, long int date);
void BubbleSort(Ocean* arr, int size);
void SwapLi(long int* x, long int* y);
void Swapf(float* x, float* y);
void RemoveChar(char* str, char c);
void DateSwap(char* str);
void PrintArray(Ocean* array, int size);
void ReadFile(Ocean* OceanArray);

int main()
{
    FILE* fp = fopen("ocean.csv", "r");
    int rows = -1;
    if (!fp){printf("Can't open file\n");}
    else
    {
        char buffer[1024];
        int r=0;
        while (fgets(buffer,1024, fp)){
            rows++;
            if (rows == 1){continue;}
            char* value = strtok(buffer, ", ");
            while (value) 
            {value = strtok(NULL, ", ");}
        }
    }
    fclose(fp);

    Ocean OceanArray[rows];
    ReadFile(OceanArray);
    //PrintArray(OceanArray, rows);
    BubbleSort(OceanArray, rows);
    //PrintArray(OceanArray, rows);
    long int date;
    printf("Please select a desired date in YYYYMMDD format:\n");
    scanf("%ld",&date);
    printf("The temperature of %ld is %.2f \n\n", date, BinarySearch(OceanArray, 0, rows-1, date));
    printf("Please select a desired date in YYYYMMDD format:\n");
    scanf("%ld",&date);
    printf("The temperature of %ld is %.2f \n", date, InterpolationSearch(OceanArray, 0, rows-1, date));
}

void ReadFile(Ocean* OceanArray)
{
    FILE* fp = fopen("ocean.csv", "r");
    if (!fp){printf("Can't open file\n");}
    else
    {
        char buffer[1024];
        int row = 0;
        int column = 0;
        int r=-1;
        while (fgets(buffer,1024, fp)){
            column = 0;
            row++;
            r++;
            if (row == 1)
            {
                r--;
                continue;
            }
                
            char* value = strtok(buffer, ", ");
            while (value) {
                if (column == 0)
                {
                    RemoveChar(value, '/');
                    DateSwap(value);
                    OceanArray[r].date = atol(value);
                }
                if (column == 1){OceanArray[r].temp = atof(value);}
                if (column == 2){OceanArray[r].phos = atof(value);}
                if (column == 3){OceanArray[r].silic = atof(value);}
                if (column == 4){OceanArray[r].nitrite = atof(value);}
                if (column == 5){OceanArray[r].nitrate = atof(value);}
                if (column == 6){OceanArray[r].sal = atof(value);}
                if (column == 7){OceanArray[r].oxyg = atof(value);}
                value = strtok(NULL, ", ");
                column++;
            }
        }
        fclose(fp);
    }
}

float BinarySearch(Ocean* array, int left, int right, int date)
{
    if (right >= left)
    {
        int mid = left + (right - left) / 2;
        if (array[mid].date == date){return array[mid].temp;}
        if (array[mid].date > date) {return BinarySearch(array, left, mid - 1, date);}
        return BinarySearch(array, mid + 1, right, date);
    }
    return -1;
}

float InterpolationSearch(Ocean* arr, int low, int high, long int date)
{
    int pos;
    if (low <= high && date >= arr[low].date && date <= arr[high].date)
    {
        pos = low + (((double)(high - low) / (arr[high].date - arr[low].date)) * (date - arr[low].date));
        if (arr[pos].date == date){return arr[pos].temp;}
        if (arr[pos].date < date){return InterpolationSearch(arr, pos + 1, high, date);}
        if (arr[pos].date > date){return InterpolationSearch(arr, low, pos - 1, date);}
    }
    return -1;
}

void SwapLi(long int* x, long int* y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void Swapf(float* x, float* y)
{
    float temp = *x;
    *x = *y;
    *y = temp;
}

void BubbleSort(Ocean* arr, int size)
{
    int i, j;
    for (i = 0; i < size - 1; i++)
    {
        for (j = 0; j < size - i - 1; j++)
        {
            if (arr[j].date > arr[j + 1].date)
            {
                SwapLi(&arr[j].date, &arr[j + 1].date);
                Swapf(&arr[j].temp, &arr[j + 1].temp);
            }
        }
    }
}

void PrintArray(Ocean* array, int size)
{
    int i;
    for(i=0;i<size;i++)
    {
        printf("%ld, %.2f\n", array[i].date, array[i].temp);
    }
    printf("\n");
    return;
}

void RemoveChar(char* s, char c)
{
    int i, j;
    int len = strlen(s);
    for(i=0; i<len; i++)
    {
        if(s[i] == c)
        {
            for(j=i; j<len; j++){s[j] = s[j+1];}
            len--;
            i--;
        }
    }
}

void DateSwap(char* str){
    char temp;
    int n;

    n = strlen(str);
    for (int i=0; i<4; i++){
        temp = str[i];
        str[i] = str[n-(4-i)];
        str[n-(4-i)] = temp;
    }
}