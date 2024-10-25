#ifndef TANK_H
#define TANK_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "path.h"  
class Tank {
public:
    Tank(float x, float y, sf::Color color);
    void draw(sf::RenderWindow& window);
    void move(float offsetX, float offsetY);
    void moveToPosition(const std::vector<std::pair<int, int>>& path);
    bool contains(float x, float y) const;
    void select();
    void deselect();
    sf::Vector2f getPosition() const;
    void clearPath();  // Aquí elimina "Tank::" ya que es solo la declaración del método
   

private:
    sf::RectangleShape shape;
    bool isSelected = false;
    static const int cellSize = 30; // Tamaño de cada celda en la cuadrícula
    Path path; 
};

#endif // TANK_H
