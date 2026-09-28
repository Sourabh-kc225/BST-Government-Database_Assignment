#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    char id[20];
    struct Node *left;
    struct Node *right;
};

struct Node* createNode(char id[])
{
    struct Node *newNode;

    newNode = (struct Node*)malloc(sizeof(struct Node));

    strcpy(newNode->id, id);
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

struct Node* insert(struct Node *root, char id[])
{
    if (root == NULL)
        return createNode(id);

    if (strcmp(id, root->id) < 0)
        root->left = insert(root->left, id);
    else
        root->right = insert(root->right, id);

    return root;
}

void inorder(struct Node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%s ", root->id);
        inorder(root->right);
    }
}

int height(struct Node *root)
{
    int leftHeight, rightHeight;

    if (root == NULL)
        return -1;

    leftHeight = height(root->left);
    rightHeight = height(root->right);

    if (leftHeight > rightHeight)
        return leftHeight + 1;
    else
        return rightHeight + 1;
}

int bstSearch(struct Node *root, char key[], int *comparisons)
{
    struct Node *current = root;

    *comparisons = 0;

    while (current != NULL)
    {
        (*comparisons)++;

        if (strcmp(key, current->id) == 0)
            return 1;

        if (strcmp(key, current->id) < 0)
            current = current->left;
        else
            current = current->right;
    }

    return 0;
}

int linearSearch(char a[][20], int n, char key[], int *comparisons)
{
    int i;

    *comparisons = 0;

    for (i = 0; i < n; i++)
    {
        (*comparisons)++;

        if (strcmp(a[i], key) == 0)
            return 1;
    }

    return 0;
}

int createTree(char a[][20], int n)
{
    struct Node *root = NULL;
    int i;

    for (i = 0; i < n; i++)
        root = insert(root, a[i]);

    return height(root);
}

int main()
{
    char ids[][20] =
    {
        "A102", "A25", "A7", "B100",
        "B12", "A120", "B3", "A45"
    };

    char ascending[][20] =
    {
        "A102", "A120", "A25", "A45",
        "A7", "B100", "B12", "B3"
    };

    char differentOrder[][20] =
    {
        "A45", "B12", "A7", "B100",
        "A120", "B3", "A102", "A25"
    };

    char shortKeys[][20] =
    {
        "A1", "A2", "A3", "B1",
        "B2", "A4", "B3", "A5"
    };

    char longKeys[][20] =
    {
        "A102345678", "A253456789", "A712345678",
        "B100123456", "B123456789", "A120123456",
        "B312345678", "A451234567"
    };

    char key[20];

    struct Node *root = NULL;
    struct Node *shortRoot = NULL;
    struct Node *longRoot = NULL;

    int n = 8;
    int i;
    int bstComp, linearComp;

    for (i = 0; i < n; i++)
        root = insert(root, ids[i]);

    printf("Inorder Traversal:\n");
    inorder(root);

    printf("\n\nBST Height = %d edges\n", height(root));

    printf("\nEnter ID to search: ");
    scanf("%19s", key);

    if (bstSearch(root, key, &bstComp))
        printf("BST Search: Found\n");
    else
        printf("BST Search: Not Found\n");

    printf("BST Comparisons = %d\n", bstComp);

    if (linearSearch(ids, n, key, &linearComp))
        printf("Linear Search: Found\n");
    else
        printf("Linear Search: Not Found\n");

    printf("Linear Search Comparisons = %d\n", linearComp);

    printf("\nInsertion Order Analysis\n");
    printf("Original Order Height = %d edges\n", height(root));
    printf("Sorted Order Height = %d edges\n", createTree(ascending, n));
    printf("Different Order Height = %d edges\n", createTree(differentOrder, n));

    for (i = 0; i < n; i++)
    {
        shortRoot = insert(shortRoot, shortKeys[i]);
        longRoot = insert(longRoot, longKeys[i]);
    }

    printf("\nKey Length Analysis\n");
    printf("Short Keys Height = %d edges\n", height(shortRoot));
    printf("Long Keys Height = %d edges\n", height(longRoot));

    return 0;
}
