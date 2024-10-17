#include "map.h"
#include <ctime>
#include <cstdlib>
#include <queue>

int Map::getNodeIndex(int x, int y) const {
    return y * width + x;
}

void Map::updateAdjacencyMatrix() {
    // Limpiar la matriz de adyacencia
    adjacencyMatrix.assign(width * height, std::vector<int>(width * height, 0));
    
    for (int i = 1; i < width - 1; ++i) {
        for (int j = 1; j < height - 1; ++j) {
            if (grid[i][j] == 0) { // Si es un camino libre
                int currentIndex = getNodeIndex(i, j);
                if (grid[i + 1][j] == 0) {
                    adjacencyMatrix[currentIndex][getNodeIndex(i + 1, j)] = 1; // Conectar a la derecha
                }
                if (grid[i - 1][j] == 0) {
                    adjacencyMatrix[currentIndex][getNodeIndex(i - 1, j)] = 1; // Conectar a la izquierda
                }
                if (grid[i][j + 1] == 0) {
                    adjacencyMatrix[currentIndex][getNodeIndex(i, j + 1)] = 1; // Conectar hacia abajo
                }
                if (grid[i][j - 1] == 0) {
                    adjacencyMatrix[currentIndex][getNodeIndex(i, j - 1)] = 1; // Conectar hacia arriba
                }
            }
        }
    }
}

void Map::removeRandomObstacle() {
    int x, y;
    do {
        x = std::rand() % (width - 2) + 1; // Evitar bordes
        y = std::rand() % (height - 2) + 1; // Evitar bordes
    } while (grid[x][y] == 0); // Asegurarse de que haya un obstáculo que eliminar

    grid[x][y] = 0; // Remover el obstáculo
}

bool Map::isFullyAccessible() {
    std::vector<std::vector<bool>> visited(width, std::vector<bool>(height, false));
    std::queue<std::pair<int, int>> queue;
    queue.push({1, 1}); // Comenzar en la primera celda libre
    visited[1][1] = true;

    while (!queue.empty()) {
        auto [x, y] = queue.front();
        queue.pop();

        const std::vector<std::pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        for (const auto& [dx, dy] : directions) {
            int nx = x + dx;
            int ny = y + dy;
            if (nx > 0 && nx < width - 1 && ny > 0 && ny < height - 1 &&
                grid[nx][ny] == 0 && !visited[nx][ny]) {
                visited[nx][ny] = true;
                queue.push({nx, ny});
            }
        }
    }

    // Verificar si todas las celdas libres han sido visitadas
    for (int i = 1; i < width - 1; ++i) {
        for (int j = 1; j < height - 1; ++j) {
            if (grid[i][j] == 0 && !visited[i][j]) {
                return false;
            }
        }
    }
    return true;
}

void Map::generateAccessibleMap() {
    do {
        // Limpiar la cuadrícula y generar nuevos obstáculos
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                if (i == 0 || i == width - 1 || j == 0 || j == height - 1) {
                    grid[i][j] = 1; // Borde
                } else {
                    grid[i][j] = (std::rand() % 100 < 8) ? 1 : 0; // Obstáculo con probabilidad del 10%
                }
            }
        }
    } while (!isFullyAccessible());

    // Asegurarse de que todas las celdas libres sean accesibles
    while (!isFullyAccessible()) {
        removeRandomObstacle(); // Eliminar un obstáculo aleatorio si hay áreas inaccesibles
    }

    // Actualizar la matriz de adyacencia después de generar el mapa
    updateAdjacencyMatrix();
}

Map::Map(int w, int h, int cs) : width(w), height(h), cellSize(cs), grid(w, std::vector<int>(h, 0)) {
    std::srand(static_cast<unsigned>(std::time(0)));
    adjacencyMatrix.resize(w * h, std::vector<int>(w * h, 0)); // Inicializar matriz de adyacencia
    generateAccessibleMap();
}

void Map::draw(sf::RenderWindow& window) {
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
            cell.setPosition(i * cellSize, j * cellSize);

            if (grid[i][j] == 1) {
                cell.setFillColor(sf::Color(100, 100, 100)); // Obstáculo o borde
            } else {
                cell.setFillColor(sf::Color(200, 200, 100)); // Camino libre
            }

            window.draw(cell);
        }
    }
}

bool Map::isObstacle(int x, int y) const {
    return grid[x][y] == 1;
}

const std::vector<std::vector<int>>& Map::getAdjacencyMatrix() const {
    return adjacencyMatrix;
}
