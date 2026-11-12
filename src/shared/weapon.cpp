#include "weapon.hpp"
#include <cmath>
#include <limits>

WeaponAffinity getWeaponAffinity(CharacterClass characterClass , WeaponType weaponType) {
    return kWeaponAffinity[static_cast<int>(characterClass)][static_cast<int>(weaponType)];
}

WeaponMastery::WeaponMastery() : LevelSystem(1 , 5) , _affinityRatio(1.0L) , _softCapLevel(3) {}

ld WeaponMastery::getRequiredExp() const {
    if (_currentLevel >= _maxLevel) return std::numeric_limits<ld>::max();
    return std::pow(kExpGrowthRate , _currentLevel - 1) * kExpBase;
}

ld WeaponMastery::getExpRatio() const {
    const int overCapLevel = _currentLevel > _softCapLevel ? _currentLevel - _softCapLevel : 0;
    return _affinityRatio * std::pow(kSoftCap , overCapLevel);
}

void WeaponMastery::update(ld experienceBonus , CharacterClass characterClass , WeaponType weaponType) {
    const WeaponAffinity affinity = getWeaponAffinity(characterClass , weaponType);
    _affinityRatio = affinity._affinityRatio;
    _softCapLevel = affinity._softCapLevel;

    while (_currentLevel < _maxLevel) {
        const ld expNeeded = (getRequiredExp() - _currentExperience) / getExpRatio();
        if (experienceBonus < expNeeded) break;
        experienceBonus -= expNeeded;
        _currentExperience = 0.0L , _currentLevel ++;
    }
    _currentExperience += experienceBonus * getExpRatio();
}

ld WeaponMastery::getPercent() const {
    if (_currentLevel == _maxLevel) return 100.0L;
    return _currentExperience * 100 / getRequiredExp();
}
