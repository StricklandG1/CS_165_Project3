

#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <ctime>
#include <string>
#include "project3.h"
#include "graph.h"


int size;
int nNode, nEdge;
std::vector<int> u, v;
Graph graph;
std::map<int, Node> id_to_node;

void testMessage(std::string s)
{
    std::cout << s << "\n";
}

enum GRAPH {COMPLETE, BALANCEDTREE, BARABASI, ERDOS, LAST};

void readGraph(std::string fname){
	int tnum;
	FILE *f = fopen(fname.c_str(), "r");
	fscanf(f, "%d\t%d\n", &nNode, &nEdge);
	
	u.clear();	
	v.clear();

	for(int i=0;i<nEdge;i++){
		fscanf(f, "%d\t", &tnum);
		u.push_back(tnum);
	}
	for(int i=0;i<nEdge;i++){
		fscanf(f, "%d\t", &tnum);
		v.push_back(tnum);
	}
	
	fclose(f);
	return ;
}

bool test_vectors_have_same_nodes(std::vector<Node> nodes1, std::vector<Node> nodes2)
{
    sort(nodes1.begin(), nodes1.end(), [](const Node& u, const Node& v){return u.id < v.id;});
    sort(nodes2.begin(), nodes2.end(), [](const Node& u, const Node& v){return u.id < v.id;});
    return nodes1 == nodes2;
}


/* 
Function Overview:
	1. diameter;
	2. average clustering coefficient;
	3. is_neighboor function;
	4. get_neighboor function;
	5. degree distribution.
*/
void testGraphMethods(std::string fname){
	FILE *f = fopen(fname.c_str(), "r");
	std::vector<int> tNodeU, tNodeV;
	std::vector<Node> ngb, ngbRead;
	int len,idx,u,v, intIsNeighRead, first, second;
	bool isNeigh, isNeighRead, isError;


	/* diameter
	*/
	int diam, diamRead;
	fscanf(f, "%d\n", &diamRead);
	testMessage("Testing graph returns get_diameter() == "+std::to_string(diamRead));
	diam = get_diameter(graph);
	if(diam != diamRead) testMessage("* Error: get_diameter func = "+std::to_string(diam));


	/* average clustering coefficient
	*/
    float coef, coefRead;
    fscanf(f, "%f\n", &coefRead);
	testMessage("Testing graph returns get_clustering_coefficient() == "+std::to_string(coefRead));
	coef = get_clustering_coefficient(graph);
    if((coef-coefRead)*(coef-coefRead)>0.00004) testMessage("* Error: get_clustering_coefficient func = "+std::to_string(coef));


	/* is_neighboor 
	*/
	testMessage("Testing graph returns is_neighbor()");
	fscanf(f, "%d\n", &len);
	// read random <U,V> array
    for(int i=0;i<len; i++){
    	fscanf(f, "%d\t", &u);
    	fscanf(f, "%d\t", &v);
    	tNodeU.push_back(u);
    	tNodeV.push_back(v);
    }
    // read results
    isError = false;
    for(int i=0; i<len; i++){
        fscanf(f, "%d\t", &intIsNeighRead);

        if(!isError){
            isNeighRead = intIsNeighRead;
            isNeigh = graph.is_neighbor(id_to_node[tNodeU[i]], id_to_node[tNodeV[i]]);
            if(isNeigh != isNeighRead){
                testMessage("* Error: is_neighboor func");
                isError = true;
            }
        }
    }


    /* get_neighboor
    */
    testMessage("Testing graph returns get_neighbors()");
	tNodeU.clear();
    isError = false;
    fscanf(f, "%d\n", &len);
    // read random <U> array
    for(int i=0;i<len;i++){ 
    	fscanf(f, "%d\t", &u);
    	tNodeU.push_back(u);
    }
    // test neighboors for each element in the <U> array;
    int ngbSizeRead, ngbSize;
    isError = false;

    for(int i=0;i<len;i++){
    	fscanf(f, "%d\t", &ngbSizeRead);
        ngbRead.clear();
    	for(int j=0;j<ngbSizeRead;j++){
    		fscanf(f, "%d\t", &v);
    		ngbRead.push_back(id_to_node[v]);
    	}

        if(!isError){
        	ngb = graph.get_neighbors(id_to_node[tNodeU[i]]);
        	ngbSize = int(ngb.size());

        	if(ngbSizeRead != ngbSize){
        		testMessage("* Error: get_neighbors func");
                isError = true;
        	} else { 
                if(!test_vectors_have_same_nodes(ngb, ngbRead)){
                    testMessage("* Error: get_neighbors func");
                    isError = true;
                }
            }
        }
    }


    /* std::map<int, int> get_degree_distribution(Graph graph);
    */
    testMessage("Testing graph returns get_degree_distribution()");
    std::map<int, int> degDist = get_degree_distribution(graph), degDistRead;    
    fscanf(f, "%d\n", &len);
    for(int i=0; i<len; i++){
    	fscanf(f,"%d\t%d\t", &first, &second);
     	degDistRead[first] = second;   	
    }

    // clean the distribution map
	for (std::map<int,int>::iterator it=degDist.begin(); it!=degDist.end();){
		if(it->second==0) it = degDist.erase(it);
		else it++;
	}

    if(degDist!= degDistRead){
    	testMessage("* Error: get_degree_distribution func");

//    	std::cout<<degDist.size()<<" vs "<<degDistRead.size()<<"\n";
//		for (std::map<int,int>::iterator it=degDist.begin(); it!=degDist.end(); ++it)
//			std::cout << it->first << " => " << it->second << '\n';
//		testMessage("++++++");
//		for (std::map<int,int>::iterator it=degDistRead.begin(); it!=degDistRead.end(); ++it)
//			std::cout << it->first << " => " << it->second << '\n';
    }

    fclose(f);
    return ;
}


void testGraph(GRAPH gg){
	std::string graphname, gfile;
	switch(gg){
		case COMPLETE:	
			graphname.assign("Complete Graph"); 
			gfile.assign("completeGraph");	
			break;
		case BALANCEDTREE:	
			graphname.assign("Balanced Tree Graph"); 
			gfile.assign("balancedtreeGraph");	
			break;
		case BARABASI: 
			graphname.assign("Barabasi-Albert Random Graph"); 
			gfile.assign("barabasiGraph");
			break;
		case ERDOS:	
			graphname.assign("Erdos-Renyi Random Graph"); 
			gfile.assign("erdosGraph");
			break;
	}

	readGraph(gfile+".txt");
	testMessage(std::string("*******************************************"));
	std::cout<<"Testing "<<graphname<<" :"<<nNode<<" nodes; "<<nEdge<<" edges."<<std::endl;
	testMessage(std::string("*******************************************"));
	graph = make_graph(nNode, u, v);
	testMessage("Testing graph returns get_num_nodes() == "+std::to_string(nNode));
    if (graph.get_num_nodes() != nNode) testMessage("* Error: get_num_nodes func = "+std::to_string(graph.get_num_nodes()));
    testMessage("Testing graph returns get_num_edges() == "+std::to_string(nEdge));
    if (graph.get_num_edges() != nEdge) testMessage("* Error: get_num_edges func = "+std::to_string(graph.get_num_edges()));
    
    id_to_node = graph.get_id_to_node_map(); 
    testGraphMethods("sol"+gfile+".txt");
    std::cout<<std::endl;

}

int main() {

	for(int gg = GRAPH::COMPLETE; gg!=GRAPH::LAST; gg++){
		testGraph((GRAPH)gg);
	}

  return 0;
}
