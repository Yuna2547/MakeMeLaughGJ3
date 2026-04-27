#include "StateMachine.h"
#include "Pawn.h"  

StateMachine::StateMachine(IState* startState) : currentState(startState) {}

void StateMachine::update(float dt, Pawn& pawn)
{
	currentState->update(dt, pawn);
	IState* next = currentState->nextState;
	if (next != nullptr && next != currentState)
	{
		delete currentState;
		currentState = next;
		currentState->nextState = nullptr;
	}
}

StateMachine::~StateMachine()
{
	delete currentState;
	currentState = nullptr;
}

static bool pressLeft(){
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q);
}
static bool pressRight(){
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
}
static bool pressUp(){
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z);
}
static bool pressDown(){
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);
}

IdleStateRight::IdleStateRight(Pawn& pawn) {
	rect = new TXanimated();
	rect->load("sprite/idleright.txt", 120, 120, pawn.pos.x, pawn.pos.y);
}

void IdleStateRight::update(float dt, Pawn& pawn) {
	pawn.velocityX = 0;
	pawn.velocityY = 0;
	rect->update(dt);
	rect->rect.setPosition(pawn.pos);

	if (pressLeft()) {
		nextState = new MovingLeftState(pawn);
		return;
	}
	if (pressRight()) {
		nextState = new MovingRightState(pawn);
		return;
	}
	if (pressUp()) {
		nextState = new MovingUpState(pawn);
		return;
	}
	if (pressDown()) {
		nextState = new MovingDownState(pawn);
		return;
	}
}

void IdleStateRight::render(sf::RenderWindow& window) {
	rect->render(window);
}

IdleStateLeft::IdleStateLeft(Pawn& pawn) {
	rect = new TXanimated();
	rect->load("sprite/idleleft.txt", 120, 120, pawn.pos.x, pawn.pos.y);
}

void IdleStateLeft::update(float dt, Pawn& pawn) {
	pawn.velocityX = 0;
	pawn.velocityY = 0;
	rect->update(dt);
	rect->rect.setPosition(pawn.pos);

	if (pressLeft()) {
		nextState = new MovingLeftState(pawn);
		return;
	}
	if (pressRight()) {
		nextState = new MovingRightState(pawn);
		return;
	}
	if (pressUp()) {
		nextState = new MovingUpState(pawn);
		return;
	}
	if (pressDown()) {
		nextState = new MovingDownState(pawn);
		return;
	}
}

void IdleStateLeft::render(sf::RenderWindow& window) {
	rect->render(window);
}

IdleStateUp::IdleStateUp(Pawn& pawn) {
	rect = new TXanimated();
	rect->load("sprite/idleup.txt", 120, 120, pawn.pos.x, pawn.pos.y);
}

void IdleStateUp::update(float dt, Pawn& pawn) {
	pawn.velocityX = 0;
	pawn.velocityY = 0;
	rect->update(dt);
	rect->rect.setPosition(pawn.pos);

	if (pressLeft()) {
		nextState = new MovingLeftState(pawn);
		return;
	}
	if (pressRight()) {
		nextState = new MovingRightState(pawn);
		return;
	}
	if (pressUp()) {
		nextState = new MovingUpState(pawn);
		return;
	}
	if (pressDown()) {
		nextState = new MovingDownState(pawn);
		return;
	}
}

void IdleStateUp::render(sf::RenderWindow& window) {
	rect->render(window);
}

IdleStateDown::IdleStateDown(Pawn& pawn) {
	rect = new TXanimated();
	rect->load("sprite/idledown.txt", 120, 120, pawn.pos.x, pawn.pos.y);
}

void IdleStateDown::update(float dt, Pawn& pawn) {
	pawn.velocityX = 0;
	pawn.velocityY = 0;
	rect->update(dt);
	rect->rect.setPosition(pawn.pos);

	if (pressLeft()) {
		nextState = new MovingLeftState(pawn);
		return;
	}
	if (pressRight()) {
		nextState = new MovingRightState(pawn);
		return;
	}
	if (pressUp()) {
		nextState = new MovingUpState(pawn);
		return;
	}
	if (pressDown()) {
		nextState = new MovingDownState(pawn);
		return;
	}
}

void IdleStateDown::render(sf::RenderWindow& window) {
	rect->render(window);
}

MovingLeftState::MovingLeftState(Pawn& pawn) {
	rect = new TXanimated();
	rect->load("sprite/walkingleftMari.txt", 120, 120, pawn.pos.x, pawn.pos.y);
}

void MovingLeftState::update(float dt, Pawn& pawn)
{
	pawn.velocityX = -pawn.speed;
	pawn.velocityY = 0;
	rect->update(dt);
	rect->rect.setPosition(pawn.pos);

	if (!pressLeft() && !pressRight() && !pressUp() && !pressDown()) {
		nextState = new IdleStateLeft(pawn);
		return;
	}

	if (pressRight() && !pressUp() && !pressDown()) {
		nextState = new MovingRightState(pawn);
		return;
	}
	if (pressUp() && !pressLeft() && !pressRight() && !pressDown()) {
		nextState = new MovingUpState(pawn);
		return;
	}
	if (pressDown() && !pressLeft() && !pressRight() && !pressUp()) {
		nextState = new MovingDownState(pawn);
		return;
	}
}

void MovingLeftState::render(sf::RenderWindow& window) {
	rect->render(window);
}

MovingRightState::MovingRightState(Pawn& pawn) {
	rect = new TXanimated();
	rect->load("sprite/walkingrightMari.txt", 120, 120, pawn.pos.x, pawn.pos.y);
}

void MovingRightState::update(float dt, Pawn& pawn) {
	pawn.velocityX = pawn.speed;
	pawn.velocityY = 0;
	rect->update(dt);
	rect->rect.setPosition(pawn.pos);

	if (!pressLeft() && !pressRight() && !pressUp() && !pressDown()) {
		nextState = new IdleStateRight(pawn);
		return;
	}

	if (pressLeft() && !pressUp() && !pressDown()) {
		nextState = new MovingLeftState(pawn);
		return;
	}
	if (pressUp() && !pressLeft() && !pressRight() && !pressDown()) {
		nextState = new MovingUpState(pawn);
		return;
	}
	if (pressDown() && !pressLeft() && !pressRight() && !pressUp()) {
		nextState = new MovingDownState(pawn);
		return;
	}
}

void MovingRightState::render(sf::RenderWindow& window) {
	rect->render(window);
}

void IState::setState(IState* state) {
	if (nextState != nullptr)
	{
		delete nextState;
	}
	nextState = state;
}

MovingDownState::MovingDownState(Pawn& pawn) {
	rect = new TXanimated();
	rect->load("sprite/walkingdownMari.txt", 120, 120, pawn.pos.x, pawn.pos.y);
}

void MovingDownState::update(float dt, Pawn& pawn)
{
	pawn.velocityY = pawn.speed;
	pawn.velocityX = 0;
	rect->update(dt);
	rect->rect.setPosition(pawn.pos);

	if (!pressLeft() && !pressRight() && !pressUp() && !pressDown()) {
		nextState = new IdleStateDown(pawn);
		return;
	}

	if (pressUp() && !pressLeft() && !pressRight() && !pressDown()) {
		nextState = new MovingUpState(pawn);
		return;
	}
	if (pressRight() && !pressLeft() && !pressUp() && !pressDown()) {
		nextState = new MovingRightState(pawn);
		return;
	}
	if (pressLeft() && !pressRight() && !pressUp() && !pressDown()) {
		nextState = new MovingLeftState(pawn);
		return;
	}
}

void MovingDownState::render(sf::RenderWindow& window) {
	rect->render(window);
}



MovingUpState::MovingUpState(Pawn& pawn) {
	rect = new TXanimated();
	rect->load("sprite/walkingupMari.txt", 120, 120, pawn.pos.x, pawn.pos.y);
}

void MovingUpState::update(float dt, Pawn& pawn)
{
	pawn.velocityY = -pawn.speed;
	pawn.velocityX = 0;
	rect->update(dt);
	rect->rect.setPosition(pawn.pos);

	if (!pressLeft() && !pressRight() && !pressUp() && !pressDown()) {
		nextState = new IdleStateUp(pawn);
		return;
	}

	if (pressDown() && !pressLeft() && !pressRight() && !pressUp()) {
		nextState = new MovingDownState(pawn);
		return;
	}
	if (pressRight() && !pressLeft() && !pressUp() && !pressDown()) {
		nextState = new MovingRightState(pawn);
		return;
	}
	if (pressLeft() && !pressRight() && !pressUp() && !pressDown()) {
		nextState = new MovingLeftState(pawn);
		return;
	}
}

void MovingUpState::render(sf::RenderWindow& window) {
	rect->render(window);
}