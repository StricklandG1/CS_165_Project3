#include "functions.h"
#include "project3.h"
#include <fstream>
#include <list>
#include <queue>

int BFS_traversal(const Graph& g, int start, int& last)
{
	int* distance = new int[g.numNodes + 1];
	for (int i = 0; i < g.numNodes + 1; ++i)
	{
		distance[i] = SHRT_MAX;
	}

	distance[start] = 0;
	last = 0;
	std::queue<int> q;

	int len = g.numNodes + 1;
	bool* visited = new bool[len];
	for (int i = 1; i < len; ++i)
	{
		visited[i] = 0;
	}

	int total_visited = 0;
	q.push(start);
	visited[start] = 1;
	while (!q.empty() && total_visited < len)
	{
		int next = q.front();
		q.pop();
		int num_visited = 0;

		if (next == last)
		{
			distance++;
		}
		
		//std::cout << "V: " << next << " { ";

		std::set<Node>::const_iterator itr = g.adjList[next].cbegin();
		std::set<Node>::const_iterator end = g.adjList[next].cend();
		for (itr; itr != end; ++itr)
		{
			if (!visited[itr->id])
			{
				++num_visited;
				++total_visited;
				q.push(itr->id);
				visited[itr->id] = 1;
				distance[itr->id] = (1 + distance[next]);
				last = itr->id;
				//std::cout << last << "  ";
			}
		}
		//std::cout << "} " << "last: " << last << std::endl;
	}

	delete[] visited;

	
	int max_dist = find_max_dist(distance, g.numNodes + 1);
	return max_dist;
}

int find_max_dist(int* distances, int size)
{
	int max = 0;

	for (int i = 0; i < size; ++i)
	{
		max = (distances[i] > max) ? distances[i] : max;
	}

	return max;
}

int triangle_count(const Graph& g)
{
	int count = 0;
	std::vector<std::list<int>> N_v(g.numNodes + 1);
	std::list<int> d = degeneracy_order(g, N_v);

	std::list<int>::const_iterator itr = d.cbegin();
	std::list<int>::const_iterator end = d.cend();

	for (itr; itr != end; ++itr)
	{
		std::list<int>::const_iterator v_adj = N_v[*itr].cbegin();
		std::list<int>::const_iterator v_adj_end = N_v[*itr].cend();

		for (v_adj; v_adj != v_adj_end; ++v_adj)
		{
			std::list<int>::const_iterator current = v_adj;
			++current;
			for (current; current != v_adj_end; ++current)
			{
				if (g.adjList[*v_adj].find(*current) != g.adjList[*v_adj].end())
					++count;
			}
		}
	}


	return count;
}

int two_edge_paths(const Graph& g)
{
	int count = 0;

	size_t len = g.numNodes;

	for (int i = 1; i < len + 1; ++i)
	{
		count += g.adjList[i].size() * g.adjList[i].size() - 1 / 2;
	}

	return count;
}

std::list<int> degeneracy_order(const Graph& g, std::vector<std::list<int>>& N_v)
{
	std::list<int> L;
	std::vector<bool> H_L(g.numNodes + 1, 0);
	int* d_v = new int[g.numNodes + 1];
	size_t len = g.numNodes + 1;
	int max = 0;
	for (size_t i = 0; i < len; ++i)
	{
		d_v[i] = g.adjList[i].size();
		max = (max > d_v[i]) ? max : d_v[i];
	}

	std::vector<std::list<int>> D(max + 1);
	for (size_t i = 0; i < len; ++i)
	{
		D[d_v[i]].push_back(i);
	}

	//std::vector<std::list<int>> N_v(len);

	for (size_t i = 0; i < len; ++i)
	{
		int j = 0;
		while (D[j].empty() && j < (max + 1))
		{
			++j;
		}

		int v = D[j].front();
		D[j].remove(v);
		L.push_front(v);
		H_L[v] = 1;

		std::set<Node>::const_iterator itr = g.adjList[v].cbegin();
		std::set<Node>::const_iterator end = g.adjList[v].cend();

		for (itr; itr != end; ++itr)
		{
			if (!H_L[itr->id])
			{
				D[d_v[itr->id]].remove(itr->id);
				--d_v[itr->id];
				D[d_v[itr->id]].push_front(itr->id);
				N_v[v].push_front(itr->id);
			}
		}
	}

	return L;
}

void test_graph(int n)
{
	Graph g = create_barabasi_albert_graph(n, 5);

	std::ofstream out_file;

	out_file.open("diameter.txt", std::ofstream::app);
	out_file << n << "," << get_diameter(g) << std::endl;

	out_file.close();
	out_file.open("clustering_coefficient.txt", std::ofstream::app);
	out_file << n << "," << get_clustering_coefficient(g) << std::endl;

	get_degree_distribution(g);
	
}

