#pragma once

using ld = long double;
using ll = long long;

inline constexpr float kRoomBorderWidth = 10.0f;

enum class CharacterClass {
    None , Warrior , Berserker , Assassin ,
    Ranger , Mage , Spellblade , Cleric ,
};

#define CT_NONE CharacterClass::None
#define CT_WARRIOR CharacterClass::Warrior
#define CT_BERSERKER CharacterClass::Berserker
#define CT_ASSASSIN CharacterClass::Assassin
#define CT_RANGER CharacterClass::Ranger
#define CT_MAGE CharacterClass::Mage
#define CT_SPELLBLADE CharacterClass::Spellblade
#define CT_CLERIC CharacterClass::Cleric

struct LevelSystem {
    int _currentLevel;
    int _maxLevel;
    ld _currentExperience;

    LevelSystem(int currentLevel , int maxLevel);
};

struct Resource {
    ld _base;
    ld _current;
    ld _max;
    ld _min;
    //assert : _min <= current <= _max
};

struct CombatStats {
    //can recover
    Resource _hp;
    Resource _mana;
    Resource _stamina;

    //stats
    ld _attack;
    ld _specialAttack;
    ld _defense;
    ld _specialDefense;
    ld _movementSpeed;
    ld _criticalRate;
    ld _criticalDamage;

    //adtional stats :>
    ld _attackSpeed;
    ld _fixDam;
    ld _dirDam;
};

enum class Element {
    Fire , Wind , Earth , Water , None
};

#define ELEM_FIRE Element::Fire
#define ELEM_WIND Element::Wind
#define ELEM_EARTH Element::Earth
#define ELEM_WATER Element::Water
#define ELEM_NONE Element::None
