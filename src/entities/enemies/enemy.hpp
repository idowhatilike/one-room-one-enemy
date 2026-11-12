#pragma once

#include "../../shared/creature.hpp"
#include "../../shared/weapon.hpp"
#include "raylib.h"



struct Enemy : Creature {
    static constexpr float kRadius = 50.0f;
    static constexpr float kBobHeight = 2.36f;
    static constexpr float kAtkRange = 3.67f;

    Weapon _mainHand{};

    Enemy();
    void update(Vector2 movement , float deltaTime);
    void draw(Texture2D texture) const;
    bool isPlayerInRange(Vector2 playerPos) const;
    bool isPlayerInRange(const Creature &player) const;
    void chasePlayer(Vector2 playerPos , float deltaTime);
    void chasePlayer(const Creature &player , float deltaTime);
};
