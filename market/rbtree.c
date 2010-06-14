/*	------------------------------------------------
	
	rbtree.c - Implementation of Red-Black tree search structure

	(c) Ilya Ponetayev, 2010
	(c) http://algolist.manual.ru/ds/rbtree.php
	Published under GNU GPL v2 License

  --------------------------------------------------- */

#include "market.h"
#include "rbtree.h"
 
#define compLT(a,b) (a < b)
#define compEQ(a,b) (a == b)

/* Red-Black tree color attribute */
typedef enum { BLACK, RED } nodeColor;

typedef struct Node_ {
    struct Node_ * left;         /* left child */
    struct Node_ * right;        /* right child */
    struct Node_ * parent;       /* parent */
    nodeColor color;            /* node color (BLACK, RED) */
    T data;                     /* data stored in node */
	int count;
} Node;

#define NIL &sentinel           /* all leafs are sentinels */
Node sentinel = { NIL, NIL, 0, BLACK, 0};

Node * root = NIL;               /* root of Red-Black tree */

void rotateLeft(Node * x) {

   /**************************
    *  rotate node x to left *
    **************************/

    Node * y = x->right;

    /* establish x->right link */
    x->right = y->left;
    if (y->left != NIL) 
		y->left->parent = x;

    /* establish y->parent link */
    if (y != NIL) 
		y->parent = x->parent;
    if (x->parent) {
        if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
    } else
        root = y;

    /* link x and y */
    y->left = x;
    if (x != NIL) 
		x->parent = y;
}

void rotateRight(Node * x) {

   /****************************
    *  rotate node x to right  *
    ****************************/

    Node * y = x->left;

    /* establish x->left link */
    x->left = y->right;
    if (y->right != NIL)
		y->right->parent = x;

    /* establish y->parent link */
    if (y != NIL) 
		y->parent = x->parent;
    if (x->parent) {
        if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
    } else
        root = y;

    /* link x and y */
    y->right = x;
    if (x != NIL) 
		x->parent = y;
}

void insertFixup(Node *x) {

   /*************************************
    *  maintain Red-Black tree balance  *
    *  after inserting node x           *
    *************************************/

    /* check Red-Black properties */
    while (x != root && x->parent->color == RED) {
        /* we have a violation */
        if (x->parent == x->parent->parent->left) {
            Node * y = x->parent->parent->right;
            if (y->color == RED) {

                /* uncle is RED */
                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            } else {

                /* uncle is BLACK */
                if (x == x->parent->right) {
                    /* make x a left child */
                    x = x->parent;
                    rotateLeft(x);
                }

                /* recolor and rotate */
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                rotateRight(x->parent->parent);
            }
        } else {

            /* mirror image of above code */
            Node * y = x->parent->parent->left;
            if (y->color == RED) {

                /* uncle is RED */
                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            } else {

                /* uncle is BLACK */
                if (x == x->parent->left) {
                    x = x->parent;
                    rotateRight(x);
                }
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                rotateLeft(x->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

Node * insertNode(T data) {
    Node * current, * parent, * x;

   /***********************************************
    *  allocate node for data and insert in tree  *
    ***********************************************/

    /* find where node belongs */
    current = root;
    parent = 0;
    while (current != NIL) {
		if (compEQ(data, current->data)) {
			++current->count;
			return (current);
		}
        parent = current;
        current = compLT(data, current->data) ? current->left : current->right;
    }
    /* setup new node */
    if ((x = malloc (sizeof(*x))) == 0)
        err(EMEM);
    x->data = data;
    x->parent = parent;
    x->left = NIL;
    x->right = NIL;
    x->color = RED;
	x->count = 1;
    /* insert node in tree */
    if(parent) {
        if(compLT(data, parent->data))
            parent->left = x;
        else
            parent->right = x;
    } else
        root = x;

    insertFixup(x);
    return(x);
}

Node *findNode(T data) {

   /*******************************
    *  find node containing data  *
    *******************************/

    Node *current = root;
    while(current != NIL)
        if(compEQ(data, current->data))
            return (current);
        else
            current = compLT (data, current->data) ?
                current->left : current->right;
    return(0);
}

void printTree(Node * a, int level) {
	int i;	

	if (a == NIL)
		return;
	for(i = 0; i < level; ++i)
		printf(" | ");
	printf(" |-> %p : L : %p; R : %p, Leaf: %d\n", a, a->left, a->right, (int)a->data);

	printTree(a->left, level + 1);
	printTree(a->right, level + 1);
}

Node * searchNode(Node * a, T val) {
	if (a == NIL)
		return NIL;

	if (a->data == val)
		return a;
	if (a->data < val)
		return searchNode(a->right, val);
	else
		return searchNode(a->left, val);
}

void releaseTree(Node * a) {
	if (a == NIL)
		return;
	releaseTree(a->left);
	releaseTree(a->right);
	free(a);
}

int heightTree(Node * a) {
	int lh, rh;
	if (a == NIL)
		return 0;
	lh = heightTree(a->left);
	rh = heightTree(a->right);
	if (lh < rh)
		return rh + 1;
	else
		return lh + 1;
}

int lengthTree(Node * a) {
	if (a == NIL)
		return 0;
	return lengthTree(a->left) + lengthTree(a->right) + 1;
}

// Walking down the tree and linearize it
void copyTree(Node * a, struct Line * l) {
	if (a == NIL)
		return;

	l->m_items[l->pos].count = a->count;
	l->m_items[l->pos].barCode = a->data;
	++l->pos;
	copyTree(a->left, l);
	copyTree(a->right, l);
}

/*  High-level interface functions,
	we should totally hide all details of realization */

// Inserting new leaf or simply increment count
void treeAdd(T value) {
	insertNode(value);
}

// Discharging
void treeFree(void) {
	releaseTree(root);
}

// Search in the tree
int treeSearch(T val) {
	return (searchNode(root, val) == NIL) ? 0 : 1;
}

// Linearizing the tree into array of lCouple structures
struct Line * treeLine(void) {
	struct Line * res = malloc(sizeof(struct Line));

	if (!res)
		err(EMEM);
	res->count = lengthTree(root);
	res->m_items = malloc(res->count * sizeof(struct lCouple));
	res->pos = 0;
	copyTree(root, res);
	return res;
}
