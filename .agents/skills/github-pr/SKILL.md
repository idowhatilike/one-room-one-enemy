---
name: github-pr
description: Chuẩn bị commit, push branch lên GitHub và tạo hoặc cập nhật pull request cho One Room One Enemy, kiểm soát phạm vi diff, verify và quyền gửi. Không dùng để triển khai tính năng, deploy hoặc tự merge PR.
---

# Git và GitHub PR

Đọc STATE, AGENTS, yêu cầu hiện tại, template PR và CI nếu có. Skill xử lý thay đổi
đã có; không tự duyệt plan DRAFT hay triển khai tính năng để làm đầy PR.
Yêu cầu thêm/cài skill này không phải quyền commit, push hay tạo PR.

## Chuẩn bị để review

1. Kiểm tra repository, branch, remote, upstream/base branch, `git status --short`,
   diff unstaged và staged. Phân biệt thay đổi thuộc yêu cầu với công việc người dùng
   đang có. Nhánh chưa có commit đầu tiên cần được xử lý riêng, không giả định HEAD tồn tại.
2. Chốt remote/base từ cấu hình và bằng chứng GitHub. Không suy ra default branch
   là main/master chỉ từ tên nhánh local. Không tự thêm/đổi remote hoặc tạo repository.
   Nếu thiếu thông tin ảnh hưởng nơi gửi, hỏi một lần sau khi chuẩn bị phần độc lập.
3. Đọc diff cuối và file untracked trong phạm vi, trừ secret. Không đọc/in `.env`,
   token, private key hay credential. Chỉ đưa source, asset và docs thực sự cần;
   kiểm tra ignore rule để không gửi build/, dependency tải về hoặc log verify.
   File đã tracked không tự được bảo vệ chỉ nhờ thêm vào .gitignore; không tự untrack
   hoặc sửa ignore ngoài phạm vi đã giao.
4. Chạy `bash tools/verify.sh` và Verify của task khi có thay đổi code/build. Chỉ
   đổi tài liệu/đường dẫn skill thì kiểm tra link và quick_validate nếu validator có
   sẵn; không chạy build lặp vô ích. Ghi đúng kiểm tra đã chạy và lý do bỏ qua.
   Kiểm tra bắt buộc thất bại thì chưa gửi; không tự cài dependency hoặc đổi lockfile.
5. Soạn commit message theo lịch sử repo; PR theo template hoặc mô tả ngắn bằng
   tiếng Việt: vấn đề/kết quả, thay đổi chính, xác minh, giới hạn. Title theo diff
   cuối; không kể lịch sử hội thoại. Hoàn tất nội dung có thể review trước khi xin
   quyền gửi còn thiếu. Cập nhật STATE trước khi chốt diff, không để docs lệch commit.

## Quyền và thực hiện

- Yêu cầu rõ commit cho phép commit trong phạm vi đã giao; không tự cho phép push.
  Yêu cầu push cho phép commit cần thiết và push phần đã giao; không tự tạo PR.
  Yêu cầu tạo/mở PR cho phép các bước commit/push cần thiết cho PR đó. Yêu cầu
  chuẩn bị PR hoặc gọi tên skill chưa đủ quyền gửi. Tôn trọng quyền đã cấp trong
  hội thoại; không hỏi lại. Nếu còn thiếu, nêu branch/remote, file, tác động và
  khả năng hoàn tác rồi chỉ xin quyền đúng thao tác đó theo AGENTS.md.
- Dùng branch đang có nếu đúng scope và không phải nhánh tích hợp cần bảo vệ;
  nếu cần, tạo branch `codex/<slug>` và giữ nguyên thay đổi đang có. Không mặc định
  push thẳng main/master. Nếu yêu cầu là push trực tiếp nhánh đó, làm đúng phạm vi
  đã chỉ định sau khi kiểm tra remote và diff.
- Stage file/hunk cụ thể đã review, xem `git diff --cached` và `git diff --cached --check`
  trước commit. Không dùng `git add .`/`git commit -am` để gom công việc ngoài scope.
  Nếu index đã có thay đổi người dùng, không tự commit hay unstage phần đó.
- Push thường với remote/branch rõ ràng; không force, amend, reset, rebase, xóa
  branch, merge PR hay đổi lịch sử nếu chưa có chỉ dẫn riêng. Push bị từ chối thì
  báo nguyên nhân; không tự pull/rebase để vượt lỗi. Không giả định push đã thành công
  chỉ vì commit local thành công.

## PR và bàn giao

Ưu tiên connector GitHub nếu đủ chức năng; nếu không dùng Git/gh đã có. Kiểm tra
CLI/auth bằng trạng thái, không lấy token ra đọc. Thiếu công cụ/quyền thì báo và
hoàn tất patch/nội dung PR có thể chuẩn bị; không tự cài gh hay đổi Git config.

Trước khi tạo, tìm PR hiện có của đúng head/base và repository để tránh trùng;
PR đã có thì cập nhật nếu nằm trong yêu cầu. Mặc định tạo draft PR để review.
Với gh, ghi body UTF-8 vào file tạm và truyền `--body-file`, không ghép nội dung
nhiều dòng vào shell command. Không sửa file body đang có của người dùng.

Xác nhận branch/commit ở remote và URL/head/base của PR từ kết quả thực tế.
Nếu gửi gặp timeout/lỗi không rõ, kiểm tra remote/PR trước khi thử lại. Kiểm tra
CI khi truy cập được; push/PR thành công không đồng nghĩa CI PASS. Không tự sửa
lỗi CI ngoài phạm vi hoặc tự merge. Cập nhật STATE ngắn gọn; nếu cập nhật sau
commit tạo diff mới, báo rõ và không tự tạo thêm commit ngoài yêu cầu.

Báo branch/commit, link PR nếu có, kiểm tra local, trạng thái CI và blocker.
Không nói đã push/tạo PR khi mới chuẩn bị, hoặc khẳng định đã verify GitHub thật
khi chưa thực hiện. Không deploy/publish/release như một phần ngầm định của PR.
