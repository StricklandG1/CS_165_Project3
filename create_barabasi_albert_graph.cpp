#include "project3.h"
#include "graph.h"
#include <random>

Graph create_barabasi_albert_graph(int n, int d)
{
	Graph g(n);

	std::random_device rd;
	std::mt19937 eng(rd());

	

	int *M = new int[2 * n * d];
	int len = 2 * n * d;
	for (int i = 0; i < len; ++i)
	{
		M[i] = 0;
	}

	for (int v = 1; v < n; ++v)
	{
		for (int i = 0; i < d; ++i)
		{
			M[2 * (v * d + i)] = v;
			std::uniform_int_distribution<> distr(1, 2 * (v * d + i));

			int r = distr(eng);
			M[2 * (v * d + i) + 1] = M[r];
		}
	}

	for (int i = 0; i < n * d - 1; ++i)
	{
		g.addEdge(M[2 * i], M[2 * i + 1]);
	}
	return g;
}