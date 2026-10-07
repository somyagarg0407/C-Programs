#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RED 1
#define BLACK 0

typedef struct Node {
    int key, color;
    struct Node *left, *right, *parent;
} Node;

Node *root, *NIL;

Node *newNode(int key) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->color = RED;
    p->left = p->right = p->parent = NIL;
    return p;
}

void leftRotate(Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if (y->left != NIL) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NIL) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void rightRotate(Node *x) {
    Node *y = x->left;
    x->left = y->right;
    if (y->right != NIL) y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == NIL) root = y;
    else if (x == x->parent->right) x->parent->right = y;
    else x->parent->left = y;
    y->right = x;
    x->parent = y;
}

void insertFix(Node *z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node *y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        } else {
            Node *y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void insert(int key) {
    Node *z = newNode(key), *y = NIL, *x = root;
    while (x != NIL) {
        y = x;
        if (z->key == x->key) {
            free(z);
            return;
        }
        x = z->key < x->key ? x->left : x->right;
    }
    z->parent = y;
    if (y == NIL) root = z;
    else if (z->key < y->key) y->left = z;
    else y->right = z;
    insertFix(z);
}

Node *search(int key) {
    Node *x = root;
    while (x != NIL && x->key != key)
        x = key < x->key ? x->left : x->right;
    return x;
}

Node *minimum(Node *x) {
    while (x->left != NIL) x = x->left;
    return x;
}

void transplant(Node *u, Node *v) {
    if (u->parent == NIL) root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    v->parent = u->parent;
}

void deleteFix(Node *x) {
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node *w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        } else {
            Node *w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

void deleteNode(int key) {
    Node *z = search(key);
    if (z == NIL) return;
    Node *y = z, *x;
    int oldColor = y->color;
    if (z->left == NIL) {
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == NIL) {
        x = z->left;
        transplant(z, z->left);
    } else {
        y = minimum(z->right);
        oldColor = y->color;
        x = y->right;
        if (y->parent == z) x->parent = y;
        else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    free(z);
    if (oldColor == BLACK) deleteFix(x);
}

void inorder(Node *r,int *c){
    if(r!=NIL){
        inorder(r->left,c);
        if(*c<10){printf("%d(%c) ",r->key,r->color?'R':'B');(*c)++;}
        inorder(r->right,c);
    }
}
void preorder(Node *r,int *c){
    if(r!=NIL){
        if(*c<10){printf("%d(%c) ",r->key,r->color?'R':'B');(*c)++;}
        preorder(r->left,c);
        preorder(r->right,c);
    }
}
void postorder(Node *r,int *c){
    if(r!=NIL){
        postorder(r->left,c);
        postorder(r->right,c);
        if(*c<10){printf("%d(%c) ",r->key,r->color?'R':'B');(*c)++;}
    }
}

void initTree() {
    NIL = (Node *)malloc(sizeof(Node));
    NIL->color = BLACK;
    NIL->left = NIL->right = NIL->parent = NIL;
    root = NIL;
}

int main() {
    int sizes[]={10,50,100,500,1000};
    int count=sizeof(sizes)/sizeof(sizes[0]);
    srand((unsigned)time(NULL));
    printf("RED-BLACK TREE PERFORMANCE\n");
    printf("---------------------------\n");
    for(int s=0;s<count;s++){
        int n=sizes[s],c;
        initTree();
        int *a=malloc(n*sizeof(int));
        clock_t start=clock();
        for(int i=0;i<n;i++){
            a[i]=rand()%(n*10);
            insert(a[i]);
        }
        clock_t it=clock()-start;
        int key=a[n/2];
        start=clock();
        Node *found=search(key);
        clock_t st=clock()-start;
        start=clock();
        deleteNode(key);
        clock_t dt=clock()-start;
        printf("\nN = %d\n",n);
        c=0; printf("Inorder: "); inorder(root,&c); printf("...\n");
        c=0; printf("Preorder: "); preorder(root,&c); printf("...\n");
        c=0; printf("Postorder: "); postorder(root,&c); printf("...\n");
        printf("Search %d: %s\n",key,found!=NIL?"Found":"Not Found");
        printf("Insertion: %.6f sec\n",(double)it/CLOCKS_PER_SEC);
        printf("Search: %.6f sec\n",(double)st/CLOCKS_PER_SEC);
        printf("Deletion: %.6f sec\n",(double)dt/CLOCKS_PER_SEC);
        free(a);
        free(NIL);
    }
    return 0;

}

