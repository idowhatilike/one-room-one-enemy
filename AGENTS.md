# AGENTS.md — One Room One Enemy

Game hướng tới combat một phòng, một Enemy, kết hợp địa hình. Hiện dùng
C++20, raylib và CMake; trạng thái thực tế nằm trong `docs/STATE.md`.
Trao đổi, comment mới và tài liệu bằng tiếng Việt; identifier theo code hiện có.

## Mỗi phiên làm việc

1. Đọc `docs/STATE.md` (tối đa 40 dòng). Đây là tài liệu bắt buộc ban đầu.
2. Chọn skill phù hợp trong bảng; chỉ đọc thêm code/tài liệu liên quan.
3. Trước khi dừng hoặc chuyển context, cập nhật STATE ngắn gọn, không ghi nhật ký.

## Skills Codex (`.agents/skills/`)

| Tình huống | Skill |
| --- | --- |
| Tính năng, mechanic, refactor nhiều file hoặc đổi hành vi | [plan-feature](.agents/skills/plan-feature/SKILL.md) |
| Có plan đã duyệt, thực hiện task tiếp theo | [execute-task](.agents/skills/execute-task/SKILL.md) |
| Bug, crash, hành vi sai, build/test lỗi | [fix-bug](.agents/skills/fix-bug/SKILL.md) |
| Thêm enum/value, struct, entity kind hoặc flags | [add-game-type](.agents/skills/add-game-type/SKILL.md) |
| Chuẩn bị commit, push GitHub, tạo hoặc cập nhật PR | [github-pr](.agents/skills/github-pr/SKILL.md) |

Skill được đọc theo đường dẫn trên; việc chọn skill không cho phép vượt phạm vi
người dùng đã giao. Không cần skill project-memory riêng: cập nhật STATE là bước
kết thúc của các workflow.

## Quy trình bắt buộc

- Plan trước code: ghi `docs/plans/NNN-slug.md`, tóm tắt tối đa 10 dòng rồi
  chờ duyệt. Chỉ đặt `Status: APPROVED` khi người dùng thực sự duyệt plan.
  Nếu đã có phê duyệt trong hội thoại thì không hỏi lại. Ngoại lệ: sửa tối đa
  1 file, 15 dòng, không đổi API/hành vi; nói ý định một dòng rồi làm.
- Mỗi lần làm một task, có acceptance criteria (AC) và `Verify:`. Chỉ đánh
  `[x]` khi kiểm tra PASS; không sửa AC chỉ để hợp thức hóa kết quả.
- Bug: có reproduction và fix plan trước khi vá. Sau hai lần vá không đạt,
  dừng và báo bằng chứng; hoàn tác riêng patch của mình khi làm được an toàn,
  không đụng thay đổi người dùng hay dùng `git reset`. Chờ thông tin mới trước lần ba.
- Thêm type qua `add-game-type`; không thêm bare enum hay bảng name/count song song
  dễ lệch. Với enum cũ, giữ convention macro và bảng hiện có, không tự migrate.
- Ý tưởng ngoài phạm vi đưa vào Parking lot của STATE. Thay đổi plan ghi Change log;
  mở rộng yêu cầu/kiến trúc phải được duyệt. Gom tối đa 3 câu hỏi nếu thiếu dữ kiện,
  nêu phương án mặc định. Giữ nguyên AC đã duyệt.

## Code và phạm vi

- Giữ layout thực tế: `src/main.cpp`, `src/shared/`, `src/entities/`, `tests/`,
  `assets/`, `scripts/`. Xem `docs/ARCHITECTURE.md` trước khi đổi kiến trúc.
- Member `_camelCase`, hàm/local `camelCase`, type/enum `PascalCase`, constant
  `kPascalCase`, macro `UPPER_SNAKE_CASE`; dòng sửa dùng `a , b`, `object . member`.
  Nhánh một câu lệnh đơn giản không cần braces. Không format cả file.
- Giữ comment cũ; nếu sửa làm comment sai, báo lại. Comment mới giải thích lý do.
  Thêm enum value phải tìm và cập nhật macro; thêm class/vũ khí cập nhật đủ
  hàng/cột `kWeaponAffinity` đúng thứ tự enum.
- Build mã dự án với 0 warning; thiếu case enum là lỗi (`-Werror=switch`,
  `-Wswitch-enum`, hoặc MSVC tương ứng). Không dùng `default:` che case game enum.
- Logic mới nên tách khỏi input/render để test được; timing dùng delta time từ
  `GetFrameTime()`. Đặt tên cho thông số có ý nghĩa, tránh thêm magic number.
- Với tài nguyên đồ họa hiện tại, Load sau `InitWindow()`, Unload trước
  `CloseWindow()` và xử lý nhánh lỗi. Đề xuất RAII/layout mới phải nằm trong plan,
  không tự refactor để tuân thủ mẫu kiến trúc chưa triển khai.
- Không sửa output trong `build/` bằng tay, không bỏ thay đổi người dùng.
  Hỏi trước khi cài/đổi dependency, commit/push, xóa dữ liệu hoặc đổi ngoài dự án.

## Tài liệu và báo cáo

- `docs/STATE.md`: trạng thái hiện tại, bước tiếp theo, blocker, Parking lot.
- `docs/ARCHITECTURE.md`: cấu trúc và luồng dữ liệu thực tế.
- `docs/DECISIONS.md`: quyết định đã có căn cứ, phân biệt đề xuất chưa duyệt.
- `docs/plans/`, `docs/bugs/`: plan và reproduction/fix; `docs/archive/`: hồ sơ
  đã kết thúc, chỉ chuyển file sau khi người dùng cho phép. Các file theo module
  được tra từ `docs/game_data.md`.
- Dùng `rg`/glob trước, đọc đoạn cần thiết; không đọc lại tài liệu đã có trong context.
  Diff nhỏ, dẫn file thay vì dán lại code/plan. Tài liệu giữ trạng thái, không viết diary.
- Chạy `bash tools/verify.sh`: build lại, 0 warning, CTest; chỉ báo dòng quan trọng
  (tối đa 30 dòng). Log đầy đủ trong build; lỗi verify không cho phép tự sửa ngoài scope.
- Báo cáo ngắn, ưu tiên tối đa 8 dòng: thay đổi, lý do, kiểm tra, tài liệu, vấn đề
  còn lại. Nêu rõ kiểm tra chưa chạy và giới hạn bằng chứng.
