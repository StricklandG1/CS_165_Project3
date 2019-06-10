#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <list>
#include "graph.h"

int BFS_traversal(const Graph& g, int start, int& last);

int find_max_dist(int* distances, int size);

int triangle_count(const Graph& g);

int two_edge_paths(const Graph& g);

std::list<int> degeneracy_order(const Graph& g, std::vector<std::list<int>>& N_v);

void test_graph(int n);
#endif
