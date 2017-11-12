#include "gtest/gtest.h"

#include <graph/PartiteGraph.h>

enum Partition { vertex_partition, edge_partition };


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


TEST(PartiteGraphTest, test_get_partition_by_number) {
    graph::PartiteGraph<int, Vertex, Edge> graph;
    const std::unordered_map<int, Vertex> &vertex_partition = graph.get_partition<0>();
    EXPECT_EQ(vertex_partition.size(), 0);
    const std::unordered_map<int, Edge> &edge_partition = graph.get_partition<1>();
    EXPECT_EQ(edge_partition.size(), 0);
}

TEST(PartiteGraphTest, test_get_partition_of_vertex) {
    graph::PartiteGraph<int, Vertex, Edge> graph;
    graph.add<vertex_partition>(0, {"0"});
    graph.add<vertex_partition>(1, {"1"});
    graph.add<edge_partition>(2, {1.0});

    EXPECT_EQ(graph.get_vertex_partition(0), 0);
    EXPECT_EQ(graph.get_vertex_partition(1), 0);
    EXPECT_EQ(graph.get_vertex_partition(2), 1);
}

TEST(PartiteGraphTest, test_add_vertex) {
    graph::PartiteGraph<int, Vertex, Edge> graph;

    EXPECT_EQ(graph.get_partition<0>().size(), 0);
    graph.add<vertex_partition>(0, {"vertex 0"});
    EXPECT_EQ(graph.get_partition<0>().size(), 1);

    EXPECT_EQ(graph.get_partition<1>().size(), 0);
    graph.add<edge_partition>(1, {0.5});
    EXPECT_EQ(graph.get_partition<1>().size(), 1);
}

TEST(PartiteGraphTest, test_get_vertex) {
    graph::PartiteGraph<int, Vertex, Edge> graph;
    graph.add<vertex_partition>(0, {"vertex 0"});
    graph.add<edge_partition>(1, {0.5});

    EXPECT_EQ(graph.get<vertex_partition>(0).name, "vertex 0");
    EXPECT_EQ(graph.get<edge_partition>(1).weight, 0.5);
}

TEST(PartiteGraphTest, test_add_edge) {
    std::unordered_set<int> expected{2};
    graph::PartiteGraph<int, Vertex, Edge> graph;

    EXPECT_THROW(graph.add_edge(0, 1), std::runtime_error);
    graph.add<vertex_partition>(0, {"vertex 0"});
    graph.add<vertex_partition>(1, {"vertex 1"});
    EXPECT_THROW(graph.add_edge(0, 1), std::runtime_error);
    graph.add<edge_partition>(2, {0.5});
    graph.add_edge(0, 2);
    graph.add_edge(2, 1);
    EXPECT_EQ(graph.get_children(0), expected);
    EXPECT_EQ(graph.get_parents(1), expected);
}