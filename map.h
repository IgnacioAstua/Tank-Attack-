#ifndef MAP_H
#define MAP_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <utility> // Para std::pair

class Map {
public:
    Map(int width, int height, int cellSize);
    void draw(sf::RenderWindow& window);
    bool isObstacle(int x, int y) const;

    // Métodos adicionales que se implementan en map.cpp
    int getNodeIndex(int x, int y) const; 
    void updateAdjacencyMatrix(); 
    void removeRandomObstacle();
    bool isFullyAccessible(); 
    void generateAccessibleMap(); 
    const std::vector<std::vector<int>>& getAdjacencyMatrix() const; // Declaración agregada

    // Método BFS para encontrar un camino
    std::vector<std::pair<int, int>> BFS(const sf::Vector2f& start, const std::pair<int, int>& goal); // Declaración agregada

    // Métodos para obtener el ancho y el alto del mapa
    int getWidth() const { return width; }
    int getHeight() const { return height; }

private:
    int width;  // Ancho del mapa en celdas
    int height; // Alto del mapa en celdas
    int cellSize; // Tamaño de cada celda
    std::vector<std::vector<int>> grid; // Matriz que representa el mapa
    std::vector<std::vector<int>> adjacencyMatrix; // Agregar la declaración de la matriz de adyacencia
};

#endif // MAP_H
