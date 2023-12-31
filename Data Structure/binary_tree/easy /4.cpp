#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

  struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };
 
class Solution {
    bool leaf(TreeNode* root){
        return root && !root->left && !root->right;
    }
public:
    int sumOfLeftLeaves(TreeNode* root) {
        if(!root) return 0;
        if(leaf(root->left)) return root->left->val +sumOfLeftLeaves(root->right);
        return sumOfLeftLeaves(root->left)+sumOfLeftLeaves(root->right);
    }
};
