#ifndef GRAPH_PARTITEGRAPH_H
#define GRAPH_PARTITEGRAPH_H

#include <type_traits>
#include "Graph.h"

template<typename V, typename ...Ts>
class PartiteGraph : public Graph<V> {
public:
    void add_vertex(const V &vertex) = delete;
};

template<typename V, typename T, typename ...Ts>
class PartiteGraph<V, T, Ts...> : public PartiteGraph<V, Ts...> {
public:

    /**
     * Get the named partition
     * @tparam partition partition to get
     * @return
     */
    template <unsigned int partition>
    const typename std::enable_if<partition == 0, std::unordered_map<V, T>>::type &
    get_partition() const {
        return _partition;
    }

    template <unsigned int partition>
    const typename std::enable_if<partition != 0, std::unordered_map<V, typename std::tuple_element<partition, std::tuple<T, Ts...>>::type>>::type &
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
    void add_vertex(const V &vertex, const typename std::enable_if<partition == 0, T>::type &type) {
        _partition.emplace(vertex, type);
    }

    template <unsigned int partition>
    void add_vertex(const V &vertex, const typename std::enable_if<partition != 0, typename std::tuple_element<partition, std::tuple<T, Ts...>>::type>::type &type) {
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
    const typename std::enable_if<partition == 0, T>::type &
    get_vertex(const V& vertex) const {
        return _partition.at(vertex);
    };

    template <unsigned int partition>
    const typename std::enable_if<partition != 0, const typename std::tuple_element<partition, std::tuple<T, Ts...>>::type>::type &
    get_vertex(const V& vertex) const {
        const PartiteGraph<V, Ts...>& graph = *this;
        return graph.get_vertex<partition - 1>(vertex);
    };


private:

    std::unordered_map<V, T> _partition;
};


#endif //GRAPH_PARTITEGRAPH_H
