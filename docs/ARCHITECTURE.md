# Kiến trúc hiện tại

Dự án là prototype C++20/raylib, build bằng CMake. Cấu trúc dưới đây mô tả
code hiện có, không coi layout từ file hướng dẫn tham khảo là đã triển khai.

| Thành phần | Trách nhiệm |
| --- | --- |
| `src/main.cpp` | Cửa sổ, texture, delta time, điều phối frame và vẽ phòng |
| `src/shared/base.*` | Resource, CombatStats, CharacterClass, Element, LevelSystem |
| `src/shared/creature.*` | CreatureLevel, dữ liệu sinh vật, movement và animation |
| `src/shared/weapon.*` | Weapon, mastery và bảng affinity class/vũ khí |
| `src/entities/player/` | Input và cấu hình Player |
| `src/entities/enemies/` | Cấu hình Enemy, range check, chase |
| `tests/` | Test assert về movement/render/input/chase và mastery |
| `scripts/remove_bg.py` | Tạo sprite RGBA từ ảnh nguồn |
| `tools/verify.sh` | Configure offline, build lại, kiểm tra warning và CTest |

## Luồng mỗi frame

`main` lấy delta time → Player đọc input → Creature chuẩn hóa hướng, cập nhật vị
trí/trạng thái → Enemy kiểm tra range rồi dừng/chase → vẽ phòng, Player, Enemy.
Creature gọi raylib để lấy kích thước màn hình và vẽ; Player đọc input raylib.
Logic hiện chưa tách hoàn toàn khỏi render/input. Texture do main tải và giải phóng,
chưa có wrapper RAII. Dữ liệu combat/mastery chưa được nối thành combat loop.

## Build và test

CMake tạo `oroe`; khi `BUILD_TESTING=ON`, tạo `player_test` và
`weapon_mastery_test`, đăng ký CTest. Player test cung cấp stub cho các hàm raylib
nó quan sát; mastery test liên kết raylib cho các symbol của Creature, không mở
cửa sổ trong test. Test giữ assert hoạt động kể cả khi build Release.
Warning flags chỉ áp dụng target của dự án, không áp sang target dependency;
include raylib được đánh dấu SYSTEM để header bên thứ ba không chịu warning policy
của mã dự án. Verify trên GCC/MinGW đã PASS build 0 warning và CTest 2/2;
MSVC và các nền tảng khác chưa được chạy.
Xem cách chạy và điều kiện offline trong [tổng quan](overview.md).

## Định hướng chưa triển khai

File tham khảo đề xuất `src/core/` (config, enum macros), `src/game/` và `defs/`
(X-macro), `src/render/`, `src/app/` (main/input). Đây là phương án để xem xét
trong plan riêng; chưa có quyết định migrate code hiện tại. Rule cho logic mới
ưu tiên khả năng test, không buộc refactor toàn dự án trong task nhỏ.
