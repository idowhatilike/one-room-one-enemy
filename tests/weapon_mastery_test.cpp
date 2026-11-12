#include "src/shared/creature.hpp"
#include "src/shared/weapon.hpp"
#include <algorithm>
#include <cassert>
#include <cmath>

bool closeEnough(ld actual , ld expected) {
    return std::abs(actual - expected) <= 1e-9L * std::max(1.0L , std::abs(expected));
}

int main() {
    CreatureLevel creatureLevel;
    creatureLevel . update(creatureLevel . getRequiredExp() - 1);
    assert(creatureLevel . _currentLevel == 1);
    creatureLevel . update(1);
    assert(creatureLevel . _currentLevel == 2);
    assert(creatureLevel . _currentExperience == 0);
    creatureLevel . update(creatureLevel . getRequiredExp());
    assert(creatureLevel . _currentLevel == 3);
    assert(creatureLevel . _currentExperience == 0);

    static_assert(sizeof(kWeaponAffinity) / sizeof(kWeaponAffinity[0]) == static_cast<int>(CT_CLERIC) + 1);
    static_assert(sizeof(kWeaponAffinity[0]) / sizeof(kWeaponAffinity[0][0]) == static_cast<int>(WPN_NONE) + 1);

    Creature creature{};
    Weapon weapon{};
    assert(creature . _characterClass == CT_NONE);
    assert(weapon . _mastery . _currentLevel == 1);
    assert(weapon . _mastery . _maxLevel == 5);
    assert(weapon . _mastery . _currentExperience == 0);
    assert(static_cast<int>(MASTER_GRANDMASTER) + 1 == weapon . _mastery . _maxLevel);

    for (int classIndex = 0; classIndex < 8; classIndex ++) {
        for (int weaponIndex = 0; weaponIndex <= static_cast<int>(WPN_NONE); weaponIndex ++) {
            const auto characterClass = static_cast<CharacterClass>(classIndex);
            const auto weaponType = static_cast<WeaponType>(weaponIndex);
            const auto affinity = getWeaponAffinity(characterClass , weaponType);
            assert(affinity . _softCapLevel >= 1 && affinity . _softCapLevel <= 5);
            assert(affinity . _affinityRatio == 0.25L * (affinity . _softCapLevel + 1));

            WeaponMastery once;
            WeaponMastery split;
            once . update(10000 , characterClass , weaponType);
            for (int step = 0; step < 100; step ++) split . update(100 , characterClass , weaponType);
            assert(once . _currentLevel == split . _currentLevel);
            assert(closeEnough(once . _currentExperience , split . _currentExperience));
            assert(once . _currentLevel <= once . _maxLevel);
            if (characterClass == CT_NONE) assert(affinity . _softCapLevel == 3);
            if (weaponType == WPN_NONE) assert(affinity . _softCapLevel == 3);
        }
    }

    WeaponMastery boundary;
    boundary . update(0 , CT_MAGE , WPN_AXE);
    const ld firstRawCost = boundary . getRequiredExp() / boundary . getExpRatio();
    boundary . update(firstRawCost , CT_MAGE , WPN_AXE);
    assert(boundary . _currentLevel == 2);
    assert(closeEnough(boundary . _currentExperience , 0));
    assert(closeEnough(boundary . getExpRatio() , 0.5L * WeaponMastery::kSoftCap));

    const ld secondRawCost = boundary . getRequiredExp() / boundary . getExpRatio();
    WeaponMastery multipleLevels;
    multipleLevels . update(firstRawCost + secondRawCost + 10 , CT_MAGE , WPN_AXE);
    assert(multipleLevels . _currentLevel == 3);
    assert(closeEnough(multipleLevels . _currentExperience , 10 * multipleLevels . getExpRatio()));

    WeaponMastery switched;
    switched . update(100 , CT_WARRIOR , WPN_SWORD);
    assert(closeEnough(switched . _currentExperience , 150));
    switched . update(100 , CT_MAGE , WPN_AXE);
    assert(closeEnough(switched . _currentExperience , 200));
    assert(switched . _softCapLevel == 1);
    assert(switched . _affinityRatio == 0.5L);

    WeaponMastery progress;
    progress . update(WeaponMastery::kExpBase / 2 , CT_NONE , WPN_SWORD);
    assert(closeEnough(progress . getPercent() , 50));

    WeaponMastery capped;
    capped . update(1000000 , CT_MAGE , WPN_AXE);
    assert(capped . _currentLevel == 5);
    assert(capped . _currentExperience > 0);
    assert(capped . getPercent() == 100);
    const ld previousExp = capped . _currentExperience;
    capped . update(100 , CT_MAGE , WPN_AXE);
    assert(capped . _currentLevel == 5);
    assert(closeEnough(capped . _currentExperience - previousExp , 100 * capped . getExpRatio()));
}
