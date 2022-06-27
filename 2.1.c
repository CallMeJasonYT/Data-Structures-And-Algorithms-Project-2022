#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

struct Node{
    int date;
    float temp;
    int height;
    struct Node* left;
    struct Node* right;
};

void RemoveChar(char* s, char c);
void DateSwap(char* str);
int Height(struct Node* node);
int Balancing(struct Node* node);
struct Node* Node_Creaction(int date, float temp);
struct Node* Insertion(struct Node* node, int date, float temp);
struct Node* Left_Rotation(struct Node* node);
struct Node* Right_Rotation(struct Node* node);
void InorderTraversal(struct Node* node);
float Search(struct Node* node,int date);
float Temp_Modification(struct Node* node, int date);
struct Node* Deletion(struct Node* node, int date);
int max(int a, int b);
struct Node* minValueNode(struct Node* node);

int main()
{
    struct Node* root = (struct Node*)malloc(sizeof(struct Node));
    root = NULL;
    int date;
    int choice;
    int rows = 0;

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
                    root = Insertion(root, date, temp);
                }
                value = strtok(NULL, ", ");
                column++;
            }
        }
        fclose(fp);
    }
    printf("There are %d lines of data in the file.\n\n", rows-1);

    while(1){
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
            printf("The Temperature on %ld is : %.2f\n\n", user_date, Search(root, user_date));
            break;
        case 3:
            printf("Give date in format: YYYYMMDD \n");
            scanf("%ld", &user_date);
            printf("The Temperature of %ld is now: %.2f\n\n", user_date, Temp_Modification(root, user_date));
            break;
        case 4:
            printf("Give date in format: YYYYMMDD \n");
            scanf("%ld", &user_date);
            root = Deletion(root, user_date);
            printf("The entry on the date %ld has been deleted\n\n", user_date);
            break;
        case 5:
            exit(0);	
        }
    }
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
    for (int i=0; i<4; i++){
        temp = str[i];
        str[i] = str[n-(4-i)];
        str[n-(4-i)] = temp;
    }
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
    if(node==NULL){return 0;}
    return node->height;
}

int Balancing(struct Node* node)
{
    if(node==NULL){return 0;}
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

struct Node* Insertion(struct Node* node, int date, float temp)
{
    if(node == NULL){return Node_Creaction(date, temp);}
    if(date < node->date){node->left = Insertion(node->left, date, temp);}
    else if(date > node->date){node->right = Insertion(node->right, date, temp);}
    else{return node;}

    node->height = Height(node);
    int balance = Balancing(node);

    if (balance > 1 && date < node->left->date){return Right_Rotation(node);}
    if (balance <-1  && date > node->right->date){return Left_Rotation(node);}
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

float Search(struct Node* node,int date)
{
    struct Node* search = node;
    while(search->date != date)
    {
        if(search!=NULL){
            if(date>search->date){search=search->right;}
            else{search=search->left;}
            if(search==NULL){return -1;}
        }
    }
    return search->temp;
}

float Temp_Modification(struct Node* node, int date)
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

struct Node* Deletion(struct Node* node, int date)
{
    if (node == NULL){return node;}

    if (date < node->date){node->left = Deletion(node->left, date);}
    else if(date > node->date){node->right = Deletion(node->right, date);}
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
            node->right = Deletion(node->right, delete->date);
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

void InorderTraversal(struct Node* node)
{
    if (node == NULL){return;}
    InorderTraversal(node->left);
    printf("%d\t-\t%.2f\n", node->date, node->temp);
    InorderTraversal(node->right);
}