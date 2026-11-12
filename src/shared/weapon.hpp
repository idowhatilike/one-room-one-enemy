#pragma once

#include "base.hpp"
#include <string>

enum class WeaponType {
    Sword , Bow , Axe , Arrow , 
    Shield , Hook , Lance , GreatSword , 
    Crossbow , Dagger , Staff , Wand , 
    SpellSword , Mace , None , 
};

#define WPN_SWORD WeaponType::Sword
#define WPN_BOW WeaponType::Bow
#define WPN_AXE WeaponType::Axe
#define WPN_ARROW WeaponType::Arrow
#define WPN_SHIELD WeaponType::Shield
#define WPN_HOOK WeaponType::Hook
#define WPN_LANCE WeaponType::Lance
#define WPN_GREAT_SWORD WeaponType::GreatSword
#define WPN_CROSSBOW WeaponType::Crossbow
#define WPN_DAGGER WeaponType::Dagger
#define WPN_STAFF WeaponType::Staff
#define WPN_WAND WeaponType::Wand
#define WPN_SPELL_SWORD WeaponType::SpellSword
#define WPN_MACE WeaponType::Mace
#define WPN_NONE WeaponType::None

enum class Master {
    Basic , Expert , Master , Champion , Grandmaster , Oneness ,
};

#define MASTER_BASIC Master::Basic
#define MASTER_EXPERT Master::Expert
#define MASTER_MASTER Master::Master
#define MASTER_CHAMPION Master::Champion
#define MASTER_GRANDMASTER Master::Grandmaster
#define MASTER_ONENESS Master::Oneness

struct WeaponAffinity {
    ld _affinityRatio;
    int _softCapLevel;
};

inline constexpr WeaponAffinity kIncompatible = {0.5L , 1};
inline constexpr WeaponAffinity kAwkward = {0.75L , 2};
inline constexpr WeaponAffinity kVersatile = {1.0L , 3};
inline constexpr WeaponAffinity kPrimary = {1.25L , 4};
inline constexpr WeaponAffinity kSignature = {1.5L , 5};

inline constexpr WeaponAffinity kWeaponAffinity[8][15] = {
    {kVersatile , kVersatile , kVersatile , kVersatile , kVersatile , kVersatile , kVersatile , kVersatile , kVersatile , kVersatile , kVersatile , kVersatile , kVersatile , kVersatile , kVersatile} ,
    {kSignature , kAwkward , kPrimary , kAwkward , kPrimary , kVersatile , kPrimary , kPrimary , kAwkward , kVersatile , kIncompatible , kIncompatible , kAwkward , kPrimary , kVersatile} ,
    {kPrimary , kIncompatible , kSignature , kIncompatible , kAwkward , kVersatile , kVersatile , kSignature , kIncompatible , kAwkward , kIncompatible , kIncompatible , kIncompatible , kPrimary , kVersatile} ,
    {kPrimary , kVersatile , kAwkward , kVersatile , kIncompatible , kPrimary , kAwkward , kIncompatible , kPrimary , kSignature , kIncompatible , kAwkward , kAwkward , kAwkward , kVersatile} ,
    {kVersatile , kSignature , kVersatile , kPrimary , kAwkward , kVersatile , kVersatile , kIncompatible , kSignature , kPrimary , kAwkward , kAwkward , kIncompatible , kAwkward , kVersatile} ,
    {kAwkward , kAwkward , kIncompatible , kAwkward , kIncompatible , kIncompatible , kIncompatible , kIncompatible , kAwkward , kVersatile , kSignature , kSignature , kPrimary , kAwkward , kVersatile} ,
    {kPrimary , kAwkward , kAwkward , kAwkward , kVersatile , kAwkward , kVersatile , kVersatile , kAwkward , kVersatile , kPrimary , kPrimary , kSignature , kAwkward , kVersatile} ,
    {kVersatile , kAwkward , kAwkward , kAwkward , kPrimary , kIncompatible , kVersatile , kIncompatible , kAwkward , kAwkward , kPrimary , kVersatile , kAwkward , kSignature , kVersatile} ,
};

WeaponAffinity getWeaponAffinity(CharacterClass characterClass , WeaponType weaponType);

struct WeaponMastery : LevelSystem {
    static constexpr ld kExpGrowthRate = 1.367 , kExpBase = 367 , kSoftCap = 0.67;
    ld _affinityRatio;
    int _softCapLevel;

    WeaponMastery();
    ld getRequiredExp() const;
    ld getExpRatio() const;
    void update(ld experienceBonus , CharacterClass characterClass , WeaponType weaponType);
    ld getPercent() const;
};

struct Weapon {
    WeaponType _type;
    std::string _name;
    CombatStats _stats;
    CombatStats _bonusStats;
    Resource _durability;
    WeaponMastery _mastery;
    Element _elementalResistance = ELEM_NONE;
    Element _elementalWeakness = ELEM_NONE;
};
