#include "Pawn.h"
#include "Camera.h"

Pawn::Pawn(sf::RenderWindow& window, int hp_, float posX_, float posY_, float sizeX_, float sizeY_, float power_jump_, float speed_, std::string image, float Iframe_, StateMachine& state_ ) : state(state_)
{
    hp = hp_;
    pos = {posX_, posY_};
    size = { sizeX_, sizeY_ };

    rect.setPosition({ posX_, posY_ });
    rect.setSize({sizeX_, sizeY_});

    power_jump = power_jump_;
    speed = speed_;

    Iframe = Iframe_;
    IframeTimer = Iframe;

    rect.setFillColor(sf::Color::Green);

    canDB = false;
    canFloat = false;
}

void Pawn::update(float dt, const std::vector<Collider*>& colliders) {

}

void Pawn::render(sf::RenderWindow& window) {
    //window.draw(rect);
}

bool Pawn::intersects(const sf::FloatRect& a, const sf::FloatRect& b) {
    return a.position.x < b.position.x + b.size.x &&
        a.position.x + a.size.x > b.position.x &&
        a.position.y < b.position.y + b.size.y &&
        a.position.y + a.size.y > b.position.y;
}

void Pawn::collision(float dt, const std::vector<Collider*>& colliders) {
    pos.x += velocityX * dt;

    PlayerLeft = pos.x;
    PlayerRight = pos.x + size.x;
    PlayerTop = pos.y;
    PlayerBottom = pos.y + size.y;

    for (auto c : colliders) {
        ColliderLeft = c->pos.x;
        ColliderRight = c->pos.x + c->size.x;
        ColliderTop = c->pos.y;
        ColliderBottom = c->pos.y + c->size.y;

        if (!intersects({ pos, size }, { c->pos, c->size })) continue;
        if (!(PlayerBottom > ColliderTop && PlayerTop < ColliderBottom)) continue;

        if (velocityX > 0)      pos.x = ColliderLeft - size.x;
        else if (velocityX < 0) pos.x = ColliderRight;

        velocityX = 0;
        PlayerLeft = pos.x;
        PlayerRight = pos.x + size.x;
    }

    pos.y += velocityY * dt;
    isGrounded = false;

    PlayerTop = pos.y;
    PlayerBottom = pos.y + size.y;

    for (auto c : colliders) {
        ColliderLeft = c->pos.x;
        ColliderRight = c->pos.x + c->size.x;
        ColliderTop = c->pos.y;
        ColliderBottom = c->pos.y + c->size.y;

        if (!intersects({ pos, size }, { c->pos, c->size })) continue;
        if (!(PlayerRight > ColliderLeft && PlayerLeft < ColliderRight)) continue;

        if (velocityY > 0) {
            pos.y = ColliderTop - size.y;
            isGrounded = true;
            isDoubleJumping = false;
        }
        else if (velocityY < 0) {
            pos.y = ColliderBottom;
        }

        velocityY = 0;
        PlayerTop = pos.y;
        PlayerBottom = pos.y + size.y;
    }
}

void Pawn::takedamage(int dmg) {
    if (!isInvincible) { 
        hp -= dmg;
        isInvincible = true;
        IframeTimer = Iframe;
    }
    if (hp <= 0) {
        isalive = false;
    }
}

void Pawn::death() {}

Pawn::~Pawn() {}