#include "PlayerEX.h"

#include <iostream>

PlayerEX::PlayerEX( sf::RenderWindow& window, int hp_, float posX_, float posY_, float sizeX_, float sizeY_, float power_jump_, float speed_, std::string image, float Iframe_, StateMachine& state_
) : Pawn(window, hp_, posX_, posY_, sizeX_, sizeY_, power_jump_, speed_, image, Iframe_, state_){
}

void PlayerEX::update(float dt, const std::vector<Collider*>& colliders) {

    state.update(dt, *this);

    Pawn::collision(dt, colliders);
    

    if (isalive == false) {
        death();
    }

    rect.setPosition(pos);
}

void PlayerEX::death() {
    pos = { Rez };
    hp = 3;
    isalive = true;
}