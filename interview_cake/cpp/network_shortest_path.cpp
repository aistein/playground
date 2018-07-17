#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <deque>

// C++11 lest unit testing framework
#include "lest.hpp"

using namespace std;

vector<string> makePath(const unordered_map<string, string> &parents, const string &endNode)
{
	string curr = endNode;
	deque<string> path (1, endNode);

	// build the path in forward order
	auto parent = parents.at(curr);
	while ( parent.compare(curr) != 0 ) {
		path.push_front(parent);
		curr = parent;
		parent = parents.at(curr);
	}

	// construct a vector from a deque
	return {path.begin(), path.end()};
}

vector<string> getPath(const unordered_map<string, vector<string>>& graph,
                       const string& startNode, const string& endNode)
{
    // find the shortest route in the network between the two users

	// error handling
	if (graph.find(startNode) == graph.end())
		throw domain_error("startNode not found.");
	if (graph.find(endNode) == graph.end())
		throw domain_error("endNode not found.");
	// corner case: sending a message to myself!
	if ( startNode.compare(endNode) == 0 )
		return { startNode };

	// BFS Queue
	deque<string> Q (1, startNode);

	// Unordered Map to hold parents
	// -- the startNode's parent has to be itself, so we can identify it later
	unordered_map<string, string> parents ( {{startNode, startNode}} );;

	// a single BFS post-order traversal to find the shortest path
	while ( !Q.empty() ) {

		// visit the current node
		string currNode = move(Q.front());
		Q.pop_front();

		// break out early if we've found the endNode
		if (currNode.compare(endNode) == 0)
			return makePath(parents, endNode);

		// never before visited? enqueue its children
		auto children = graph.find(currNode)->second;
		for ( const auto &child : children ) {
			// push child on the queue (only if not already visited!)
			if (parents.count(child) == 0) {
				Q.push_back(child);
				parents.insert({child, currNode});
			}
		}
	}



	// If we haven't found the endNode, then there is no path!
    return  vector<string>();
}


















// tests

unordered_map<string, vector<string>> getNetwork()
{
    return unordered_map<string, vector<string>> {
        { "a", {"b", "c", "d"} },
        { "b", {"a", "d"} },
        { "c", {"a", "e"} },
        { "d", {"a", "b"} },
        { "e", {"c"} },
        { "f", {"g"} },
        { "g", {"f"} }
    };
}

const lest::test tests[] = {
    CASE("two hop path 1") {
        const vector<string> expected {"a", "c", "e"};
        const auto actual = getPath(getNetwork(), "a", "e");
        EXPECT(actual == expected);
    },
    CASE("two hop path 2") {
        const vector<string> expected {"d", "a", "c"};
        const auto actual = getPath(getNetwork(), "d", "c");
        EXPECT(actual == expected);
    },
    CASE("one hop path 1") {
        const vector<string> expected {"a", "c"};
        const auto actual = getPath(getNetwork(), "a", "c");
        EXPECT(actual == expected);
    },
    CASE("one hop path 2") {
        const vector<string> expected {"f", "g"};
        const auto actual = getPath(getNetwork(), "f", "g");
        EXPECT(actual == expected);
    },
    CASE("one hop path 3") {
        const vector<string> expected {"g", "f"};
        const auto actual = getPath(getNetwork(), "g", "f");
        EXPECT(actual == expected);
    },
    CASE("zero hop path") {
        const vector<string> expected {"a"};
        const auto actual = getPath(getNetwork(), "a", "a");
        EXPECT(actual == expected);
    },
    CASE("no path") {
        const vector<string> expected;
        const auto actual = getPath(getNetwork(), "a", "f");
        EXPECT(actual == expected);
    },
    CASE("start node not present") {
        EXPECT_THROWS(getPath(getNetwork(), "h", "a"));
    },
    CASE("end node not present") {
        EXPECT_THROWS(getPath(getNetwork(), "a", "h"));
    }
};

int main(int argc, char** argv)
{
    return lest::run(tests, argc, argv);
}
