#include <iostream>
#include <memory>
#include <stack>

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

bool isBinarySearchTree(const BinaryTreeNode* root)
{
    // determine if the tree is a valid binary search tree

	stack<pair<pair<int, int>, const BinaryTreeNode *>> nodes;

	// the boundaries for the root node are +/- infinity
	nodes.push( make_pair( make_pair( INT_MIN, INT_MAX ), root ) );

	while ( !nodes.empty() ) {
		auto curr = nodes.top().second;
		auto currLimits = nodes.top().first;
		nodes.pop();

		// leaf node, nothing to do
		if ( !curr->left_ && !curr->right_ ) {
			// do nothing
		}
		else {
			// left branch gets limits (myLowerLimit, myValue]
			if ( curr->left_ ) {
				int leftValue = curr->left_->value_;
				auto leftLimits = make_pair( currLimits.first, curr->value_ );
				if ( leftValue >= leftLimits.first && leftValue < leftLimits.second ) {
					nodes.push( make_pair( leftLimits, curr->left_ ) );
				} else {
					return false;
				}
			}
			// right branch gets limits [myValue, myUpperLimit)
			if ( curr->right_ ) {
				int rightValue = curr->right_->value_;
				auto rightLimits = make_pair( curr->value_, currLimits.second );
				if ( rightValue > rightLimits.first && rightValue <= rightLimits.second ) {
					nodes.push( make_pair( rightLimits, curr->right_ ) );
				} else {
					return false;
				}
			}
		}
	}


    return true;
}


















// tests

const lest::test tests[] = {
    CASE("Valid full tree") {
        auto root = make_unique<BinaryTreeNode>(50);
        root->insertLeft(30)->insertLeft(10);
        root->insertRight(70)->insertRight(80);
        root->left_->insertRight(40);
        root->right_->insertLeft(60);
        EXPECT(isBinarySearchTree(root.get()) == true);
    },
    CASE("Both subtrees valid") {
        auto root = make_unique<BinaryTreeNode>(50);
        root->insertLeft(30)->insertLeft(20);
        root->insertRight(80)->insertRight(90);
        root->left_->insertRight(60);
        root->right_->insertLeft(70);
        EXPECT(isBinarySearchTree(root.get()) == false);
    },
    CASE("Descending linked list") {
        auto root = make_unique<BinaryTreeNode>(50);
        root->insertLeft(40)->insertLeft(30)->insertLeft(20)->insertLeft(10);
        EXPECT(isBinarySearchTree(root.get()) == true);
    },
    CASE("Out of order linked list") {
        auto root = make_unique<BinaryTreeNode>(50);
        root->insertRight(70)->insertRight(60)->insertRight(80);
        EXPECT(isBinarySearchTree(root.get()) == false);
    },
    CASE("One node tree") {
        auto root = make_unique<BinaryTreeNode>(50);
        EXPECT(isBinarySearchTree(root.get()) == true);
    }
};

int main(int argc, char** argv)
{
    return lest::run(tests, argc, argv);
}
