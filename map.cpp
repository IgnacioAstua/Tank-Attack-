#include "map.h"
#include <queue>
#include <utility> // Para std::pair
#include <cstdlib> // Para std::rand y std::srand
#include <ctime>   // Para std::time

// Constructor
Map::Map(int width, int height, int cellSize)
    : width(width), height(height), cellSize(cellSize) {
    grid.resize(height, std::vector<int>(width, 0));
    std::srand(static_cast<unsigned>(std::time(0))); 
    adjacencyMatrix.resize(width * height, std::vector<int>(width * height, 0)); // Inicializar matriz de adyacencia
    generateAccessibleMap(); // Generar un mapa accesible
}

// Método para dibujar el mapa
void Map::draw(sf::RenderWindow& window) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
            cell.setPosition(x * cellSize, y * cellSize);
            if (grid[y][x] == 1) { // Suponiendo que 1 representa un obstáculo
                cell.setFillColor(sf::Color(85, 107, 47));
            } else {
                cell.setFillColor(sf::Color(248, 229, 197));
            }
            window.draw(cell);
        }
    }
}

// Método para verificar si hay un obstáculo
bool Map::isObstacle(int x, int y) const {
    return (x < 0 || x >= width || y < 0 || y >= height || grid[y][x] == 1); // 1 indica obstáculo
} // Suponiendo que 1 representa un obstáculo


// Método BFS para encontrar el camino desde una posición inicial a una posición objetivo
std::vector<std::pair<int, int>> Map::BFS(const sf::Vector2f& start, const std::pair<int, int>& goal) {
    std::vector<std::pair<int, int>> path;
    std::queue<std::pair<int, int>> queue;
    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));
    std::vector<std::vector<std::pair<int, int>>> previous(height, std::vector<std::pair<int, int>>(width, {-1, -1}));

    int startX = static_cast<int>(start.x / cellSize);
    int startY = static_cast<int>(start.y / cellSize);
    int goalX = goal.first;
    int goalY = goal.second;

    if (isObstacle(goalX, goalY)) {
        return path; // Si la meta es un obstáculo, retorna vacío
    }

    queue.push({startX, startY});
    visited[startY][startX] = true;

    std::vector<std::pair<int, int>> directions = {
        {0, 1},  // Abajo
        {1, 0},  // Derecha
        {0, -1}, // Arriba
        {-1, 0}  // Izquierda
    };

    while (!queue.empty()) {
        auto current = queue.front();
        queue.pop();

        if (current.first == goalX && current.second == goalY) {
            // Reconstruir el camino desde el objetivo hasta el inicio
            for (auto at = current; at != std::pair<int, int>{-1, -1}; at = previous[at.second][at.first]) {
                path.push_back(at);
            }
            std::reverse(path.begin(), path.end()); // Invertir el camino para tenerlo desde el inicio hasta el objetivo
            break;
        }

        for (const auto& direction : directions) {
            int newX = current.first + direction.first;
            int newY = current.second + direction.second;

            // Comprobar límites y obstáculos
            if (newX >= 0 && newX < width && newY >= 0 && newY < height &&
                !isObstacle(newX, newY) && !visited[newY][newX]) {
                visited[newY][newX] = true;
                previous[newY][newX] = current; // Guardar el nodo anterior
                queue.push({newX, newY});
            }
        }
    }
    return path; // Retornar el camino encontrado
}


void Map::removeRandomObstacle() {
    int x, y;
    do {
        x = std::rand() % (width - 2) + 1; // Evitar bordes
        y = std::rand() % (height - 2) + 1; // Evitar bordes
    } while (grid[y][x] == 0); // Asegurarse de que haya un obstáculo que eliminar

    grid[y][x] = 0; // Remover el obstáculo
}

bool Map::isFullyAccessible() {
    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));
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
                grid[ny][nx] == 0 && !visited[ny][nx]) {
                visited[ny][nx] = true;
                queue.push({nx, ny});
            }
        }
    }

    // Verificar si todas las celdas libres han sido visitadas
    for (int i = 1; i < height - 1; ++i) {
        for (int j = 1; j < width - 1; ++j) {
            if (grid[i][j] == 0 && !visited[i][j]) {
                return false;
            }
        }
    }
    return true;
}

void Map::updateAdjacencyMatrix() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (grid[i][j] == 0) { // Si es un espacio libre
                int currentIndex = i * width + j;

                // Conectar a los vecinos
                if (i > 0 && grid[i - 1][j] == 0) { // Arriba
                    adjacencyMatrix[currentIndex][(i - 1) * width + j] = 1;
                }
                if (i < height - 1 && grid[i + 1][j] == 0) { // Abajo
                    adjacencyMatrix[currentIndex][(i + 1) * width + j] = 1;
                }
                if (j > 0 && grid[i][j - 1] == 0) { // Izquierda
                    adjacencyMatrix[currentIndex][i * width + (j - 1)] = 1;
                }
                if (j < width - 1 && grid[i][j + 1] == 0) { // Derecha
                    adjacencyMatrix[currentIndex][i * width + (j + 1)] = 1;
                }
            }
        }
    }
}


void Map::generateAccessibleMap() {
    do {
        // Limpiar la cuadrícula y generar nuevos obstáculos
        for (int j = 0; j < height; ++j) {
            for (int i = 0; i < width; ++i) {
                if (i == 0 || i == width - 1 || j == 0 || j == height - 1) {
                    grid[j][i] = 1; // Borde
                } else {
                    grid[j][i] = (std::rand() % 100 < 8) ? 1 : 0; // Obstáculo con probabilidad del 10%
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

const std::vector<std::vector<int>>& Map::getAdjacencyMatrix() const {
    return adjacencyMatrix;
}
