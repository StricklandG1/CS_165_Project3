#include "project3.h"
#include "graph.h"
#include "functions.h"
#include <random>
#include <fstream>
#include <string>

int get_diameter(const Graph& graph)
{
	int diameter = 0;

	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(1, graph.numNodes);

	int start = distr(eng);
	int last = 0;
	int temp = BFS_traversal(graph, start, last);

	while (temp > diameter)
	{
		start = last;
		last = 0;
		diameter = BFS_traversal(graph, start, last);
	}

	return diameter;
}

float get_clustering_coefficient(const Graph& graph)
{
	float coefficient = 0.0;

	coefficient = 3 * static_cast<float>(triangle_count(graph)) / static_cast<float>(two_edge_paths(graph));

	return coefficient;
}

std::map<int, int> get_degree_distribution(const Graph& graph)
{
	std::map<int, int> degree_dist;

	std::ofstream out_file;


	size_t len = graph.adjList.size();
	out_file.open("degree_distribution_" + std::to_string(len - 1) + ".txt", std::ofstream::app);

	for (size_t i = 1; i < len; ++i)
	{
		if (degree_dist.find(graph.adjList[i].size()) == degree_dist.end())
		{
			degree_dist[graph.adjList[i].size()] = 1;
		}
		else
		{
			++degree_dist[graph.adjList[i].size()];
		}
	}

	std::map<int, int>::const_iterator itr = degree_dist.cbegin();
	std::map<int, int>::const_iterator end = degree_dist.cend();

	for (itr; itr != end; ++itr)
	{
		out_file << itr->first << "," << itr->second << "\r\n";
	}
	return degree_dist;
}