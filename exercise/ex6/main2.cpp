#include "ex6.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>


int main() {
    // Test default constructor
    BinaryTree tree1;
    std::cout << "Tree 1 is empty: " << (tree1.isEmpty() ? "Yes" : "No") << std::endl;

    // Test parameterized constructor with single value
    BinaryTree tree2(10);
    std::cout << "Tree 2 is empty: " << (tree2.isEmpty() ? "Yes" : "No") << std::endl;
    std::cout << "Tree 2 (in-order): " << tree2 << std::endl;

    // Test parameterized constructor with value and subtrees
    BinaryTree leftSubtree(5);
    BinaryTree rightSubtree(15);
    BinaryTree tree3(10, leftSubtree, rightSubtree);
    std::cout << "Tree 3 (in-order): " << tree3 << std::endl;

    // Test copy constructor
    BinaryTree tree4(tree3);
    std::cout << "Tree 4 (copy of Tree 3, in-order): " << tree4 << std::endl;

    // Test assignment operator
    BinaryTree tree5;
    tree5 = tree3;
    std::cout << "Tree 5 (assigned from Tree 3, in-order): " << tree5 << std::endl;

    // Test equality and inequality operators
    std::cout << "Tree 3 == Tree 4: " << (tree3 == tree4 ? "Yes" : "No") << std::endl;
    std::cout << "Tree 3 != Tree 5: " << (tree3 != tree5 ? "Yes" : "No") << std::endl;

    // Test sum and depth
    std::cout << "Sum of Tree 3: " << tree3.sum() << std::endl;
    std::cout << "Depth of Tree 3: " << tree3.depth() << std::endl;

    // Modify Tree 4 and check equality again
    BinaryTree tree6(20);
    tree4 = BinaryTree(10, leftSubtree, tree6); // Modify right subtree of Tree 4
    std::cout << "Modified Tree 4 (in-order): " << tree4 << std::endl;
    std::cout << "Tree 3 == Tree 4: " << (tree3 == tree4 ? "Yes" : "No") << std::endl;

    // Test destructor implicitly (as objects go out of scope)

    std::cout << "All tests completed successfully!" << std::endl;

    return 0;
}