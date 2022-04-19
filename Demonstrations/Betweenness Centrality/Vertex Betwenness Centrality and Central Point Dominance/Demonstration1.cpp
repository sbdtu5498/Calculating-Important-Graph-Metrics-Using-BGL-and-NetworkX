#include <boost/config.hpp>
#include <vector>
#include <iostream>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/betweenness_centrality.hpp>

using namespace boost;
using namespace std;

int main(int, char *[])
{
    typedef adjacency_list<vecS, vecS, undirectedS, no_property, property<edge_weight_t, int>>
        graph;

    graph G;

    typedef graph::vertex_descriptor vertex;
    typedef graph::edge_descriptor edge;

    add_edge(1, 2, G);
    add_edge(2, 3, G);
    add_edge(3, 4, G);

    std::vector<double> centrality(num_vertices(G), 0.0);

    brandes_betweenness_centrality(
        G,
        centrality_map(
            make_iterator_property_map(centrality.begin(), get(vertex_index, G), double()))
            .vertex_index_map(get(vertex_index, G))
            .weight_map(get(edge_weight, G)));

    int n = num_vertices(G) - 1;
    std::cout << "number of vertices: " << n << endl;
    int m = num_edges(G);
    std::cout << "number of edges: " << m << endl;

    // absoute and relative vertex betweenness centrality
    for (int i = 1; i <= n; i++)
    {
        if (is_directed(G))
        {
            std::cout << "absolute_BC[" << i << "]: " << centrality[i] << " "
                 << "relative_BC[" << i << "]: " << ((centrality[i]) / (n * n - 3 * n + 2)) << '\n';
        }
        else
        {
            std::cout << "absolute_BC[" << i << "]: " << centrality[i] << " "
                 << "relative_BC[" << i << "]: " << ((centrality[i] * 2) / (n * n - 3 * n + 2)) << '\n';
        }
    }

    // central point dominance

    // finding highest betweenness centrality
    double highest_BC = 0;
    for (int i = 1; i <= n; i++)
    {
        if (highest_BC < centrality[i])
        {
            highest_BC = centrality[i];
        }
        else
        {
            highest_BC = highest_BC;
        }
    }
    std::cout << "highest_BC: " << highest_BC << endl;

    // converting highest betweenness centrality to highest relative betweenness centrality
    double highest_RBC = 0;
    if (is_directed(G))
    {
        highest_RBC = highest_BC / (n * n - 3 * n + 2);
        std::cout << "highest_RBC: " << highest_RBC << endl;
    }
    else
    {
        highest_RBC = (highest_BC * 2) / (n * n - 3 * n + 2);
        std::cout << "highest_RBC: " << highest_RBC << endl;
    }

    // calculating central point dominance
    double temp = 0;
    double central_PD = 0;
    for (int i = 1; i <= n; i++)
    {
        if (is_directed(G))
        {
            temp = (1 / (double(n) - 1)) * (highest_RBC - (centrality[i] / (n * n - 3 * n + 2)));
            std::cout << temp << endl;
            central_PD = central_PD + temp;
        }
        else
        {
            temp = (1 / (double(n) - 1)) * (highest_RBC - ((centrality[i] * 2) / (n * n - 3 * n + 2)));
            std::cout << temp << endl;
            central_PD = central_PD + temp;
        }
    }
    std::cout << "central_PD: " << central_PD << endl;

    std::cout << "is directed: " << is_directed(G) << '\n';

    return 0;
}

    