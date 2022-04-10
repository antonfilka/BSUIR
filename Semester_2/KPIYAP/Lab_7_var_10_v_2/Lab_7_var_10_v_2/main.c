#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int inputValidationInt(void)
{
    int n;
    while (scanf("%d", &n) != 1 || n < 0)
    {
        rewind(stdin);
        printf("Try again\n");
    }
    return n;
}


int menu(void){
    puts("Select choice");
    puts("1) Create");
    puts("2) Output");
    puts("3) Non-recursive output");
    puts("4) Delete");
    puts("5) Exit");
    int choice = inputValidationInt();
    return choice;
}
 

typedef struct tree{
    char data[60];
    struct tree *left;
    struct tree *right;
}treeNode;
 

typedef struct stack{
    struct tree *tree;
    struct stack* next;
}stackNode;


 
treeNode* create(treeNode* root, char* value){
    if(!root) {
        root = (treeNode*) malloc(sizeof(treeNode));
        strcpy(root->data, value);
        root ->left = root->left = NULL;
    }else {
        if (strcmp(value, root->data)) root->left = create(root->left, value);
        else root->right = create(root->right, value);
    }
    return root;
}
 
void output (treeNode* root){
    if(root){
        if(root->left) output(root->left);
        printf("Value: %s\n", root->data);
        if(root->right) output(root->right);
    }
}
 
void pushStack (treeNode* current, stackNode **topReference){
    stackNode *newStack = (stackNode*) malloc(sizeof(stackNode)); //создаем доп. указ. для работы со стеком
    if(newStack == NULL)
    {
        printf("Stack is empty\n");                       //Проверяем выделилась ли память по доп. указ.
        exit(0);
    }
    newStack->tree = current;                                     //Обычное создание стека
    newStack->next = (*topReference);
    (*topReference) = newStack;
}
 
bool isEmpty(stackNode *top){
    return (top == NULL)? true : false; // если top == NULL, то true. Иначе false.
}
treeNode *pop(stackNode **topReference)
{
    treeNode *leaf;                             //лист нашего дерева
    stackNode *topOfStack;                      //дополнительный указатель для работы со стеком
    if(isEmpty(*topReference)){
        printf("Stack is empty\n");     //проверка на существование стека
        exit(0);
    }else{
        topOfStack = *topReference;             //в доп. указ. записываем вершину исходнего стека
        leaf = topOfStack->tree;                //в этот указ. мы присваиваем тот лист дерева, который соответствуют
        *topReference = topOfStack->next;       //нашей вершине, а далее мы снимаем вершину и передвигаемся на один
        free(topOfStack);                       //вниз и получаем новую вершину стека. Затем очищаем вершину стека.
        return leaf;                            //возращаем укатель на предка.
    }
 
}
 
 
void inOrder (treeNode *root){
    stackNode *stack = NULL;                    //создаем указатель на стек
    treeNode *current = root;                   //текущая позиция в бинарном дереве
    bool isType =false;                         //переменная, позволяющая контролировать работу while.
    while (!isType)                             //пока переменная !false(true), то у нас работает while
    {
        if(current != NULL){                    //проходим по самому левому поддереву до конца, при этом записывая
            pushStack(current, &stack);         //каждае значение из дерева в стек
            current = current->left;            //переход в левое поддерево
        }else{
            if(!isEmpty(stack)){                //если стек не пустой, то начинаем снимать вершину
                current = pop(&stack);          //при снятии вершины мы переходим от потомка к предку благодаря стеку
                printf("%s\n", current->data); //стек у нас в качестве своеобразного лифта, снимая вершину
                current = current->right;       //со стека мы поднимаемся по дереву вверх, после того как снли вершину и
            }else                               //поднялись к предку мы должны зайти в правое поддерево.
                isType = true;                  //если у нас стек пустой - это значит, что мы прошлись по всему дереву.
        }
    }
}
 
treeNode* minValueNode(treeNode* node)
{
    treeNode* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL)
        current = current->left;
 
    return current;
}
 
treeNode *deleteNode(treeNode *root,char* key) {
 
    if (root == NULL)
        return root;
 
    if (key < *root->data)
        root->left = deleteNode(root->left, key);
    else
        if (key > *root->data)
        root->right = deleteNode(root->right, key);
    else
    {
        if (root->left == NULL)
        {
            treeNode* temp = root->right;
            free(root);
            return temp;
        }
        else
            if (root->right == NULL)
            {
                treeNode* temp = root->left;
                free(root);
                return temp;
            }
        treeNode* temp = minValueNode(root->right);
        strcpy(root->data, temp->data);
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}
 
int main() {
    treeNode *root = NULL;
    while (1) {
        switch (menu()) {
            case 1:
                while (1) {
                    rewind(stdin);
                    puts("Enter");
                    char value[50];
                    rewind(stdin);
                    fgets(value, 50, stdin);
        
                    
                    root = create(root, value);
                    printf("More (y/n) ");
                    rewind(stdin);
                    if (getchar() == 'n') break;
                }
                break;
            case 2:
                output(root);
                break;
            case 3:
                inOrder(root);
                break;
            case 4:
                puts("Enter");
                char key[50];
                rewind(stdin);
                fgets(key, 50, stdin);
                deleteNode(root, key);
                break;
            case 5:
                return 0;
        }
    }
}

