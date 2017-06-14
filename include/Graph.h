#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

#include <stack>
#include <unordered_map>
#include <unordered_set>


/*
 * A (un)directed graph that supports only a single edge between vertices. Can be treated as ordered by using the
 * get_parents and get_children functions. Can be treated as unordered by using the get_neighbours function.
 */
template<typename V>
class Graph {

    struct Vertex {
        std::unordered_set<V> parents;
        std::unordered_set<V> children;
    };

    std::unordered_map<V, Vertex> _edges;

public:

    void add_edge(const V &from, const V &to) {
        add_vertex(from);
        add_vertex(to);
        _edges[from].children.insert(to);
        _edges[to].parents.insert(from);
    }

    void add_vertex(const V &vertex) {
        if (_edges.find(vertex) == _edges.end()) {
            _edges.emplace(vertex, Vertex{});
        }
    }

    const std::unordered_set<V> get_children(const V &vertex) const {
        std::unordered_set<V> children;
        if (_edges.find(vertex) == _edges.end()) {
            return children;
        }
        return _edges.at(vertex).children;
    }

    const std::unordered_set<V> get_parents(const V &vertex) const {
        std::unordered_set<V> parents;
        if (_edges.find(vertex) == _edges.end()) {
            return parents;
        }
        return _edges.at(vertex).parents;
    }

    const std::unordered_set<V> get_neighbours(const V &vertex) const {
        std::unordered_set<V> neighbours;
        if (_edges.find(vertex) == _edges.end()) {
            return neighbours;
        }
        neighbours.insert(_edges.at(vertex).parents.begin(), _edges.at(vertex).parents.end());
        neighbours.insert(_edges.at(vertex).children.begin(), _edges.at(vertex).children.end());
        return neighbours;
    }

    const std::unordered_set<V> get_descendents(const V &vertex) const {
        std::unordered_set<V> descendents;
        if (_edges.find(vertex) == _edges.end()) {
            return descendents;
        }
        std::unordered_set<V> visited;
        std::stack<V> stack;
        visited.insert(vertex);
        for (auto child : _edges.at(vertex).children) {
            stack.push(child);
        }
        while (stack.size() > 0) {
            const V top = stack.top();
            stack.pop();
            if (visited.find(top) != visited.end()) {
                continue;
            }
            visited.insert(top);
            descendents.insert(top);
            for (auto child : _edges.at(top).children) {
                stack.push(child);
            }
        }
        return descendents;
    }

    const std::unordered_set<V> get_ancestors(const V &vertex) const {
        std::unordered_set<V> ancestors;
        if (_edges.find(vertex) == _edges.end()) {
            return ancestors;
        }
        std::unordered_set<V> visited;
        std::stack<V> stack;
        visited.insert(vertex);
        for (auto parent : _edges.at(vertex).parents) {
            stack.push(parent);
        }
        while (stack.size() > 0) {
            const V top = stack.top();
            stack.pop();
            if (visited.find(top) != visited.end()) {
                continue;
            }
            visited.insert(top);
            ancestors.insert(top);
            for (auto parent : _edges.at(top).parents) {
                stack.push(parent);
            }
        }
        return ancestors;
    }

    void update(const Graph &that) {
        for (auto item : that._edges) {
            add_vertex(item.first);
            for (auto child : item.second.children) {
                add_edge(item.first, child);
            }
        }
    }
};

#endif //GRAPH_GRAPH_H
