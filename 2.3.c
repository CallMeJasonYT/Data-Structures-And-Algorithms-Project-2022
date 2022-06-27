#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define SIZE 1405

struct Node
{
    int date;
    int key;
    float temp;
    struct Node* next;
};

float Search(struct Node** table,int date,int key);
void Deletion(struct Node** table ,int date,int key);
float Temp_Modification(struct Node** table, int date, int key);
void DateSwap(char* str);
void RemoveChar(char* s, char c);
int Ascii_Sum(char* s, int len);
void Insertion(struct Node** table, int date , int key, float temp);

int m = 15;

int HashFunction(int key){return (key % m);}

int main()
{
    int i, key, rows, choice, date;
    struct Node* Hash_Table[SIZE];

    for(i=0; i<SIZE; i++){Hash_Table[i]=NULL;}

    FILE* fp = fopen("ocean.csv", "r");
    if (!fp){printf("Can't open file\n");}
    else
    {
        char buffer[1024];
        rows = 0;
        int column = 0;
        int r=-1;
        while (fgets(buffer,1024, fp))
        {
            column = 0;
            rows++;
            r++;
            if (rows == 1)
            {
                r--;
                continue;
            }
                
            char* value = strtok(buffer, ", ");
            while(value) 
            {
                if (column == 0)
                {
                    key = Ascii_Sum(value, strlen(value));
                    RemoveChar(value, '/');
                    DateSwap(value);
                    date = atol(value);
                }
                if (column == 1)
                {
                    float temp = atof(value);
                    Insertion(Hash_Table, date, key, temp);
                }
                value = strtok(NULL, ", ");
                column++;
            }
        }
        fclose(fp);
    }

    while(1)
    {
        char user_date[9];
        int format_date = 0;
        printf("Please Select One of the Following Options:\n");
        printf("1) Searching\n2) Modification\n3) Deletion\n4) Exit\n");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                printf("Give date in format: MM/DD/YYYY\n");
                scanf("%s", &user_date);
                key = Ascii_Sum(user_date, strlen(user_date));
                RemoveChar(user_date, '/');
                DateSwap(user_date);
                format_date = atol(user_date);
                printf("The Temperature on %ld is : %.2f\n\n", format_date, Search(Hash_Table, format_date, key));
                printf("\n");
                break;
            case 2:
                printf("Give date in format: MM/DD/YYYY\n");
                scanf("%s", &user_date);
                key = Ascii_Sum(user_date, strlen(user_date));
                RemoveChar(user_date, '/');
                DateSwap(user_date);
                format_date = atol(user_date);
                printf("The Temperature of %ld is now: %.2f\n\n", format_date, Temp_Modification(Hash_Table, format_date, key));
                break;
            case 3:
                printf("Give date in format: MM/DD/YYYY\n");
                scanf("%s", &user_date);
                key = Ascii_Sum(user_date, strlen(user_date));
                RemoveChar(user_date, '/');
                DateSwap(user_date);
                format_date = atol(user_date);
                Deletion(Hash_Table, format_date, key);
                printf("The entry on the date %ld has been deleted\n\n", format_date);
                break;
            case 4:
                exit(0);
        }
    }
    return 0;
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

void DateSwap(char* str)
{
    char temp;
    int n;

    n = strlen(str);
    for (int i = 0; i<4; i++){
        temp = str[i];
        str[i] = str[n-(4-i)];
        str[n-(4-i)] = temp;
    }
}

int Ascii_Sum(char* s, int len)
{
    int sum = 0;
    int i;
    for (i = 0; i < len; i++){sum = sum + s[i];}
    return sum;
}

void Insertion(struct Node** table, int date, int key, float temp)
{
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    struct Node* temp_node = (struct Node*)malloc(sizeof(struct Node));

    new_node->date = date;
    new_node->key = key;
    new_node->temp = temp;
    new_node->next = NULL;

    int index = HashFunction(key);

    if(table[index] == NULL){table[index] = new_node;}
    else
    {
        temp_node = table[index];
        while(temp_node->next != NULL){temp_node = temp_node->next;}
        temp_node->next = new_node;
    }
}

float Search(struct Node** table, int date, int key)
{
    int index = HashFunction(key);
    struct Node* cur = (struct Node*)malloc(sizeof(struct Node));
    cur = table[index];

    while(cur != NULL)
    {
        if(cur->date == date){return cur->temp;}
        cur = cur->next;
    }
    return -1;
}

float Temp_Modification(struct Node** table, int date, int key)
{
    int index = HashFunction(key);
    struct Node* cur = (struct Node*)malloc(sizeof(struct Node));
    cur = table[index];

    while(cur != NULL)
    {
        if(cur->date == date)
        {
            printf("Please Input the New Temperature\n");
            scanf("%f", &cur->temp);
            return cur->temp;
        }
        cur = cur->next;
    }
    return -1;
}

void Deletion(struct Node** table, int date, int key)
{
    int index = HashFunction(key);
    struct Node* cur = table[index];
    if(cur != NULL)
    {
        if(cur->date == date){cur = cur->next;}
        else
        {
            while(cur->next != NULL)
            {
                if(cur->next->date == date){cur->next = cur->next->next;}
                cur = cur->next;
            }
        }
    }
}