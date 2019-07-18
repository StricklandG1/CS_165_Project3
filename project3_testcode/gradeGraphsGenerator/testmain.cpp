


#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <ctime>
#include <string>
#include <assert.h>
#include <math.h>
#include "project3.h"
#include "graph.h"

int n = 10000, d=5;
float p = 2*log(n)/n;
Graph graph;
std::map<int, int> degDist;

void outputDegDist(std::string fname){
	FILE *f = fopen(fname.c_str(), "w");
	degDist = get_degree_distribution(graph);

	int len = degDist.size();
	fprintf(f, "%d\n", len);
	for(auto it=degDist.begin();it!=degDist.end();++it){
    	fprintf(f, "%d\t%d\t", it->first, it->second);    	
    }
    fclose(f);
}

int main(){

	std::string fname, fwname;


	std::cout<<"Generating Erdos Graph..."<<std::endl;
	fname.assign("erdos_renyi.cpp");
	if (FILE *file = fopen(fname.c_str(), "r")) {
        fclose(file);

        graph = create_erdos_renyi_graph(n,p);
        fwname.assign("ddErdos.txt");
        outputDegDist(fwname);
    } 

	std::cout<<"Generating Barabasi Graph..."<<std::endl;
	fname.assign("barabasi_albert.cpp");
	if (FILE *file = fopen(fname.c_str(), "r")) {
        fclose(file);
        
        graph = create_barabasi_albert_graph(n,d);
        fwname.assign("ddBarabasi.txt");
        outputDegDist(fwname);
    } 

    std::cout<<"Done "<<std::endl;
    return 0;
}