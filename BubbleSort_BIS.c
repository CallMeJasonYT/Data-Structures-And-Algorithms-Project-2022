/*This is a program that reads the .csv file and saves the values into a struct. After that it runs a Bubble Sort Algorithm, a BIS Algorithm*/
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

float LinearSearch(Ocean* arr, int left, int right, long int date); //Linear Search Algorithm
float BIS(Ocean* OceanArray, int left, int right, long int date); //Binary Interpolation Search Algorithm
void BubbleSort(Ocean* arr, int size); //BubbleSort Algorithm
void SwapLi(long int* x, long int* y); //A function used to swap two long int variables
void Swapf(float* x, float* y); //A function used to swap two float variables
void RemoveChar(char* str, char c); //A function used to remove the '/' characters from the date
void DateSwap(char* str); //A function used to swap the date number in order to be able to Sort the dates from the earliest to the latest
void PrintArray(Ocean* array, int size); //A function used to Print the Ocean Struct
void ReadFile(Ocean* OceanArray); //A function used to read the File and Pass the data to the Ocean Struct

int main()
{
    FILE* fp = fopen("ocean.csv", "r");
    int rows = -1;
    if (!fp){printf("Can't open file\n");} //If the file is empty exit the program
    else
    {
        char buffer[1024];
        int r = 0;
        while (fgets(buffer, 1024, fp)){
            rows++;
            if (rows == 1){continue;}
            char* value = strtok(buffer, ", ");
            while (value) 
            {value = strtok(NULL, ", ");}
        }
    }
    fclose(fp);
    printf("Count is: %d \n", rows); //Printing the Rows Number of the File
    Ocean OceanArray[rows]; //Initialization of the Struct OceanArray which is our main struct
    ReadFile(OceanArray); //Passing the data into the OceanArray
    //PrintArray(OceanArray, rows);
    BubbleSort(OceanArray, rows); //BubbleSort Algorithm
    //PrintArray(OceanArray, rows);
    long int date;
    printf("Please input the desired date in YYYYMMDD format:\n");
    scanf("%ld",&date);
    clock_t t; //Initializing a variable in order to count the clocks between the completions of the algorithms
    t = clock();
    float btemp = BIS(OceanArray, 0, rows-1, date); //Printing the Temperature on the Desired date using Binary Search
    t = clock() - t;
    double total = ((double)t)/CLOCKS_PER_SEC;
    printf("\n");
    printf("The temperature of %ld is %.2f \n\n", date, btemp);
    printf("After BIS...\nTime Elapsed: %lf \n\n", (total));
}

float BIS(Ocean* arr, int left, int right, long int date)
{
    int size = right - left;
    int next = (int) size * (date - arr[left].date) / (arr[right].date - arr[left].date) + 1;
    while(date != arr[next].date)
    {
        int i = 0;
        size = right - left;
        if(size <= 3){return LinearSearch(arr, left, right, date);} //We are using Linear Search when the field of search is small enough
        if(date >= arr[next].date)
        {
            while(date > arr[next + i * ((int) sqrt(size)) - 1].date){i++;}
            right = next + (int) (i * sqrt(size));
            left = next + (int) ((i - 1) * sqrt(size));
        }
        else if(date < arr[next].date)
        {
            while(date < arr[next - i * ((int)sqrt(size)) + 1].date){i++;}
            right = next - (int)((i - 1) * sqrt(size));
            left = next - (int)(i * sqrt(size));
        }
        next = (int) (left + ((right - left + 1) * (date - arr[left].date) / (arr[right].date - arr[left].date))) - 1;
    }
    if(date == arr[next].date){return arr[next].temp;}
    else{return -1;}
}

float LinearSearch(Ocean* arr, int left, int right, long int date)
{
	int i = left, found = 0;
	while (!found && i < right){
		if (arr[i].date == date){
		return arr[i].temp;
		}
		++i;
	}
	return -1;
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
        int r = -1;
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
    for(i = 0; i < size; i++)
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
    for(i = 0; i < len; i++)
    {
        if(s[i] == c)
        {
            for(j = i; j < len; j++){s[j] = s[j + 1];}
            len--;
            i--;
        }
    }
}

void DateSwap(char* str)
{
    char temp;
    int n;

    n = strlen(str);
    for (int i = 0; i < 4; i++){
        temp = str[i];
        str[i] = str[n - (4 - i)];
        str[n - (4 - i)] = temp;
    }
}