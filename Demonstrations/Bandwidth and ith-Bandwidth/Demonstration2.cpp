#include <boost/config.hpp>
#include <vector>
#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/bandwidth.hpp>

using namespace boost;
using namespace std;

int main(int, char *[])
{
    typedef adjacency_list<vecS, vecS, undirectedS, no_property, no_property> Graph;
    typedef std::pair<std::size_t, std::size_t> Pair;

    Pair edges[12] = {Pair(1, 2),
                      Pair(1, 4),
                      Pair(1, 5),
                      Pair(2, 3),
                      Pair(2, 6),
                      Pair(3, 4),
                      Pair(3, 7),
                      Pair(4, 8),
                      Pair(5, 6),
                      Pair(5, 8),
                      Pair(6, 7),
                      Pair(7, 8)};

    Graph G;

    for (int i = 0; i < 12; ++i)
    {
        add_edge(edges[i].first, edges[i].second, G);
    }

    std::cout << "bandwidth of Given Graph: " << bandwidth(G) << '\n'
              << '\n';

    for (int i = 1; i <= 8; i++)
    {
        std::cout << "ith-bandwidth of vertex " << i << ": " << ith_bandwidth(i, G) << std::endl;
    }

    return 0;
}