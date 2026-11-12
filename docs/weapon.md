# Weapon và mastery

Code: [weapon.hpp](../src/shared/weapon.hpp), [weapon.cpp](../src/shared/weapon.cpp).

`Weapon` lưu loại, tên, stats, bonus, độ bền và mastery.
Cả `Creature` lẫn `Weapon` có nguyên tố bất lợi và kháng, mặc định `None`;
chưa có logic điều chỉnh damage theo nguyên tố.

## Weapon mastery

`WeaponMastery` mặc định level 1, EXP bằng 0, tối đa level 5 (`Grandmaster`).

`WeaponMastery . update(exp , characterClass , weaponType)` tra lại tương thích
theo class/vũ khí hiện tại. Caller cần truyền EXP gốc hữu hạn, không âm; hàm
hiện chưa kiểm tra điều kiện này.
EXP nhận = EXP gốc × affinityRatio × 0.67^max(0 , level − softCapLevel).
Ngưỡng lên cấp là `367 * pow(1.367 , level - 1)`.
Mỗi khi đủ EXP, tăng level và tính lại penalty cho phần EXP gốc còn lại.
Tại level 5, EXP vẫn tích lũy theo hệ số của level 5; `Oneness` chưa triển khai.
Đổi class/vũ khí không tính lại EXP đã nhận. `getPercent()` trả 100 ở trần.

Năm bậc tương thích lần lượt là kỵ hệ `(0.5 , 1)`, trái tay `(0.75 , 2)`,
phụ/đa dụng `(1.0 , 3)`, chính `(1.25 , 4)`, trấn phái `(1.5 , 5)`.
Bảng dưới ghi số bậc; đây là phân bổ cân bằng ban đầu, chưa được playtest.
Class `None` dùng bậc 3 cho mọi vũ khí. Bậc trấn phái không khóa quyền sử dụng.

| Weapon | None | Warrior | Berserker | Assassin | Ranger | Mage | Spellblade | Cleric |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| Sword | 3 | 5 | 4 | 4 | 3 | 2 | 4 | 3 |
| Bow | 3 | 2 | 1 | 3 | 5 | 2 | 2 | 2 |
| Axe | 3 | 4 | 5 | 2 | 3 | 1 | 2 | 2 |
| Arrow | 3 | 2 | 1 | 3 | 4 | 2 | 2 | 2 |
| Shield | 3 | 4 | 2 | 1 | 2 | 1 | 3 | 4 |
| Hook | 3 | 3 | 3 | 4 | 3 | 1 | 2 | 1 |
| Lance | 3 | 4 | 3 | 2 | 3 | 1 | 3 | 3 |
| GreatSword | 3 | 4 | 5 | 1 | 1 | 1 | 3 | 1 |
| Crossbow | 3 | 2 | 1 | 4 | 5 | 2 | 2 | 2 |
| Dagger | 3 | 3 | 2 | 5 | 4 | 3 | 3 | 2 |
| Staff | 3 | 1 | 1 | 1 | 2 | 5 | 4 | 4 |
| Wand | 3 | 1 | 1 | 2 | 2 | 5 | 4 | 3 |
| SpellSword | 3 | 2 | 1 | 2 | 1 | 4 | 5 | 2 |
| Mace | 3 | 4 | 4 | 2 | 2 | 2 | 2 | 5 |
| None | 3 | 3 | 3 | 3 | 3 | 3 | 3 | 3 |

Khi thêm class hoặc vũ khí, cập nhật đủ macro và hàng/cột tương ứng trong
`kWeaponAffinity`; thứ tự bảng phải khớp thứ tự hai enum.

[Mục lục](game_data.md)
