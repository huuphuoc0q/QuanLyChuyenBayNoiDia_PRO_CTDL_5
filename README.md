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
data/           Dữ liệu máy bay, chuyến bay, khách hàng
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
- `data/KhachHang.txt`: mỗi dòng gồm số thứ tự khách hàng, tên khách hàng, số cccd, mã vé, mã chuyến bay, số ghế chọn.
- `data/DATA_VE/`: nơi chương trình ghi tệp thông tin vé sau khi duyệt.

## Sơ đồ tổ chức thư mục mã nguồn

QuanLyChuyenBayNoiDia
│
├── data/                               # Cơ sở dữ liệu dạng văn bản và tệp lưu trữ thông tin vé
│   ├── DATA_VE/                        # Thư mục chứa các phiếu thông tin vé riêng lẻ (<MãVé>.txt)
│   ├── Admin.txt                       # Lưu thông tintài khoản và mật khẩu của Quản trị viên
│   ├── MayBay.txt                      # Lưu thông tin số hiệu máy bay và số lượng chỗ ngồi trong máy bay
│   ├── ChuyenBay.txt                   # Lưu thông tin danh sách các chuyến bay nội địa
│   └── KhachHang.txt                   # Lưu thông tin danh sách các khách hàng đã đặt vé thành công                     
│
├── include/                            # Thư mục chứa các tệp tiêu đề khai báo (Header files - .h)
│   ├── MayBay.h                        # Khai báo cấu trúc lớp Máy bay
│   ├── ChuyenBay.h                     # Khai báo cấu trúc lớp Chuyến bay
│   ├── KhachHang.h                     # Khai báo cấu trúc lớp Khách hàng
│   ├── Ve.h                            # Khai báo cấu trúc lớp Vé
│   ├── BST.h                           # Khai báo cấu trúc Cây AVL tự cân bằng (Template)
│   ├── LinkedList.h                    # Khai báo cấu trúc Danh sách liên kết đơn (Template)
│   ├── FileStore.h                     # Khai báo các chức năng đọc/ghi tệp tin và đồng bộ dữ liệu
│   ├── ThongKe.h                       # Khai báo các chức năng tra cứu và hiển thị thông tin thống kê
│   ├── Validation.h                    # Khai báo các chức năng kiểm tra ràng buộc và chuẩn hóa dữ liệu
│   └── UI_Menu.h                       # Khai báo cơ chế tương tác trong giao diện ứng dụng console
│
├── src/                                # Thư mục chứa các tệp cài đặt mã nguồn (.cpp)
│   ├── MayBay.cpp                      # Định nghĩa các phương thức của lớp MayBay
│   ├── ChuyenBay.cpp                   # Định nghĩa các phương thức của lớp ChuyenBay
│   ├── KhachHang.cpp                   # Định nghĩa các phương thức của lớp KhachHang
│   ├── Ve.cpp                          # Định nghĩa các phương thức của lớp Ve
│   ├── FileStore.cpp                   # Cài đặt chức năng đọc/ghi tệp tin và đồng bộ dữ liệu
│   ├── ThongKe.cpp                     # Cài đặt chức năng tra cứu và hiển thị thông tin thống kê
│   ├── Validation.cpp                  # Cài đặt chức năng kiểm tra ràng buộc và chuẩn hóa dữ liệu
│   ├── UI_Menu.cpp                     # Cài đặt cơ chế tương tác trong giao diện ứng dụng console
│   └── main.cpp                        # Điểm khởi chạy và điều phối luồng hoạt động chính của chương trình
│                            
└── README.md                           # Giới thiệu chương trình hệ thống và hướng dẫn biên dịch, cài đặt

## Lưu ý về trạng thái dữ liệu

Ở phiên bản hiện tại, trạng thái chuyến bay được tạo ngẫu nhiên khi khởi động; giá trị trạng thái cuối dòng trong `data/ChuyenBay.txt` chưa được dùng để khôi phục trạng thái. Danh sách vé đã lưu trong `data/DATA_VE/` cũng chưa được nạp lại vào bộ nhớ khi khởi động. Vì vậy, dữ liệu vé và trạng thái chuyến bay chưa được duy trì đầy đủ giữa các lần chạy.
