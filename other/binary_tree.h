#include <bits/stdc++.h>

/*
API
makeTree(m) - create binary tree from vector m and return pointer to its root
fromTree(l) - return vector of values of linked list with root l
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

TreeNode* makeTreeLocal(vector<int>& m, int s, int e, int n) {
    if (s > e) {
        return nullptr;
    }
    int mid = (s + e + 1) / 2;
    TreeNode* p = new TreeNode(m[mid]);
    p->left = makeTreeLocal(m, s, mid - 1, n);
    p->right = makeTreeLocal(m, mid + 1, e, n);
    return p;
}

TreeNode* makeTree(vector<int>& m) {
    if (m.empty()) {
        return nullptr;
    }
    return makeTreeLocal(m, 0, m.size() - 1, m.size() - 1);
}
