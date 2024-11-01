#ifndef TANK_H
#define TANK_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "path.h"  
#include "bullet.h"

class Tank {
public:
    Tank(float x, float y, sf::Color color);
  
    void move(float offsetX, float offsetY);
    void moveToPosition(const std::vector<std::pair<int, int>>& path);
    bool contains(float x, float y) const;
    void select();
    void deselect();
    sf::Vector2f getPosition() const;
    void clearPath();
    void decideMovement(const std::vector<std::vector<int>>& grid, int targetX, int targetY);

    std::vector<Bullet> bullets; // Para almacenar las balas

    void shoot(const sf::Vector2f& target);
    void draw(sf::RenderWindow& window);
    bool hasShot = false; // Inicializado a false


    bool isActive() const { return active; } // Para comprobar si el tanque está activo
    
    void deactivate(); // Solo la declaración



private:
    
    sf::RectangleShape shape;

    bool active = true;

    bool isSelected = false;
    static const int cellSize = 30; // Tamaño de cada celda en la cuadrícula
    Path path;
    std::vector<sf::Vector2f> bulletPath; // Almacena la trayectoria de la bala
    std::vector<std::pair<int, int>> performBFS(const std::vector<std::vector<int>>& grid, int startX, int startY, int targetX, int targetY);
    std::vector<std::pair<int, int>> performRandomMovement(const std::vector<std::vector<int>>& grid, int startX, int startY);
    bool isPositionValid(int x, int y, const std::vector<std::vector<int>>& grid);
};

#endif // TANK_H
