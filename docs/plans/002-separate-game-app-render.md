# Tách logic game, input và render

Status: DRAFT

Người dùng đã chọn hướng “Lập plan tái cấu trúc code”. Chưa có phê duyệt
triển khai plan này. Plan 001 về combat không thuộc công việc đang được chọn.

## Mục tiêu và phạm vi

Tách trách nhiệm để movement, chase và level/mastery test được mà không cần
cửa sổ hay stub API input/render. Giữ hành vi chạy game hiện tại, C++20,
raylib tag 6.2, naming và asset. Không làm combat, địa hình hay cân bằng mới.

Phạm vi gồm chuyển file/include/CMake, truyền kích thước phòng vào logic,
tách input/render, quản lý texture bằng RAII nhỏ và điều chỉnh test tương ứng.
API nội bộ của entity thay đổi ở các điểm liệt kê bên dưới. Khi duyệt triển khai,
phạm vi này bao gồm các thao tác chuyển file được liệt kê; không xóa hàng loạt.

## Bằng chứng hiện trạng

- `src/main.cpp:12`: `setupFrame()` gọi `Player::inputHandler()` rồi xử lý Enemy.
  Hàm `main` vừa giữ vòng đời texture vừa điều phối update/render.
- `src/shared/creature.cpp:38`: movement lấy `GetScreenWidth/Height()` trực tiếp;
  cùng file có `drawMovement()` gọi `DrawTexturePro()`.
- `src/entities/player/player.cpp:8`: đọc `IsKeyDown()` trực tiếp trong Player;
  Player và Enemy có wrapper `draw()` phụ thuộc Texture2D.
- `tests/player_test.cpp:13`: stub input, kích thước màn hình và draw dùng chung
  một executable. `weapon_mastery_test` liên kết raylib vì cùng biên dịch Creature
  chứa phần vẽ, dù test không dùng phần đó.
- CMake hiện liệt kê lại source game ở executable và cả hai test; có warning
  policy, CTest và copy assets. Log verify trước đã có 2/2 PASS; chưa chạy lại
  baseline trong bước lập plan, chưa kiểm chứng kiến trúc đề xuất.

## Phương án

| Phương án | Lợi ích | Hạn chế |
| --- | --- | --- |
| Chỉ đổi folder/include | Diff cơ học, ít rủi ro | Giữ nguyên logic phụ thuộc input/render và stub |
| Tách bốn vùng, truyền dữ liệu đầu vào | Giải quyết coupling hiện có, vẫn giữ model và raylib math | Đổi API nội bộ và chia lại test |
| Thêm ECS, backend interface hoặc math riêng | Linh hoạt cho nhu cầu lớn hơn | Chưa có yêu cầu cụ thể, tăng chi phí refactor |

Đề xuất phương án thứ hai. Không tạo service locator, event bus, resource manager
hay wrapper math. Giữ `Vector2` và phép toán thuần từ `raymath.h`: `game/` vẫn cần
header raylib, nhưng không gọi API cửa sổ, input, render hoặc Load/Unload và không
liên kết thư viện raylib runtime. Đây là tách phụ thuộc runtime, không phải bỏ raylib.

## Cấu trúc đích và mapping

| File hiện tại | File đích / trách nhiệm |
| --- | --- |
| `src/main.cpp` | `src/app/main.cpp`: entry point; `src/app/application.hpp/.cpp`: cửa sổ, dt/kích thước phòng, điều phối frame |
| Hằng screen/FPS trong main, border trong base | `src/core/config.hpp`: giá trị cấu hình phòng dùng chung |
| `src/shared/base.hpp/.cpp` | `src/game/base.hpp/.cpp`: model dùng chung, giữ enum/macro |
| `src/shared/creature.hpp/.cpp` | `src/game/creature.hpp/.cpp`: dữ liệu, level, movement thuần |
| `src/shared/weapon.hpp/.cpp` | `src/game/weapon.hpp/.cpp`: dữ liệu, mastery, affinity nguyên trạng |
| `src/entities/player/player.hpp/.cpp` | `src/game/player.hpp/.cpp`: cấu hình và update Player |
| `src/entities/enemies/enemy.hpp/.cpp` | `src/game/enemy.hpp/.cpp`: cấu hình, range và chase |
| `Player::inputHandler()` | `src/app/input.hpp/.cpp`: đọc bàn phím thành vector movement |
| `drawRoom()`, `Creature::drawMovement()`, wrapper `draw()` | `src/render/scene_renderer.hpp/.cpp`: vẽ phòng và entity |
| Load/filter/Unload texture trong main | `src/render/texture_asset.hpp/.cpp`: một chủ sở hữu texture |

Chỉ đưa screen width/height, target FPS và room border vào config. Các constant
radius/bob, stretch/rotation, EXP và bảng affinity giữ ở nơi sở hữu hiện tại;
không gom mọi giá trị thành một config lớn. Giữ `.hpp/.cpp` theo dự án.
Chưa tạo `game/defs/` hay `core/enum_macros.hpp`: task này không thêm game enum
và không migrate enum cũ sang X-macro.

## Ranh giới và thay đổi API nội bộ

- App lấy movement từ `readMovementInput()`, truyền vào Player; bỏ
  `Player::inputHandler()`. Không đọc bàn phím trong `game/`.
- Thêm tham số bắt buộc `Vector2 roomSize` ở cuối `Creature::updateMovement()`,
  `Player::update()`, `Enemy::update()` và hai overload `Enemy::chasePlayer()`.
  App lấy kích thước màn hình một lần mỗi frame rồi truyền cùng giá trị cho hai actor.
  Không thêm singleton hay default parameter ẩn phụ thuộc màn hình.
- Giữ `getPos()`, `distanceTo()`, `directionTo()` và overload range hiện có.
  Giữ dữ liệu state/hướng/animation trong Creature để update và render cùng đọc.
- Bỏ các member `draw()`/`drawMovement()` khỏi entity; thay bằng free function
  trong renderer nhận `const Creature&`, texture, radius và bob. App chọn cấu hình
  Player/Enemy từ constant hiện có; không suy luận loại entity hay dùng virtual.
- Renderer giữ nguyên công thức scale/bob/co giãn/xoay/lật và thứ tự vẽ.
  Không tách thêm một cây class hoặc command buffer cho vài lệnh draw.
- `TextureAsset` chỉ sở hữu một Texture2D; không copy/move trong scope này để tránh
  double-unload. Constructor load và áp point filtering khi hợp lệ; destructor
  unload đúng một lần nếu hợp lệ. Có truy cập texture và kiểm tra valid rõ ràng.
- `main` chỉ gọi `runApplication()` trong app/application. Hàm này mở cửa sổ,
  gọi helper chạy game có scope chứa hai TextureAsset, rồi đóng cửa sổ sau khi
  helper trả về. Nhờ scope, texture bị hủy trước `CloseWindow()`; load lỗi trả
  mã 1 như cũ. Tách application khỏi entry point để test chạy đúng luồng lifecycle
  bằng stub, không viết lại luồng cleanup trong test. Không cần wrapper Window
  hay cache tài nguyên.
- Giữ đường dẫn từ thư mục executable, target `oroe` và bước copy assets hiện tại.

## CMake và test

Tạo một static library nội bộ `oroe_game` cho các `.cpp` trong `game/`; executable
và logic tests liên kết library này. Include root là `src/`, dùng đường dẫn
`game/...`, `core/...` thay cho include tương đối nhiều cấp. Header raylib vẫn
được cấp dạng SYSTEM cho target cần chúng. Không link raylib runtime vào library
game hay logic test; app/render mới link raylib.

Giữ tên test `player_test`, `weapon_mastery_test`. Chuyển case input/render từ
player_test sang `presentation_test` mới, dùng stub tại biên app/render để quan
sát API. Target này biên dịch application/input/renderer/texture nhưng không
`app/main.cpp`, dùng stub cửa sổ, input, load/valid/filter/unload và draw. Chạy
`runApplication()` với vòng lặp kết thúc có kiểm soát để kiểm tra thứ tự cleanup.
Không bỏ assertion cũ hoặc nới tolerance để refactor pass. Test vẫn giữ assert
khi Release, warning policy và `--no-tests=error` của verify không đổi.

## Invariant phải giữ

- Phòng 1200×900, viền 10, target FPS 67; input WASD/mũi tên, hướng đối nhau triệt tiêu.
- Player `(600 , 450)`, Enemy `(850 , 450)`, tốc độ 300; radius 40/50,
  bob 1.5/2.36. Chuẩn hóa hướng, clamp viền có tính stretch/rotation/bob giữ nguyên.
- State dựa trên vị trí thực sự thay đổi; khi không di chuyển reset animation.
  Hướng ngang cập nhật kể cả khi bị chặn như code hiện tại; không “sửa tiện”.
- Range tâm 3.67, bằng ngưỡng là trong range; chase không vượt đích, không tự
  kiểm tra range. Thứ tự frame vẫn Player trước, Enemy kiểm tra sau.
- `GetFrameTime()` một lần mỗi frame; không clamp dt, đổi nhịp animation hay spawn.
- Texture Reze/Makima, giữ tỷ lệ, point filtering, thứ tự phòng → Player → Enemy;
  load lỗi hoặc thoát bình thường đều cleanup texture trước cửa sổ.
- Enum ordinal, macro, resource, EXP, level cap, penalty và mọi ô affinity giữ nguyên.
  Không đổi xử lý EXP âm hay bổ sung validation trong task refactor.

## Tasks và acceptance criteria

- [ ] T1 — Chốt baseline trước khi chuyển file.
  AC: đọc diff/untracked hiện có để bảo toàn công việc người dùng; lưu kết quả
  verify baseline và kiểm tra asset đang dùng. Phân loại assertion logic/input/render
  để giữ đủ coverage khi chia test; không sửa code gameplay ở bước này.
  Verify: `bash tools/verify.sh` PASS, 0 warning, CTest 2/2; ghi bằng chứng trong plan.
  Tài liệu: kết quả baseline và STATE.
- [ ] T2 — Chuyển layout và cấu hình dùng chung.
  AC: chuyển các file theo mapping, cập nhật include/source list/test; giữ logic
  cũ trong bước chuyển. Chỉ tạo core config cho nhóm constant đã liệt kê, không
  tạo alias header cũ hay migrate enum. Không sửa assets, script, dependency hay lockfile.
  Verify: verify PASS với test cũ; `rg` không còn include/source list trỏ đường dẫn cũ.
  Tài liệu: cập nhật link code ở trang module và mô tả layout thực tế sau bước này.
- [ ] T3 — Tách input và dữ liệu kích thước phòng khỏi logic.
  AC: app/input đọc phím; game nhận movement/roomSize; mọi caller dùng API mới.
  Logic tests không cần stub bàn phím/kích thước màn hình. Kiểm tra roomSize bằng
  dữ liệu test tường minh, không gọi GetScreen trong game. Chưa đổi điều kiện movement.
  Verify: logic tests giữ case hướng chéo/đối nhau, dt=0, tốc độ=0, blocked, frame
  chia nhỏ, chase trùng đích/bước lớn, range biên; input test giữ đủ case hiện có;
  verify PASS. Tài liệu: Player, Enemy, Creature và architecture.
- [ ] T4 — Tách render và quản lý texture.
  AC: toàn bộ Draw/Load/Unload nằm ở app/render; game không còn Texture2D trong
  API. Scope cleanup giữ đúng nhánh lỗi tải ảnh đầu/ảnh thứ hai và thoát thường.
  Giữ các assertion draw cũ trong presentation_test, không giả lập raylib ở logic test.
  Verify: test portrait/square, flip, bob, stretch, rotation, origin và bốn góc
  với đủ pha animation; stub lifetime xác nhận load đầu lỗi, load thứ hai lỗi,
  hai ảnh thành công, unload đúng một lần và trước close. Verify PASS.
  Tài liệu: Assets, Creature, Player, Enemy, architecture.
- [ ] T5 — Hoàn thiện dependency và kiểm tra hồi quy.
  AC: oroe_game biên dịch một lần và logic tests link không cần raylib runtime;
  presentation_test chỉ stub biên cần kiểm chứng; không còn source game bị khai
  báo lặp trong nhiều target. Không còn API platform/input/render trong game.
  Verify: `bash tools/verify.sh` PASS, 0 warning, CTest 3/3; kiểm tra compile/link
  commands cho dependency; `rg` kiểm tra ranh giới và các include cũ. Build Release
  với `bash tools/verify.sh build Release` để xác nhận assert/test vẫn hoạt động.
  Sau đó dùng cùng script với Debug khi cần phục hồi cấu hình mặc định.
  Tài liệu: build/test trong overview, kết quả và giới hạn nền tảng trong plan.
- [ ] T6 — Smoke test và bàn giao tài liệu.
  AC: chạy game xác nhận input, chase/dừng, biên phòng, hai sprite và thoát thường
  so với baseline; không thêm combat/terrain. Có bằng chứng cho các AC trước.
  Verify: smoke test cửa sổ thật trên môi trường khả dụng, kiểm tra link docs và
  STATE tối đa 40 dòng. Nếu không chạy được smoke test, ghi rõ và để task chưa tick.
  Tài liệu: STATE, ARCHITECTURE, DECISIONS, AGENTS, các trang module và mục lục
  khớp layout/API thực tế; kiểm tra cả skill có ví dụ đường dẫn bị ảnh hưởng.

`tools/verify.sh` được dùng sau các bước thay đổi tích hợp, không chạy lặp lại khi
không có diff mới hoặc nghi vấn. Mỗi task chỉ tick sau AC và Verify PASS.

## Rủi ro, giới hạn và cách quay lui

- Code hiện tại có raylib math/header coupling; giữ nó tránh sai số do viết lại
  normalize/distance. Bỏ hẳn dependency header sẽ là scope khác, cần duyệt riêng.
- Có thể bỏ sót assertion khi chia test; phải map mỗi case cũ sang test đích trước
  khi bỏ stub hoặc wrapper. Kết quả CTest không thay thế smoke test hiển thị.
- Renderer và movement cùng dùng stretch/rotation để chừa viền; giữ một nguồn
  constant hiện có để hai bên không lệch. Không đổi giá trị khi chuyển nơi dùng.
- Refactor nhiều đường dẫn; không dùng bulk move/delete hoặc git reset trên cây
  đang untracked. Chuyển từng file theo mapping sau duyệt, kiểm tra đích trước ghi.
  Nếu lỗi, đảo riêng thao tác/patch của task, giữ nguyên nội dung người dùng.
- Trường hợp màn hình quá nhỏ cho margin hoặc dt/EXP không hợp lệ không được đổi
  behavior trong plan này; nếu quan sát bug riêng thì lập hồ sơ theo workflow bug.
- Không tự sửa comment cũ. Nếu API mới làm comment cũ sai, ghi cụ thể trong mục
  vấn đề còn lại để người dùng xử lý theo quy định dự án.
- MSVC/Linux chưa được xác minh; không thêm yêu cầu CI/dependency chỉ để chứng minh
  đa nền tảng trong task này.

## Change log

- 2026-11-12: tạo DRAFT theo lựa chọn lập plan tái cấu trúc; chưa chuyển file hay sửa code.
