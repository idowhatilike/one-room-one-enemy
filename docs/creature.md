# Creature

Code: [creature.hpp](../src/shared/creature.hpp), [creature.cpp](../src/shared/creature.cpp).

## Dữ liệu và level

`Creature` lưu thông tin, quan hệ, trạng thái, level và combat stats.
`SpeciesType::ElementalEntity` chỉ loài sinh vật nguyên tố; `Element` chỉ hệ nguyên tố.

Nguyên tố bất lợi và kháng mặc định `None`; chưa có logic điều chỉnh damage
theo nguyên tố trong module. `Relationship`, `SpeciesType`, `StatusEffect`,
`MoveState` có macro tương ứng với tiền tố `REL_`, `SPEC_`, `FX_`, `MOVE_`.

`CreatureLevel` mặc định level 1, tối đa 18. Ngưỡng lên cấp là
`367 * pow(1.367 , level - 1)`. EXP khởi tạo bằng 0; `update()` cộng EXP và
lên cấp ngay khi EXP bằng hoặc vượt ngưỡng, trừ EXP đã dùng ở từng level.
EXP âm có thể làm giảm level đến 0 theo vòng lặp hiện tại; EXP còn âm sau đó
được đưa về 0. Ở trần, `getPercent()` trả 100 và EXP vẫn được cộng.

## Movement và animation dùng chung

`shared/creature.hpp/.cpp` dùng chung `MoveState`, vị trí, hướng nhìn và nhịp animation.
`Creature::updateMovement()` chuẩn hóa hướng, giới hạn viền và cập nhật trạng thái;
`drawMovement()` vẽ bob/co giãn/xoay/lật ảnh. Player chỉ đọc input rồi gọi phần dùng chung.

`distanceTo(target)` và `directionTo(target)` lấy vị trí nguồn từ chính Creature;
`directionTo()` trả vector đơn vị, hoặc zero khi trùng vị trí.
Player/Enemy có `update(movement , deltaTime)` và `draw(texture)` tự truyền radius/bob.

`drawMovement()` giữ tỷ lệ ảnh, scale chiều lớn nhất về `radius * 2`.
Nhịp `sin(_animationTime * 12)` khi Running tạo bob, squash/stretch 4% và
xoay tối đa 3°. Khi Idle, sprite trở về kích thước cơ sở và không bob/xoay.

Khoảng chừa tâm so với mép trong phòng được tính theo:

```text
spriteExtent = radius × (1 + 0.04) × (cos(3°) + sin(3°)) + bobHeight
minPosition = kRoomBorderWidth + spriteExtent
```

Mỗi trục được clamp từ `minPosition` đến kích thước màn hình trừ
`minPosition`. Đây là giới hạn viền, chưa phải va chạm với địa hình trong phòng.
Thành phần hướng ngang khác 0 cập nhật `_facingRight`, kể cả khi vị trí cuối
cùng bị chặn bởi viền.

[Mục lục](game_data.md)
