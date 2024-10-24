#include <SFML/Graphics.hpp>
#include "map.h"
#include "tank.h"
#include <sstream> // Para std::ostringstream
#include <vector> // Para std::vector
#include <iostream> // Para std::cout

// Clase para los bloques
class Block {
public:
    sf::RectangleShape shape;
    bool isInGame;

    Block(float x, float y, sf::Color color) {
        shape.setSize(sf::Vector2f(30, 30)); // Tamaño del bloque
        shape.setFillColor(color);
        shape.setPosition(x, y);
        isInGame = false; // Al inicio no está en el área de juego
    }

    void moveToGameArea(float x, float y) {
        shape.setPosition(x, y);
        isInGame = true; // Ahora está en el área de juego
    }

    bool contains(float mouseX, float mouseY) {
        return shape.getGlobalBounds().contains(mouseX, mouseY);
    }
};

int main() {
    int mapWidth = 30;
    int mapHeight = 20;
    int cellSize = 30;
    Map gameMap(mapWidth, mapHeight, cellSize);

    // Inicializar los tanques en la parte inferior de la pantalla (fuera del campo de juego)
    Tank blueTank(50, mapHeight * cellSize + 20, sf::Color::Blue);

    sf::RenderWindow window(sf::VideoMode(mapWidth * cellSize, mapHeight * cellSize + 120), "Tank Attack!");
    Tank* selectedTank = nullptr;

    // Cargar la fuente
    sf::Font font;
    if (!font.loadFromFile("/home/viviana/Desktop/font/bebasneue.ttf")) {
        return -1;
    }

    // Crear textos para el contador y nombres de los jugadores
    sf::Text timerText, player1Text, player2Text;
    timerText.setFont(font);
    timerText.setCharacterSize(24);
    timerText.setFillColor(sf::Color::Black);
    timerText.setPosition(10, mapHeight * cellSize);

    player1Text.setFont(font);
    player1Text.setCharacterSize(24);
    player1Text.setFillColor(sf::Color::Black);
    player1Text.setString("Jugador 1");
    player1Text.setPosition(10, mapHeight * cellSize + 30);

    // Titulo de Jugador 2
    player2Text.setFont(font);
    player2Text.setCharacterSize(24);
    player2Text.setFillColor(sf::Color::Black);
    player2Text.setString("Jugador 2");
    player2Text.setPosition(200, mapHeight * cellSize + 30);

    // Variables para el contador
    float timer = 300;
    sf::Clock clock;

    // Definir el rectángulo para el fondo
    sf::RectangleShape backgroundRect(sf::Vector2f(mapWidth * cellSize, 90));
    backgroundRect.setFillColor(sf::Color::White);
    backgroundRect.setPosition(0, mapHeight * cellSize);

    std::vector<sf::RectangleShape> inGameBlocks;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                float mouseX = event.mouseButton.x;
                float mouseY = event.mouseButton.y;

                // Manejar la selección del tanque
                if (blueTank.contains(mouseX, mouseY)) {
                    if (selectedTank) selectedTank->deselect();
                    blueTank.select();
                    selectedTank = &blueTank;
                } else if (selectedTank) { // Si hay un tanque seleccionado
                    // Obtener la posición de clic en el mapa
                    int targetX = mouseX / cellSize;
                    int targetY = mouseY / cellSize;

                    // Verificar que X y Y estén dentro de los límites del mapa
                    if (targetX >= 0 && targetX < mapWidth && targetY >= 0 && targetY < mapHeight) {
                        // Calcular el camino usando BFS
                        std::vector<std::pair<int, int>> path = gameMap.BFS(selectedTank->getPosition(), { targetX, targetY });

                        // Verificar si la ruta es válida
                        if (!path.empty()) {
                            // Mover el tanque al nuevo destino utilizando el camino
                            selectedTank->moveToPosition(path);
                        } else {
                            std::cout << "No hay un camino válido." << std::endl;
                        }
                    }
                }
            }

            if (selectedTank && event.type == sf::Event::MouseButtonReleased) {
                float newX = event.mouseButton.x;
                float newY = event.mouseButton.y;

                // Verificar que el tanque no esté fuera del área de juego
                if (newX >= 0 && newX < mapWidth * cellSize && newY >= 0 && newY < mapHeight * cellSize) {
                    selectedTank->move(newX - selectedTank->getPosition().x, newY - selectedTank->getPosition().y);
                }
            }
        }

        timer -= clock.restart().asSeconds();
        if (timer < 0) timer = 0;

        int minutes = static_cast<int>(timer) / 60;
        int seconds = static_cast<int>(timer) % 60;

        std::ostringstream oss;
        oss << "Tiempo: " << minutes << ":" << (seconds < 10 ? "0" : "") << seconds;
        timerText.setString(oss.str());

        window.clear(sf::Color::White);
        gameMap.draw(window);

        // Dibujar tanques solo en el área de selección
        window.draw(backgroundRect);
        window.draw(timerText);
        window.draw(player1Text);
        window.draw(player2Text);

        // Dibujar el tanque azul
        blueTank.draw(window);

        window.display();
    }

    return 0;
}
