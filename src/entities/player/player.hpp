#pragma once

#include "../../shared/creature.hpp"
#include "../../shared/weapon.hpp"
#include "raylib.h"

struct Player : Creature {
    static constexpr float kRadius = 40.0f;
    static constexpr float kBobHeight = 1.5f;

    Weapon _mainHand{};

    Player();
    void inputHandler(float deltaTime);
    void update(Vector2 movement , float deltaTime);
    void draw(Texture2D texture) const;
};
