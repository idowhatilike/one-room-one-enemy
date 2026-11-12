# Trạng thái dự án

- Stack: C++20, CMake từ 3.22, raylib tag 6.2.
- Mục tiêu: combat một phòng, một Enemy, có kết hợp địa hình.
- Hiện có: phòng 1200×900, Player input/movement, Enemy range/chase, animation.
- Shared: Resource, CombatStats, CreatureLevel, WeaponMastery, bảng affinity.
- Chưa có trong src/: attack/damage và tương tác địa hình trong phòng.
- Layout thực tế: src/main.cpp, src/shared/, src/entities/; chưa tách core/game/render/app.
- Hướng dẫn: AGENTS.md; bốn skill trong .claude/skills/.
- Docs module: [mục lục](game_data.md); [kiến trúc](ARCHITECTURE.md); [quyết định](DECISIONS.md).
- Verify: bash tools/verify.sh; log trong build/verify-logs/.
- Xác minh 2026-11-12: verify.sh PASS, build 0 warning, CTest 2/2 PASS (GCC/MinGW).
- Bốn skill PASS quick_validate; 52 link Markdown hợp lệ; chưa chạy game/playtest.
- Plan hiện tại: [002 — tách game/app/render](plans/002-separate-game-app-render.md), DRAFT.
- Người dùng chọn lập plan tái cấu trúc; plan 001 combat chưa được chọn, chưa duyệt.
- Bước tiếp theo: duyệt plan 002 trước khi chuyển file hoặc đổi API nội bộ.

## Blockers

- Chờ duyệt plan tái cấu trúc; chưa có phê duyệt triển khai code.

## Parking lot

- Combat/địa hình ở plan 001 chưa thuộc công việc hiện tại.
