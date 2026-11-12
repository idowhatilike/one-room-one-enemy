# Quyết định dự án

Chỉ ghi quyết định có căn cứ; đề xuất chưa duyệt không phải kiến trúc hiện hành.

| Quyết định | Căn cứ và hệ quả |
| --- | --- |
| Giữ C++20, raylib tag 6.2 | CMakeLists.txt hiện tại; không hạ xuống C++17 từ mẫu |
| Giữ layout shared/entities và naming hiện tại | Code và hướng dẫn đã thống nhất; không refactor gameplay trong task thiết lập workflow |
| Comment mới và tài liệu tiếng Việt | Quy tắc làm việc người dùng đã cung cấp; không áp dụng quy tắc tiếng Anh xung đột trong file tham khảo |
| Dùng AGENTS.md | Người dùng yêu cầu tự sửa tên hướng dẫn phù hợp; thay cho AGENT.md |
| Bốn skill trong .claude/skills/ | Vị trí của file tham khảo, AGENTS.md dẫn tới từng SKILL.md; không tạo project-memory riêng ngoài bốn skill yêu cầu |
| STATE tối đa 40 dòng, docs tách theo vai trò | Yêu cầu bộ nhớ dự án gọn; hồ sơ hoàn tất nằm ở archive khi được phép chuyển |
| Verify phải build, 0 warning và CTest | Yêu cầu người dùng; đăng ký hai test sẵn có thay vì chấp nhận kết quả không có test |
| Verify không tải raylib ngầm | Dependency cần phê duyệt; cấu hình verify dùng FETCHCONTENT_FULLY_DISCONNECTED=ON |
| Chưa migrate core/game/render/app hay RAII | Đây là đề xuất của mẫu, khác code thực tế; cần plan và duyệt riêng |

Quyết định mới cần ghi lý do từ yêu cầu, code hoặc thảo luận đã duyệt, và ảnh
hưởng đến module. Không suy diễn mục tiêu thiết kế từ tên biến.
