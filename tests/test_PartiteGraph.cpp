#include "gtest/gtest.h"

#include <graph/PartiteGraph.h>


struct Vertex {
    std::string name;

    bool operator==(const Vertex &that) const {
        return name == that.name;
    }
};


struct Edge {
    float weight;

    bool operator==(const Edge &that) const {
        return weight == that.weight;
    }
};


TEST(PartiteGraphTest, test_get_partition) {
    PartiteGraph<int, Vertex, Edge> graph;
    const std::unordered_map<int, Vertex> &vertex_partition = graph.get_partition<0>();
    EXPECT_EQ(vertex_partition.size(), 0);
    const std::unordered_map<int, Edge> &edge_partition = graph.get_partition<1>();
    EXPECT_EQ(edge_partition.size(), 0);
}

TEST(PartiteGraphTest, test_add_vertex) {
    PartiteGraph<int, Vertex, Edge> graph;
    Vertex vertex{"vertex 0"};
    Edge edge{0.5};

    EXPECT_EQ(graph.get_partition<0>().size(), 0);
    graph.add_vertex<0>(0, vertex);
    EXPECT_EQ(graph.get_partition<0>().size(), 1);

    EXPECT_EQ(graph.get_partition<1>().size(), 0);
    graph.add_vertex<1>(1, edge);
    EXPECT_EQ(graph.get_partition<1>().size(), 1);
}

TEST(PartiteGraphTest, test_get_vertex) {
    PartiteGraph<int, Vertex, Edge> graph;
    Vertex vertex{"vertex 0"};
    Edge edge{0.5};
    graph.add_vertex<0>(0, vertex);
    graph.add_vertex<1>(1, edge);

    EXPECT_EQ(graph.get_vertex<0>(0), vertex);
    EXPECT_EQ(graph.get_vertex<1>(1), edge);
}
