#include "CustomCursor.h"

CustomCursor::CustomCursor(sf::RenderWindow& window, const std::string& handPath, const std::string& featherPath) : currentMode(Mode::Hand){
    handTexture.loadFromFile(handPath);
    featherTexture.loadFromFile(featherPath);

    window.setMouseCursorVisible(false);

    sprite.setSize({ 200.f, 200.f });
    applyTexture();
}

void CustomCursor::setMode(Mode mode) {
    currentMode = mode;
    applyTexture();
}

CustomCursor::Mode CustomCursor::getMode() const {
    return currentMode;
}

void CustomCursor::update(sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sprite.setPosition({ static_cast<float>(mousePos.x - 100), static_cast<float>(mousePos.y - 80) });
}

void CustomCursor::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void CustomCursor::applyTexture() {
    sf::Texture& tex = (currentMode == Mode::Hand) ? handTexture : featherTexture;
    sprite.setTexture(&tex);
    sprite.setTextureRect({ {0, 0}, { static_cast<int>(tex.getSize().x), static_cast<int>(tex.getSize().y) } });
}