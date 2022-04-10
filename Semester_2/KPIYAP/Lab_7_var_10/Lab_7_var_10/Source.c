
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"

int menu()
{
    int choice;
    printf("Choose:\n");
    printf("1)Add word\n2)Show words\n3)Delete\n4)Exit\n\n");
    while (!scanf("%d", &choice) || choice>4 || choice<1)
    {
        rewind(stdin);
        printf("Incorrect value! Try again...\n");
    }
    return choice;
}

struct Tree* delMenu(struct Tree* rootOfTree){
    char compare[30];
    rewind(stdin);
    puts("\nEnter word to delete: ");
    fgets(compare, 30, stdin);
    rewind(stdin);
    compare[strlen(compare) - 1] = '\0';
    return delItem(rootOfTree, compare);
}

struct Tree* delItem(struct Tree* rootOfTree, char* compare)
{
    
    if(rootOfTree == NULL)
        return rootOfTree;

    if(strcmp(compare, rootOfTree->word)==0)
    {
        struct Tree *temp = NULL;
        
        if(rootOfTree->right == NULL)
        temp = rootOfTree->left;
        
        else
        {
            struct Tree *pointer = rootOfTree->right;
                
            if(pointer->left == NULL)
            {
                pointer->left = rootOfTree->left;
                temp = pointer;
            }
            else
            {
                struct Tree* minimal = pointer->left;
                while (minimal ->left != NULL)
                {
                    pointer = minimal;
                    minimal = pointer->left;
                }

                pointer->left = minimal->right;
                minimal->left = rootOfTree->left;
                minimal->right = rootOfTree->right;
                temp = pointer;
            }
        }
        free(rootOfTree);
        return temp;
    }
    else if (strcmp(compare, rootOfTree->word) < 0)
        rootOfTree->left = delItem(rootOfTree->left, compare);
    else
        rootOfTree->right = delItem(rootOfTree->left, compare);
    return rootOfTree;
}


void add(struct Tree** root)
{
    
    do
    {
        struct Tree* temp = (struct Tree*)malloc(sizeof(struct Tree));
        printf("\nEnter english word: ");
        char word[30];
        char translation[30];
        rewind(stdin);
        fgets(word, 30, stdin);
        strcpy(temp->word, word);
        printf("\nEnter russian translation: ");
        rewind(stdin);
        fgets(translation, 30, stdin);
        strcpy(temp->translation, translation);
        rewind(stdin);
        temp->left = temp->right = NULL;
        temp->word[strlen(temp->word) - 1] = '\0';
        temp->translation[strlen(temp->translation) - 1] = '\0';
        if (!*root) *root = temp;
        else
        {
            struct Tree* temp2 = *root;
            while (temp2)
            {
                if (strcmp(temp->word, temp2->word) == 0)
                {
                    free(temp);
                    break;
                }
                else
                    if (strcmp(temp->word, temp2->word) < 0)
                        if (temp2->left == NULL)
                        {
                            temp2->left = temp;
                            temp2 = NULL;
                        }
                        else temp2 = temp2->left;
                    else
                        if (temp2->right == NULL)
                        {
                            temp2->right = temp;
                            temp2 = NULL;
                        }
                        else temp2 = temp2->right;
            }
        }
        printf("\nDo you want to add one more word?(y/n): ");
    }while(getchar() == 'y');
}


void showMenu(struct Tree* root)
{
    if (!root)
    {
        puts("Binary tree is empty...\n");
        return;
    }
    
    printf("\n1)Recursive output\n2)Non-recursive output\n3)Exit\n");
    int choice;
    while (!scanf("%d", &choice) || choice > 3 || choice < 1)
    {
        rewind(stdin);
        printf("\nIncorrect value! Try again...\n");
    }
    
    switch (choice)
    {
    case 1:
        recShow(root);
        break;
    case 2:
        show(root);
        break;
    case 3: break;
    }
}


void recShow(struct Tree* root)
{
    if (root)
    {
        if (root->left) recShow(root->left);
        
        if (root->right) recShow(root->right);
        printf("\nEnglish: %-30s | Russian: %-30s\n", root->word, root->translation);
    }
}


void show(struct Tree* root)
{
    struct Stack
    {
        struct Tree* tree;
        struct Stack* stack;
    } *temp, * temp1 = NULL;

    if (!root)
    {
        printf("Binary tree is empty...\n");
        return;
    }
    int pr = 1;
                                            
    temp = (struct Stack*)calloc(1, sizeof(struct Stack));
    temp->tree = root;
    temp->stack = temp1;
    printf("\nEnglish: %-20s | Russian: %-20s\n", root->word, root->translation);
    
    
    while (temp || root->right)
    {
        do
        {
            if (pr && root->left) root = root->left;
            else if (root->right) root = root->right;
            pr = 1;
            if (root->left && root->right)
            {
                temp1 = temp;
                temp = (struct Stack*)calloc(1, sizeof(struct Stack));
                temp->tree = root;
                temp->stack = temp1;
            }
            printf("\nEnglish: %-20s | Russian: %-20s\n", root->word, root->translation);
        } while (root->left || root->right);
        if (temp)
        {
            root = temp->tree;
            temp1 = temp->stack;
            free(temp);
        }
        temp = temp1;
        if (root->left && root->right) pr = 0;
        else break;
    }
}




void del(struct Tree** root)
{
    if (!*root)
    {
        puts("Binary tree is empty...\n");
        return;
    }
    struct Tree* temp1, * temp2, * temp3;
    char str[20];
    int compare;
    int flag;
    rewind(stdin);
    puts("\nEnter word to delete: ");
    fgets(str, 20, stdin);
    rewind(stdin);
    str[strlen(str) - 1] = '\0';
    temp2 = temp1 = *root;
    flag = 0;
    do
    {
        if (!(compare = strcmp(str, temp1->word)))
            flag = 1;
        if (compare < 0)
        {
            if (temp1->left)
            {
                temp2 = temp1;
                temp1 = temp1->left;
            }
            else flag = 1;
        }
        if (compare > 0)
        {
            if (temp1->right)
            {
                temp2 = temp1;
                temp1 = temp1->right;
            }
            else flag = 1;
        }
    } while (!flag);
    if (compare)
    {
        puts("\nNot found...\n");
        return;
    }
    else
    {
        compare = strcmp(temp1->word, temp2->word);
        temp3 = temp1;
        if (compare < 0)
        {
            if (temp1->right)
            {
                temp3 = temp1->right;
                while (temp3->left) temp3 = temp3->left;
                temp2->left = temp1->right;
                temp3->left = temp1->left;
            }
            else temp2->left = temp1->left;
        }
        else
        {
            if (temp1->left)
            {
                temp3 = temp1->left;
                while (temp3->right) temp3 = temp3->right;
                temp2->right = temp1->left;
                temp3->right = temp1->right;
            }
            else temp2->right = temp1->right;
        }
        free(temp1);
    }
}



void clean(struct Tree** root)
{
    if (*root)
    {
        if ((*root)->left) clean(&(*root)->left);
        if ((*root)->right) clean(&(*root)->right);
        free(*root);
    }
}
