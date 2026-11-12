# Tổng quan game

Code: [main.cpp](../src/main.cpp), [CMakeLists.txt](../CMakeLists.txt).

Mục tiêu người phát triển mô tả là game combat một phòng, một Enemy, có kết hợp
địa hình. Prototype hiện tại tạo phòng 1200×900 px, nền xám, viền đen dày
`kRoomBorderWidth = 10`, target FPS 67.

Trong phạm vi `src/` hiện tại, game đã có Player di chuyển và Enemy đuổi Player.
Chưa có xử lý tấn công, damage hay tương tác địa hình bên trong phòng;
ràng buộc không gian hiện tại là giới hạn vị trí theo viền phòng trong Creature.

## Vòng lặp game

Mỗi frame, `main` lấy `GetFrameTime()` một lần rồi gọi `setupFrame()`:
cập nhật Player, kiểm tra range và cho Enemy chase; trong range thì Enemy về IDLE.

Khi vẽ, thứ tự là phòng → Player → Enemy. `main` tải texture sau
`InitWindow()` từ thư mục executable. Nếu tải thất bại, game giải phóng texture
đã tải, đóng cửa sổ và trả mã lỗi 1. Khi thoát bình thường, hai texture được
giải phóng trước `CloseWindow()`.

## Build và kiểm tra

`CMakeLists.txt` yêu cầu CMake từ 3.22, C++20 và dùng FetchContent lấy raylib
với `GIT_TAG 6.2`. Target executable là `oroe`, gồm `main`, Player, Enemy,
base, creature và weapon. Sau build, CMake chép `assets/` cạnh executable.

Từ thư mục gốc, với compiler và generator phù hợp đã có trên máy:

```sh
cmake -S . -B build
cmake --build build
```

Configure ban đầu có thể tải raylib khi dependency chưa có; cần xin phép trước
khi thực hiện việc tải/cài dependency. Khi đã có dependency local, dùng verify:

```sh
bash tools/verify.sh
```

Script chạy configure với `BUILD_TESTING=ON`, build lại bằng `--clean-first`,
rồi CTest với `--no-tests=error`. Warning compiler là lỗi ở target dự án;
script cũng thất bại nếu log configure/build/test có warning. Test luôn bật
assert kể cả cấu hình Release. Script không tải raylib ngầm
(`FETCHCONTENT_FULLY_DISCONNECTED=ON`); thiếu dependency thì dừng để setup riêng.

Tham số tùy chọn: `bash tools/verify.sh <build-dir> <configuration>`;
mặc định là `build` và `Debug`. Với generator nhiều cấu hình, configuration được
truyền qua `--config`/`-C`. Nếu tạo build-dir mới, compiler/generator phải được
cấu hình phù hợp và dependency phải có sẵn, chẳng hạn qua CMake cache hoặc
`FETCHCONTENT_SOURCE_DIR_RAYLIB`. Muốn configure có mạng về sau phải chủ động
tắt `FETCHCONTENT_FULLY_DISCONNECTED` trong cache.

Trên Windows cần Bash có `dirname`, `mkdir`, `grep`, `tail`, cùng CMake/CTest và
compiler trong PATH. MSYS2 hiện tại dùng `C:/msys64/ucrt64/bin` và
`C:/msys64/usr/bin` trong PATH của tiến trình. Không cần đổi PATH hệ thống.
Output chỉ gồm trạng thái bước và tối đa 20 dòng chẩn đoán khi lỗi; log đầy đủ
ở `<build-dir>/verify-logs/{configure,build,ctest}.log`. Bước lỗi dừng ngay,
không báo PASS khi không có test.

[tests/player_test.cpp](../tests/player_test.cpp) dùng stub raylib để kiểm tra
input, movement, animation, giới hạn viền và Enemy chase.
[tests/weapon_mastery_test.cpp](../tests/weapon_mastery_test.cpp) kiểm tra lên
cấp, affinity, soft cap và đổi class/vũ khí. `CMakeLists.txt` đăng ký hai target
`player_test`, `weapon_mastery_test` khi `BUILD_TESTING=ON`. Test không mở cửa sổ;
kết quả CTest không xác minh gameplay tương tác hay chất lượng hiển thị thực tế.
Chưa có linter riêng được cấu hình.

Lần xác minh 2026-11-12 trên Windows/GCC-MinGW: `bash tools/verify.sh` PASS,
build 0 warning, CTest 2/2 PASS. Chưa xác minh MSVC, Linux hoặc playtest.

[Mục lục](game_data.md)
