typedef struct s_node Node;

struct s_node {
    int key;
    int count;
    Node *left;
    Node *right;
};

typedef struct s_tree Tree;

struct s_tree {
    Node *root;
};

Tree *tree_alloc(void);
void tree_add(Tree *tree, int key);
void tree_print(Tree *tree);
void tree_free(Tree **p);

void tree_dump(Tree *tree);
