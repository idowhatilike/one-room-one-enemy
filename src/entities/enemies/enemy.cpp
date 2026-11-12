#include "enemy.hpp"

Enemy::Enemy() : Creature{} {
    _moveSpeed = {300.0L , 300.0L , 300.0L , 0.0L};
    _position = {850.0f , 450.0f};
}

void Enemy::update(Vector2 movement , float deltaTime) {
    updateMovement(movement , deltaTime , kRadius , kBobHeight);
}

void Enemy::draw(Texture2D texture) const {
    drawMovement(texture , kRadius , kBobHeight);
}

bool Enemy::isPlayerInRange(Vector2 playerPos) const {
    return distanceTo(playerPos) <= kAtkRange;
}

bool Enemy::isPlayerInRange(const Creature &player) const {
    return isPlayerInRange(player.getPos());
}

void Enemy::chasePlayer(Vector2 playerPos , float deltaTime) {
    const float speed = static_cast<float>(_moveSpeed._current);
    const float distance = distanceTo(playerPos);
    if (speed > 0 && speed * deltaTime > distance) deltaTime = distance / speed;
    update(directionTo(playerPos) , deltaTime);
}

void Enemy::chasePlayer(const Creature &player , float deltaTime) {
    chasePlayer(player.getPos() , deltaTime);
}
