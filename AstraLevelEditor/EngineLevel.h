#pragma once
#include "Scene.h"

#include "LevelLoader.h"
#include "Collider.h"
#include "Camera.h"
#include "PlayerEX.h"
#include "Trigger.h"
#include "BG_parralax_Full.h"
#include "Dialog.h"
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

	void onComputerDialogFinished();
	void onChoiceMade(ChoiceDialog::Choice choice);

public:
	sf::Texture backgroundTexture;
	sf::Sprite* backgroundSprite;
};