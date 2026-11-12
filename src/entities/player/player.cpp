#include "player.hpp"

Player::Player() : Creature{} {
    _moveSpeed = {300.0L , 300.0L , 300.0L , 0.0L};
    _position = {600.0f , 450.0f};
}

void Player::inputHandler(float deltaTime){
    Vector2 movement{};
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) movement.x += 1;
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) movement.x -= 1;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) movement.y += 1;
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) movement.y -= 1;

    update(movement , deltaTime);
}

void Player::update(Vector2 movement , float deltaTime) {
    updateMovement(movement , deltaTime , kRadius , kBobHeight);
}

void Player::draw(Texture2D texture) const {
    drawMovement(texture , kRadius , kBobHeight);
}
