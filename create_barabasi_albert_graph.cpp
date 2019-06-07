#include "project3.h"
#include "graph.h"

Graph create_barabasi_albert_graph(int n, int d)
{
	Graph g(n);

	short *M = new short[2 * n * d];
	int len = 2 * n * d;
	for (int i = 0; i < len; ++i)
	{
		M[i] = 0;
	}


	return g;
}