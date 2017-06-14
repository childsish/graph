# graph

A simple header library of basic C++ graph (network) classes.

A couple of basic classes are implemented that allow most other graph types to be simulated; `Graph` and `PartiteGraph`.
 
**`Graph`** is a directed graph with only one edge per vertex pair and no edge weights. Vertices do not need to be
  predefined. Currently cyclic/acyclic behaviour needs to be enforced by the user. 
  
**`PartiteGraph`** is a subclass of `Graph` that splits vertices into separate partitions and prevents vertices from
  belonging to multiple partitions or edges among vertices from the same partition.

## Example

```cpp
Graph<int> graph;
graph.add_edge(0, 1);
graph.add_edge(0, 2);

auto children = graph.get_children(0); // std::unordered_set<int> == {0, 1}
```
