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
void Max_Temp(struct Node* node);
void Min_Temp(struct Node* node);
struct Node* minValueNode(struct Node* node);

int main()
{
    struct Node* root = (struct Node*)malloc(sizeof(struct Node));
    root = NULL;
    int date, choice, rows = 0;

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
    printf("1) Minimum Temperature Date\n2) Maximum Temperature Date\n3) Exit\n");
    scanf("%d",&choice);
    switch(choice){
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

struct Node* Insertion(struct Node* node, int date, float temp)
{
    if(node == NULL){return Node_Creaction(date, temp);}
    if(temp < node->temp){node->left = Insertion(node->left, date, temp);}
    else if(temp > node->temp){node->right = Insertion(node->right, date, temp);}
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