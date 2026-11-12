---
name: plan-feature
description: Lập plan cho tính năng, mechanic hoặc refactor của One Room One Enemy trước khi triển khai; không dùng để thực hiện task đã duyệt.
---

# Lập plan

Đọc `docs/STATE.md`, `docs/ARCHITECTURE.md`, quyết định liên quan và code bị ảnh
hưởng. Dùng `docs/game_data.md` để tìm đúng tài liệu module; không đọc toàn bộ docs.

- Xác định yêu cầu, hiện trạng, invariant và điều chưa rõ. So sánh phương án khả thi,
  chọn cách đơn giản đủ yêu cầu. Không biến ý tưởng thêm thành yêu cầu.
- Chọn số NNN tiếp theo chưa dùng trong `docs/plans/` và `docs/archive/`.
  Viết `docs/plans/NNN-slug.md`: `Status: DRAFT`, mục tiêu, phạm vi/ngoài phạm vi,
  bằng chứng hiện trạng, phương án, file bị ảnh hưởng, rủi ro, task và Change log.
- Mỗi task có checkbox, AC quan sát được, `Verify:` cụ thể, tài liệu cần cập nhật.
  Tách task để có thể triển khai và kiểm tra riêng, không thêm tầng kiến trúc vô cớ.
- Tóm tắt tối đa 10 dòng, dẫn plan rồi chờ duyệt trước khi sửa code. Chỉ đặt
  `Status: APPROVED` sau phê duyệt thực tế; ghi nhận phạm vi đã duyệt.
- Cập nhật STATE với plan hiện tại, câu hỏi/blocker và bước tiếp theo.

Ngoại lệ nhỏ theo AGENTS.md được thực hiện trực tiếp. Tài liệu chỉ tổ chức lại
không được mô tả thành thay đổi gameplay. Khi thực hiện plan dùng `execute-task`.
