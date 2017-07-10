#ifndef GRAPH_PARTITEGRAPH_H
#define GRAPH_PARTITEGRAPH_H

#include <array>
#include <sstream>
#include <unordered_set>
#include "Graph.h"


template<typename V, std::size_t N>
class PartiteGraph : public Graph<V> {
public:

    /**
     * Add an edge between two named vertices
     * @param from vertex to join from
     * @param to vertex to join to
     */
    void add_edge(const V &from, const V &to) {
        int from_partition = _get_partition(from);
        int to_partition = _get_partition(to);
        if (from_partition == -1) {
            std::stringstream message;
            message << "Vertex " << from << " has not been assigned a partition.";
            throw std::runtime_error(message.str());
        }
        else if (to_partition == -1) {
            std::stringstream message;
            message << "Vertex " << to << " has not been assigned a partition.";
            throw std::runtime_error(message.str());
        }
        else if (from_partition == to_partition) {
            std::stringstream message;
            message << "Vertex " << from << " and vertex " << to <<
                    " can not be connected as they are both in partition " << from_partition << ".";
            throw std::runtime_error(message.str());
        }
        Graph<V>::add_edge(from, to);
    }

    void add_vertex(const V &vertex) = delete;

    /**
     * Add a named vertex
     * @param vertex name of the vertex to add
     * @param partition partition to add vertex to
     */
    void add_vertex(const V &vertex, int partition) {
        int current_partition = _get_partition(vertex);
        if (current_partition == -1) {
            partitions[partition].insert(vertex);
            Graph<V>::add_vertex(vertex);
        }
        else if (current_partition != partition) {
            std::stringstream message;
            message << "Vertex " << vertex << " already exists in partition " << current_partition << ".";
            throw std::runtime_error(message.str());
        }
    }

    /**
     * Join two graphs
     * @param that graph to join to
     */
    void update(const PartiteGraph<V, N> &that) {
        for (unsigned int i = 0; i < N; ++i) {
            partitions[i].insert(that.partitions[i].begin(), that.partitions[i].end());
        }
        Graph<V>::update(that);
    }

    /**
     * Get the partition of a vertex. -1 if vertex not in a partition.
     * @param vertex get the partition of this vertex
     * @return partition the vertex belongs to
     */
    int get_partition(const V &vertex) {
        for (unsigned int i = 0; i < N; ++i) {
            if (partitions[i].find(vertex) != partitions[i].end()) {
                return i;
            }
        }
        return -1;
    }

private:

    std::array<std::unordered_set<V>, N> partitions;

};

#endif //GRAPH_PARTITEGRAPH_H
