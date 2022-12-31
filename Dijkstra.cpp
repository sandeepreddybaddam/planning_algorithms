#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

/*
Notes:

1. Mark all the vertices as unvisited
2. Consider a starting vertex, A
3. Set the distance from A to A as 0 and A to other as infinity
4. Now, visit the unvisited vertex with smallest known distance from the
    start vertex.
5. For the current vertex, we visit the unvisited neighbors. Note down the 
   distances.
6. Distance = Distance at cur. state + distance to next state
7. If the calculated distance is less than the already present value. UPDATE
8. Note down the previous state information for the visited states.
9. Add the current vertex to the visited list
10. REPEAT from 4 until unvisited becomes empty

| -----   | -------------------------------------- | --------------- |
| Vertex  | Shortest distance from starting vertex | Previous vertex |
| -----   | -------------------------------------- | --------------- |
*/

// find the unvisted vertex with the smallest known distance from the 
// start index
int find_minimum_distance_index(const std::vector<int>& minimum_distance, \
                                const std::vector<bool>& is_visited) {
    
    int index=0;
    int minimum_value=INT_MAX;

    for (int i=0; i<minimum_distance.size(); i++) {
        if (!is_visited[i] && minimum_distance[i] < minimum_value){
            minimum_value=minimum_distance[i];
            index = i;
        }
    }
    return index;
}


void find_shortest_path(const std::vector<std::vector<int>>& graph, \
                        const int& start_vertex, \
                        const int& goal_vertex) {
    // TODO: assert if graph is symmetric
    
    // mark all states as unvisited
    std::vector<bool> is_visited(graph.size(), false);
    
    // create a vector of size graph.size() with values as infinity
    std::vector<int> minimum_distance(graph.size(), INT_MAX);
    // set the minimum_distance from start to start as 0
    minimum_distance[start_vertex] = 0;

    // store the previous vertex
    std::vector<int> prev_index(graph.size(), 0);

    for (int i=0; i<graph.size(); i++) {
        int index = find_minimum_distance_index(minimum_distance,
                                                is_visited);
        is_visited[index] = true;

        for(int j=0; j<graph.size(); j++) {
            int cal_distance = minimum_distance[index] + graph[index][j];
            /*
            conditions: unvisited, neighhbor, distance comparison
            */
            if (!is_visited[j] &&
                graph[index][j] &&
                cal_distance < minimum_distance[j]) {
                // update the minimum_distance
                minimum_distance[j] = cal_distance;
                prev_index[j] = index;
            }
        }
    }

    std::cout << "Vertex\tDistance from starting vertex\tPrevious index"
              << std::endl;
    for (int i=0; i<graph.size(); i++) {
        std::cout<<i<<"\t\t"<<minimum_distance[i]<<"\t\t\t\t"<< prev_index[i] \
                                                             << std::endl;
    }
    
    // visualizing the shortest path
    
    int tminus_index=goal_vertex;
    std::cout<<"\nShortest path: (goal) " << tminus_index;

    while (tminus_index!=start_vertex) {
        tminus_index = prev_index[tminus_index];
        std::cout<<" <- " << tminus_index;
    }
    std::cout<<" (start)\n"<<std::endl;
}

int main() {
    // std::cout<<INT_MAX; //2147483647
    std::vector<std::vector<int>> graph = {{0, 6, 0, 1, 0},
                                           {6, 0, 5, 2, 2},
                                           {0, 5, 0, 0, 5},
                                           {1, 2, 0, 0, 1},
                                           {0, 2, 5, 1, 0}};
    int origin = 0;
    int goal = 2;
    find_shortest_path(graph, origin, goal);
}