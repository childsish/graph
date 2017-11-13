# graph

*graph* is a simple header library of basic C++ graph (as in networks, not plots) classes. A couple of basic classes are
implemented that allow most other graph types to be simulated; `Graph` and `PartiteGraph`.
 
`Graph` is a directed graph with only one edge per vertex pair and no edge weights. Vertices do not need to be
  predefined. Currently cyclic/acyclic behaviour needs to be enforced by the user. 
  
`PartiteGraph` is a subclass of `Graph` that splits vertices into separate partitions and prevents vertices from
  belonging to multiple partitions or edges among vertices from the same partition.

## `Graph` example

### Specifying type

When declaring a `Graph`, the type of the vertex identifiers needs to be defined using the template parameter. Internally
vertices are stored in an [`std::unordered_map`](1) and thus must follow the specifications outlined for
[`UnorderedAssociativeContainers`](2).

```cpp
#include <string>
#include <graph/Graph.h>

graph::Graph<int> int_graph;
graph::Graph<std::String> string_graph;
```

### Adding edges

Edges are added using `Graph::add_edge`. Unlike the `PartiteGraph`, vertices will be created automatically if they don't
already exist. 

```cpp
#include <graph/Graph.h>

graph::Graph<int> graph;
graph.add_edge(0, 1);
graph.add_edge(0, 2);

graph.get_children(0);  // {0, 1}
```

### Querying neighbours

`Graph` has five methods for getting the various types of neighbours:
* `Graph::get_children`
* `Graph::get_parents`
* `Graph::get_neightbours`
* `Graph::get_descendents`
* `Graph::get_ancestors` 

```cpp
#include <string>
#include <graph/Graph.h>

graph::Graph<std::string>
graph.add_edge("A", "B");
graph.add_edge("B", "C");
graph.add_edge("B", "D");

graph.get_children("B");     // {"C", "D"}
graph.get_parents("B");      // {"A"}
graph.get_neightbours("B");  // {"A", "C", "D"}
graph.get_descendents("A");  // {"B", "C", "D"}
graph.get_ancestors("C")     // {"A", "B"}
```

## `PartiteGraph` example

### Specifying types

When declaring a `PartiteGraph`, the type of the vertex identifiers and all partitions need to be defined.

```cpp
#include <graph/PartiteGraph.h>

struct Vertex { std::string name; };
struct Edge { float weight; };

graph::PartiteGraph<int, Vertex, Edge> graph;
```

### Adding edges

Edges are also added using `PartiteGraph::edge_edge`. However, unlike `Graph`, vertices are not created automatically
and first need to be added using `PartiteGraph::add`. Additionally, an edge can not be created between two
vertices from the same partition.

```cpp
#include <graph/PartiteGraph.h>

enum Partition { vertex_partition, edge_partition };
struct Vertex { std::string name; };
struct Edge { float weight; };

// Add vertices
graph::PartiteGraph<int, Vertex, Edge> graph;
graph.add<vertex_partition>(0, {"A"});
graph.add<vertex_partition>(1, {"B"});
graph.add<vertex_partition>(2, {"C"});
graph.add<vertex_partition>(3, {"D"});
graph.add<edge_partition>(4, {1.0});
graph.add<edge_partition>(5, {0.5});
graph.add<edge_partition>(6, {0.0});

// Add edges
graph.add_edge(0, 4);
graph.add_edge(4, 1);
graph.add_edge(1, 5);
graph.add_edge(1, 6);
graph.add_edge(5, 2);
graph.add_edge(6, 3);
```

## Different graph types

* **Undirected graph.** Simply use `Graph::get_neighbours`.
* **Multigraph.** Use a `PartiteGraph` with two partitions. One partition is for vertex vertices and the other is for
 edge vertices. This will allow vertices in the vertex partition to be connected with each other via vertices in the
 edge partition. A subclass could be used to simplify getting neighbours. See example [Adding edges](#adding-edges-1).
* **Edge weights.** Use a `PartiteGraph` and add edge weights to one of the partition types. Also see example
[Adding edges](#adding-edges-1).


[1]: http://en.cppreference.com/w/cpp/container/unordered_map
[2]: http://en.cppreference.com/w/cpp/concept/UnorderedAssociativeContainer
