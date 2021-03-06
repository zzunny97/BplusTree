#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>

using namespace std;

// Note: You need to add additional member variables and functions as you need.

//#define NUM_KEYS 10 
#define NUM_KEYS 10
// NUM_KEYS should be set to make each tree node as large as 4KB. 
// But for this assignment, we will set the degree of node to 10 just to make debugging and grading easy
// Please do not change this number. 
// In practice, DBMS employs 'slotted page structure' to store variable-length records in B+tree.
// But again, the purpose of this assignment is to make students familiar with B-tree itself. 

enum NodeType {
	ROOT,
	INTERNAL,
	LEAF
};

class BTreeNode {   
	private:
		long long keys[NUM_KEYS];
		int num_keys;
		BTreeNode* parent;
		BTreeNode* child[NUM_KEYS+1];
		NodeType type;
	public:
		BTreeNode(NodeType _type);
		~BTreeNode() {}
		//NodeType getNodeType();
		//string getNodeType2();
		BTreeNode* sibling(bool is_left);
		void printLeafNode();
		int findIndex(long long value);
		int get_child_num();
		BTreeNode* find_last_non_null();
	friend class BTree;
};

class BTree {  
	private:
		int depth;
		BTreeNode *root;
	public:
		// You are not allowed to change the interfaces of these public methods.
		BTree() {
			root = new BTreeNode(ROOT);
			depth=1;
		}

		~BTree() {}



		void insert_in_leaf(BTreeNode* n, long long value);
		void insert_in_parent(BTreeNode* n1, long long value, BTreeNode* n2);
		void insert(long long value);

		void borrow(BTreeNode* left, BTreeNode* right, int position, bool n_idx);
		void merge(BTreeNode* left, BTreeNode* right, int position);
		void delete_entry(BTreeNode* n, long long value, int position);
		void remove(long long value);

		void print(BTreeNode* cur);
		void printAllLeafNode();


		void printLeafNode(long long value); 
		// find the leaf node that contains 'value' and print all values in the leaf node.
		void pointQuery(long long value);
		// print the found value or "NOT FOUND" if there is no value in the index
		void rangeQuery(long long low, long long high);
		// print all found key (low <= keys < high), seperated by comma
};
