#pragma once
#include "Scene.h"

#include "LevelLoader.h"
#include "Collider.h"
#include "Camera.h"
#include "PlayerEX.h"
#include "Trigger.h"
#include "BG_parralax_Full.h"
#include "Dialog.h"
#include "CustomCursor.h"
#include <SFML/Audio.hpp>

#include "DebugDisplay.h"

class Global;

class EngineLevel : public Scene {
public:

	EngineLevel(sf::RenderWindow& window, Global& var_);
	~EngineLevel();

	void displayScene(sf::RenderWindow& window) override;
	void update(const bool* keys, float dt);
	void nextScene(SceneState& currentScene, keys* _myKeys, sf::RenderWindow& window) override;

	void handleEvent(const sf::Event& event, sf::RenderWindow& window);

	void onComputerDialogFinished();
	void onChoiceMade(ChoiceDialog::Choice choice);

public:
	Dialog* dialog;
	sf::Texture backgroundTexture;
	sf::Sprite* backgroundSprite;

	sf::Texture alexTexture;
	sf::Sprite* alexSprite;

	CustomCursor* cursor;

	sf::Font buttonFont;

	sf::RectangleShape featherButton;
	sf::Text* featherButtonText;

	sf::RectangleShape handButton;
	sf::Text* handButtonText;

	sf::RectangleShape jokeButton;
	sf::Text* jokeButtonText;

	sf::RectangleShape teaseButton;
	sf::Text* teaseButtonText;
	bool wasMousePressed;

	bool alexIsSad = false;
	float alexSadTimer = 0.0f;
	bool triste = false;

	sf::Music oof;
};