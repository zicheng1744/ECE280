#include "p2.h"
#include <iostream>
#include <cassert>

using namespace std;

/*
In all of the recuisions, I think two things should be noticed:
First, how can we move forward? How can I get to the right place?
Second, when I move back using return, what should I moldify to get the right answer?

There are also two ways to build a recursion:
The first one I named it as "While" recursion.
In this kind of recursion, we replaced the while loop with a recursion. In other words, we use a recursion help function to do the things in a while loop and move forward step by step.
The second one I named it as "Pure Recursion".
In this kind, we will meet troubles when using while because we don't no turn left or right in the binary tree. But a recursion will fix the problem as it will always choose the right way to go.
*/

// EFFECTS: Returns the number of elements in "list".
//          Returns zero if "list" is empty.
int size(list_t list)
{
    if (list_isEmpty(list))
    {
        return 0;
    }
    else
    {
        return 1 + size(list_rest(list));
    }
}

// EFFECTS: Returns true if the value "val" appears in "list".
//          Returns false otherwise.
bool memberOf(list_t list, int val)
{
    if (list_isEmpty(list))
    {
        return false;
    }
    else if (list_first(list) == val)
    {
        return true;
    }
    else
    {
        return memberOf(list_rest(list), val);
    }
}

// REQUIRES: Both "v1" and "v2" are non-empty
//
// EFFECTS: Treats both lists as vectors. Returns the dot
//          product of the two vectors. If one list is longer
//          than the other, ignore the longer part of the vector.
int dot(list_t v1, list_t v2)
{
    if (list_isEmpty(v1) || list_isEmpty(v2))
    {
        return 0;
    }
    else
    {
        return list_first(v1) * list_first(v2) + dot(list_rest(v1), list_rest(v2));
    }
}

// EFFECTS: Checks if the list of integers is increasing.
//          A list is increasing if and only if no element
//          is smaller than its previous element. By default,
//          an empty list and a list of a single element are
//          increasing.
//
//          For example: (), (2), (1, 1), and (1, 2, 3, 3, 5) are
//          all increasing. (2, 1) and (1, 2, 3, 2, 5) are not.
bool isIncreasing(list_t v)
{
    // test the first two elements
    if (list_isEmpty(v) || list_isEmpty(list_rest(v)))
    {
        return true;
    }
    else if (list_first(v) > list_first(list_rest(v)))
    {
        return false;
    }
    else
    {
        // move a step forward
        return isIncreasing(list_rest(v));
    }
}

// EFFECTS: Returns the reverse of "list".
//
//          For example: the reverse of ( 3 2 1 ) is ( 1 2 3 ).
static list_t reverse_helper(list_t list, list_t reversed)
{
    if (list_isEmpty(list))
    {
        return reversed;
    }
    else
    {
        // store the first element to the bottom of another list
        return reverse_helper(list_rest(list), list_make(list_first(list), reversed));
    }
}
list_t reverse(list_t list)
{
    list_t reversed = list_make();
    return reverse_helper(list, reversed);
}

// EFFECTS: Returns the list (first second).
//
//          For example: append(( 2 4 6 ), ( 1 3 )) gives
//          the list ( 2 4 6 1 3 ).
list_t append(list_t first, list_t second)
{
    if (list_isEmpty(first))
    {
        return second;
    }
    else
    {
        // based on the second list, add elements from the bottom of the first list
        return list_make(list_first(first), append(list_rest(first), second));
    }
}

// EFFECTS: Checks if the list of integers forms an
//          arithmetic sequence. By default, an empty list and
//          a list of a single element are arithmetic sequences.
//
//          For example: (), (1), (1, 3, 5, 7), and (2, 8, 14, 20)
//          are arithmetic sequences. (1, 2, 4), (1, 3, 3),
//          and (2, 4, 8, 10) are not.
static bool ArithmeticHelper(list_t v, int diff)
{
    if (list_isEmpty(v) || list_isEmpty(list_rest(v)))
    {
        return true;
    }
    else if (list_first(v) + diff != list_first(list_rest(v)))
    {
        return false;
    }
    else
    {
        return ArithmeticHelper(list_rest(v), diff);
    }
}
bool isArithmeticSequence(list_t v)
{
    // test the first two elements
    if (list_isEmpty(v) || list_isEmpty(list_rest(v)))
    {
        return true;
    }
    else
    {
        return ArithmeticHelper(list_rest(v), list_first(list_rest(v)) - list_first(v));
    }
}

// EFFECTS: Returns a new list containing only the elements of the
//          original "list" which are odd in value,
//          in the order in which they appeared in list.
//
//          For example, if you apply filter_odd to the list
//          ( 3 4 1 5 6 ), you would get the list ( 3 1 5 ).
static list_t filter_odd_helper(list_t list, list_t odd)
{
    if (list_isEmpty(list))
    {
        return odd;
    }
    else if (list_first(list) % 2 != 0)
    {
        // if the element is odd, add it to the bottom of the list
        list_make(list_first(list), odd);
    }
    // if the element is even, ignore it
    return filter_odd_helper(list_rest(list), odd);
}
list_t filter_odd(list_t list)
{
    list_t odd = list_make();
    return filter_odd_helper(list, odd);
}

// EFFECTS: Returns a list containing precisely the elements of "list"
//          for which the predicate fn() evaluates to true, in the
//          order in which they appeared in list.
//
//          For example, if predicate bool odd(int a) returns true
//          if a is odd, then the function filter(list, odd) has
//          the same behavior as the function filter_odd(list).
list_t filter(list_t list, bool (*fn)(int))
{
    if (list_isEmpty(list))
    {
        return list_make();
    }
    else if (fn(list_first(list)))
    {
        return list_make(list_first(list), filter(list_rest(list), fn));
    }
    else
    {
        return filter(list_rest(list), fn);
    }
}

// EFFECTS: Returns a new list comprising of each unique element
//          in "list". The order is determined by the first
//          occurrence of each unique element in "list".
//
//          For example, if you apply unique to the list
//          (1 1 2 1 3 5 5 3 4 5 4), you would get (1 2 3 5 4).
//          If you apply unique to the list (0 1 2 3), you would
//          get (0 1 2 3)

list_t unique(list_t list)
{
    if (list_isEmpty(list))
    {
        // don't make a list until all the element is checked
        return list_make();
    }
    else
    {
        if (memberOf(list_rest(list), list_first(list)))
        {
            return unique(list_rest(list));
        }
        else
        {
            // add the elements from back to forth
            // therefore, the first element is the last element in the stack, which is the first element in the list
            return list_make(list_first(list), unique(list_rest(list)));
        }
    }
}

// REQUIRES: n <= the number of elements in "first".
//
// EFFECTS: Returns a list comprising the first n elements of
//          "first", followed by all elements of "second",
//          followed by any remaining elements of "first".
//
//          For example: insert(( 1 2 3 ), ( 4 5 6 ), 2)
//          gives ( 1 2 4 5 6 3 ).
list_t insert_list(list_t first, list_t second, unsigned int n)
{
    if (n == 0)
    {
        // when n=0, take the second list as a whole and append the rest of the first list to it and return a combination of the two
        return append(second, first);
    }
    else
    {
        // move forward by take the first element from the first list out and implement the the rest of the list with n-1
        // when recursion go back from n=0, the element that has been taken out will be added to the second list from back to forth
        return list_make(list_first(first), insert_list(list_rest(first), second, n - 1));
    }
}

// REQUIRES: "list" has at least n elements.
//
// EFFECTS: Returns the list equal to "list" without its last n
//          elements.
list_t chop(list_t list, unsigned int n)
{
    if (n == 0)
    {
        // when n=0, return the whole list
        return list;
    }
    else if (n == static_cast<unsigned int>(size(list)))
    {
        // when n is equal to the size of the list, build an empty list and stack all the elements from back to forth
        return list_make();
    }
    else
    {
        // move forward without the first element while we still have n elements to remove
        return list_make(list_first(list), chop(list_rest(list), n));
    }
}

// EFFECTS: Returns the sum of all elements in "tree".
//          Returns zero if "tree" is empty.
int tree_sum(tree_t tree)
{
    if (tree_isEmpty(tree))
    {
        return 0;
    }
    else
    {
        return tree_elt(tree) + tree_sum(tree_left(tree)) + tree_sum(tree_right(tree));
    }
}

// EFFECTS: Returns true if the value "val" appears in "tree".
//          Returns false otherwise.
bool tree_search(tree_t tree, int val)
{
    if (tree_isEmpty(tree))
    {
        return false;
    }
    else if (tree_elt(tree) == val)
    {
        return true;
    }
    else
    {
        return tree_search(tree_left(tree), val) || tree_search(tree_right(tree), val);
    }
}

// EFFECTS: Returns the depth of "tree", which equals the number of
//          layers of nodes in the tree.
//          Returns zero if "tree" is empty.
//
// For example, the tree
//
// has depth 4.
// The element 4 is on the first layer.
// The elements 2 and 5 are on the second layer.
// The elements 3 and 8 are on the third layer.
// The elements 6 and 7 are on the fourth layer.
//
int depth(tree_t tree)
{
    if (tree_isEmpty(tree))
    {
        return 0;
    }
    else
    {
        // for every tree node, we always get a max value from the left and right subtree
        return 1 + max(depth(tree_left(tree)), depth(tree_right(tree)));
    }
}

// REQUIRES: "tree" is non-empty.
//
// EFFECTS: Returns the largest element in "tree".
int tree_max(tree_t tree)
{
    if (tree_isEmpty(tree))
    {
        return 0;
    }
    int max_val = tree_elt(tree);
    // from down to top, get the max value, just like a football game, two compete and one wins
    if (!tree_isEmpty(tree_left(tree)))
    {
        max_val = max(max_val, tree_max(tree_left(tree)));
    }
    if (!tree_isEmpty(tree_right(tree)))
    {
        max_val = max(max_val, tree_max(tree_right(tree)));
    }
    return max_val;
}

// EFFECTS: Returns the elements of "tree" in a list using an
//          in-order traversal. An in-order traversal prints
//          the "left most" element first, then the second-left-most,
//          and so on, until the right-most element is printed.
//
//          For any node, all the elements of its left subtree
//          are considered as on the left of that node and
//          all the elements of its right subtree are considered as
//          on the right of that node.
list_t traversal(tree_t tree)
{
    if (tree_isEmpty(tree))
    {
        return list_make();
    }
    else
    {
        // build from right to left
        // empty list is on the right thus on the bottom.
        // for every node, we always build the list from right and add the current value and then add the left subtree which makes the left subtree on the top of the list
        return append(traversal(tree_left(tree)), list_make(tree_elt(tree), traversal(tree_right(tree))));
    }
}

// EFFECTS: Returns true if and only if "tree" has at least one
//          root-to-leaf path such that all the elements along the
//          path form a monotonically increasing or decreasing
//          sequence.
//
//          A root-to-leaf path is a sequence of elements in a tree
//          starting with the root element and proceeding downward
//          to a leaf (an element with no children).
//
//          An empty tree has no root-to-leaf path.
//
//          A monotonically increasing (decreasing) sequence is a
//          sequence of numbers where no number is smaller (larger)
//          than its previous number.
static bool tree_increase(tree_t tree)
{
    if (tree_isEmpty(tree))
    {
        return false;
    }
    if (tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree)))
    {
        return true;
    }
    bool left_path = !tree_isEmpty(tree_left(tree)) && tree_elt(tree) < tree_elt(tree_left(tree)) && tree_increase(tree_left(tree));
    bool right_path = !tree_isEmpty(tree_right(tree)) && tree_elt(tree) < tree_elt(tree_right(tree)) && tree_increase(tree_right(tree));
    return left_path || right_path;
}

static bool tree_decrease(tree_t tree)
{
    if (tree_isEmpty(tree))
    {
        return false;
    }
    if (tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree)))
    {
        return true;
    }
    bool left_path = !tree_isEmpty(tree_left(tree)) && tree_elt(tree) > tree_elt(tree_left(tree)) && tree_decrease(tree_left(tree));
    bool right_path = !tree_isEmpty(tree_right(tree)) && tree_elt(tree) > tree_elt(tree_right(tree)) && tree_decrease(tree_right(tree));
    return left_path || right_path;
}

bool tree_hasMonotonicPath(tree_t tree)
{
    // If one subtree is empty, return false; if both subtree are empty which means the current node is a leaf, return true
    // If tree node is bigger than subtree node, return true
    // If the former two all return true, we continuously check the left and right subtree until the leaf node
    // for all the nodes, we use OR gate to connect them, if one of them is true, return true
    return tree_increase(tree) || tree_decrease(tree);
}

// REQUIRES: tree is not empty
//
// EFFECTS: Returns true if and only if for each root-to-leaf
//          path of "tree", the sum of all elements along the path
//          is greater than "sum".
//
//          A root-to-leaf path is a sequence of elements in a tree
//          starting with the root element and proceeding downward
//          to a leaf (an element with no children).
bool tree_allPathSumGreater(tree_t tree, int sum)
{
    if (tree_isEmpty(tree))
    {
        return true;
    }
    if (tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree)))
    {
        return tree_elt(tree) > sum;
    }
    // compared with hasMonotonicPath, we use AND gate to connect the left and right subtree
    // because we need to check all the path, if one of them is false, return false
    // every time we move forward by subtract the current value from the sum
    return tree_allPathSumGreater(tree_left(tree), sum - tree_elt(tree)) && tree_allPathSumGreater(tree_right(tree), sum - tree_elt(tree));
}

// EFFECTS: Returns true if tree A is covered by tree B.
bool covered_by(tree_t A, tree_t B)
{
    if (tree_isEmpty(A))
    {
        return true;
    }
    if (tree_isEmpty(B))
    {
        return false;
    }
    if (tree_elt(A) != tree_elt(B))
    {
        return false;
    }
    // check all the elements one by one
    // for every node, we first check A
    // if A is empty, there is no need to check B
    // but if A is not empty, whatever B is except for empty, we can always return false
    // if both of them are not empty, then we check if they are equal
    // whenever there is a false, all the recursion should return false which leads to the AND gate
    return covered_by(tree_left(A), tree_left(B)) && covered_by(tree_right(A), tree_right(B));
}

// EFFECTS: Returns true if tree A is covered by tree B
//          or a subtree of B.
bool contained_by(tree_t A, tree_t B)
{
    if (depth(A) > depth(B))
    {
        return false;
    }
    // first we use covered_by to check if A is covered by B
    // if not, we check if A is covered by the left or right subtree of B
    // until the depth of A is greater than B, we can give in and return false
    return covered_by(A, B) || contained_by(A, tree_left(B)) || contained_by(A, tree_right(B));
}

// REQUIRES: "tree" is a sorted binary tree.
//
// EFFECTS: Returns a new tree with elt inserted as a leaf such that
//          the resulting tree is also a sorted binary tree.
//
// For example, inserting 1 into the tree:
//
tree_t insert_tree(int elt, tree_t tree)
{
    if (tree_isEmpty(tree))
    {
        return tree_make(elt, tree_make(), tree_make());
    }
    // the tree builds from bottom to the top
    // first we should know where to build the new element
    // so we do the following algorithm
    // if the element is smaller than the current node, we choose the left subtree as a new node and do the thing recursively
    // for the right, do the same thing
    // finally, we can get the right place to insert the new element
    // then we build a new tree with thr new element
    // on the way back to the top, we should append another tree that we haven't choose in the former step
    // Therefore, in every recuision, we should build a new path and append the other path to it.
    if (elt < tree_elt(tree))
    {
        return tree_make(tree_elt(tree), insert_tree(elt, tree_left(tree)), tree_right(tree));
    }
    else
    {
        return tree_make(tree_elt(tree), tree_left(tree), insert_tree(elt, tree_right(tree)));
    }
}