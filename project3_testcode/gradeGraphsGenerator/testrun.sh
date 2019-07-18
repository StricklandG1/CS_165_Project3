#!/bin/bash
erdos_cpp="erdos_renyi.cpp"
barabasi_cpp="barabasi_albert.cpp"

# has Erdos Graph
echo "*** testrun.sh ***"
g++ main.cpp graph.cpp graph_algorithms.cpp erdos_renyi.cpp barabasi_albert.cpp
python plotgraph.py
echo "**************"