#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

// Structure to define the x and y co-ordinates of city
struct city
{
    /* data */
    int index;
    double x;
    double y;
};

double distance(city a, city b) {
    double del_x = a.x - b.x;
    double del_y = a.y - b.y;
    double distance = sqrt(pow(del_x, 2) + pow(del_y, 2));

    return distance;
}


int main() {
    int n;
    std::cout << "Enter the number of cities: ";
    std::cin >> n;
    std::vector<city> cities(n);

    // Enter the x and y co-ordinates of the cities
    for (int i=0; i<n; i++) {
        cities[i].index = i;
        std::cout << "x" << i << ": ";
        std::cin >> cities[i].x;
        std::cout << "y" << i << ": ";
        std::cin >> cities[i].y;
    }

    // Idea: find the distance sum of all the permutations and
    //       then choose the best (minimum distance) one

    std::vector<double> total_distances;
    std::vector<std::vector<city>> paths;

    do {    
        double total = 0;

        for(int i=1; i<n; i++) {
            double dist = distance( cities[i-1], cities[i] );
            total += dist;
        }
        total += distance(cities[n-1], cities[0]);

        // record the path traversed and also the distance value
        paths.push_back(cities);
        total_distances.push_back(total);

    } while (std::next_permutation(cities.begin(), cities.end(), \
                                   [](const auto & lhs, const auto & rhs) \
                                   { return lhs.index < rhs.index; }));
    /*
    std::next_permutation has an overload that takes a comparison object and
    uses it to compare the elements of the range to get the next permutation.
    You can use that overload and specify a custom camparator that will sort
    by only the index. Using a lambda that could look like above
    */
   
    // 'min_element' returns address of minimum value element
    auto it = std::min_element(total_distances.begin(), total_distances.end());
    int min_element_idx = std::distance(total_distances.begin(), it);

    double best_path_distance = *it;
    std::cout << "Best path distance: " << best_path_distance << std::endl;
    // double best_path_distance_1 = total_distances[min_element_idx];
    
    std::vector<city> best_path = paths[min_element_idx];

    std::cout << "Best path: ";
    for(int i=0; i<best_path.size(); i++) {
        std::cout << best_path[i].index << "-> ";
    }
    std::cout << best_path[0].index << std::endl;

}