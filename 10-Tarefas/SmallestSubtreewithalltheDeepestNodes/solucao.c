#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int profundidade (struct TreeNode * root, struct TreeNode ** output, int depth, int *deepest);
struct TreeNode* subtreeWithAllDeepest(struct TreeNode* root);
void desalocaArvore(struct TreeNode* nodo);
void imprimeArvore(struct TreeNode* nodo);

int main()
{
    struct TreeNode * nodo1 = (struct TreeNode*) malloc(sizeof(struct TreeNode)); // 3
    struct TreeNode * nodo2 = (struct TreeNode*) malloc(sizeof(struct TreeNode)); // 5
    struct TreeNode * nodo3 = (struct TreeNode*) malloc(sizeof(struct TreeNode)); // 6
    struct TreeNode * nodo4 = (struct TreeNode*) malloc(sizeof(struct TreeNode)); // 2
    struct TreeNode * nodo5 = (struct TreeNode*) malloc(sizeof(struct TreeNode)); // 7
    struct TreeNode * nodo6 = (struct TreeNode*) malloc(sizeof(struct TreeNode)); // 4
    struct TreeNode * nodo7 = (struct TreeNode*) malloc(sizeof(struct TreeNode)); // 1
    struct TreeNode * nodo8 = (struct TreeNode*) malloc(sizeof(struct TreeNode)); // 0
    struct TreeNode * nodo9 = (struct TreeNode*) malloc(sizeof(struct TreeNode)); // 8

    nodo1->val = 3;
    nodo1->left = nodo2;
    nodo1->right = nodo7;

    nodo2->val = 5;
    nodo2->left = nodo3;
    nodo2->right = nodo4;

    nodo3->val = 6;
    nodo3->left = NULL;
    nodo3->right = NULL;

    nodo4->val = 2;
    nodo4->left = nodo5;
    nodo4->right = nodo6;

    nodo5->val = 7;
    nodo5->left = NULL;
    nodo5->right = NULL;
    
    nodo6->val = 4;
    nodo6->left = NULL;
    nodo6->right = NULL;

    nodo7->val = 1;
    nodo7->left = nodo8;
    nodo7->right = nodo9;

    nodo8->val = 0;
    nodo8->left = NULL;
    nodo8->right = NULL;

    nodo9->val = 8;
    nodo9->left = NULL;
    nodo9->right = NULL;

    imprimeArvore(nodo1);
    puts("");
    imprimeArvore(subtreeWithAllDeepest(nodo1));
    puts("");
    desalocaArvore(nodo1);

    return EXIT_SUCCESS;
}


int profundidade (struct TreeNode * root, struct TreeNode ** output, int depth, int *deepest) {
  if ( (root) == NULL ) {
    return depth;
  }

  int profEsquerda = profundidade( root->left, output, depth + 1, deepest );
  int profDireita = profundidade( root->right, output, depth + 1, deepest );

  if ( profEsquerda > profDireita ) {
    return profEsquerda;
  } else if ( profDireita > profEsquerda ) {
    return profDireita;
  } else {
    if ( profEsquerda >= *deepest ) {
      *output = root;
      *deepest = profEsquerda;
    }
    return profDireita;
  }
}

struct TreeNode* subtreeWithAllDeepest(struct TreeNode* root) {
  int deepest = 0;
  struct TreeNode * output = root;
  profundidade( root, &output, 0, &deepest );
  return output;
}

void desalocaArvore(struct TreeNode* nodo) {
    if (nodo == NULL) {
        return;
    }
    desalocaArvore(nodo->left);
    desalocaArvore(nodo->right);
    free(nodo);
}

void imprimeArvore(struct TreeNode* nodo){
    if (nodo == NULL)
        return;

    printf("%d ", nodo->val);
    imprimeArvore(nodo->left);
    imprimeArvore(nodo->right);
}
