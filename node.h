#ifndef NODE_H
#define NODE_H

#include "project3.h"

class Node
{
	friend std::ostream& operator<<(std::ostream& out, const Node& n) { std::cout << n.id; return out; };
public:
	int id;

	Node() { id = -1; }
	Node(int newId) { id = newId; }
	int getId() { return id; } const

	bool operator==(const Node& other) const { return id == other.id; }
	bool operator<(const Node& other) const { return id < other.id; }
	
};

#endif
