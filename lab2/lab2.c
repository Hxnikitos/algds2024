#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
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

bool isSame(struct TreeAVLNode* root1, struct TreeAVLNode* root2) {
    if (root1 == NULL && root2 == NULL) {
        return true;
    }
    if (root1 != NULL && root2 != NULL) {
        return (root1->key == root2->key && isSame(root1->left, root2->left) && isSame(root1->right, root2->right));
    }
    return false;
}


void PrintAVLTree(struct TreeAVLNode* root, int height) {
    if (root == NULL) return;

    
    int levelNodes = 1; // ���������� ����� �� ������� ������

    struct TreeAVLNode** queue = (struct TreeAVLNode*)malloc(sizeof(struct TreeAVLNode*) * 100);
    int front = 0, rear = 0;
    queue[rear++] = root;

    for (int level = 1; level <= height; level++) {
        // ���������� �������� ��� �������� ������
        int spaces = pow(2, height - level) - 1;
        for (int i = 0; i < spaces; i++) printf(" ");

        for (int i = 0; i < levelNodes; i++) {
            struct TreeAVLNode* current = queue[front++];
            if (current == NULL) {
                printf("  "); // ��� ������ �����
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

    struct TreeAVLNode* NodeCheck = NewNodeCreating(10);
    NodeCheck->left = NewNodeCreating(2);
    NodeCheck->left->parent = NodeCheck;
    NodeCheck->right = NewNodeCreating(11);
    NodeCheck->right->parent = NodeCheck;
    NodeCheck->left->right = NewNodeCreating(6);
    NodeCheck->left->right->parent = NodeCheck->left;
    //PrintAVLTree(NodeCheck, 5);

    struct TreeAVLNode* NodeCheck8 = NewNodeCreating(10);
    NodeCheck8->left = NewNodeCreating(6);
    NodeCheck8->left->parent = NodeCheck8;
    NodeCheck8->right = NewNodeCreating(11);
    NodeCheck8->right->parent = NodeCheck8;
    NodeCheck8->left->right = NewNodeCreating(8);
    NodeCheck8->left->right->parent = NodeCheck8->left;
    NodeCheck8->left->left = NewNodeCreating(2);
    NodeCheck8->left->left->parent = NodeCheck8->left;
    //PrintAVLTree(NodeCheck8, 5);

    printf("\n\nTests\n\n");
    printf("���� �� ����������\n���� ����������� ������\n\n");
    struct TreeAVLNode* Node = NewNodeCreating(10);
    Node->left = NewNodeCreating(2);
    Node->left->parent = Node;
    Node->right = NewNodeCreating(11);
    Node->right->parent = Node;
    PrintAVLTree(Node, 5);
    printf("������� ������� 6\n\n");
    InsertNode(Node, 6);
    PrintAVLTree(Node, 5);
    if (isSame(Node, NodeCheck) == true)
    {
        printf("��������� ���������\n\n");
    }
    else
    {
        printf("����������� ���������\n\n");
    }
    
    printf("������� ������� 8\n\n");
    InsertNode(Node, 8);
    PrintAVLTree(Node, 5);
    if (isSame(Node, NodeCheck8) == true)
    {
        printf("��������� ���������\n\n");
    }
    else
    {
        printf("����������� ���������\n\n");
    }
    
    free(Node);
    free(NodeCheck);
    free(NodeCheck8);
}

void TestRemove()
{
    struct TreeAVLNode* NodeCheck5 = NewNodeCreating(10);
    NodeCheck5->left = NewNodeCreating(6);
    NodeCheck5->left->parent = NodeCheck5;
    NodeCheck5->right = NewNodeCreating(11);
    NodeCheck5->right->parent = NodeCheck5;
    NodeCheck5->right->right = NewNodeCreating(12);
    NodeCheck5->right->right->parent = NodeCheck5->right;;
    NodeCheck5->left->left = NewNodeCreating(2);
    NodeCheck5->left->left->parent = NodeCheck5->left;
    NodeCheck5->left->left->left = NewNodeCreating(1);
    NodeCheck5->left->left->left->parent = NodeCheck5->left->left;
    NodeCheck5->left->left->right = NewNodeCreating(3);
    NodeCheck5->left->left->right->parent = NodeCheck5->left->left;

    printf("���� �� ��������\n���� ����������� ������\n\n");
    struct TreeAVLNode* Node = NewNodeCreating(10);
    Node->left = NewNodeCreating(5);
    Node->left->parent = Node;
    Node->right = NewNodeCreating(11);
    Node->right->parent = Node;
    
    InsertNode(Node, 3);    
    InsertNode(Node, 6);    
    InsertNode(Node, 12);
    InsertNode(Node, 2);
    InsertNode(Node, 1);
    PrintAVLTree(Node, 5);
    printf("������ ������� 5\n\n");
    Delete(Node, 5);
    PrintAVLTree(Node, 5);
    if (isSame(Node, NodeCheck5) == true)
    {
        printf("��������� ���������\n\n");
    }
    else
    {
        printf("����������� ���������\n\n");
    }
    free(Node);
    free(NodeCheck5);
}

int main() {
    setlocale(LC_CTYPE, "Rus");
    printf("������� ������ 5030102/20003 2 ���\n\n");

    TestInsert();
    TestRemove();

    return 0;
}