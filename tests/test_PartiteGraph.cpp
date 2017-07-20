#include "gtest/gtest.h"

#include <unordered_set>

#include "PartiteGraph.h"


struct Vertex {
    std::string name;
};

struct Edge {
    float weight;
};

TEST(PartiteGraphTest, test_add_vertex) {
    PartiteGraph<int, Vertex, Edge> graph;

    add_vertex<0>(graph, 0, Vertex{"vertex 0"});
}

TEST(PartiteGraphTest, test_add_edge) {
    PartiteGraph<int, Vertex, Edge> graph;

    EXPECT_THROW(graph.add_edge(0, 1), std::runtime_error);

    add_vertex<0>(graph, 0, Vertex{"vertex 0"});
    add_vertex<0>(graph, 1, Vertex{"vertex 1"});
    EXPECT_THROW(graph.add_edge(0, 1), std::runtime_error);

    add_vertex<1>(graph, 0, Edge{0.1});
    /*add_edge(0, 2);
    add_edge(1, 2);
    std::unordered_set<int> expected{0, 1};
    EXPECT_EQ(graph.get_parents(2), expected);*/
}
