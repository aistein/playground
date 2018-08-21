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

int _findSecondLargest__R__(const BinaryTreeNode *rootNode, int secondLargestSoFar, int largestSoFar) {
	int nextSecondLargest = secondLargestSoFar;
	int nextLargest = largestSoFar;

	if ( rootNode->value_ > largestSoFar ) {
		nextLargest = rootNode->value_;
		nextSecondLargest = largestSoFar;
	}
	else if ( rootNode->value_ > secondLargestSoFar ) {
		nextSecondLargest = rootNode->value_;
	}

	if ( rootNode->right_ ) {
		return _findSecondLargest__R__(rootNode->right_, nextSecondLargest, nextLargest);
	}
	if ( rootNode->left_ ) {
		return _findSecondLargest__R__(rootNode->left_, nextSecondLargest, nextLargest);
	}
	return nextSecondLargest;
}


int _findSecondLargest__I__(const BinaryTreeNode *rootNode) {
	// Initializers
	stack<pair<pair<int,int>, const BinaryTreeNode *>> theStack;
	theStack.push( make_pair( make_pair( INT_MIN, INT_MIN ), rootNode ) );

	// walk the tree (partial to right branches)
	int largestSoFar, secondLargestSoFar, nextLargest, nextSecondLargest;
	const BinaryTreeNode *curr;
	while( !theStack.empty() ) {
		nextLargest = largestSoFar = theStack.top().first.first;
		nextSecondLargest = secondLargestSoFar = theStack.top().first.second;
		curr = theStack.top().second;
		theStack.pop();

		if ( curr->value_ > largestSoFar ) {
			nextLargest = curr->value_;
			nextSecondLargest = largestSoFar;
		}
		else if ( curr->value_ > secondLargestSoFar ) {
			nextSecondLargest = curr->value_;
		}

		if ( curr->right_ )
			theStack.push( make_pair( make_pair( nextLargest, nextSecondLargest ), curr->right_ ) );
		else if ( curr->left_ )
			theStack.push( make_pair( make_pair( nextLargest, nextSecondLargest ), curr->left_ ) );
	}

	return nextSecondLargest;
}


int findSecondLargest(const BinaryTreeNode* rootNode)
{
    // find the second largest item in the binary search tree

	// error checking
	if ( rootNode == nullptr || (!rootNode->left_ && !rootNode->right_) ) {
		throw invalid_argument("tree must have at least two nodes.");
	}

	// preprocessor directive to choose between recursive and iterative implementations
	#ifdef RECURSIVE
		return _findSecondLargest__R__(rootNode, INT_MIN, INT_MIN);
	#else
		return _findSecondLargest__I__(rootNode);
	#endif
}
















// tests

const lest::test tests[] = {
    CASE("Full tree") {
		printf("Full tree\n");
        auto root = make_unique<BinaryTreeNode>(50);
        root->insertLeft(30)->insertLeft(10);
        root->insertRight(70)->insertRight(80);
        root->left_->insertRight(40);
        root->right_->insertLeft(60);
        EXPECT(findSecondLargest(root.get()) == 70);
    },
    CASE("Largest has a left child") {
		printf("Largest has a left child\n");
        auto root = make_unique<BinaryTreeNode>(50);
        root->insertLeft(30)->insertLeft(10);
        root->insertRight(70)->insertLeft(60);
        root->left_->insertRight(40);
        EXPECT(findSecondLargest(root.get()) == 60);
    },
    CASE("Largest has a left subtree") {
		printf("Largest has a left subtree\n");
        auto root = make_unique<BinaryTreeNode>(50);
        root->insertLeft(30)->insertLeft(10);
        root->left_->insertRight(40);
        root->insertRight(70)->insertLeft(60)->insertLeft(55)->insertRight(58);
        root->right_->left_->insertRight(65);
        EXPECT(findSecondLargest(root.get()) == 65);
    },
    CASE("Second largest is root node") {
		printf("Second largest is root node\n");
        auto root = make_unique<BinaryTreeNode>(50);
        root->insertLeft(30)->insertLeft(10);
        root->insertRight(70);
        root->left_->insertRight(40);
        EXPECT(findSecondLargest(root.get()) == 50);
    },
    CASE("Descending linked list") {
		printf("Descending linked list\n");
        auto root = make_unique<BinaryTreeNode>(50);
        root->insertLeft(40)->insertLeft(30)->insertLeft(20)->insertLeft(10);
        EXPECT(findSecondLargest(root.get()) == 40);
    },
    CASE("Ascending linked list") {
		printf("Ascending linked list\n");
        auto root = make_unique<BinaryTreeNode>(50);
        root->insertRight(60)->insertRight(70)->insertRight(80);
        EXPECT(findSecondLargest(root.get()) == 70);
    },
    CASE("Exception when tree has one node") {
		printf("Exception when tree has one node\n");
        auto root = make_unique<BinaryTreeNode>(50);
        EXPECT_THROWS(findSecondLargest(root.get()));
    },
    CASE("Exception when tree is empty") {
		printf("Exception when tree is empty\n");
        EXPECT_THROWS(findSecondLargest(nullptr));
    },
};

int main(int argc, char** argv)
{
    return lest::run(tests, argc, argv);
}
