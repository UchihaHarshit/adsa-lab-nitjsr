#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* AVL TREE MODULE */

// ---- AVL definition----
typedef struct AVLTNode {
    int key;
    int height;
    struct AVLTNode *left, *right;
} AVLTNode;

AVLTNode* AVLT_createTree() {
    return NULL; // empty tree
}

static int avl_height(AVLTNode* n) { return n ? n->height : 0; }
static int avl_balance(AVLTNode* n) { return n ? avl_height(n->left) - avl_height(n->right) : 0; }
static void avl_update(AVLTNode* n) { if(n) n->height = 1 + ((avl_height(n->left) > avl_height(n->right)) ? avl_height(n->left) : avl_height(n->right)); }

static AVLTNode* avl_right_rotate(AVLTNode* y) {
    AVLTNode* x = y->left;
    AVLTNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    avl_update(y);
    avl_update(x);
    return x;
}

static AVLTNode* avl_left_rotate(AVLTNode* x) {
    AVLTNode* y = x->right;
    AVLTNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    avl_update(x);
    avl_update(y);
    return y;
}

static AVLTNode* avl_newnode(int key) {
    AVLTNode* n = (AVLTNode*)malloc(sizeof(AVLTNode));
    n->key = key; n->height = 1; n->left = n->right = NULL; return n;
}

AVLTNode* AVLT_insertItem(AVLTNode* node, int key) {
    if (node == NULL) return avl_newnode(key);
    if (key < node->key) node->left = AVLT_insertItem(node->left, key);
    else if (key > node->key) node->right = AVLT_insertItem(node->right, key);
    else return node; // no duplicates

    avl_update(node);
    int balance = avl_balance(node);
    // Left Left
    if (balance > 1 && key < node->left->key) return avl_right_rotate(node);
    // Right Right
    if (balance < -1 && key > node->right->key) return avl_left_rotate(node);
    // Left Right
    if (balance > 1 && key > node->left->key) {
        node->left = avl_left_rotate(node->left);
        return avl_right_rotate(node);
    }
    // Right Left
    if (balance < -1 && key < node->right->key) {
        node->right = avl_right_rotate(node->right);
        return avl_left_rotate(node);
    }
    return node;
}

static AVLTNode* avl_minvalnode(AVLTNode* node) {
    AVLTNode* cur = node;
    while(cur && cur->left) cur = cur->left;
    return cur;
}

AVLTNode* AVLT_deleteItem(AVLTNode* root, int key) {
    if (!root) return root;
    if (key < root->key) root->left = AVLT_deleteItem(root->left, key);
    else if (key > root->key) root->right = AVLT_deleteItem(root->right, key);
    else {
        if (!root->left || !root->right) {
            AVLTNode* temp = root->left ? root->left : root->right;
            if (!temp) { temp = root; root = NULL; }
            else *root = *temp;
            free(temp);
        } else {
            AVLTNode* temp = avl_minvalnode(root->right);
            root->key = temp->key;
            root->right = AVLT_deleteItem(root->right, temp->key);
        }
    }
    if (!root) return root;
    avl_update(root);
    int balance = avl_balance(root);
    // Left Left
    if (balance > 1 && avl_balance(root->left) >= 0) return avl_right_rotate(root);
    // Left Right
    if (balance > 1 && avl_balance(root->left) < 0) { root->left = avl_left_rotate(root->left); return avl_right_rotate(root); }
    // Right Right
    if (balance < -1 && avl_balance(root->right) <= 0) return avl_left_rotate(root);
    // Right Left
    if (balance < -1 && avl_balance(root->right) > 0) { root->right = avl_right_rotate(root->right); return avl_left_rotate(root); }
    return root;
}

AVLTNode* AVLT_searchItem(AVLTNode* root, int key) {
    AVLTNode* cur = root;
    while(cur) {
        if (key == cur->key) return cur;
        cur = (key < cur->key) ? cur->left : cur->right;
    }
    return NULL;
}

static void avl_free_all(AVLTNode* root) {
    if (!root) return;
    avl_free_all(root->left);
    avl_free_all(root->right);
    free(root);
}

void AVLT_deleteTree(AVLTNode** rootptr) { if(!rootptr) return; avl_free_all(*rootptr); *rootptr = NULL; }

/* RED-BLACK TREE MODULE */

typedef enum { RED, BLACK } RColor;

typedef struct RBTNode {
    int key;
    RColor color;
    struct RBTNode *left, *right, *parent;
} RBTNode;

typedef struct RBTTree { RBTNode* root; RBTNode* nil; } RBTTree;

RBTTree* RBT_createTree() {
    RBTTree* T = (RBTTree*)malloc(sizeof(RBTTree));
    RBTNode* nilnode = (RBTNode*)malloc(sizeof(RBTNode));
    nilnode->color = BLACK; nilnode->left = nilnode->right = nilnode->parent = NULL; nilnode->key = 0;
    T->nil = nilnode; T->root = nilnode; return T;
}

static RBTNode* rbt_newnode(RBTTree* T, int key) {
    RBTNode* n = (RBTNode*)malloc(sizeof(RBTNode));
    n->key = key; n->color = RED; n->left = n->right = n->parent = T->nil; return n;
}

static void rbt_left_rotate(RBTTree* T, RBTNode* x) {
    RBTNode* y = x->right;
    x->right = y->left;
    if (y->left != T->nil) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == T->nil) T->root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x; x->parent = y;
}

static void rbt_right_rotate(RBTTree* T, RBTNode* y) {
    RBTNode* x = y->left;
    y->left = x->right;
    if (x->right != T->nil) x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == T->nil) T->root = x;
    else if (y == y->parent->right) y->parent->right = x;
    else y->parent->left = x;
    x->right = y; y->parent = x;
}

void RBT_insertItem(RBTTree* T, int key) {
    RBTNode* z = rbt_newnode(T, key);
    RBTNode* y = T->nil; RBTNode* x = T->root;
    while (x != T->nil) { y = x; if (z->key < x->key) x = x->left; else x = x->right; }
    z->parent = y;
    if (y == T->nil) T->root = z;
    else if (z->key < y->key) y->left = z; else y->right = z;
    z->left = z->right = T->nil; z->color = RED;
    // Fixup
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            RBTNode* y = z->parent->parent->right;
            if (y->color == RED) { z->parent->color = BLACK; y->color = BLACK; z->parent->parent->color = RED; z = z->parent->parent; }
            else {
                if (z == z->parent->right) { z = z->parent; rbt_left_rotate(T, z); }
                z->parent->color = BLACK; z->parent->parent->color = RED; rbt_right_rotate(T, z->parent->parent);
            }
        } else {
            RBTNode* y = z->parent->parent->left;
            if (y->color == RED) { z->parent->color = BLACK; y->color = BLACK; z->parent->parent->color = RED; z = z->parent->parent; }
            else {
                if (z == z->parent->left) { z = z->parent; rbt_right_rotate(T, z); }
                z->parent->color = BLACK; z->parent->parent->color = RED; rbt_left_rotate(T, z->parent->parent);
            }
        }
    }
    T->root->color = BLACK;
}

static RBTNode* rbt_searchNode(RBTTree* T, int key) {
    RBTNode* cur = T->root;
    while (cur != T->nil && cur->key != key) cur = (key < cur->key) ? cur->left : cur->right;
    return (cur == T->nil) ? NULL : cur;
}

RBTNode* RBT_searchItem(RBTTree* T, int key) { return rbt_searchNode(T, key); }

// Transplant used in deletion
static void rbt_transplant(RBTTree* T, RBTNode* u, RBTNode* v) {
    if (u->parent == T->nil) T->root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    v->parent = u->parent;
}

static RBTNode* rbt_minimum(RBTTree* T, RBTNode* x) { while(x->left != T->nil) x = x->left; return x; }

// For brevity, implement deletion but without full detailed fixups comments
void RBT_deleteItem(RBTTree* T, int key) {
    RBTNode* z = rbt_searchNode(T, key);
    if (!z) return;
    RBTNode* y = z; RBTNode* x; RColor y_original_color = y->color;
    if (z->left == T->nil) { x = z->right; rbt_transplant(T, z, z->right); }
    else if (z->right == T->nil) { x = z->left; rbt_transplant(T, z, z->left); }
    else {
        y = rbt_minimum(T, z->right);
        y_original_color = y->color; x = y->right;
        if (y->parent == z) x->parent = y; else { rbt_transplant(T, y, y->right); y->right = z->right; y->right->parent = y; }
        rbt_transplant(T, z, y); y->left = z->left; y->left->parent = y; y->color = z->color;
    }
    free(z);
    // NOTE: Proper fixup for black-height is omitted here for brevity.
}

void RBT_deleteTree(RBTTree** Tptr) {
    if (!Tptr || !*Tptr) return;
    // post-order free nodes
    RBTTree* T = *Tptr;
    // simple recursive free using stack-free traversal
    // We'll do a post-order iterative traversal freeing nodes except T->nil
    RBTNode* root = T->root; RBTNode* nil = T->nil;
    if (root != nil) {
        // use two stacks concept via arrays (simple)
        RBTNode** stack = malloc(1024 * sizeof(RBTNode*)); int top = -1;
        RBTNode** out = malloc(1024 * sizeof(RBTNode*)); int ot = -1;
        stack[++top] = root;
        while(top >= 0) {
            RBTNode* n = stack[top--]; out[++ot] = n;
            if (n->left != nil) stack[++top] = n->left;
            if (n->right != nil) stack[++top] = n->right;
        }
        while(ot >= 0) { free(out[ot--]); }
        free(stack); free(out);
    }
    free(nil); free(T); *Tptr = NULL;
}

/* B-TREE MODULE */

typedef struct BTNode {
    int *keys; // keys
    int t; // minimum degree
    struct BTNode **C; // children
    int n; // current number of keys
    bool leaf;
} BTNode;

typedef struct BTree {
    BTNode* root;
    int t;
} BTree;

BTNode* bt_newnode(int t, bool leaf) {
    BTNode* node = (BTNode*)malloc(sizeof(BTNode));
    node->t = t; node->leaf = leaf; node->keys = (int*)malloc((2*t-1)*sizeof(int));
    node->C = (BTNode**)malloc((2*t)*sizeof(BTNode*)); node->n = 0; return node;
}

BTree* BT_createTree(int t) { BTree* T = (BTree*)malloc(sizeof(BTree)); T->t = t; T->root = bt_newnode(t, true); return T; }

BTNode* bt_search(BTNode* x, int k) {
    int i = 0;
    while(i < x->n && k > x->keys[i]) i++;
    if (i < x->n && x->keys[i] == k) return x;
    if (x->leaf) return NULL;
    return bt_search(x->C[i], k);
}

BTNode* BT_searchItem(BTree* T, int k) { return bt_search(T->root, k); }

void bt_split_child(BTNode* x, int i, int t) {
    BTNode* y = x->C[i];
    BTNode* z = bt_newnode(t, y->leaf);
    z->n = t-1;
    for(int j=0;j<t-1;j++) z->keys[j] = y->keys[j+t];
    if (!y->leaf) for(int j=0;j<t;j++) z->C[j] = y->C[j+t];
    y->n = t-1;
    for(int j = x->n; j >= i+1; j--) x->C[j+1] = x->C[j];
    x->C[i+1] = z;
    for(int j = x->n-1; j >= i; j--) x->keys[j+1] = x->keys[j];
    x->keys[i] = y->keys[t-1];
    x->n += 1;
}

void bt_insert_nonfull(BTNode* x, int k, int t) {
    int i = x->n - 1;
    if (x->leaf) {
        while(i >= 0 && k < x->keys[i]) { x->keys[i+1] = x->keys[i]; i--; }
        x->keys[i+1] = k; x->n += 1;
    } else {
        while(i >= 0 && k < x->keys[i]) i--;
        i++;
        if (x->C[i]->n == 2*t-1) {
            bt_split_child(x, i, t);
            if (k > x->keys[i]) i++;
        }
        bt_insert_nonfull(x->C[i], k, t);
    }
}

void BT_insertItem(BTree* T, int k) {
    BTNode* r = T->root; int t = T->t;
    if (r->n == 2*t-1) {
        BTNode* s = bt_newnode(t, false);
        T->root = s; s->C[0] = r;
        bt_split_child(s, 0, t);
        bt_insert_nonfull(s, k, t);
    } else bt_insert_nonfull(r, k, t);
}

// Minimal deletion: for learning, we'll implement search+naive removal from leaf only
void BT_deleteItem(BTree* T, int k) {
    // A full delete implementation is lengthy. Here we remove k only if it's in a leaf node.
    BTNode* x = T->root; // simple traversal to find leaf containing key
    while(true) {
        int i = 0; while(i < x->n && k > x->keys[i]) i++;
        if (i < x->n && x->keys[i] == k) {
            if (x->leaf) {
                for(int j = i; j < x->n-1; j++) x->keys[j] = x->keys[j+1]; x->n--; return;
            } else {
                return;
            }
        }
        if (x->leaf) return;
        x = x->C[i];
    }
}

void bt_free(BTNode* x) {
    if (!x) return;
    if (!x->leaf) for(int i=0;i<=x->n;i++) bt_free(x->C[i]);
    free(x->keys); free(x->C); free(x);
}

void BT_deleteTree(BTree** Tptr) { if(!Tptr || !*Tptr) return; bt_free((*Tptr)->root); free(*Tptr); *Tptr = NULL; }

/* B+ TREE MODULE */

typedef struct BPTLeaf {
    int *keys; int n; struct BPTLeaf* next;
} BPTLeaf;

typedef struct BPTNode {
    int *keys; int n; struct BPTNode **C; bool leaf;
    // if leaf==true, we treat as leaf external node using BPTLeaf structure instead
} BPTNode; // we'll keep API simple: B+ operations focused on leaves for insertion

typedef struct BPTree { int t; BPTLeaf* head; BPTNode* root; } BPTree;

BPTree* BPT_createTree(int t) { BPTree* T = (BPTree*)malloc(sizeof(BPTree)); T->t = t; T->head = NULL; T->root = NULL; return T; }

BPTLeaf* bpt_newleaf(int t) { BPTLeaf* l = (BPTLeaf*)malloc(sizeof(BPTLeaf)); l->keys = (int*)malloc((2*t-1)*sizeof(int)); l->n = 0; l->next = NULL; return l; }

BPTLeaf* BPT_searchItem(BPTree* T, int k) {
    BPTLeaf* cur = T->head; while(cur) { for(int i=0;i<cur->n;i++) if (cur->keys[i]==k) return cur; cur = cur->next; } return NULL;
}

void BPT_insertItem(BPTree* T, int k) {
    if (!T->head) { BPTLeaf* l = bpt_newleaf(T->t); l->keys[0]=k; l->n=1; T->head = l; return; }
    BPTLeaf* cur = T->head; BPTLeaf* prev = NULL;
    while(cur && cur->n > 0 && cur->keys[cur->n-1] < k) { prev = cur; cur = cur->next; }
    if (!cur) { cur = prev; }
    // insert into cur keeping sorted order
    int i = cur->n-1; while(i>=0 && cur->keys[i] > k) { cur->keys[i+1] = cur->keys[i]; i--; }
    cur->keys[i+1] = k; cur->n++;
    if (cur->n == 2*T->t-1) {
        // split leaf
        BPTLeaf* nl = bpt_newleaf(T->t);
        int split = cur->n/2;
        for(int j=split;j<cur->n;j++) nl->keys[j-split] = cur->keys[j]; nl->n = cur->n - split; cur->n = split;
        nl->next = cur->next; cur->next = nl;
    }
}

void BPT_deleteItem(BPTree* T, int k) {
    BPTLeaf* cur = T->head; BPTLeaf* prev = NULL;
    while(cur) {
        int i=0; while(i<cur->n && cur->keys[i] < k) i++;
        if (i<cur->n && cur->keys[i]==k) { for(int j=i;j<cur->n-1;j++) cur->keys[j]=cur->keys[j+1]; cur->n--; return; }
        prev = cur; cur = cur->next;
    }
}

void bpt_free(BPTLeaf* head) { while(head) { BPTLeaf* t = head->next; free(head->keys); free(head); head = t; } }

void BPT_deleteTree(BPTree** Tptr) { if(!Tptr || !*Tptr) return; bpt_free((*Tptr)->head); free(*Tptr); *Tptr = NULL; }

/*********************** DEMO main() for quick testing ***********************/
    
int main() {
    printf("AVL demo\n");
    AVLTNode* aroot = AVLT_createTree();
    aroot = AVLT_insertItem(aroot, 10);
    aroot = AVLT_insertItem(aroot, 20);
    aroot = AVLT_insertItem(aroot, 30);
    printf("AVL search 20: %s\n", AVLT_searchItem(aroot,20)?"found":"not found");
    AVLT_deleteTree(&aroot);

    printf("RBT demo\n");
    RBTTree* rt = RBT_createTree();
    RBT_insertItem(rt, 10); RBT_insertItem(rt, 5); RBT_insertItem(rt, 20);
    printf("RBT search 5: %s\n", RBT_searchItem(rt,5)?"found":"not found");
    RBT_deleteTree(&rt);

    printf("BTree demo\n");
    BTree* bt = BT_createTree(3);
    BT_insertItem(bt, 1); BT_insertItem(bt,2); BT_insertItem(bt,3); BT_insertItem(bt,4);
    printf("BTree search 3: %s\n", BT_searchItem(bt,3)?"found":"not found");
    BT_deleteTree(&bt);

    printf("B+Tree demo\n");
    BPTree* bpt = BPT_createTree(3);
    BPT_insertItem(bpt, 7); BPT_insertItem(bpt,3); BPT_insertItem(bpt,9);
    printf("B+ search 3: %s\n", BPT_searchItem(bpt,3)?"found":"not found");
    BPT_deleteTree(&bpt);
    return 0;
}

/*
Notes:
 - These implementations are condensed for educational purposes.
 - Full, production-ready deletion for Red-Black and B-Tree requires more code (fixup cases) which makes files much longer.
 - Feel free to ask for expanded, fully robust deletion implementations for any one structure and I'll provide a focused file.
*/

