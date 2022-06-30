/*This is a program that reads the .csv file and Inserts the Values into an AVL tree, Date is the key, but it's arranged by the Date. 
After that it runs a selection of Search, Delete and Modification Algorithms.*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

struct Node //An AVL Tree Node
{
    int date;
    float temp;
    int height;
    struct Node* left;
    struct Node* right;
};

void RemoveChar(char* s, char c); //A function used to remove the '/' characters from the date
void DateSwap(char* str); //A function used to swap the date number in order to be able to Sort the dates from the earliest to the latest
int Height(struct Node* node); //A function used to calculate the height of the AVL tree
int Balancing(struct Node* node); //A function used to get Balance factor of a Node
struct Node* Node_Creaction(int date, float temp); //A function used to allocate a new node with the given key and NULL left and right pointers
struct Node* Insertion(struct Node* node, int date, float temp); //The Insertion Function
struct Node* Left_Rotation(struct Node* node); //A function used to left rotate subtree rooted with y
struct Node* Right_Rotation(struct Node* node); //A utility function to right rotate subtree rooted with x
void InorderTraversal(struct Node* node); //A function used to print Inorder traversal of the tree.
float Search(struct Node* node,int date); //The Search Function
float Temp_Modification(struct Node* node, int date); //The Modification of the Temperature Function
struct Node* Deletion(struct Node* node, int date); //The Deletion Function
int max(int a, int b); //A function used to find the max of two intergers
struct Node* minValueNode(struct Node* node); //A function that returns the node with minimum key value found in that tree

int main()
{
    struct Node* root = (struct Node*)malloc(sizeof(struct Node)); //Dynamically Create an AVL tree
    root = NULL;
    int date, choice, rows = 0;

    //Reading the .csv File and Inserting Data while Creating the AVL Tree with the Insertion Function
    FILE* fp = fopen("ocean.csv", "r");
    if (!fp){printf("Can't open file\n");} //If the file is empty exit the program
    else
    {
        char buffer[1024];
        rows = 0;
        int column = 0;
        int r = -1;
        while (fgets(buffer, 1024, fp))
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
                    root = Insertion(root, date, temp); //Calling the Insertion Function in order to Create The AVL tree
                }
                value = strtok(NULL, ", ");
                column++;
            }
        }
        fclose(fp);
    }
    printf("There are %d lines of data in the file.\n\n", rows-1); //Printing the Rows Number of the File

    while(1)
    {
        int user_date = 0;
        printf("Please Select One of the Following Options:\n");
        printf("1) InOrder Traversal\n2) Searching\n3) Modification\n4) Deletion\n5) Exit\n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                InorderTraversal(root); //InOrderTraversal Function Call
                printf("\n");
                break;
            case 2:
                printf("Give date in format: YYYYMMDD \n");
                scanf("%ld", &user_date);
                printf("The Temperature on %ld is : %.2f\n\n", user_date, Search(root, user_date)); //Printing the Temperature on the Desired date using the Search Function
                break;
            case 3:
                printf("Give date in format: YYYYMMDD \n");
                scanf("%ld", &user_date);
                printf("The Temperature of %ld is now: %.2f\n\n", user_date, Temp_Modification(root, user_date)); //Changing the Temperature and Printing the Changed Temperature
                break;
            case 4:
                printf("Give date in format: YYYYMMDD \n");
                scanf("%ld", &user_date);
                root = Deletion(root, user_date);
                printf("The entry on the date %ld has been deleted\n\n", user_date); //Deleting the Temperature and Printing the Deleted Temperature
                break;
            case 5:
                exit(0); //Exits the Program
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
    for (int i = 0; i < 4; i++){
        temp = str[i];
        str[i] = str[n - (4 - i)];
        str[n - (4 - i)] = temp;
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
    //Loop in order to find the leftmost leaf 
    while (current->left != NULL){current = current->left;}
    return current;
}
 
struct Node *Right_Rotation(struct Node *node)
{
    struct Node *x = node->left;
    struct Node *T2 = x->right;

    //Perform rotation
    x->right = node;
    node->left = T2;

    //Update heights
    node->height = Height(node);
    x->height = Height(x);
 
    return x;
}

struct Node *Left_Rotation(struct Node *node)
{
    struct Node *y = node->right;
    struct Node *T2 = y->left;

    //Perform rotation
    y->left = node;
    node->right = T2;

    //Update heights
    node->height = Height(node);
    y->height = Height(y);

    return y;
}

struct Node* Insertion(struct Node* node, int date, float temp)
{
    //Performing the normal BST rotation
    if(node == NULL){return Node_Creaction(date, temp);}
    if(date < node->date){node->left = Insertion(node->left, date, temp);}
    else if(date > node->date){node->right = Insertion(node->right, date, temp);}
    else{return node;}
    
    node->height = Height(node); //Updating the height of the node
    int balance = Balancing(node); //Getting the balance factor of the node
    
    //If this node becomes unbalanced, then there are 4 cases:
    if (balance > 1 && date < node->left->date){return Right_Rotation(node);} //Left Left Case
    if (balance <-1  && date > node->right->date){return Left_Rotation(node);} //Right Right Case
    if (balance > 1 && date > node->left->date) //Left Right Case
    {
        node->left = Left_Rotation(node->left);
        return Right_Rotation(node);
    }
    if (balance < -1 && date < node->right->date) //Right Left Case
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
        if(search != NULL){
            if(date > search->date){search = search->right;}
            else{search = search->left;}
            if(search == NULL){return -1;}
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
    if (date < node->date){node->left = Deletion(node->left, date);} //If the key to be deleted is smaller than the root's key, then it lies in left subtree
    else if(date > node->date){node->right = Deletion(node->right, date);} //If the key to be deleted is greater than the root's key, then it lies in right subtree
    else //if key is same as root's key, then This is the node to be deleted
    {
        if((node->left == NULL) || (node->right == NULL)) //Node with only one child or no child
        {
            struct Node *delete = node->left ? node->left : node->right; 
            if (delete == NULL) //No child case
            {
                delete = node;
                node = NULL;
            }
            else //One child case
            {
                *node = *delete;
                free(delete);
            }
        }
        else //node with two children
        {
            struct Node* delete = minValueNode(node->right);
            node->date = delete->date;
            node->right = Deletion(node->right, delete->date);
        }
    }

    if (node == NULL){return node;} //If the tree had only one node then return

    node->height = 1 + max(Height(node->left), Height(node->right)); //Updating the Height of the Current Node
    int balance = Balancing(node); //Getting the Balance Factor of the node

    //Same cases as the Insertion Function
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