#include "gtest/gtest.h"

#include <unordered_set>

#include "Graph.h"


class GraphTest : public ::testing::Test {
public:

    Graph<int> graph;

    std::unordered_set<int> expected;

    void SetUp() {
        graph.add_edge(0, 1);
        graph.add_edge(0, 2);
        graph.add_edge(1, 3);
        graph.add_edge(1, 4);
        graph.add_edge(3, 5);
        graph.add_edge(4, 5);
    }
};


TEST_F(GraphTest, test_get_children) {
    expected = {1, 2};
    EXPECT_EQ(expected, graph.get_children(0));
    expected = {};
    EXPECT_EQ(expected, graph.get_children(2));
}

TEST_F(GraphTest, test_get_parents) {
    expected = {};
    EXPECT_EQ(expected, graph.get_parents(0));
    expected = {3, 4};
    EXPECT_EQ(expected, graph.get_parents(5));
}

TEST_F(GraphTest, test_get_neighbours) {
    expected = {0, 3, 4};
    EXPECT_EQ(expected, graph.get_neighbours(1));
}

TEST_F(GraphTest, test_get_descendants) {
    expected = {1, 2, 3, 4, 5};
    EXPECT_EQ(expected, graph.get_descendants(0));
    expected = {3, 4, 5};
    EXPECT_EQ(expected, graph.get_descendants(1));
}

TEST_F(GraphTest, test_get_ancestors) {
    expected = {0, 1, 3, 4};
    EXPECT_EQ(expected, graph.get_ancestors(5));
    expected = {};
    EXPECT_EQ(expected, graph.get_ancestors(0));
}

TEST_F(GraphTest, test_union) {
    Graph<int> that;
    that.add_edge(2, 6);
    that.add_edge(2, 7);
    that.add_edge(6, 8);
    that.add_edge(9, 3);

    expected = {3};
    EXPECT_EQ(expected, that.get_descendants(9));
    expected = {2, 6};
    EXPECT_EQ(expected, that.get_ancestors(8));

    that.union_(graph);

    expected = {3, 5};
    EXPECT_EQ(expected, that.get_descendants(9));
    expected = {0, 2, 6};
    EXPECT_EQ(expected, that.get_ancestors(8));
}
