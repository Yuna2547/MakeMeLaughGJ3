#include "SceneManager.h"

SceneManager* SceneManager::Instance = nullptr;

SceneManager::SceneManager(sf::RenderWindow& window) {

	currentState = SceneState::Elevel;
	previousState = SceneState::Elevel;

	MyLevel = new EngineLevel(window, var);
}

SceneManager::~SceneManager() {
	if (MyLevel) {
		delete MyLevel;
	}

	MyLevel = nullptr;

}

void SceneManager::manageState(keys* _myKeys, sf::RenderWindow& window) {

	previousState = currentState;

	if (currentState == SceneState::Elevel) {
		MyLevel->nextScene(currentState, _myKeys, window);
	}
	//else if (currentState == SceneState::Map1) {
	//	MyLevel0->nextScene(currentState, _myKeys, window);
	//}

	if (currentState != previousState)
	{
		//if (previousState == SceneState::Map1) {
		//	delete MyLevel0;
		//	MyLevel0 = nullptr;
		//}

		//if (currentState == SceneState::Map1)
		//	MyLevel0 = new Level0(window, var);

		//else if (currentState == SceneState::Map2)
		//	MyLevel1 = new Level1(window, var);

	}
}

void SceneManager::displayState(sf::RenderWindow& window) {
	switch (currentState)
	{
	case SceneState::Elevel:
		MyLevel->displayScene(window);
		break;
	}
}

void SceneManager::updateState(const bool* keys, float dt, sf::RenderWindow& window) {
	if (currentState == SceneState::Elevel) {
		static_cast<EngineLevel*>(MyLevel)->update(keys, dt);
	}
	//else if (currentState == SceneState::Map1) {
	//	static_cast<Level0*>(MyLevel0)->update(keys, dt);
	//}
}

SceneState SceneManager::getState() const {
	return currentState;
}

SceneManager* SceneManager::GetSceneManager()
{
	return Instance;
}