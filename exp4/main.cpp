
#include <iostream>
#include "utilities/graph/tools.hpp"

void testGraphAlgorithms() {
    // Create a graph
    GraphMatrix<std::string, int> graph;

    // Insert vertices
    int cityA = graph.insert("New York");
    int cityB = graph.insert("Los Angeles");
    int cityC = graph.insert("Chicago");
    int cityD = graph.insert("Houston");
    int cityE = graph.insert("Phoenix");

    // Insert edges (with weights representing distance or cost)
    graph.insert(1, 1000, cityA, cityB);  // New York to Los Angeles
    graph.insert(1, 800, cityA, cityC);   // New York to Chicago
    graph.insert(1, 1400, cityB, cityD);  // Los Angeles to Houston
    graph.insert(1, 500, cityC, cityD);   // Chicago to Houston
    graph.insert(1, 300, cityC, cityE);   // Chicago to Phoenix
    graph.insert(1, 600, cityD, cityE);   // Houston to Phoenix

    // BFS Traversal
    std::cout << "BFS Traversal starting from New York:\n";
    graph.bfs(cityA);

    // DFS Traversal
    std::cout << "\nDFS Traversal starting from New York:\n";
    graph.dfs(cityA);

    // Dijkstra's Shortest Path
    std::cout << "\nDijkstra's Shortest Path from New York:\n";
    graph.dijkstra(cityA);

    // Prim's Minimum Spanning Tree
    std::cout << "\nPrim's Minimum Spanning Tree starting from New York:\n";
    graph.prim(cityA);
}

int main() {
    testGraphAlgorithms();
    return 0;
}