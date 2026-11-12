#pragma once

#include "base.hpp"
#include "raylib.h"
#include <string>

enum class MoveState {
    Idle , Running ,
};

#define MOVE_IDLE MoveState::Idle
#define MOVE_RUNNING MoveState::Running

enum class Relationship {
    Enemy , Rival , Friend , Lover ,
    Soulmate , Family , Teammate , None , Neutral ,
};

enum class SpeciesType {
    Human , Elf , Orc , Dragon ,
    Demon , Angel , Animal , Slime ,
    Undead , Mechanic , God , Unknown ,
    ElementalEntity ,
};

enum class StatusEffect {
    Sleep , Poison , Burn , Freeze ,
    Paralysis , Stun , Bleed , None ,
};

#define REL_ENEMY Relationship::Enemy
#define REL_RIVAL Relationship::Rival
#define REL_FRIEND Relationship::Friend
#define REL_LOVER Relationship::Lover
#define REL_SOULMATE Relationship::Soulmate
#define REL_FAMILY Relationship::Family
#define REL_TEAMMATE Relationship::Teammate
#define REL_NONE Relationship::None
#define REL_NEUTRAL Relationship::Neutral

#define SPEC_HUMAN SpeciesType::Human
#define SPEC_ELF SpeciesType::Elf
#define SPEC_ORC SpeciesType::Orc
#define SPEC_DRAGON SpeciesType::Dragon
#define SPEC_DEMON SpeciesType::Demon
#define SPEC_ANGEL SpeciesType::Angel
#define SPEC_ANIMAL SpeciesType::Animal
#define SPEC_SLIME SpeciesType::Slime
#define SPEC_UNDEAD SpeciesType::Undead
#define SPEC_MECHANIC SpeciesType::Mechanic
#define SPEC_GOD SpeciesType::God
#define SPEC_UNKNOWN SpeciesType::Unknown
#define SPEC_ELEMENTAL_ENTITY SpeciesType::ElementalEntity

#define FX_SLEEP StatusEffect::Sleep
#define FX_POISON StatusEffect::Poison
#define FX_BURN StatusEffect::Burn
#define FX_FREEZE StatusEffect::Freeze
#define FX_PARALYSIS StatusEffect::Paralysis
#define FX_STUN StatusEffect::Stun
#define FX_BLEED StatusEffect::Bleed
#define FX_NONE StatusEffect::None

struct CreatureLevel : LevelSystem {
    CreatureLevel();

    static constexpr ld kExpGrowthRate = 1.367 , kExpBase = 367;
    ld getRequiredExp() const;
    void update(ld experienceBonus);
    ld getPercent() const;
};

struct Friendship {
    ld _intimacy; // 0 -> 100%
    Relationship _status;
};

struct Creature {
    static constexpr float kStretchRatio = 0.04f , kRotationDegrees = 3.0f;

    //info
    std::string _name;
    SpeciesType _species;
    CharacterClass _characterClass = CT_NONE;
    Friendship _friendship;
    StatusEffect _statusEffect;
    Element _elementalWeakness = ELEM_NONE;
    Element _elementalResistance = ELEM_NONE;
    //base stats
    Resource _hp;
    Resource _mana;
    Resource _stamina;
    Resource _moveSpeed;
    //combat stats
    CreatureLevel _level;
    CombatStats _combatStats;
    Vector2 _position{};
    MoveState _state = MOVE_IDLE;
    
    bool _facingRight = true;
    float _animationTime = 0.0f;

    Vector2 getPos() const;
    float distanceTo(Vector2 target) const;
    Vector2 directionTo(Vector2 target) const;
    void updateMovement(Vector2 movement , float deltaTime , float radius , float bobHeight);
    void drawMovement(Texture2D texture , float radius , float bobHeight) const;
};
