#include "ex6.h"
#include <iostream>

using namespace std;

int main()
{
    // 创建一个空的二叉树
    BinaryTree tree1;
    cout << "Tree1 is empty: " << tree1.isEmpty() << endl;
    cout << "Tree1 sum: " << tree1.sum() << endl;
    cout << "Tree1 depth: " << tree1.depth() << endl;
    cout << "Tree1: " << tree1 << endl;

    // 创建一个带有根节点值为10的二叉树
    BinaryTree tree2(10);
    cout << "Tree2 is empty: " << tree2.isEmpty() << endl;
    cout << "Tree2 sum: " << tree2.sum() << endl;
    cout << "Tree2 depth: " << tree2.depth() << endl;
    cout << "Tree2: " << tree2 << endl;

    // 创建一个带有子树的二叉树
    BinaryTree leftSubtree(5);
    BinaryTree rightSubtree(15);
    BinaryTree tree3(10, leftSubtree, rightSubtree);
    cout << "Tree3 sum: " << tree3.sum() << endl;
    cout << "Tree3 depth: " << tree3.depth() << endl;
    cout << "Tree3: " << tree3 << endl;

    // 创建一个更加复杂的二叉树
    BinaryTree leftSubtree2(2, BinaryTree(1), BinaryTree(3));
    BinaryTree rightSubtree2(6, BinaryTree(5), BinaryTree(7));
    BinaryTree tree6(4, leftSubtree2, rightSubtree2);
    cout << "Tree6 sum: " << tree6.sum() << endl;
    cout << "Tree6 depth: " << tree6.depth() << endl;
    cout << "Tree6: " << tree6 << endl;

    // 创建一个左右不对称的二叉树
    BinaryTree leftSubtree3(2, BinaryTree(1), BinaryTree(3));
    BinaryTree rightSubtree3(6, tree6, tree3);
    BinaryTree tree7(4, leftSubtree3, rightSubtree3);
    cout << "Tree7 sum: " << tree7.sum() << endl;
    cout << "Tree7 depth: " << tree7.depth() << endl;
    cout << "Tree7: " << tree7 << endl;

    // 测试拷贝构造函数
    BinaryTree tree4(tree3);
    cout << "Tree4 (copy of Tree3): " << tree4 << endl;

    // 测试赋值操作符
    BinaryTree tree5;
    tree5 = tree2;
    cout << "Tree5 (assigned from Tree2): " << tree5 << endl;

    // 测试相等操作符
    cout << "Tree3 == Tree4: " << (tree3 == tree4) << endl;
    cout << "Tree2 != Tree3: " << (tree2 != tree3) << endl;

    return 0;
}