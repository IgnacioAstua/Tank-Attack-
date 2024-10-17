#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>

class Map {
private:
    int width;
    int height;
    int cellSize;
    std::vector<std::vector<int>> grid;
    std::vector<std::vector<int>> adjacencyMatrix;

    int getNodeIndex(int x, int y) const;
    void updateAdjacencyMatrix();
    void removeRandomObstacle();
    bool isFullyAccessible();
    void generateAccessibleMap();

public:
    Map(int w, int h, int cs);
    void draw(sf::RenderWindow& window);
    bool isObstacle(int x, int y) const;
    const std::vector<std::vector<int>>& getAdjacencyMatrix() const;
};

#endif // MAP_H
