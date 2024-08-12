/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/*
Given the root of a binary tree, the depth of each node is the shortest distance to the root.

Return the smallest subtree such that it contains all the deepest nodes in the original tree.

A node is called the deepest if it has the largest depth possible among any node in the entire tree.

The subtree of a node is a tree consisting of that node, plus the set of all descendants of that node.
*/
int altura (struct TreeNode * root) {
  if ( (root) == NULL ) {
    return 0; //base da recursão, folhas tem altura 0.
  }


  int altEsquerda = altura( root->left );
  int altDireita = altura( root->right );

  if ( altEsquerda > altDireita ) {
    return altEsquerda + 1;

  } else {
    return altDireita + 1;
  }
}

void preorder_depth( struct TreeNode* root, struct TreeNode* aux, struct TreeNode* deepest, int height, int * depth, int * amount) {
  if (root == NULL){
    if ( depth > 0) {
    *depth-=1;
    }
    return;
  }
  // *depth+=1;
  // printf("percorrendo %d com depth = %d\n",root->val ,*depth);
  // preorder_depth(root->left, aux, deepest, height, depth, amount);
  // printf("percorrendo %d com depth = %d\n",root->val ,*depth);
  // aux = root;
  // preorder_depth(root->right, aux, deepest, height, depth, amount);
  //   printf("percorrendo %d com depth = %d\n",root->val ,*depth);

  // if(aux != root->left)
  //   puts("lajhljasdl");
  //   *depth+=1;

  

}

struct TreeNode* subtreeWithAllDeepest(struct TreeNode* root) {
  int alturaArvore = altura(root);
  int depth, amount;
  struct TreeNode * deepest;
    struct TreeNode * aux;

  preorder_depth(root, aux,deepest, alturaArvore, &depth, &amount);

  return deepest;
}
