# Dữ liệu nền

Code: [base.hpp](../src/shared/base.hpp), [base.cpp](../src/shared/base.cpp).

`base.hpp` chứa dữ liệu dùng chung: `Resource`, `CombatStats`, `Element`
và `LevelSystem`. Mỗi enum value có macro viết tắt tương ứng.
Các `.hpp` khai báo kiểu và hàm; phần định nghĩa hàm nằm trong `.cpp` cùng tên.
Hằng số `constexpr` và bảng tương thích vẫn ở header.

`Resource` chứa `_base`, `_current`, `_max`, `_min`. Quan hệ
`_min <= _current <= _max` được ghi trong comment của code; struct chưa tự
kiểm tra hay clamp giá trị.

`CombatStats` chứa HP, mana, stamina; attack, special attack, defense,
special defense, movement speed, critical rate/damage; attack speed,
`_fixDam`, `_dirDam`. Đây là dữ liệu, chưa phải công thức tính damage.

`CharacterClass` có macro tiền tố `CT_`; `Element` có macro tiền tố `ELEM_`.
`kRoomBorderWidth = 10.0f` dùng chung khi vẽ phòng và giới hạn movement.

`LevelSystem(currentLevel , maxLevel)` lưu level hiện tại, level tối đa và
EXP trong level hiện tại; EXP khởi tạo bằng 0. Constructor chỉ gán dữ liệu.
Logic lên cấp thuộc [CreatureLevel](creature.md) và [WeaponMastery](weapon.md).

[Mục lục](game_data.md)
