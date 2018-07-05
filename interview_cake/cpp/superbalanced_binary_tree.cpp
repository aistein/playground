#include <iostream>
#include <climits>
#include <stack>
#include <unordered_set>

using namespace std;

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

bool isSuperbalanced(BinaryTreeNode *root) {
	stack<BinaryTreeNode *> s;
	unordered_set<BinaryTreeNode *> explored;
	int minLeafDepth, maxLeafDepth;
	int currDepth;

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
			printf("exploring leaf: %d\n", curr->value_);
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
			printf("exploring left branch: %d\n", curr->value_);
			s.push(curr->left_);
			currDepth++;
		} else if (curr->right_ != nullptr && explored.find(curr->right_) == explored.end()) {
			/* This is an unexplored right branch */
			printf("exploring right branch: %d\n", curr->value_);
			s.push(curr->right_);
			currDepth++;
		} else {
			/* This branch has been fully explored */
			printf("branch has been fully explored: %d\n", curr->value_);
			explored.insert(curr);
			s.pop();
			currDepth--;
		}
	}
	return true;
}

int main(int argc, char **argv) {
	// Make a toy tree
	BinaryTreeNode root(0);
	BinaryTreeNode *a = root.insertLeft(1);
	BinaryTreeNode *b = root.insertRight(2);
	BinaryTreeNode *c = b->insertLeft(3);
	BinaryTreeNode *d = b->insertRight(4);
	BinaryTreeNode *e = d->insertRight(5);

	printTree(&root);
	cout << isSuperbalanced(&root) << endl;

	return 0;
}
