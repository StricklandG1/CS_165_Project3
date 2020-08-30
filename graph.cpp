#include "graph.h"

Graph::Graph()
{
	numNodes = 0;
	currentId = 1;
}

Graph::Graph(int numNodes)
{
	adjList.resize(numNodes + 1);
	this->numNodes = numNodes;
	currentId = 1;
}

int Graph::get_num_nodes()
{
	return numNodes;
}

int Graph::get_num_edges()
{
	int result = 0;
	for (int i = 1; i < numNodes + 1; ++i)
	{
		result += adjList[i].size();
	}
	return result / 2; //counts each edge twice {a, b} & {b, a}
}

bool Graph::is_neighbor(Node u, Node v)
{
	std::set<Node>::const_iterator itr = adjList[u.getId()].find(v);
	return itr != adjList[u.getId()].end();
}

std::vector<Node> Graph::get_neighbors(Node u)
{
	size_t len = adjList[u.getId()].size();
	std::vector<Node> neighbors(len);

	std::set<Node>::const_iterator itr = adjList[u.getId()].cbegin();

	int i = 0;
	for (itr; itr != adjList[u.getId()].end(); ++itr)
	{
		neighbors[i] = *itr;
		++i;
	}

	return neighbors;
}

std::map<int, Node> Graph::get_id_to_node_map()
{
	std::map<int, Node> nodeMap;
	for (int i = 1; i < numNodes + 1; ++i)
	{
		nodeMap[i] = Node(i);
	}

	return nodeMap;
}

void Graph::addEdge(int u, int v)
{
	if (u != v)
	{
		Node a(u);
		Node b(v);
		adjList[u].insert(b);
		adjList[v].insert(a);
	}
}

int Graph::getCurrentId()
{
	return currentId;
}

void Graph::incrementCurrentId()
{
	++currentId;
}

Graph make_graph(int num_nodes, std::vector<int> u, std::vector<int> v)
{
	Graph g(num_nodes);
	size_t len = u.size();
	for (size_t i = 0; i < len; ++i)
	{
		g.addEdge(u[i], v[i]);
	}

	return g;
}

Graph::~Graph()
{}

std::ostream& operator<<(std::ostream& out, Graph& g)
{
	int len = g.get_num_nodes() + 1;
	for(int i = 1; i < len; ++i)
	{
		std::cout << "Vertex " << i << ": { ";
		std::set<Node>::const_iterator citr = g.adjList[i].cbegin();
		for (citr; citr != g.adjList[i].cend(); citr++)
		{
			std::cout << *citr << " ";
		}
		std::cout << "}\n";
	}
	return out;
}

