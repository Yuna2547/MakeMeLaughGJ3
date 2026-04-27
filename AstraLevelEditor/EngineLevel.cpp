#include "EngineLevel.h"
#include "Global.h"


EngineLevel::EngineLevel(sf::RenderWindow& window, Global& var_) {
    backgroundTexture.loadFromFile("level/class.png");

    backgroundSprite = new sf::Sprite(backgroundTexture);

    sf::Vector2u texSize = backgroundTexture.getSize();
    sf::Vector2u winSize = window.getSize();
    backgroundSprite->setScale({ static_cast<float>(winSize.x) / texSize.x, static_cast<float>(winSize.y) / texSize.y });
}

EngineLevel::~EngineLevel() {
	delete backgroundSprite;
	backgroundSprite = nullptr;
}

void EngineLevel::onComputerDialogFinished() {
}

void EngineLevel::onChoiceMade(ChoiceDialog::Choice choice) {
}

void EngineLevel::update(const bool* keys, float dt) {
}

void EngineLevel::displayScene(sf::RenderWindow& window) {
	window.draw(*backgroundSprite);
  
}

void EngineLevel::nextScene(SceneState& currentScene, keys* _myKeys, sf::RenderWindow& window) {
}