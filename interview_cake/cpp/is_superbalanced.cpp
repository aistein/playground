#include <iostream>
#include <memory>
#include <stack>
#include <unordered_set>

// C++11 lest unit testing framework
#include "lest.hpp"

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

bool isBalanced(const BinaryTreeNode* treeRoot)
{
    // determine if the tree is superbalanced
    stack<pair<const BinaryTreeNode *, int>> nodeStack;
    int minLeafDepth = INT_MAX;
    int maxLeafDepth = 0;
    int numDistinctDepths = 0;

    nodeStack.push(make_pair(treeRoot, 0));
    while (!nodeStack.empty()) {
        // get the next node from the stack
        const BinaryTreeNode *curr = nodeStack.top().first;
		int currDepth = nodeStack.top().second;
		nodeStack.pop();


		#ifdef DEBUG
		printf("-- current depth is %d\n", currDepth);
		printf("-- current node's value: %d\n", curr->value_);
		#endif

        // this is a leaf node
        if (!curr->left_ && !curr->right_) {

			#ifdef DEBUG
			printf("found a leaf!\n");
			#endif

            // first check if this is a new distinct depth
            if (numDistinctDepths == 0 || (currDepth != minLeafDepth && currDepth != maxLeafDepth))
                ++numDistinctDepths;

            // next, update min and max leaf depths
            maxLeafDepth = max(maxLeafDepth, currDepth);
            minLeafDepth = min(minLeafDepth, currDepth);

            // check termination conditions
            if ((maxLeafDepth - minLeafDepth > 1) || (numDistinctDepths > 2)) {
				#ifdef DEBUG
				printf("this tree is not superbalanced!\n\n");
				#endif

                return false;
			}
        }

        // this is not a leaf node, continue post-order traversal
        /// if the left branch exists and node isn't explored, go there
        else {
			if ( curr->left_ ) {
				#ifdef DEBUG
				printf("exploring left branch\n");
				#endif

            	nodeStack.push(make_pair(curr->left_, currDepth + 1));
			}

        	/// if the right branch exists and node isn't explored, go there
        	if ( curr->right_ ) {
				#ifdef DEBUG
				printf("exploring right branch\n");
				#endif

            	nodeStack.push(make_pair(curr->right_, currDepth + 1));
			}
		}
    }

	#ifdef DEBUG
	printf("this tree is superbalanced!\n\n");
	#endif

    return true;
}


















// tests

const lest::test tests[] = {
    CASE("Full Tree") {
        auto root = make_unique<BinaryTreeNode>(5);
        root->insertLeft(8)->insertLeft(1);
        root->insertRight(6)->insertRight(4);
        root->left_->insertRight(2);
        root->right_->insertLeft(3);
        EXPECT(isBalanced(root.get()) == true);
    },
    CASE("Both leaves at the same depth") {
        auto root = make_unique<BinaryTreeNode>(3);
        root->insertLeft(4)->insertLeft(1);
        root->insertRight(2)->insertRight(9);
        EXPECT(isBalanced(root.get()) == true);
    },
    CASE("Leaf heights differ by one") {
        auto root = make_unique<BinaryTreeNode>(6);
        root->insertLeft(1);
        root->insertRight(0)->insertRight(7);
        EXPECT(isBalanced(root.get()) == true);
    },
    CASE("Leaf heights differ by two") {
        auto root = make_unique<BinaryTreeNode>(6);
        root->insertLeft(1);
        root->insertRight(0)->insertRight(7)->insertRight(8);
        EXPECT(isBalanced(root.get()) == false);
    },
    CASE("Three leaves total") {
        auto root = make_unique<BinaryTreeNode>(1);
        root->insertLeft(5);
        root->insertRight(9)->insertRight(5);
        root->right_->insertLeft(8);
        EXPECT(isBalanced(root.get()) == true);
    },
    CASE("Both subtrees superbalanced") {
        auto root = make_unique<BinaryTreeNode>(1);
        root->insertLeft(5);
        root->insertRight(9)->insertRight(5);
        root->right_->insertLeft(8)->insertLeft(7);
        EXPECT(isBalanced(root.get()) == false);
    },
    CASE("Only one node") {
        auto root = make_unique<BinaryTreeNode>(1);
        EXPECT(isBalanced(root.get()) == true);
    },
    CASE("Linked list tree") {
        auto root = make_unique<BinaryTreeNode>(1);
        root->insertRight(2)->insertRight(3)->insertRight(4);
        EXPECT(isBalanced(root.get()) == true);
    },
};

int main(int argc, char** argv)
{
    return lest::run(tests, argc, argv);
}
