#include <SFML/Graphics.hpp>
#include "map.h"
#include "tank.h"
#include <sstream>
#include <vector>
#include <iostream>
#include "bullet.h"

class Block {
public:
    sf::RectangleShape shape;
    bool isInGame;

    Block(float x, float y, sf::Color color) {
        shape.setSize(sf::Vector2f(30, 30));
        shape.setFillColor(color);
        shape.setPosition(x, y);
        isInGame = false;
    }

    void moveToGameArea(float x, float y) {
        shape.setPosition(x, y);
        isInGame = true;
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

    Tank blueTank1(10, mapHeight * cellSize + 120, sf::Color(70, 130, 180));
    Tank blueTank2(85, mapHeight * cellSize + 120, sf::Color(70, 130, 180));
    Tank lightBlueTank1(360, mapHeight * cellSize + 120, sf::Color(173, 216, 230));
    Tank lightBlueTank2(440, mapHeight * cellSize + 120, sf::Color(173, 216, 230));

    Tank redTank1(180, mapHeight * cellSize + 120, sf::Color(255, 99, 71)); // Tanque rojo 1
    Tank redTank2(260, mapHeight * cellSize + 120, sf::Color(255, 99, 71)); // Tanque rojo 2
    Tank yellowTank1(530, mapHeight * cellSize + 120, sf::Color(255, 255, 128)); // Tanque amarillo 1
    Tank yellowTank2(615, mapHeight * cellSize + 120, sf::Color(255, 255, 128)); // Tanque amarillo 2


    sf::RenderWindow window(sf::VideoMode(mapWidth * cellSize, mapHeight * cellSize + 180), "Tank Attack!");
    Tank* selectedTank = nullptr;

    sf::Font font;
    if (!font.loadFromFile("/home/viviana/Desktop/font/bebasneue.ttf")) {
        return -1;
    }

    sf::Text timerText, player1Text, player2Text, turnText, errorText;
    timerText.setFont(font);
    timerText.setCharacterSize(24);
    timerText.setFillColor(sf::Color::Black);;
    timerText.setPosition(10, mapHeight * cellSize + 6); 
    
    player1Text.setFont(font);
    player1Text.setCharacterSize(24);
    player1Text.setFillColor(sf::Color::Black);
    player1Text.setString("Jugador 1");
    player1Text.setPosition(150, mapHeight * cellSize + 50);

    player2Text.setFont(font);
    player2Text.setCharacterSize(24);
    player2Text.setFillColor(sf::Color::Black);
    player2Text.setString("Jugador 2");
    player2Text.setPosition(500, mapHeight * cellSize + 50);

    turnText.setFont(font);
    turnText.setCharacterSize(24);
    turnText.setFillColor(sf::Color::Black);
    turnText.setPosition(10, mapHeight * cellSize + 60);

    errorText.setFont(font);
    errorText.setCharacterSize(24);
    errorText.setFillColor(sf::Color::Red);
    errorText.setPosition(mapWidth * cellSize - 200, mapHeight * cellSize + 30);
    errorText.setString("");

    bool gameActive = true;  // Variable para controlar si el juego está activo
    float timer = 300;       // Tiempo en segundos
    sf::Clock clock;         // Reloj para el cronómetro

    // Variables de turno
    int currentPlayer = 1; // 1 para Jugador 1, 2 para Jugador 2
    int movesRemaining = 2; // Número de movimientos permitidos por turno

    float nuevaAltura = 150; 
    sf::RectangleShape backgroundRect(sf::Vector2f(mapWidth * cellSize, nuevaAltura));

    backgroundRect.setFillColor(sf::Color::White);
    backgroundRect.setPosition(0, window.getSize().y - nuevaAltura);



std::vector<Bullet> bullets; // Vector para almacenar las balas
bool bulletFired = false; // Variable para controlar si se ha disparado una bala en el turno

std::vector<Tank*> tanks = { 
    &blueTank1, &blueTank2, 
    &redTank1, &redTank2, // Agrega los tanques rojos
    &lightBlueTank1, &lightBlueTank2, 
    &yellowTank1, &yellowTank2 // Agrega los tanques amarillos
};

std::vector<int> lives = {2, 2, 2, 2, 2, 2, 2, 2}; // Dos vidas para cada tanque

while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (gameActive) {
            if (event.type == sf::Event::MouseButtonPressed) {
                float mouseX = event.mouseButton.x;
                float mouseY = event.mouseButton.y;

                // Limpiar caminos de todos los tanques antes de seleccionar uno nuevo
                for (auto& tank : tanks) {
                    tank->clearPath();
                }

                // Manejar la selección de los tanques del jugador actual
                if (currentPlayer == 1) {
                    if (blueTank1.contains(mouseX, mouseY)) {
                        if (selectedTank) selectedTank->deselect();
                        blueTank1.select();
                        selectedTank = &blueTank1;
                    } else if (blueTank2.contains(mouseX, mouseY)) {
                        if (selectedTank) selectedTank->deselect();
                        blueTank2.select();
                        selectedTank = &blueTank2;
                    } else if (redTank1.contains(mouseX, mouseY)) {
                        if (selectedTank) selectedTank->deselect();
                        redTank1.select();
                        selectedTank = &redTank1;
                    } else if (redTank2.contains(mouseX, mouseY)) {
                        if (selectedTank) selectedTank->deselect();
                        redTank2.select();
                        selectedTank = &redTank2;
                    }
                } else {
                    if (lightBlueTank1.contains(mouseX, mouseY)) {
                        if (selectedTank) selectedTank->deselect();
                        lightBlueTank1.select();
                        selectedTank = &lightBlueTank1;
                    } else if (lightBlueTank2.contains(mouseX, mouseY)) {
                        if (selectedTank) selectedTank->deselect();
                        lightBlueTank2.select();
                        selectedTank = &lightBlueTank2;
                    } else if (yellowTank1.contains(mouseX, mouseY)) {
                        if (selectedTank) selectedTank->deselect();
                        yellowTank1.select();
                        selectedTank = &yellowTank1;
                    } else if (yellowTank2.contains(mouseX, mouseY)) {
                        if (selectedTank) selectedTank->deselect();
                        yellowTank2.select();
                        selectedTank = &yellowTank2;
                    }
                }

                // Mover el tanque seleccionado
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (selectedTank && movesRemaining > 0) {
                        int targetX = mouseX / cellSize;
                        int targetY = mouseY / cellSize;

                        if (targetX >= 0 && targetX < mapWidth && targetY >= 0 && targetY < mapHeight) {
                            std::vector<std::pair<int, int>> path = gameMap.BFS(selectedTank->getPosition(), { targetX, targetY });

                            if (!path.empty()) {
                                selectedTank->moveToPosition(path);
                                movesRemaining--; // Reduce los movimientos restantes
                                errorText.setString(""); // Limpiar mensaje de error
                            } else {
                                errorText.setString("Camino bloqueado");
                                errorText.setPosition(mapWidth * cellSize - 180, mapHeight * cellSize + 50);
                                errorText.setFillColor(sf::Color(255, 182, 193)); 
                            }
                        }
                    }

                    // Comprobar si se debe pasar el turno
                    if (movesRemaining == 0) {
                        currentPlayer = (currentPlayer == 1) ? 2 : 1; // Cambiar de jugador
                        movesRemaining = 2; // Reiniciar movimientos para el nuevo jugador
                        selectedTank = nullptr; // Deseleccionar cualquier tanque
                        bulletFired = false; // Reiniciar la variable de disparo
                    }
                }

                // Disparar la bala si se hace clic derecho
                if (event.mouseButton.button == sf::Mouse::Right) {
                    if (selectedTank && !bulletFired) {
                        bullets.emplace_back(
                            selectedTank->getPosition().x, 
                            selectedTank->getPosition().y, 
                            mouseX, 
                            mouseY
                        );
                        bulletFired = true; // Marcar que se ha disparado una bala
                    }
                }
            }

            if (selectedTank && event.type == sf::Event::MouseButtonReleased) {
                // Eliminar el movimiento al soltar el clic del mouse
                if (event.mouseButton.button == sf::Mouse::Left) {
                    float newX = event.mouseButton.x;
                    float newY = event.mouseButton.y;
                    selectedTank->move(newX - selectedTank->getPosition().x, newY - selectedTank->getPosition().y);
                }
            }
        }
    }

    // Actualizar el cronómetro solo si el juego está activo
    if (gameActive) {
        timer -= clock.restart().asSeconds();
        if (timer <= 0) {
            timer = 0;
            gameActive = false; // Detener el juego cuando el tiempo se agota
        }
    }

    // Actualiza las balas
    for (auto it = bullets.begin(); it != bullets.end();) {
        it->update(); // Actualiza la posición de la bala

        if (it->shouldRemove()) {
            it = bullets.erase(it); // Elimina la bala si ha rebotado 2 veces
        } else {
            // Comprobar colisiones con los tanques
            bool collided = false;
            for (size_t i = 0; i < tanks.size(); ++i) {
                if (tanks[i]->contains(it->getShape().getPosition().x, it->getShape().getPosition().y) && 
                    tanks[i] != selectedTank) {
                    lives[i]--; // Reduce la vida del tanque
                    if (lives[i] <= 0) {
                        tanks[i]->deactivate(); // Desactiva el tanque
                    }
                    it = bullets.erase(it); // Elimina la bala si colisionó
                    collided = true; // Marca que hubo colisión
                    break; // Sal del bucle de colisión
                }
            }

            if (!collided) {
                ++it; // Solo avanza si no hubo colisión
            }
        }
    }

    // Mostrar el tiempo restante
    int minutes = static_cast<int>(timer) / 60;
    int seconds = static_cast<int>(timer) % 60;
    std::ostringstream oss;
    oss << "Tiempo: " << minutes << ":" << (seconds < 10 ? "0" : "") << seconds;
    timerText.setString(oss.str());

    // Actualizar el texto del turno
    turnText.setString("Turno: Jugador " + std::to_string(currentPlayer));
    turnText.setPosition(mapWidth * cellSize - 176, mapHeight * cellSize + 10);

    window.clear(sf::Color::White);
    gameMap.draw(window);
    window.draw(backgroundRect);
    window.draw(timerText);
    window.draw(player1Text);
    window.draw(player2Text);
    window.draw(turnText);
    window.draw(errorText);

    // Dibujar las vidas de los tanques
    for (size_t i = 0; i < tanks.size(); ++i) {
        sf::Text lifeText;
        lifeText.setFont(font);
        lifeText.setCharacterSize(24);
        lifeText.setFillColor(sf::Color::Black);
        lifeText.setString("Vidas: " + std::to_string(lives[i]));
        lifeText.setPosition(tanks[i]->getPosition().x, tanks[i]->getPosition().y - 30);
        window.draw(lifeText);
    }

    // Dibujar tanques
    blueTank1.draw(window);
    blueTank2.draw(window);
    lightBlueTank1.draw(window);
    lightBlueTank2.draw(window);

    // Dibujar las balas
    for (const auto& bullet : bullets) {
        bullet.draw(window);
    }

    // Dibujar los tanques activos
    for (const auto& tank : tanks) {
        if (tank->isActive()) {
            tank->draw(window);
        }
    }

    // Si el tiempo se ha agotado, muestra un mensaje en pantalla
    if (!gameActive) {
        sf::Text endText("El tiempo ha terminado", font, 30);
        endText.setFillColor(sf::Color::Black);
        endText.setPosition(mapWidth * cellSize / 2 - 150, mapHeight * cellSize / 2); // Centrado
        window.draw(endText);
    }

    window.display();
}

return 0;

}