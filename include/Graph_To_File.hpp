#ifndef __GRAPH_TO_FILE_HPP__
#define __GRAPH_TO_FILE_HPP__

#include <vector>
#include <cstdio>
 
#include <boost/config.hpp>

using namespace std;
using namespace boost;

#include "FileWriter.h"

template <typename Graph,typename Edge_Iterator,typename Edge_Weight_Array, typename Edge_Index_Array>
void write_graph_to_file(const char *file_name, Graph &G, bool write_edge_mapping = false)
{
	FileWriter fout(file_name, num_vertices(G), num_edges(G));

    int src, dest, weight;

    Edge_Iterator ei, ei_end;
    Edge_Weight_Array edge_weights = get(edge_weight, G);

    for (tie(ei, ei_end) = edges(G); ei != ei_end; ++ei)
    {
        src = source(*ei, G);
        dest = target(*ei, G);
        weight = edge_weights[*ei];
        if(weight == 0)
        {
            weight = rand()%500 + 1;
            edge_weights[*ei] = weight;
        }

        fout.write_edge(src, dest, weight);
    }

    FILE *foutput = fout.get_file();

    if(write_edge_mapping == true)
    {
        Edge_Index_Array edge_array = get(edge_index, G);
        for (tie(ei, ei_end) = edges(G); ei != ei_end; ++ei)
        {
            fprintf(foutput, "%d\n",edge_array[*ei]);
        }
    }
   // cout << edge_weights[*ei] << endl;

    fout.fileClose();
}

#endif