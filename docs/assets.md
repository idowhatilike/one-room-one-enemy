# Assets và xử lý sprite

Code: [remove_bg.py](../scripts/remove_bg.py), [main.cpp](../src/main.cpp).

Texture Player và boss nằm trong `assets/`; CMake chép thư mục này cạnh
executable sau build. `main` tải texture một lần sau `InitWindow()`, dùng
point filtering và giải phóng trước `CloseWindow()`.

## Script xóa nền

`scripts/remove_bg.py` cần Pillow. Chạy không tham số để xử lý Reze;
chạy `python scripts/remove_bg.py makima` để tạo `assets/makima_idle.png` từ `makima_raw.png`.
Script lấy màu góc trên trái và đổi mọi pixel trùng chính xác thành RGBA `(0 , 0 , 0 , 0)`;
giữ nguyên kích thước và nét pixel nhân vật, không blur hay anti-aliasing.
Riêng chữ ký trong vùng `(10 , 10 , 100 , 60)` giảm alpha còn 20%.
Ảnh nguồn hiện là 1920×1920, nền `#45283c`; script không resize về 192×192.
Việc giảm alpha chữ ký chỉ áp dụng cho Reze. Makima giữ nguyên 335×597 px,
xóa nền `#390947`, giữ các chi tiết khác kể cả bong bóng thoại.

Script đọc `assets/<sprite>_raw.png` và ghi đè `assets/<sprite>_idle.png`.
Chỉ chạy khi muốn tạo lại ảnh đích. Các thông số kích thước/màu ảnh ở trên
được giữ từ tài liệu gốc, chưa được đo lại trong lần chỉnh tài liệu này.

[Mục lục](game_data.md)
