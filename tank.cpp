#include "tank.h"
#include <cstdlib> // Para rand y srand
#include <ctime>   // Para time
#include <queue>   // Para usar la cola en BFS

// Constructor
Tank::Tank(float x, float y, sf::Color color) {
    shape.setSize(sf::Vector2f(30, 30)); // Tamaño del tanque
    shape.setFillColor(color);
    shape.setPosition(x, y);
}

// Método para dibujar el tanque
void Tank::draw(sf::RenderWindow& window) {
    window.draw(shape);
    path.draw(window);  // Dibuja el camino recorrido por el tanque
}

// Método para mover el tanque por un desplazamiento
void Tank::move(float offsetX, float offsetY) {
    shape.move(offsetX, offsetY);
}

// Método para mover el tanque usando una ruta (BFS)
void Tank::moveToPosition(const std::vector<std::pair<int, int>>& pathPairs) {
    this->path.setPath(pathPairs);  // Establecer el nuevo camino
    this->path.setColor(sf::Color(88, 42, 18)); // Cambiar el color del camino a verde musgo
    shape.setPosition(pathPairs.back().first * cellSize, pathPairs.back().second * cellSize);
}

// Método para verificar si el tanque contiene el punto
bool Tank::contains(float x, float y) const {
    return shape.getGlobalBounds().contains(x, y);
}

// Seleccionar el tanque
void Tank::select() {
    isSelected = true;
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::Yellow);
}

// Deseleccionar el tanque
void Tank::deselect() {
    isSelected = false;
    shape.setOutlineThickness(0);
}

// Obtener la posición actual del tanque
sf::Vector2f Tank::getPosition() const {
    return shape.getPosition();
}

// Limpiar el camino actual
void Tank::clearPath() {
    path.clear();  // Borra el camino almacenado
}

// Implementación del algoritmo BFS para encontrar el camino
std::vector<std::pair<int, int>> Tank::performBFS(const std::vector<std::vector<int>>& grid, int startX, int startY, int targetX, int targetY) {
    std::vector<std::vector<bool>> visited(grid.size(), std::vector<bool>(grid[0].size(), false));
    std::queue<std::pair<int, int>> q;
    std::vector<std::pair<int, int>> parent(grid.size() * grid[0].size());

    q.push({startX, startY});
    visited[startX][startY] = true;
    parent[startX * grid[0].size() + startY] = {-1, -1}; // No hay padre al inicio

    // Direcciones para moverse en la cuadrícula
    const std::vector<std::pair<int, int>> directions = {
        {0, 1},   // Derecha
        {1, 0},   // Abajo
        {0, -1},  // Izquierda
        {-1, 0}   // Arriba
    };

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        // Si se ha alcanzado la meta, reconstruir el camino
        if (x == targetX && y == targetY) {
            std::vector<std::pair<int, int>> path;
            for (auto pos = std::make_pair(targetX, targetY); pos != std::make_pair(-1, -1);) {
                path.push_back(pos);
                pos = parent[pos.first * grid[0].size() + pos.second];
            }
            std::reverse(path.begin(), path.end()); // Revertir el camino
            return path;
        }

        // Explorar las posiciones adyacentes
        for (const auto& direction : directions) {
            int newX = x + direction.first;
            int newY = y + direction.second;

            // Verificar si la nueva posición es válida y no ha sido visitada
            if (newX >= 0 && newX < grid.size() && newY >= 0 && newY < grid[0].size() &&
                grid[newX][newY] == 0 && !visited[newX][newY]) {
                visited[newX][newY] = true;
                q.push({newX, newY});
                parent[newX * grid[0].size() + newY] = {x, y}; // Guardar el padre
            }
        }
    }
    return {}; // Retornar vacío si no hay camino
}

// Función para realizar movimiento aleatorio
std::vector<std::pair<int, int>> Tank::performRandomMovement(const std::vector<std::vector<int>>& grid, int startX, int startY) {
    std::vector<std::pair<int, int>> path;
    srand(static_cast<unsigned>(time(nullptr))); // Inicializa la semilla

    int randomX = rand() % grid.size();
    int randomY = rand() % grid[0].size();

    //Posición es válida y no hay obstáculos
    while (!isPositionValid(randomX, randomY, grid)) {
        randomX = rand() % grid.size();
        randomY = rand() % grid[0].size();
    }

    path.push_back({randomX, randomY});
    return path;
}

// Verificar si la posición es válida
bool Tank::isPositionValid(int x, int y, const std::vector<std::vector<int>>& grid) {
    return (x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size() && grid[x][y] == 0);
}

// Función para decidir el movimiento (BFS o aleatorio)
void Tank::decideMovement(const std::vector<std::vector<int>>& grid, int targetX, int targetY) {
    if (rand() % 2 == 0) { // 50% de probabilidad para BFS
        auto pathPairs = performBFS(grid, shape.getPosition().x / cellSize, shape.getPosition().y / cellSize, targetX, targetY);
        if (!pathPairs.empty()) {
            moveToPosition(pathPairs);
        }
    } else { // 50% de probabilidad para movimiento aleatorio
        auto pathPairs = performRandomMovement(grid, shape.getPosition().x / cellSize, shape.getPosition().y / cellSize);
        moveToPosition(pathPairs);
    }
}
