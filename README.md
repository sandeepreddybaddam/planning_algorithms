# planning_algorithms in C++
1. Traveling Salesman Problem
  - Problem statement: "Given a list of cities and the distances between each pair of cities, what is the shortest possible route that visits each city exactly once and returns to the origin city?" 

2. Dijkstra's Algorithm
  - Problem statement: Find the shortest path between nodes in a graph. Particularly, find the shortest path from a node (called the "source node") to all other nodes in the graph, producing a shortest-path tree.
  - **Definition:** `It is a graph` **traversal** `algorithm that finds the shortest path from a start node to all other nodes in a **weighted graph** by iteratively selecting a node with the smallest known distance and updating the distances to its neighbors`

3. A* Search
  - Problem statement: Find the shortest path between nodes for a given occupancy grid.
  - **Definition:** `It is a graph` **search** `algorithm that finds the shortest path from start node to goal node, by considering the cost to reach the current node and an` **estimate** `of the cost to reach the goal from that node, making it efficient and effective for pathfinding in various applications.`

| Traversal | Search |
|---|---|
| Involves examining every node in a graph | Involves visiting nodes in a graph in a systematic manner, and may or may not result into a visit to all nodes |
