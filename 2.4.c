#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 1405

struct Node{
    int date;
    float temp;
    int height;
    int key;
    struct Node* left;
    struct Node* right;
    struct Node* next;
};

void RemoveChar(char* s, char c);
void DateSwap(char* str);
int Ascii_Sum(char* s, int len);
int Height(struct Node* node);
int Balancing(struct Node* node);
struct Node* Node_Creaction(int date, float temp);
struct Node* Insertion_Temp(struct Node* node, int date, float temp);
struct Node* Insertion_Date(struct Node* node, int date, float temp);
void Insertion_Hash(struct Node** table, int date, int key, float temp);
struct Node* Left_Rotation(struct Node* node);
struct Node* Right_Rotation(struct Node* node);
void InorderTraversal(struct Node* node);
float Search_AVL(struct Node* node,int date);
float Search_Hash(struct Node** table, int date, int key);
float Temp_Modification_AVL(struct Node* node, int date);
float Temp_Modification_Hash(struct Node** table, int date, int key);
struct Node* Deletion_AVL(struct Node* node, int date);
void Deletion_Hash(struct Node** table, int date, int key);
void Max_Temp(struct Node* node);
void Min_Temp(struct Node* node);
int max(int a, int b);
struct Node* minValueNode(struct Node* node);

int m = 15;
int HashFunction(int key){return (key % m);}

int main()
{
    struct Node* root = (struct Node*)malloc(sizeof(struct Node));
    root = NULL;
    int date, choice, rows = 0;
    char buffer[1024];
    int column = 0;
    int r=-1;
    FILE* fp = fopen("ocean.csv", "r");
    if (!fp){printf("Can't open file\n");}
    else
    {
        while(1)
        {
            printf("Please Select One of the Following Options:\n");
            printf("1) AVL Tree\n2) Hash Table\n3) Exit\n");
            scanf("%d",&choice);
            switch(choice)
            {
                case 1:
                    while(1)
                    {
                        printf("Please Select One of the Following Options:\n");
                        printf("1) Based on the Date\n2) Based on the Temperature\n3) Exit\n");
                        scanf("%d",&choice);
                        switch(choice)
                        {
                            case 1: ;
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
                                    while (value) 
                                    {
                                        if (column == 0)
                                        {
                                            RemoveChar(value, '/');
                                            DateSwap(value);
                                            date = atol(value);
                                        }
                                        if (column == 1)
                                        {
                                            float temp = atof(value);
                                            root = Insertion_Date(root, date, temp);
                                        }
                                        value = strtok(NULL, ", ");
                                        column++;
                                    }
                                }
                                fclose(fp);
                                while(1)
                                {
                                    int user_date = 0;
                                    printf("Please Select One of the Following Options:\n");
                                    printf("1) InOrder Traversal\n2) Searching\n3) Modification\n4) Deletion\n5) Exit\n");
                                    scanf("%d",&choice);
                                    switch(choice){
                                        case 1:
                                            InorderTraversal(root);
                                            printf("\n");
                                            break;
                                        case 2:
                                            printf("Give date in format: YYYYMMDD \n");
                                            scanf("%ld", &user_date);
                                            printf("The Temperature on %ld is : %.2f\n\n", user_date, Search_AVL(root, user_date));
                                            break;
                                        case 3:
                                            printf("Give date in format: YYYYMMDD \n");
                                            scanf("%ld", &user_date);
                                            printf("The Temperature of %ld is now: %.2f\n\n", user_date, Temp_Modification_AVL(root, user_date));
                                            break;
                                        case 4:
                                            printf("Give date in format: YYYYMMDD \n");
                                            scanf("%ld", &user_date);
                                            root = Deletion_AVL(root, user_date);
                                            printf("The entry on the date %ld has been deleted\n\n", user_date);
                                            break;
                                        case 5:
                                            exit(0);	
                                        }
                                }
                                case 2: ;
                                    struct Node* root = (struct Node*)malloc(sizeof(struct Node));
                                    root = NULL;
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
                                        while (value) 
                                        {
                                            if (column == 0)
                                            {
                                                RemoveChar(value, '/');
                                                DateSwap(value);
                                                date = atol(value);
                                            }
                                            if (column == 1)
                                            {
                                                float temp = atof(value);
                                                root = Insertion_Temp(root, date, temp);
                                            }
                                            value = strtok(NULL, ", ");
                                            column++;
                                        }
                                    }
                                    fclose(fp);
                                    while(1)
                                    {
                                        int user_date = 0;
                                        printf("Please Select One of the Following Options:\n");
                                        printf("1) Minimum Temperature Date\n2) Maximum Temperature Date\n3) Exit\n");
                                        scanf("%d",&choice);
                                        switch(choice)
                                        {
                                            case 1:
                                                Min_Temp(root);
                                                break;
                                            case 2:
                                                Max_Temp(root);
                                                break;
                                            case 3:
                                                exit(0);	
                                        }
                                    }
                                case 3:
                                    exit(0);
                            }
                        }
                case 2: ;
                    struct Node* Hash_Table[SIZE];
                    int key;
                    for(int i=0; i<SIZE; i++){Hash_Table[i]=NULL;}
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
                                Insertion_Hash(Hash_Table, date, key, temp);
                            }
                            value = strtok(NULL, ", ");
                            column++;
                        }
                    }
                    fclose(fp);
                    while(1)
                    {
                        char user_date[9];
                        int format_date = 0;
                        printf("Please Select One of the Following Options:\n");
                        printf("1) Searching\n2) Modification\n3) Deletion\n4) Exit\n");
                        scanf("%d", &choice);
                        switch(choice)
                        {
                            case 1:
                                printf("Give date in format: MM/DD/YYYY\n");
                                scanf("%s", &user_date);
                                key = Ascii_Sum(user_date, strlen(user_date));
                                RemoveChar(user_date, '/');
                                DateSwap(user_date);
                                format_date = atol(user_date);
                                printf("The Temperature on %ld is : %.2f\n\n", format_date, Search_Hash(Hash_Table, format_date, key));
                                printf("\n");
                                break;
                            case 2:
                                printf("Give date in format: MM/DD/YYYY\n");
                                scanf("%s", &user_date);
                                key = Ascii_Sum(user_date, strlen(user_date));
                                RemoveChar(user_date, '/');
                                DateSwap(user_date);
                                format_date = atol(user_date);
                                printf("The Temperature of %ld is now: %.2f\n\n", format_date, Temp_Modification_Hash(Hash_Table, format_date, key));
                                break;
                            case 3:
                                printf("Give date in format: MM/DD/YYYY\n");
                                scanf("%s", &user_date);
                                key = Ascii_Sum(user_date, strlen(user_date));
                                RemoveChar(user_date, '/');
                                DateSwap(user_date);
                                format_date = atol(user_date);
                                Deletion_Hash(Hash_Table, format_date, key);
                                printf("The entry on the date %ld has been deleted\n\n", format_date);
                                break;
                            case 4:
                                exit(0);
                        }
                    }
                case 3:
                    exit(0);
            }
        }
    }
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

struct Node* Node_Creaction(int date, float temp)
{
    struct Node* create = (struct Node*)malloc(sizeof(struct Node));
    create->date = date;
    create->temp = temp;
    create->height = 1;
    create->left = NULL;
    create->right = NULL;
    return(create);
}

int Height(struct Node* node)
{
    if(node == NULL){return 0;}
    return node->height;
}

int Balancing(struct Node* node)
{
    if(node == NULL){return 0;}
    return (Height(node->left) - Height(node->right));
}

int max(int a, int b)
{
    return (a > b)? a : b;
}

struct Node* minValueNode(struct Node* node)
{
    struct Node* current = node;

    while (current->left != NULL){current = current->left;}
    return current;
}
 
struct Node *Right_Rotation(struct Node *node)
{
    struct Node *x = node->left;
    struct Node *T2 = x->right;

    x->right = node;
    node->left = T2;

    node->height = Height(node);
    x->height = Height(x);
    return x;
}

struct Node *Left_Rotation(struct Node *node)
{
    struct Node *y = node->right;
    struct Node *T2 = y->left;
 
    y->left = node;
    node->right = T2;

    node->height = Height(node);
    y->height = Height(y);
    return y;
}

struct Node* Insertion_Date(struct Node* node, int date, float temp)
{
    if(node == NULL){return Node_Creaction(date, temp);}
    if(date < node->date){node->left = Insertion_Date(node->left, date, temp);}
    else if(date > node->date){node->right = Insertion_Date(node->right, date, temp);}
    else{return node;}

    node->height = Height(node);
    int balance = Balancing(node);

    if (balance > 1 && date < node->left->date){return Right_Rotation(node);}
    if (balance < -1  && date > node->right->date){return Left_Rotation(node);}
    if (balance > 1 && date > node->left->date)
    {
        node->left = Left_Rotation(node->left);
        return Right_Rotation(node);
    }
    if (balance < -1 && date < node->right->date)
    {
        node->right = Right_Rotation(node->right);
        return Left_Rotation(node);
    }
    return node;
}

struct Node* Insertion_Temp(struct Node* node, int date, float temp)
{
    if(node == NULL){return Node_Creaction(date, temp);}
    if(temp < node->temp){node->left = Insertion_Temp(node->left, date, temp);}
    else if(temp > node->temp){node->right = Insertion_Temp(node->right, date, temp);}
    else{return node;}

    node->height = Height(node);
    int balance = Balancing(node);

    if (balance > 1 && temp < node->left->temp){return Right_Rotation(node);}
    if (balance < -1  && temp > node->right->temp){return Left_Rotation(node);}
    if (balance > 1 && temp > node->left->temp)
    {
        node->left = Left_Rotation(node->left);
        return Right_Rotation(node);
    }
    if (balance < -1 && temp < node->right->temp)
    {
        node->right = Right_Rotation(node->right);
        return Left_Rotation(node);
    }
    return node;
}

void Insertion_Hash(struct Node** table, int date, int key, float temp)
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

float Search_AVL(struct Node* node,int date)
{
    struct Node* search = node;
    while(search->date != date)
    {
        if(search != NULL){
            if(date > search->date){search = search->right;}
            else{search = search->left;}
            if(search == NULL){return -1;}
        }
    }
    return search->temp;
}

float Search_Hash(struct Node** table, int date, int key)
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

float Temp_Modification_AVL(struct Node* node, int date)
{
    float temp;
    struct Node* modif = node;
    while(modif->date != date)
    {
        if(modif != NULL)
        {
            if(date > modif->date){modif = modif->right;}
            else{modif = modif->left;}
            if(modif == NULL){return -1;}
        }
    }
    printf("Please input the new Temperature:\n");
    scanf("%f", &modif->temp);
    return modif->temp;
    
}

float Temp_Modification_Hash(struct Node** table, int date, int key)
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

struct Node* Deletion_AVL(struct Node* node, int date)
{
    if (node == NULL){return node;}

    if (date < node->date){node->left = Deletion_AVL(node->left, date);}
    else if(date > node->date){node->right = Deletion_AVL(node->right, date);}
    else
    {
        if((node->left == NULL) || (node->right == NULL))
        {
            struct Node *delete = node->left ? node->left : node->right;
            if (delete == NULL)
            {
                delete = node;
                node = NULL;
            }
            else
            {
                *node = *delete;
                free(delete);
            }
        }
        else
        {
            struct Node* delete = minValueNode(node->right);
            node->date = delete->date;
            node->right = Deletion_AVL(node->right, delete->date);
        }
    }

    if (node == NULL){return node;}

    node->height = 1 + max(Height(node->left), Height(node->right));
    int balance = Balancing(node);

    if (balance > 1 && Balancing(node->left) >= 0){return Right_Rotation(node);}

    if (balance > 1 && Balancing(node->left) < 0)
    {
        node->left =  Left_Rotation(node->left);
        return Right_Rotation(node);
    }

    if (balance < -1 && Balancing(node->right) <= 0){return Left_Rotation(node);}
    if (balance < -1 && Balancing(node->right) > 0)
    {
        node->right = Right_Rotation(node->right);
        return Left_Rotation(node);
    }
    return node;
}

void Deletion_Hash(struct Node** table, int date, int key)
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

void InorderTraversal(struct Node* node)
{
    if (node == NULL){return;}
    InorderTraversal(node->left);
    printf("%d\t-\t%.2f\n", node->date, node->temp);
    InorderTraversal(node->right);
}

void Max_Temp(struct Node* node)
{
    struct Node* max = node;
    while(max->right != NULL){max = max->right;}
    printf("The Maximum Temperature %.2f occured on %ld.\n\n", max->temp, max->date);
}

void Min_Temp(struct Node* node)
{
    struct Node* min = node;
    while(min->left != NULL){min = min->left;}
    printf("The Minimum Temperature %.2f occured on %ld.\n\n", min->temp, min->date);
}