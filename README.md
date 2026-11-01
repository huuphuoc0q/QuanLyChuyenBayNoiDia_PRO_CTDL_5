# Quản lý chuyến bay nội địa

Chương trình dòng lệnh viết bằng C++ để quản lý chuyến bay nội địa, đặt và trả vé, đồng thời tra cứu một số thông tin thống kê, phục vụ đồ án giữa kì chiếm 30% môn Cấu trúc dữ liệu mã học phần 2611COMP101602.

## Chức năng

- Hiển thị danh sách chuyến bay.
- Đặt vé bằng cách chọn chuyến bay và ghế còn trống.
- Đăng nhập khu vực quản lý để:
  - Duyệt các yêu cầu đặt vé đang chờ.
  - Xử lý trả vé.
  - Thống kê khách hàng theo chuyến bay, ghế còn trống và số chuyến bay của máy bay.
- Nhấn `ESC` tại các bước nhập liệu có hỗ trợ để quay lại.

## Yêu cầu

- Windows.
- Trình biên dịch `g++` (MinGW-w64), có thể gọi được từ `PATH`.
- Hỗ trợ chuẩn C++11 trở lên.


## Biên dịch và chạy

Mở PowerShell hoặc Command Prompt tại thư mục gốc dự án, sau đó chạy:

```bat
.\run.bat
```

Tập lệnh sẽ biên dịch các tệp trong `src/` bằng `g++` thành `main.exe`, rồi chạy chương trình nếu biên dịch thành công. Nếu lệnh `g++` không được nhận diện, hãy cài MinGW-w64 và thêm thư mục chứa `g++.exe` vào biến môi trường `PATH`.

Có thể biên dịch thủ công bằng lệnh tương đương:

```bat
g++ -std=c++11 -Iinclude src/main.cpp src/UI_Menu.cpp src/MayBay.cpp src/ChuyenBay.cpp src/FileStore.cpp src/ThongKe.cpp src/KhachHang.cpp src/Ve.cpp src/Validation.cpp -o main.exe
```

Chạy chương trình sau khi biên dịch:

```bat
.\main.exe
```

## Hướng dẫn sử dụng

1. Ở menu chính, chọn xem chuyến bay, đặt vé hoặc vào khu vực quản lý.
2. Khi đặt vé, nhập mã chuyến bay, chọn ghế còn trống, rồi nhập họ tên và số căn cước công dân.
3. Yêu cầu đặt vé mới cần được duyệt trong mục **Quản lý → Xử lý đặt vé** trước khi trở thành vé đã xác nhận.
4. Để trả vé hoặc xem thống kê, vào khu vực quản lý và đăng nhập bằng tài khoản được cấu hình trong `data/Admin.txt`.

## Cấu trúc dự án

```text
include/        Các khai báo lớp và cấu trúc dữ liệu
src/            Mã nguồn chương trình
data/           Dữ liệu máy bay, chuyến bay, khách hàng và vé
data/DATA_VE/   Các tệp thông tin vé
docs/           Tài liệu tham khảo của dự án
run.bat         Tập lệnh biên dịch và chạy trên Windows
```

Một số lớp và thành phần chính:

- `MayBay`, `ChuyenBay`, `Ve`, `KhachHang`: mô hình dữ liệu.
- `Tree` trong `BST.h`: lưu trữ và tìm kiếm chuyến bay.
- `LinkedList`: lưu các yêu cầu đặt vé đang chờ duyệt.
- `FileStore`: đọc và ghi dữ liệu.
- `ThongKe`: các chức năng thống kê.
- `UI_Menu`, `Validation`: giao diện console và kiểm tra/chuẩn hóa dữ liệu nhập.

## Dữ liệu

Chương trình đọc dữ liệu tương đối từ thư mục làm việc hiện tại. Vì vậy, hãy chạy `run.bat` hoặc `main.exe` từ thư mục gốc dự án để các đường dẫn `data/...` hoạt động đúng.

- `data/MayBay.txt`: mỗi dòng gồm mã máy bay và số chỗ.
- `data/ChuyenBay.txt`: mỗi dòng gồm mã chuyến bay, mã máy bay, thời gian khởi hành, sân bay đến và một giá trị trạng thái.
- `data/Admin.txt`: tài khoản dùng để đăng nhập khu vực quản lý.
- `data/DATA_VE/`: nơi chương trình ghi tệp thông tin vé sau khi duyệt.

## Lưu ý về trạng thái dữ liệu

Ở phiên bản hiện tại, trạng thái chuyến bay được tạo ngẫu nhiên khi khởi động; giá trị trạng thái cuối dòng trong `data/ChuyenBay.txt` chưa được dùng để khôi phục trạng thái. Danh sách vé đã lưu trong `data/DATA_VE/` cũng chưa được nạp lại vào bộ nhớ khi khởi động. Vì vậy, dữ liệu vé và trạng thái chuyến bay chưa được duy trì đầy đủ giữa các lần chạy.
