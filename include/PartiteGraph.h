#ifndef GRAPH_PARTITEGRAPH_H
#define GRAPH_PARTITEGRAPH_H

#include <array>
#include <sstream>
#include <unordered_set>
#include "Graph.h"


template<typename V, typename ...Ts>
class PartiteGraph : public Graph<V> {
public:
    void add_vertex(const V &vertex) = delete;

    /*template<typename T>
    T &get_vertex(const V &vertex) {
        std::stringstream message;
        message << "Vertex " << vertex << " not found.";
        throw std::runtime_error(message.str());
    }*/

    /*void update(const PartiteGraph<V, Ts...> &that) {
        Graph<V>::update(that);
    }*/
};

template<typename V, typename T, typename ...Ts>
class PartiteGraph<V, T, Ts...> : public PartiteGraph<V, Ts...> {
public:
    std::unordered_map<V, T> _partition;
};


template <unsigned int, typename> struct VertexAdder;

template <class V, class T, class... Ts>
struct VertexAdder<0, PartiteGraph<V, T, Ts...>> {
    typedef T type;
};

template <unsigned int partition, class V, class T, class... Ts>
struct VertexAdder<partition, PartiteGraph<V, T, Ts...>> {
    typedef typename VertexAdder<partition - 1, PartiteGraph<V, Ts...>>::type type;
};


/**
 * Add a named vertex
 * @param vertex name of the vertex to add
 * @param partition partition to add vertex to
 */
template <unsigned int partition, class V, class... Ts>
void add_vertex(PartiteGraph<V, Ts...>& graph, const V &vertex, typename std::enable_if<partition == 0, const typename VertexAdder<0, PartiteGraph<V, Ts...>>::type>::type &type) {
    graph._partition.emplace(vertex, type);
}

template <unsigned int partition, class V, class T, class... Ts>
void add_vertex(PartiteGraph<V, T, Ts...>& graph, const V &vertex, typename std::enable_if<partition != 0, const typename VertexAdder<partition, PartiteGraph<V, T, Ts...>>::type>::type &type) {
    PartiteGraph<V, Ts...>& base = graph;
    return add_vertex<partition - 1>(base, vertex, type);
}


#endif //GRAPH_PARTITEGRAPH_H
