#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <locale.h>

struct TreeAVLNode {
    int key;
    int height;
    struct TreeAVLNode* parent;
    struct TreeAVLNode* left;
    struct TreeAVLNode* right;
};


int Max(int a, int b) {
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int GetHeight(struct TreeAVLNode* Node) {
    if (Node)
    {
        return Node->height;
    }
    else {return 0;}

}

int bfactor(struct TreeAVLNode* Node) {
    return (GetHeight(Node->right) - GetHeight(Node->left));
}

void FixHeight(struct TreeAVLNode* Node) {
    int rheight = GetHeight(Node->right);
    int lheight = GetHeight(Node->left);
    Node->height = Max(lheight,rheight) + 1;
}
struct TreeAVLNode* NewNodeCreating(int key) {

    struct TreeAVLNode* Node = (struct TreeAVLNode*)malloc(sizeof(struct TreeAVLNode));
    if (!Node) {
        exit(EXIT_FAILURE);
    }
    Node->key = key;
    Node->height = 1;
    Node->parent = NULL;
    Node->left = NULL;
    Node->right = NULL;
    

    return Node;
}

void FindingRoot(struct TreeAVLNode** Node) {
    while ((*Node)->parent) {
        (*Node) = (*Node)->parent;  
    }
}
struct TreeAVLNode* SmallRotationRight(struct TreeAVLNode* p) {
    struct TreeAVLNode* q = p->left;
    struct TreeAVLNode* parent = p->parent;
    p->left = q->left;
    q->right = p;
    q->parent = parent;
    p->left = NULL;
    FixHeight(p);
    FixHeight(q);
    return q;
}

struct TreeAVLNode* SmallRotationLeft(struct TreeAVLNode* q) {

    struct TreeAVLNode* p = q->right;
    struct TreeAVLNode* parent = q->parent;
    q->right = p->right;

    p->left = q;
    p->parent = parent;
    q->right = NULL;
    FixHeight(q);
    FixHeight(p);
    return p;


}

struct TreeAVLNode* Balance(struct TreeAVLNode* Node) {

    FixHeight(Node);
    
    if (bfactor(Node) == 2) {
        if (bfactor(Node->right) < 0) 
        {
            
            Node->right = SmallRotationRight(Node->right);
            Node->right->parent->right = Node->right;
        }

        Node= SmallRotationLeft(Node);
        Node->parent->left = Node;
    }
    if (bfactor(Node) == -2) {
        if (bfactor(Node->left) > 0) 
        {
            
            Node->left = SmallRotationLeft(Node->left);
            Node->left->parent->left = Node->left;
        }

        Node=SmallRotationRight(Node);
        Node->parent->left = Node;
    }
    return Node;
}


void InsertFind(struct TreeAVLNode** Node, struct TreeAVLNode** q, struct TreeAVLNode* FindingRoot, int key) {
    struct TreeAVLNode* current = FindingRoot;

    while (current) {
        *Node = current;
        if (key < current->key) current = current->left;
        else current = current->right;
    }

    if (key < (*Node)->key) (*Node)->left = *q;
    else (*Node)->right = *q;

    (*q)->parent = (*Node);
}

void BalanceTree( struct TreeAVLNode* parent, struct TreeAVLNode* new) {
    while (parent) {
        FixHeight(parent);
        int balance = bfactor(parent);

        if (balance == 0) break;

        else if (abs(balance) == 1) {
            new = parent;
            parent = parent->parent;
        }
        else {
           parent= Balance(parent);
           
            break;
        }
    }
}



struct TreeAVLNode* InsertNode(struct TreeAVLNode* Node, int key) {
    struct TreeAVLNode* new = NewNodeCreating(key);
    if (!Node) return new;

    struct TreeAVLNode* parent = NULL;

    InsertFind(&parent, &new, Node, key);
    BalanceTree(parent, new);
    return Node;
}

void NodeDelete(struct TreeAVLNode* Node, struct TreeAVLNode* current, struct TreeAVLNode* parent) {

    struct TreeAVLNode* child;
    if (current->right)
    {
        child = current->right;

    }
    else
    {
        child = current->left;
    }
   

    if (!parent) Node = child;
    else if (parent->left == current) {
        parent->left = child;
        child->left = current->left;
    }
    else {
        parent->right = child;
        child->right = Node->right;

    }

    if (child) child->parent = parent;

    free(current);
}

struct TreeAVLNode* Delete(struct TreeAVLNode* Node, int k) {
    if (!Node) return NULL;

    struct TreeAVLNode* parent = NULL;
    struct TreeAVLNode* current = Node;

    while (current && current->key != k) {
        parent = current;
        if (k < current->key) current = current->left;
        else current = current->right;
    }
    if (!current) return Node;

    NodeDelete(Node, current, parent);

    return Balance(Node);
}




void PrintAVLTree(struct TreeAVLNode* root, int height) {
    if (root == NULL) return;

    
    int levelNodes = 1; // количество узлов на текущем уровне

    struct TreeAVLNode** queue = (struct TreeAVLNode*)malloc(sizeof(struct TreeAVLNode*) * 100);
    int front = 0, rear = 0;
    queue[rear++] = root;

    for (int level = 1; level <= height; level++) {
        // Вычисление отступов для текущего уровня
        int spaces = pow(2, height - level) - 1;
        for (int i = 0; i < spaces; i++) printf(" ");

        for (int i = 0; i < levelNodes; i++) {
            struct TreeAVLNode* current = queue[front++];
            if (current == NULL) {
                printf("  "); // для пустых узлов
                queue[rear++] = NULL;
                queue[rear++] = NULL;
            }
            else {
                printf("%2d", current->key);
                queue[rear++] = current->left;
                queue[rear++] = current->right;
            }
            for (int j = 0; j < 2 * spaces ; j++) printf(" ");
        }
        printf("\n");
        levelNodes *= 2;
    }

    free(queue);
}





void TestInsert()
{
    printf("\n\nTests\n\n");
    printf("Тест на добавление\nНаше изначальное дерево\n\n");
    struct TreeAVLNode* Node = NewNodeCreating(10);
    Node->left = NewNodeCreating(5);
    Node->left->parent = Node;
    Node->right = NewNodeCreating(11);
    Node->right->parent = Node;
    PrintAVLTree(Node, 5);
    printf("Добавим элемент 6\n\n");
    InsertNode(Node, 6);
    PrintAVLTree(Node, 5);
    printf("Правильно добавился\n\n");
    printf("Добавим элемент 8\n\n");
    InsertNode(Node, 8);
    PrintAVLTree(Node, 5);
    printf("Правильно добавился с малым левым поворотом\n\n");

    free(Node);
}

void TestRemove()
{
    printf("Тест на удаление\nНаше изначальное дерево\n\n");
    struct TreeAVLNode* Node = NewNodeCreating(10);
    Node->left = NewNodeCreating(5);
    Node->left->parent = Node;
    Node->right = NewNodeCreating(11);
    Node->right->parent = Node;
    PrintAVLTree(Node, 5);
    InsertNode(Node, 3);    
    InsertNode(Node, 6);    
    InsertNode(Node, 12);
    InsertNode(Node, 2);
    InsertNode(Node, 1);
    printf("Удалим элемент 5\n\n");
    Delete(Node, 5);
    PrintAVLTree(Node, 5);
    free(Node);
}

int main() {
    setlocale(LC_CTYPE, "Rus");
    printf("Хаяйнен Никита 5030102/20003 2 вар\n\n");
    TestInsert();
    TestRemove();
    return 0;
}