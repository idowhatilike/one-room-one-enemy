---
name: add-game-type
description: Thêm enum/value, struct, entity kind hoặc flags cho One Room One Enemy; giữ đồng bộ macro, bảng affinity và các consumer.
---

# Thêm game type

Đọc STATE, plan đã duyệt nếu có và định nghĩa/consumer hiện tại bằng `rg`.
Skill này xử lý phần type của task, không thay thế bước duyệt plan khi đổi API/hành vi.

- Xác định ý nghĩa, giá trị mặc định, thứ tự/index và nơi dùng cho switch, macro,
  bảng, serialization nếu có. Không tự thêm behavior hay dependency.
- Với enum hiện có: tìm tất cả value/macro; thêm macro tương ứng. Nếu không có
  macro, báo thực tế thay vì đoán. Giữ thứ tự cũ nếu consumer phụ thuộc ordinal.
- `CharacterClass`/`WeaponType` cần cập nhật mọi hàng/cột và kích thước
  `kWeaponAffinity`, bảng trong `docs/weapon.md`, test biên và mapping. Thông số
  cân bằng mới phải có căn cứ hoặc được người dùng chọn, không tự điền cho đủ bảng.
- Với enum mới có name/count metadata: dùng danh sách X-macro làm một nguồn sinh
  enum và metadata, không viết bare enum kèm bảng name/count độc lập. Không migrate
  các enum cũ ngoài scope. Struct/entity mới chỉ thêm dữ liệu/hành vi cần cho task.
- Switch trên game enum phải liệt kê các case, không thêm `default:` che thiếu case.
  Dùng compile-time check cho kích thước/mapping và runtime test cho behavior có rủi ro.
- Chạy Verify của task và `bash tools/verify.sh`; cập nhật docs module, STATE và
  DECISIONS chỉ khi có quyết định thiết kế mới đã được duyệt.
