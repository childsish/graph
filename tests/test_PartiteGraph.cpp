#include "gtest/gtest.h"

#include <unordered_set>
#include <graph/PartiteGraph.h>


TEST(PartiteGraphTest, test_add_vertex) {
    graph::PartiteGraph<int, 2> graph;

    graph.add_vertex(0, 0);
    EXPECT_THROW(graph.add_vertex(0, 1), std::runtime_error);
}

TEST(PartiteGraphTest, test_add_edge) {
    graph::PartiteGraph<int, 2> graph;

    EXPECT_THROW(graph.add_edge(0, 1), std::runtime_error);

    graph.add_vertex(0, 0);
    graph.add_vertex(1, 0);
    EXPECT_THROW(graph.add_edge(0, 1), std::runtime_error);

    graph.add_vertex(2, 1);
    graph.add_edge(0, 2);
    graph.add_edge(1, 2);
    std::unordered_set<int> expected{0, 1};
    EXPECT_EQ(graph.get_parents(2), expected);
}
