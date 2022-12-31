#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <cmath>

typedef std::pair<int, int> Pair;
typedef std::tuple<double, int, int> Tuple;

/*
Notes:

1. Initialize OPEN and CLOSED lists
    i. OPEN - set of nodes to be evaluated
    ii. CLOSED - set of nodes already evaluated
2. Add the start node to OPEN
3. Loop
    i. Current = node in OPEN with the lowest f_cost
    ii. Remove current from OPEN
    iii. Add current to CLOSED
    iv. if current is the target node
            return
    v. for each neighbor of the current node
        if neighbor is not traversable or neighbor is in CLOSED
            skip to the next neighbor
        
        if new path to neighbor is shorter OR neighbor is not in OPEN
            set f_cost of neighbor
            set parent of neighbor to current
            if neighbor is not in OPEN
                add neighbor to OPEN 


Params:
1. Inputs: start, goal, binary occupancy grid
2. Ouput: Shortest path

NOTE: Try different heuristics

References:
1. Video by Sebastian Lague
2. Geeks for Geeks
*/


struct node {
    Pair parent;
    // f_cost = g_cost + h_cost
    double f, g, h;
    node(): parent(-1, -1), f(-1), g(-1), h(-1) {}
};


bool is_valid(const std::vector<std::vector<int>>& grid, const Pair& location) {
    int rows = grid.size();
    int cols = grid[0].size();

    int i, j;
    i = location.first, j = location.second;
    return (i>=0 && i<rows && j>=0 && j<cols);
}


bool is_traversable(const std::vector<std::vector<int>>& grid, \
                    const Pair& location) {
    // 0 is obstacle i.e., not traversable
    return grid[location.first][location.second];
}


bool is_goal(const Pair& location, const Pair& goal) {
    return (location==goal);
}


std::vector<Pair> find_neighbors(const Pair& location) {
    int i, j;
    i = location.first;
    j = location.second;
    std::vector<Pair> neighbors;

    for (int p=-1; p<=1; p++) {
        for (int q=-1; q<=1; q++) {
            Pair point(i+p, j+q);
            neighbors.push_back(point);
        }
    }
    return neighbors;
}


double heuristic_distance(const Pair& location, const Pair& goal) {
    // TODO: Add different heuristics
    int dx = goal.first - location.first;
    int dy = goal.second - location.second;

    return sqrt(dx*dx + dy*dy);
}


void visualize_path(const std::vector<std::vector<node>>& grid_w_params, \
                    const Pair& start, const Pair& goal) {
    int i, j;
    i = goal.first, j= goal.second;
    std::cout << "Shortest path: " << "[" << i << ", " << j <<"]";

    while(i!=start.first || j!=start.second) {
        int a = grid_w_params[i][j].parent.first;
        int b = grid_w_params[i][j].parent.second;
        i = a, j = b;

        std::cout << " <- " << "[" << i << ", " << j <<"]";
    }
}


void find_shortest_path(std::vector<std::vector<int>>& grid, \
                        Pair start, Pair goal)
{   
    int rows = grid.size();
    int cols = grid[0].size();

    // check if the start and goal nodes are valid
    if (!is_valid(grid, start) || !is_valid(grid, goal)) {
        std::cout << "Either START, GOAL, or both nodes are invalid.\n";
        return;
    }
    
    // check if the start and goal nodes are not obstacles
    if (!is_traversable(grid, start) || !is_traversable(grid, goal)) {
        std::cout << "Either START, GOAL, or both nodes are not traversable.\n";
        return;
    }
    
    if (is_goal(start, goal)) {
        std::cout << "Already at goal position." << std::endl;
        return;
    }

    // CLOSED List (boolean)
    std::vector<std::vector<bool>> is_closed(cols, std::vector<bool>(rows, false));
    // OPEN List (prority queue)
    std::priority_queue <Tuple, std::vector<Tuple>, std::greater<Tuple>> open_list;

    std::vector<std::vector<node>> grid_w_params(cols, std::vector<node>(rows));

    int i = start.first;
    int j = start.second;
    grid_w_params[i][j].g = grid_w_params[i][j].h = grid_w_params[i][j].f =  0.0;
    grid_w_params[i][j].parent = {i, j};
    
    Tuple t = std::make_tuple(0.0, i, j);
    open_list.push(t);
    
    // loop until the open_list is NOT empty
    while (!open_list.empty()) {
        Tuple t = open_list.top();
        int i, j;
        i = std::get<1>(t), j = std::get<2>(t);
        
        open_list.pop(); // remove current from OPEN
        is_closed[i][j] = true; // add current to CLOSED
        
        Pair current(i, j);
        if (is_goal(current, goal)) {
            std::cout << "Path has been found." << std::endl;
            visualize_path(grid_w_params, start, goal);
            return;
        }

        std::vector<Pair> neighbors = find_neighbors(current);

        for (int m=0; m<neighbors.size(); m++) {
            int a = neighbors[m].first;
            int b = neighbors[m].second;
            
            // valid node, traversable, and not in closed list
            if (is_valid(grid, neighbors[m]) && grid[a][b]!=0 && !is_closed[a][b]) {
                double g_new, h_new, f_new;
                g_new = grid_w_params[a][b].g + 1.0;
                h_new = heuristic_distance(neighbors[m], goal);
                f_new = g_new + h_new;

                if (grid_w_params[a][b].f == -1 || grid_w_params[a][b].f > f_new) {
                    // Update grid_w_params
                    // TODO: reduce duplicate code
                    grid_w_params[a][b].g = g_new;
                    grid_w_params[a][b].h = h_new;
                    grid_w_params[a][b].f = f_new;
                    grid_w_params[a][b].parent = current;
                    // add neighbor to OPEN List
                    Tuple t = std::make_tuple(f_new, a, b);
                    open_list.push(t);
                }
            }
        }
    }
}                        


int main() {
    // 0 is obstacle, 1 is traversable
    std::vector<std::vector<int>> grid = { { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
                                           { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
                                           { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
                                           { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
                                           { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
                                           { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
                                           { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
                                           { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
                                           { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 }};

    Pair start(8, 0);
    Pair goal(0, 0);

    find_shortest_path(grid, start, goal);

}