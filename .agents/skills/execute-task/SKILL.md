---
name: execute-task
description: Thực hiện một task tiếp theo trong plan đã được duyệt của One Room One Enemy, kèm acceptance criteria và verify.
---

# Thực hiện task

Đọc STATE, plan đang hoạt động và code/tài liệu của task đầu tiên chưa hoàn tất.
Kiểm tra `Status: APPROVED` có căn cứ trong hội thoại hoặc hồ sơ duyệt; nếu chưa
có thì yêu cầu duyệt plan cụ thể, không tự gán trạng thái.

- Chọn một task, giữ nguyên AC; nêu ngắn kết quả cần đạt và lệnh Verify.
- Kiểm tra thay đổi đang có, sửa tối thiểu theo convention. Không tự cài dependency,
  đổi architecture hoặc sửa bug ngoài task. Nếu task thêm type, đọc `add-game-type`.
- Chạy Verify riêng của task và `bash tools/verify.sh`. Lỗi kiểm tra phải được giải
  thích; chỉ tick `[x]` khi tất cả AC và Verify PASS. Không coi build cache hoặc
  test không chạy là PASS.
- Cập nhật tài liệu module, STATE và Change log nếu cách thực hiện đổi so với plan.
  Nếu scope tăng, ghi đề xuất và chờ duyệt phần mở rộng trước khi làm.
- Báo kết quả của task, bằng chứng và bước tiếp theo. Không tự triển khai task khác
  nếu người dùng chỉ giao một task; lệnh làm toàn plan cho phép đi tuần tự từng task.
