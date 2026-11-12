#include "creature.hpp"
#include "raymath.h"
#include <algorithm>
#include <cmath>
#include <limits>

CreatureLevel::CreatureLevel() : LevelSystem(1 , 18) {}

ld CreatureLevel::getRequiredExp() const {
    if (_currentLevel >= _maxLevel) return std::numeric_limits<ld>::max();
    return std::pow(kExpGrowthRate , _currentLevel - 1) * kExpBase;
}

void CreatureLevel::update(ld experienceBonus) {
    _currentExperience += experienceBonus;
    while (_currentLevel < _maxLevel && _currentExperience >= getRequiredExp())
        _currentExperience -= getRequiredExp() , _currentLevel ++;
    while (_currentExperience < 0.0 && _currentLevel > 0)
        _currentLevel -- , _currentExperience += getRequiredExp();
    if (_currentExperience < 0.0) _currentExperience = 0.0;
}

ld CreatureLevel::getPercent() const {
    if (_currentLevel == _maxLevel) return 100.0;
    return _currentExperience * 100 / getRequiredExp();
}

Vector2 Creature::getPos() const {return _position;}

float Creature::distanceTo(Vector2 target) const {
    return Vector2Distance(_position , target);
}

Vector2 Creature::directionTo(Vector2 target) const {
    return Vector2Normalize(Vector2Subtract(target , _position));
}

void Creature::updateMovement(Vector2 movement , float deltaTime , float radius , float bobHeight) {
    const float speed = static_cast<float>(_moveSpeed._current);
    const float screenWidth = static_cast<float>(GetScreenWidth());
    const float screenHeight = static_cast<float>(GetScreenHeight());
    const float angle = kRotationDegrees * DEG2RAD;
    // Chừa cả xoay, co giãn và bob để sprite không đè lên viền.
    const float spriteExtent = radius * (1 + kStretchRatio) * (std::cos(angle) + std::sin(angle)) + bobHeight;
    const float minPosition = kRoomBorderWidth + spriteExtent;

    movement = Vector2Normalize(movement);
    const Vector2 previousPosition = _position;
    _position.x += movement.x * speed * deltaTime;
    _position.y += movement.y * speed * deltaTime;
    if (movement.x != 0) _facingRight = movement.x > 0;

    if (_position.x < minPosition) _position.x = minPosition;
    if (_position.x > screenWidth - minPosition) _position.x = screenWidth - minPosition;
    if (_position.y < minPosition) _position.y = minPosition;
    if (_position.y > screenHeight - minPosition) _position.y = screenHeight - minPosition;

    const bool moved = _position.x != previousPosition.x || _position.y != previousPosition.y;
    _state = moved ? MOVE_RUNNING : MOVE_IDLE;
    _animationTime = moved ? _animationTime + deltaTime : 0.0f;
}

void Creature::drawMovement(Texture2D texture , float radius , float bobHeight) const {
    const float step = _state == MOVE_RUNNING ? std::sin(_animationTime * 12.0f) : 0.0f;
    const float frameWidth = static_cast<float>(texture.width);
    const float frameHeight = static_cast<float>(texture.height);
    const float scale = radius * 2 / std::max(frameWidth , frameHeight);
    const float width = frameWidth * scale * (1.0f + step * kStretchRatio);
    const float height = frameHeight * scale * (1.0f - step * kStretchRatio);
    const Rectangle source = {0.0f , 0.0f , _facingRight ? frameWidth : -frameWidth , frameHeight};
    const Rectangle destination = {_position.x , _position.y - std::abs(step) * bobHeight , width , height};
    DrawTexturePro(texture , source , destination , Vector2{width / 2 , height / 2} , step * kRotationDegrees , WHITE);
}
