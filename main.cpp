#include "project3.h"
#include "graph.h"
#include "tests.h"

#include <iostream>

int main()
{
	Graph g = make_graph(3, { 1, 2, 3 }, { 3, 1, 2 });

	std::cout << g;

	std::map<int,int> deg = get_degree_distribution(g);

	size_t len = deg.size();
	for (size_t i = 1; i < len; ++i)
	{
		std::cout << deg[i];
	}

	std::cout << std::endl;
	system("pause");
	return 0;
}