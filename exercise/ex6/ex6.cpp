#include "ex6.h"

using namespace std;

BinaryTree::BinaryTree() : root(nullptr) {}

BinaryTree::BinaryTree(int val) : root(new TreeNode{val, nullptr, nullptr}) {}

BinaryTree::BinaryTree(int val, const BinaryTree &left, const BinaryTree &right)
    : root(new TreeNode{val, copy(left.root), copy(right.root)}) {}

BinaryTree::BinaryTree(const BinaryTree &other) : root(copy(other.root)) {}

BinaryTree &BinaryTree::operator=(const BinaryTree &other)
{
    if (this != &other)
    {
        removeAll(root);
        root = copy(other.root);
    }
    return *this;
}

BinaryTree::~BinaryTree() { removeAll(root); }

bool BinaryTree::operator==(const BinaryTree &other) const
{
    return equal(root, other.root);
}

bool BinaryTree::operator!=(const BinaryTree &other) const
{
    return !equal(root, other.root);
}

bool BinaryTree::isEmpty() const { return root == nullptr; }

int BinaryTree::sum() const
{
    // we need a helper function here to do the recursion
    return sumHelper(root);
}

// helper function in the same way as p2
int BinaryTree::sumHelper(TreeNode *root) const
{
    if (root == nullptr)
    {
        return 0;
    }
    return root->val + sumHelper(root->left) + sumHelper(root->right);
}

int BinaryTree::depth() const
{
    // we need a helper function here to do the recursion
    return depthHelper(root);
}

// helper function in the same way as p2
int BinaryTree::depthHelper(TreeNode *root) const
{
    if (root == nullptr)
    {
        return 0;
    }
    return 1 + max(depthHelper(root->left), depthHelper(root->right));
}

TreeNode *BinaryTree::copy(TreeNode *root)
{
    if (root == nullptr)
    {
        return nullptr;
    }
    // we need to copy the left and right subtree recursively
    return new TreeNode{root->val, copy(root->left), copy(root->right)};
}

void BinaryTree::removeAll(TreeNode *root)
{
    if (root != nullptr)
    {
        // we need to remove the left and right subtree recursively
        removeAll(root->left);
        removeAll(root->right);
        delete root;
    }
}

bool BinaryTree::equal(TreeNode *root1, TreeNode *root2) const
{
    if (root1 == nullptr && root2 == nullptr) // both are nullptr
    {
        return true;
    }
    else if (root1 == nullptr || root2 == nullptr) // only one is nullptr
    {
        return false;
    }
    // both are not nullptr
    return root1->val == root2->val && equal(root1->left, root2->left) && equal(root1->right, root2->right);
}

ostream &operator<<(ostream &os, const BinaryTree &tree)
{
    // we need a helper function here to do the recursion
    // delete the last space
    return os << tree.tranversal(tree.root).substr(0, tree.tranversal(tree.root).size() - 1);
}

string BinaryTree::tranversal(TreeNode *root) const
{
    if (root == nullptr)
    {
        return "";
    }
    // we need to tranverse the left and right subtree recursively
    return tranversal(root->left) + to_string(root->val) + " " + tranversal(root->right);
}
