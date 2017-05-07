#pragma once
#include <vector>
#include <string>

using namespace std;
class Tree {
public:

	struct Leaf {
		string name;
		Leaf* parent = nullptr;
		Leaf* child = nullptr;
		Leaf* next = nullptr;
		void* data = nullptr;

		Leaf(string _name, void* _data) {
			data = _data;
			name = _name;
		}
	};

	Leaf* root = nullptr;

	Tree(const string& rootName, void* rootData) {
		Leaf* newLeaf = new Leaf(rootName, rootData);
		root = newLeaf;
	}  

	~Tree() {
		root = nullptr;
		clear();
	}

	void addNode(const string& name, void* newData) {
		Leaf* newLeaf = new Leaf(name, newData);
		pairNode(newLeaf, root);

	}

	void addNodeAsChild(const string& name, void* newData, Leaf* parent) {
		Leaf* newLeaf = new Leaf(name, newData);
		pairNode(newLeaf, parent);
	}

	Leaf* findNode(const string& name) {
		if (name == "root")
			return root;
		else
			return findNodeInChildren(root, name);
	}

	Leaf* findNodeInChildren(Leaf* parent, const string& name) {
		Leaf* itr = parent->child;
		while (itr != parent) {
			if (itr->name == name)
				return itr;
			else if (itr->child != nullptr)
				itr = itr->child;
			else if (itr->next != nullptr)
				itr = itr->next;
			else {
				Leaf* itr2 = itr->parent;
				while (itr2 != parent) {
					if (itr2->parent->next != nullptr) {
						itr = itr2->parent->next;
						break;
					}
					else {
						itr2 = itr2->parent;
					}
				}
				return nullptr;
			}
		}
	}

	void findAndRemoveNode(const string& name) {
		Tree::Leaf* leaf = findNodeInChildren(root, name);
		Tree::Leaf* itr = leaf->child;
		while (itr != nullptr) {
			itr->parent = itr->parent->parent;
			Tree::Leaf* tmp = itr;
			itr = itr->next;
			tmp = nullptr;
		}
		leaf->child = nullptr;
		leaf->parent->child = leaf->next;
		leaf->next = nullptr;
	}

	void clear() {
		
	}

	void pairNode(Leaf* newNode, Leaf* parent) {
		if (parent->child == nullptr) {
			parent->child = newNode;
			newNode->parent = parent;
		}
		else {
			Leaf* itr = parent->child;
			while (itr->next != nullptr)
				itr = itr->next;
			itr->next = newNode;
			newNode->parent = parent;
		}
	}
};






