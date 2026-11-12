# Player

Code: [player.hpp](../src/entities/player/player.hpp), [player.cpp](../src/entities/player/player.cpp).

Player kế thừa [Creature](creature.md), đọc input và truyền cấu hình riêng
cho movement/animation dùng chung.

`Player` dùng `_moveSpeed._current` để di chuyển WASD hoặc phím mũi tên theo delta time,
khởi đầu ở `(600 , 450)` với tốc độ 300. Tâm Player được giới hạn theo mép trong
viền phòng, chừa đủ kích thước ảnh cùng bob/xoay/co giãn để không vượt viền.
Độ dày viền dùng chung qua `kRoomBorderWidth = 10`. `_mainHand` thuộc riêng từng player.
Vector di chuyển được chuẩn hóa để tốc độ chéo bằng tốc độ ngang/dọc.
`main` vẽ `assets/reze_idle.png` bằng point filtering, kích thước IDLE 80×80 px,
tương ứng `kRadius = 40`. RUNNING có bob tối đa 1.5 px, squash/stretch 4%
và xoay tối đa 3 độ. Khi ngừng di chuyển hoặc bị chặn, trở về IDLE và reset nhịp.
Đi sang trái/phải cập nhật `_facingRight`; texture lật bằng chiều rộng source âm.
Texture được tải một lần sau `InitWindow()` và giải phóng trước `CloseWindow()`.
CMake chép assets cạnh executable; đường dẫn tải ảnh dựa trên thư mục executable.

`update(movement , deltaTime)` và `draw(texture)` truyền `kRadius = 40`,
`kBobHeight = 1.5` cho Creature. Hai hướng đối nhau triệt tiêu trên cùng trục.
Vòng đời texture do [main](overview.md) quản lý; xem thêm [Assets](assets.md).

[Mục lục](game_data.md)
