---
name: fix-bug
description: Điều tra và sửa bug, crash, sai hành vi hoặc lỗi build/test trong One Room One Enemy bằng reproduction trước và kiểm tra regression sau.
---

# Sửa bug

Đọc STATE, code và tài liệu liên quan; ghi `docs/bugs/NNN-slug.md` với triệu
chứng, môi trường, bước tái hiện, expected/actual, bằng chứng và fix plan.
Dùng số chưa có trong bugs/archive. Phân biệt nguyên nhân đã chứng minh với giả thuyết.

- Tạo hoặc chọn reproduction test quan sát đúng lỗi. Chạy và xác nhận FAIL đúng
  nguyên nhân, không tính lỗi setup/compiler/dependency là bằng chứng cho bug khác.
- Trước khi sửa code, ghi fix plan, phạm vi và AC/Verify; tóm tắt và chờ duyệt theo
  AGENTS.md nếu chưa có phê duyệt. Không hỏi lại phạm vi đã được duyệt.
- Vá nguyên nhân bằng diff nhỏ. Chạy lại reproduction để thấy PASS, regression liên
  quan và `bash tools/verify.sh`. Không đổi expected chỉ để test pass.
- Đếm lần vá không đạt theo kết quả reproduction/AC. Sau hai lần không đạt, dừng,
  hoàn tác riêng patch sửa lỗi của mình nếu an toàn, giữ reproduction và bằng chứng;
  không reset/ghi đè thay đổi người dùng. Báo hạn chế, chờ dữ kiện mới trước lần ba.
- Cập nhật hồ sơ bug: nguyên nhân, patch, lệnh/kết quả, trạng thái OPEN hoặc FIXED;
  cập nhật docs module và STATE. Chỉ FIXED khi AC/Verify đạt; không tự archive file.
