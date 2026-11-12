# Prototype combat và vật cản

Status: DRAFT

Người dùng đã chọn lập plan tái cấu trúc code; bản nháp combat này chưa được chọn
cho công việc hiện tại. Tham khảo [plan 002](002-separate-game-app-render.md).

Chưa được người dùng duyệt. Đây là hướng đề xuất để tiếp tục từ trạng thái hiện
tại; yêu cầu “đọc và tiếp tục” chưa xác định mechanic, input hay thông số combat.
Không dùng bản nháp này như phê duyệt triển khai.

## Mục tiêu đề xuất

Có một vòng chơi tối thiểu: Player đánh một Enemy trong phòng, cả hai bị vật cản
chặn di chuyển, có kết quả thắng/thua và có thể bắt đầu lại. Giữ prototype nhỏ
để thử tương tác combat với không gian trước khi bổ sung hệ thống khác.

## Hiện trạng đã kiểm tra

- `src/main.cpp`: mỗi frame cập nhật Player rồi cho Enemy dừng/chase theo range;
  sau đó vẽ phòng, Player và Enemy. Chưa có bước xử lý đòn đánh hoặc kết thúc trận.
- `src/shared/creature.*`: có `_hp` và `_combatStats._hp`, nhưng movement hiện chỉ
  dùng `_moveSpeed`, giới hạn viền và animation. Cần chọn một nguồn HP cho combat.
- `src/entities/player/player.cpp`: đọc WASD/phím mũi tên, chưa đọc input tấn công.
- `src/entities/enemies/enemy.*`: range 3.67 px tính theo khoảng cách tâm, chase
  giới hạn bước để không vượt đích. Đây chưa phải khoảng cách đòn đánh theo hitbox.
- `CMakeLists.txt`: có target `oroe`, hai target test và warning policy.
- Log verify gần nhất ghi CTest 2/2 PASS; lần lập plan này chỉ đọc log, chưa chạy
  lại build/test. Kết quả đó không phải kiểm chứng cho gameplay đề xuất.

## Phạm vi đề xuất, cần duyệt

- Một Player và một Enemy; một kiểu đòn cận chiến đơn giản cho mỗi bên.
- HP, damage, thời gian chuẩn bị đòn và cooldown có hằng số đặt tên. Trước khi
  triển khai phải chốt giá trị demo, không lấy trường dữ liệu chưa khởi tạo làm damage.
- Dùng `Creature::_hp` làm nguồn HP cho vòng chơi này. Chưa đồng bộ hay sử dụng
  `_combatStats._hp`; không refactor các struct ngoài phần cần thiết.
- Player kích hoạt đòn bằng Space, mỗi lần nhấn bắt đầu tối đa một đòn khi sẵn sàng.
  Enemy tự bắt đầu đòn khi đủ gần; chuẩn bị đòn rồi mới kiểm tra trúng ở thời điểm đánh.
- Một vật cản hình chữ nhật cố định, không phá hủy. Spawn hai actor phải nằm trong
  vùng đi được; bố trí cụ thể cần duyệt cùng thông số demo.
- Vật cản chặn di chuyển và đòn đánh trực tiếp xuyên qua nó; không chỉ là hình vẽ.
- Hiển thị HP và kết quả trận; R khởi tạo lại trạng thái chơi, không tải lại texture.

Các mục trên là đề xuất sản phẩm, không suy ra từ code hay coi là yêu cầu đã chốt.

## Ngoài phạm vi

Pathfinding, né đòn, stamina, combo, nguyên tố, mastery EXP trong trận, loot,
chuyển phòng, procedural generation, asset mới và migrate sang core/game/render/app.
Enemy chase thẳng có thể đứng sau vật cản; phải thể hiện đây là giới hạn của
prototype, không mô tả là AI biết đi vòng.

## Phương án và lựa chọn đề xuất

1. Chỉ làm combat trong phòng trống: ít thay đổi nhất, nhưng chưa thử được yêu cầu
   kết hợp địa hình. Có thể chọn nếu người dùng muốn ưu tiên cảm giác đánh trước.
2. Combat và một vật cản tĩnh: thêm collision/kiểm tra đường đánh, đủ thử vai trò
   của vị trí trong trận. Đề xuất cho milestone này.
3. Thêm pathfinding và nhiều loại địa hình ngay: tăng phạm vi, cần thiết kế riêng;
   chưa đề xuất cho vòng prototype đầu tiên.

Giữ layout hiện có. Dự kiến thêm logic combat và va chạm nhỏ trong `src/shared/`,
không gọi input/render trong các hàm tính toán đó. `main` điều phối input,
movement, đòn đánh, kết quả và render. Chốt API sau khi duyệt mechanic; chỉ thêm
type cần thiết qua skill `add-game-type`, giữ macro và consumer đồng bộ.

## Invariant và trường hợp biên

- HP trong `[0 , maxHP]`; chỉ giảm khi đòn đã tới thời điểm đánh, target còn sống,
  trong range và không bị vật cản chắn. Mỗi đòn gây damage tối đa một lần.
- Range dựa trên khoảng cách mép hitbox: `max(0 , khoảng cách tâm − r1 − r2)`.
  Bán kính vật lý cần được chọn rõ, không mặc định rằng animation là hitbox.
- Cooldown/windup tiến theo delta time; frame dài vượt một mốc thời gian không
  tạo nhiều hit từ cùng một đòn. Phải quy định cách xử lý hai đòn cùng trúng trong
  một frame, đề xuất tính cả hai từ trạng thái trước damage và cho phép hòa.
- Di chuyển giữ giới hạn viền cũ và không xuyên vật cản khi bước lớn. Chuyển động
  chéo khi bị chặn một trục được trượt theo trục còn lại; kiểm tra cả góc và mép.
- Khi kết thúc trận, không cập nhật di chuyển hoặc tạo đòn mới. Restart reset HP,
  vị trí, animation, windup/cooldown và kết quả; tài nguyên texture giữ nguyên.
- Input giữ Space không tự tạo chuỗi đòn trong đề xuất này. Delta time hợp lệ là
  hữu hạn và không âm; test phải bao gồm 0 và một bước dài.

## File dự kiến bị ảnh hưởng

- `src/main.cpp`: điều phối và UI prototype, reset trận.
- `src/entities/player/player.*`, `src/entities/enemies/enemy.*`: input/cấu hình
  combat, chase tới khoảng cách thích hợp, giữ đường gọi cũ khi không cần thay đổi.
- `src/shared/creature.*`: kết nối HP/movement với logic mới khi cần.
- Module mới dưới `src/shared/` cho tính combat và collision, tên/API chốt sau duyệt.
- `tests/`: test logic mới và regression movement/chase; `CMakeLists.txt`: đăng ký.
- `docs/player.md`, `docs/enemy.md`, `docs/creature.md`, `docs/overview.md`,
  `docs/ARCHITECTURE.md`, `docs/STATE.md`; thêm trang module và mục lục nếu có module mới.

## Tasks đề xuất

- [ ] T1 — Chốt input, thông số, hitbox, vị trí vật cản/spawn và quy tắc đồng thời.
  AC: người dùng duyệt phạm vi và các giá trị cụ thể; không còn mục gameplay
  ảnh hưởng implementation phải tự đoán. Ghi căn cứ duyệt; chỉ sau đó APPROVED.
  Verify: đối chiếu từng lựa chọn trong phần phạm vi/invariant với phê duyệt.
  Tài liệu: cập nhật plan, STATE; DECISIONS chỉ ghi lựa chọn đã chốt.
- [ ] T2 — Logic combat có thể test độc lập.
  AC: kiểm tra HP, windup, cooldown, ranh giới range, hit một lần, miss và actor
  đã chết; đòn ở ngoài range hoặc bị chắn không gây damage. Giữ logic ngoài render/input.
  Verify: test mới cho các case trên, dt=0, bước dài và đòn cùng frame;
  `bash tools/verify.sh` PASS. Tài liệu: module combat và invariant thực tế.
- [ ] T3 — Vật cản và movement.
  AC: hai actor không xuyên vật cản/viền, kể cả bước lớn; trượt cạnh đúng quy tắc;
  spawn hợp lệ; kiểm tra chắn đòn ở mép/góc, đoạn không cắt và đoạn cắt vật cản.
  Verify: test collision, regression `player_test`, `bash tools/verify.sh` PASS.
  Tài liệu: module collision, creature, player, enemy.
- [ ] T4 — Kết nối vòng chơi và phản hồi trên màn hình.
  AC: Space tạo đòn theo quy tắc; Enemy chase/đánh; thấy HP và kết quả; actor
  ngừng hành động khi hết trận; R reset đủ trạng thái; Load/Unload không đổi vòng đời.
  Verify: test luồng update/reset; verify PASS; chạy game kiểm tra input, vật cản,
  không xuyên đòn và thắng/thua/hòa/reset. Ghi rõ nếu chưa thực hiện được playtest.
  Tài liệu: overview, player, enemy, architecture.
- [ ] T5 — Tổng kiểm và cập nhật trạng thái.
  AC: task trước có bằng chứng PASS, tài liệu khớp code; nêu giới hạn chase thẳng,
  không tự mở rộng sang pathfinding. Không DONE nếu AC/playtest bắt buộc chưa đạt.
  Verify: rà chứng cứ từng task, link tài liệu; chạy lại verify chỉ khi có thay đổi
  mới hoặc vấn đề cần kiểm chứng. Tài liệu: STATE, mục lục và kết quả trong plan.

## Rủi ro và quyết định còn mở

- Chưa xác định người dùng muốn tiếp tục gameplay hay workflow; cần chọn hướng
  trước khi dùng plan này để triển khai.
- Thông số demo và hitbox chưa chốt; tỷ lệ ảnh Makima khác Reze nên sprite và
  hitbox có thể không trùng nhau. Cần thể hiện vùng đánh khi playtest nếu khó đọc.
- Không pathfinding có thể khiến Enemy kẹt sau vật cản. Đây là giới hạn có chủ ý
  của phạm vi đề xuất, chỉ chấp nhận sau khi người dùng duyệt.
- Case đồng thời, chắn đòn sát mép và bước di chuyển lớn cần test cụ thể để
  tránh phụ thuộc thứ tự update hoặc tốc độ frame.

## Change log

- 2026-11-12: lập DRAFT từ code hiện tại, chưa sửa gameplay; chờ chọn hướng và duyệt.
