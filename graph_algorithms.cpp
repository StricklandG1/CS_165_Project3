#include "project3.h"
#include "graph.h"
#include <fstream>
#include <string>

int get_diameter(Graph graph)
{
	int diameter = 0;

	return diameter;
}

float get_clustering_coefficient(Graph graph)
{
	float coefficient = 0.0;

	return coefficient;
}

std::map<int, int> get_degree_distribution(Graph graph)
{
	std::map<int, int> degree_dist;

	std::ofstream out_file;


	size_t len = graph.adjList.size();
	out_file.open("degree_distribution_" + std::to_string(len) + ".txt", std::ofstream::app);

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

	size_t degrees = degree_dist.size();
	for(size_t i = 0; i < degrees; ++i)
	{ 
		out_file << i << "," << degree_dist[i] << std::endl;
	}
	return degree_dist;
}