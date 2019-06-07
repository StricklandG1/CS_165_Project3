#ifndef GRAPH_H
#define GRAPH_H

#include <set>
#include <iostream>
#include <unordered_map>
#include "node.h"

class Graph : public AbstractGraph
{
	friend std::ostream& operator<<(std::ostream& out, Graph& g);
public:
	Graph();
	Graph(int numNodes);
	int get_num_nodes(); // number of nodes
	int get_num_edges(); // number of edges
	bool is_neighbor(Node u, Node v);
	std::vector<Node> get_neighbors(Node u);

	std::map<int, Node> get_id_to_node_map();

	void addEdge(int u, int v);

	int getCurrentId();

	void incrementCurrentId();

	~Graph();

	int currentId;
	std::vector<std::set<Node>> adjList;
	int numNodes;
};

#endif
