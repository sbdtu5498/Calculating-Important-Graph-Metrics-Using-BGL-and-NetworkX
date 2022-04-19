#include <boost/config.hpp>
#include <vector>
#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/betweenness_centrality.hpp>

using namespace std;
using namespace boost;

typedef boost::property<boost::edge_weight_t, double> EdgeWeight;
typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, boost::no_property, EdgeWeight> Graph;
typedef boost::graph_traits<Graph>::edge_iterator edge_iterator;

int main(int, char *[])
{
    Graph G;

    add_edge(1, 2, G);
    add_edge(2, 3, G);
    add_edge(3, 4, G);

    boost::property_map<Graph, boost::edge_weight_t>::type EdgeWeightMap = get(boost::edge_weight_t(), G);
    auto edge_centrality_map = boost::make_shared_array_property_map(num_vertices(G), 1.0, get(boost::vertex_index, G));

    std::map<Graph::edge_descriptor, double> edge_centralities;
    auto ecm = boost::make_assoc_property_map(edge_centralities);

    brandes_betweenness_centrality(G, boost::edge_centrality_map(ecm).weight_map(get(edge_weight, G)));

    int n = num_vertices(G) - 1;
    std::cout << "number of vertices: " << n << std::endl;
    int m = num_edges(G);
    std::cout << "number of edges: " << m << std::endl;

    std::pair<edge_iterator, edge_iterator> edgePair;
    for (edgePair = edges(G); edgePair.first != edgePair.second; ++edgePair.first)
    {
        double absolute_BC = edge_centralities.at(*edgePair.first);

        if (is_directed(G))
        {
            std::cout << *edgePair.first << " " << EdgeWeightMap[*edgePair.first]
                      << " absolute_BC: " << edge_centralities.at(*edgePair.first)
                      << "relative_BC: " << ((absolute_BC) / (n * n - n)) << std::endl;
        }
        else
        {
            std::cout << *edgePair.first << " " << EdgeWeightMap[*edgePair.first]
                      << " absolute_BC: " << edge_centralities.at(*edgePair.first)
                      << "relative_BC: " << (((absolute_BC) * 2) / (n * n - n)) << std::endl;
        }
    }

    std::cout << "is directed: " << is_directed(G) << '\n';

    return 0;
}