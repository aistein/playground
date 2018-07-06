#include <iostream>
#include <climits>
#include <stack>
#include <memory>
#include <unordered_set>

using namespace std;

// C++11 lest unit testing framework
#include "lest.hpp"

// Check the order of DFS exploration in VERBOSE mode
//#define VERBOSE

class BinaryTreeNode
{
public:
    int value_;
    BinaryTreeNode* left_;
    BinaryTreeNode* right_;

    BinaryTreeNode(int value) :
        value_(value),
        left_(nullptr),
        right_(nullptr)
    {
    }

    ~BinaryTreeNode()
    {
        delete left_;
        delete right_;
    }

    BinaryTreeNode* insertLeft(int value)
    {
        this->left_ = new BinaryTreeNode(value);
        return this->left_;
    }

    BinaryTreeNode* insertRight(int value)
    {
        this->right_ = new BinaryTreeNode(value);
        return this->right_;
    }
};

// Taken from https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
// recursive in-order traversal
#define COUNT 6
void printTree(BinaryTreeNode* root, int space=1) {
	// Base case
	if (root == NULL)
		return;

	// Increase distance between levels
	space += COUNT;

	// Process right child first
	printTree(root->right_, space);

	// Print current node after space count
	printf("\n");
	for (int i = COUNT; i < space; i++)
		printf(" ");
	printf("%d\n", root->value_);

	// Process left child
	printTree(root->left_, space);
}

// My solution uses a stack to implement DFS, some registers to keep track of depth,
// and an unordered_set to keep track of explored nodes.
bool isSuperbalanced(BinaryTreeNode *root) {
	stack<BinaryTreeNode *> s;
	unordered_set<BinaryTreeNode *> explored;
	int minLeafDepth, maxLeafDepth;
	int currDepth;

	// empty case: an empty tree is superbalanced!
	if (root == nullptr)
		return true;

	// initialize the stack
	s.push(root);
	currDepth = maxLeafDepth = 0;
	minLeafDepth = INT_MAX;

	while (!s.empty()) {
		BinaryTreeNode *curr = s.top();
		// if the current node has unexplored children, explore them
		// else mark as explored
		if (curr->left_ == nullptr && curr->right_ == nullptr) {
			/* This is a leaf node! */
			#ifdef VERBOSE
				printf("exploring leaf: %d\n", curr->value_);
			#endif
			if (currDepth > maxLeafDepth)
				maxLeafDepth = currDepth;
			if (currDepth < minLeafDepth)
				minLeafDepth = currDepth;
			if (maxLeafDepth - minLeafDepth > 1)
				return false;
			explored.insert(curr);
			s.pop();
			currDepth--;
		} else if (curr->left_ != nullptr && explored.find(curr->left_) == explored.end()) {
			/* This is an unexplored left branch */
			#ifdef VERBOSE
				printf("exploring left branch: %d\n", curr->value_);
			#endif
			s.push(curr->left_);
			currDepth++;
		} else if (curr->right_ != nullptr && explored.find(curr->right_) == explored.end()) {
			/* This is an unexplored right branch */
			#ifdef VERBOSE
				printf("exploring right branch: %d\n", curr->value_);
			#endif
			s.push(curr->right_);
			currDepth++;
		} else {
			/* This branch has been fully explored */
			#ifdef VERBOSE
				printf("branch has been fully explored: %d\n", curr->value_);
			#endif
			explored.insert(curr);
			s.pop();
			currDepth--;
		}
	}
	return true;
}

const lest::test tests[] = {
	CASE("Full Tree") {
		auto root = new BinaryTreeNode(5);
		root->insertLeft(8)->insertLeft(1);
		root->insertRight(6)->insertRight(4);
		root->left_->insertRight(2);
		root->right_->insertLeft(3);
		#ifdef VERBOSE
			printTree(root);
		#endif
		EXPECT(isSuperbalanced(root) == true);
	},
	CASE("Both leaves at the same depth") {
		auto root = new BinaryTreeNode(3);
		root->insertLeft(4)->insertLeft(1);
		root->insertRight(2)->insertRight(9);
		#ifdef VERBOSE
			printTree(root);
		#endif
		EXPECT(isSuperbalanced(root) == true);
	},
	CASE("Leaf heights differ by one") {
		auto root = new BinaryTreeNode(6);
		root->insertLeft(1);
		root->insertRight(0)->insertRight(7);
		#ifdef VERBOSE
			printTree(root);
		#endif
		EXPECT(isSuperbalanced(root) == true);
	},
	CASE("Leaf heights differ by two") {
		auto root = new BinaryTreeNode(6);
		root->insertLeft(1);
		root->insertRight(0)->insertRight(7)->insertRight(8);
		#ifdef VERBOSE
			printTree(root);
		#endif
		EXPECT(isSuperbalanced(root) == false);
	},
	CASE("Three leaves total") {
		auto root = new BinaryTreeNode(1);
		root->insertLeft(5);
		root->insertRight(9)->insertRight(5);
		root->right_->insertLeft(8);
		#ifdef VERBOSE
			printTree(root);
		#endif
		EXPECT(isSuperbalanced(root) == true);
	},
	CASE("Both subtrees superbalanced") {
		auto root = new BinaryTreeNode(1);
		root->insertLeft(5);
		root->insertRight(9)->insertRight(5);
		root->right_->insertLeft(8)->insertLeft(7);
		#ifdef VERBOSE
			printTree(root);
		#endif
		EXPECT(isSuperbalanced(root) == false);
	},
	CASE("Only one node") {
		auto root = new BinaryTreeNode(1);
		#ifdef VERBOSE
			printTree(root);
		#endif
		EXPECT(isSuperbalanced(root) == true);
	},
	CASE("Linked list tree") {
		auto root = new BinaryTreeNode(1);
		root->insertRight(2)->insertRight(3)->insertRight(4);
		EXPECT(isSuperbalanced(root) == true);
	},
};

int main(int argc, char** argv)
{
    return lest::run(tests, argc, argv);
}
