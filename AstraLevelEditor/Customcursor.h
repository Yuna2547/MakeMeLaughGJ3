#pragma once
#include <SFML/Graphics.hpp>

class CustomCursor {
public:
    enum class Mode { Hand, Feather };

    CustomCursor(sf::RenderWindow& window, const std::string& handPath, const std::string& featherPath);

    void setMode(Mode mode);
    Mode getMode() const;

    void update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

private:
    sf::Texture  handTexture;
    sf::Texture  featherTexture;
    sf::RectangleShape sprite;
    Mode currentMode;

    void applyTexture();
};