# Tài liệu game

Nội dung trước đây trong `game_data.md` được tách theo module để dễ tra cứu
và cập nhật cùng code. Trang này giữ vai trò mục lục cho đường dẫn cũ.

| Tài liệu | Code tương ứng | Nội dung |
| --- | --- | --- |
| [Tổng quan](overview.md) | `src/main.cpp`, `CMakeLists.txt` | Prototype, vòng lặp game và build |
| [Dữ liệu nền](base.md) | `src/shared/base.hpp/.cpp` | Resource, CombatStats, class, nguyên tố và LevelSystem |
| [Creature](creature.md) | `src/shared/creature.hpp/.cpp` | Dữ liệu sinh vật, level, movement và animation |
| [Weapon](weapon.md) | `src/shared/weapon.hpp/.cpp` | Vũ khí, mastery và bảng affinity |
| [Player](player.md) | `src/entities/player/player.hpp/.cpp` | Input và cấu hình Player |
| [Enemy](enemy.md) | `src/entities/enemies/enemy.hpp/.cpp` | Range, chase và cấu hình Enemy |
| [Assets](assets.md) | `scripts/remove_bg.py`, `assets/` | Texture và xử lý nền sprite |

## Theo dõi dự án

- [STATE](STATE.md): trạng thái ngắn gọn, bước tiếp theo và blocker.
- [ARCHITECTURE](ARCHITECTURE.md): layout, trách nhiệm và luồng dữ liệu thực tế.
- [DECISIONS](DECISIONS.md): quyết định có căn cứ và đề xuất chưa triển khai.
- [Plans](plans/README.md), [bugs](bugs/README.md), [archive](archive/README.md):
  hồ sơ triển khai, sửa lỗi và lưu trữ.
- [AGENTS.md](../AGENTS.md): quy trình và đường dẫn tới bốn skill của dự án.

Các trang mô tả code đã đọc; chưa bao gồm playtest. Khi đổi một module,
cập nhật trang tương ứng và mục lục nếu cần.
