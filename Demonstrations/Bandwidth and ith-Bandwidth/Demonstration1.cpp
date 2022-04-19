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

    Pair edges[12] = {Pair(1, 6),
                      Pair(1, 7),
                      Pair(1, 8),
                      Pair(2, 5),
                      Pair(2, 7),
                      Pair(2, 8),
                      Pair(3, 5),
                      Pair(3, 6),
                      Pair(3, 8),
                      Pair(4, 5),
                      Pair(4, 6),
                      Pair(4, 7)};

    Graph G;

    for (int i = 0; i < 12; ++i)
    {
        add_edge(edges[i].first, edges[i].second, G);
    }

    std::cout << "bandwidth of Given Graph: " << bandwidth(G) << '\n' << '\n';

    for (int i = 1; i <= 8; i++)
    {
        std::cout << "ith-bandwidth of vertex " << i << ": " << ith_bandwidth(i, G) << std::endl;
    }

    return 0;
}