/**
 * @author: Liam Childs (liam.h.childs@gmail.com)
 * @brief: A graph class
 */
#ifndef GRAPH_PARTITEGRAPH_H
#define GRAPH_PARTITEGRAPH_H

#include <sstream>
#include <type_traits>
#include "Graph.h"

namespace graph {

    /**
     * An undirected graph that support multiple named partitions with different
     * types. V is used to define the type for the partition names while Ts is
     * used to define the types for each partition.
     * @tparam V type for partition names
     * @tparam Ts types for the partition values
     */
    template<typename V, typename ...Ts>
    class PartiteGraph : public Graph<V> {
    public:
        void add_vertex(const V &vertex) = delete;

        bool has_vertex(const V &vertex) const {
            return false;
        }

        unsigned int get_vertex_partition(const V &vertex,
                                          unsigned int partition = 0) const {
            std::stringstream buffer;
            buffer << "Vertex " << vertex << " not found in any partition.";
            throw std::runtime_error(buffer.str());
        }
    };

    template<typename V, typename T, typename ...Ts>
    class PartiteGraph<V, T, Ts...> : public PartiteGraph<V, Ts...> {
    public:

        template<unsigned int partition>
        using PartitionTypeAt = typename std::tuple_element<partition, std::tuple<T, Ts...>>::type;

        template<unsigned int partition>
        using FirstPartitionType = typename std::enable_if<partition == 0, T>::type;

        template<unsigned int partition>
        using PartitionType = typename std::enable_if<partition != 0,
                const PartitionTypeAt<partition>>::type;

        template<unsigned int partition>
        using FirstPartition = typename std::enable_if<partition == 0,
                std::unordered_map<V, T>>::type;

        template<unsigned int partition>
        using Partition = typename std::enable_if<partition != 0,
                std::unordered_map<V, PartitionTypeAt<partition>>>::type;

        /**
         * Add a connection between from and to.
         * add_edge can not create missing vertices as they need to be added to a partition
         * @param from connect from
         * @param to connect to
         */
        void add_edge(const V &from, const V &to) {
            if (!has_vertex(from)) {
                std::stringstream buffer;
                buffer << "From vertex (" << from << ") has not been created.";
                throw std::runtime_error(buffer.str());
            }
            unsigned int from_partition = get_vertex_partition(from);

            if (!has_vertex(to)) {
                std::stringstream buffer;
                buffer << "To vertex (" << to << ") has not been created.";
                throw std::runtime_error(buffer.str());
            }
            unsigned int to_partition = get_vertex_partition(to);


            if (from_partition == to_partition) {
                std::stringstream buffer;
                buffer << "From vertex (" << from << ") and to vertex (" << to
                       << ") both belong to partition " << get_vertex_partition(from) << ".";
                throw std::runtime_error(buffer.str());
            }
            Graph<V>::add_edge(from, to);
        }

        /**
         * Add a vertex to the named partition
         * @tparam partition partition to add vertex to
         * @param vertex vertex identifier
         * @param type vertex to add
         */
        template <unsigned int partition>
        void add_vertex(const V &vertex, const FirstPartitionType<partition> &type) {
            _partition.emplace(vertex, type);
        }

        template <unsigned int partition>
        void add_vertex(const V &vertex, const PartitionType<partition> &type) {
            PartiteGraph<V, Ts...>& graph = *this;
            graph.template add_vertex<partition - 1>(vertex, type);
        }

        /**
         * Return true if vertex in graph
         * @param vertex vertex to search for
         * @return true if vertex in graph else false
         */
        bool
        has_vertex(const V vertex) const {
            if (_partition.find(vertex) == _partition.end()) {
                const PartiteGraph<V, Ts...> &graph = *this;
                return graph.has_vertex(vertex);
            }
            return true;
        }

        /**
         * Get a vertex from the named partition
         * @tparam partition partition to get vertex from
         * @param vertex vertex identifier
         * @return gotten vertex
         */
        template <unsigned int partition>
        const FirstPartitionType<partition>&
        get_vertex(const V &vertex) const {
            return _partition.at(vertex);
        };

        template <unsigned int partition>
        const PartitionType<partition>&
        get_vertex(const V &vertex) const {
            const PartiteGraph<V, Ts...> &graph = *this;
            return graph.template get_vertex<partition - 1>(vertex);
        };

        /**
         * Get the named partition
         * @tparam partition partition to get
         * @return
         */
        template <unsigned int partition>
        const FirstPartition<partition>&
        get_partition() const {
            return _partition;
        }

        template<unsigned int partition>
        const Partition<partition>&
        get_partition() const {
            const PartiteGraph<V, Ts...> &graph = *this;
            return graph.template get_partition<partition - 1>();
        }

        /**
         * Get the partition the vertex belongs to
         * @param vertex vertex to inquire about
         * @return partition number vertex belongs to
         */
        unsigned int
        get_vertex_partition(const V &vertex, unsigned int partition = 0) const {
            if (_partition.find(vertex) == _partition.end()) {
                const PartiteGraph<V, Ts...> graph = *this;
                return graph.get_vertex_partition(vertex, partition + 1);
            }
            return partition;
        }


    private:

        std::unordered_map<V, T> _partition;

    };
}

#endif //GRAPH_PARTITEGRAPH_H
