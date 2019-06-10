#include "project3.h"
#include "graph.h"
#include "tests.h"
#include "functions.h"

#include <iostream>

int main()
{
	test_graph(10);

	test_graph(100);

	test_graph(1000);

	test_graph(10000);

	test_graph(100000);

	//run_tests();





	std::cout << std::endl;
	system("pause");
	return 0;
}