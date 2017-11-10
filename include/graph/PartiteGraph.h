#ifndef GRAPH_PARTITEGRAPH_H
#define GRAPH_PARTITEGRAPH_H


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
    };

    template<typename V, typename T, typename ...Ts>
    class PartiteGraph<V, T, Ts...> : public PartiteGraph<V, Ts...> {

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

    public:

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

        template <unsigned int partition>
        const Partition<partition>&
        get_partition() const {
            const PartiteGraph<V, Ts...>& graph = *this;
            return graph.get_partition<partition - 1>();
        }

        /**
         * Add a vertex to the named partition
         * @tparam partition parition to add vertex to
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
            graph.add_vertex<partition - 1>(vertex, type);
        }

        /**
         * Get a vertex from the named partition
         * @tparam partition partition to get vertex from
         * @param vertex vertex identifier
         * @return gotten vertex
         */
        template <unsigned int partition>
        const FirstPartitionType<partition>&
        get_vertex(const V& vertex) const {
            return _partition.at(vertex);
        };

        template <unsigned int partition>
        const PartitionType<partition>&
        get_vertex(const V& vertex) const {
            const PartiteGraph<V, Ts...>& graph = *this;
            return graph.get_vertex<partition - 1>(vertex);
        };


    private:

        std::unordered_map<V, T> _partition;
    };
}

#endif //GRAPH_PARTITEGRAPH_H
