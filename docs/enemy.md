# Enemy

Code: [enemy.hpp](../src/entities/enemies/enemy.hpp), [enemy.cpp](../src/entities/enemies/enemy.cpp).

Enemy kế thừa [Creature](creature.md), dùng chung movement/animation.

Enemy dùng cùng các hàm movement/animation, bán kính 50 so với Player 40
(chiều lớn nhất khi IDLE là 100 px, lớn hơn Player 25%). Enemy khởi đầu ở `(850 , 450)`,
dùng `assets/makima_idle.png` làm boss. Texture được scale giữ tỷ lệ ảnh dọc,
dùng point filtering và giải phóng trước khi đóng cửa sổ. Chưa có logic tấn công.

Enemy có `isPlayerInRange(player)` và `chasePlayer(player , deltaTime)`, nhận `Creature`
hoặc `Vector2` vị trí đích. Range vẫn là 3.67 px theo khoảng cách tâm.
Chase giới hạn bước di chuyển để không vượt đích; không tự kiểm tra range hay tấn công.

Enemy có tốc độ ban đầu 300, `kBobHeight = 2.36`; `_mainHand` thuộc riêng
từng Enemy. Range bằng ngưỡng vẫn tính là trong range và không cộng bán kính
sprite. `setupFrame()` trong [main](overview.md) quyết định dừng/chase;
giới hạn viền của Creature vẫn áp dụng khi chase.

[Mục lục](game_data.md)
