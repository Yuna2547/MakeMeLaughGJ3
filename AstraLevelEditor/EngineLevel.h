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

struct TriggerDialog {
	Trigger* trigger;
	Dialog* dialog;
	bool interacted = false;
	bool triggersChoice = false;
};

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
	sf::Music music;
	DebugDisplay* fps;
	StateMachine* Machine;
	LevelLoader* loader;
	PlayerEX* player;
	Camera* cam;
	std::vector<Collider*> Colliderlist;
	BG_parralax_Full* parralax;

	std::vector<Trigger*>       triggers;
	std::vector<TriggerDialog>  dialogs;

	bool pressed = false;

	sf::Font font;
	sf::Text* fpstext;

	Global& glob;

	ChoiceDialog  choiceOverlay;
	Dialog* followUpDialog = nullptr;

	const sf::RenderWindow* win = nullptr;
};