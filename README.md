# Hệ thống quản lý chuyến bay nội địa

Ứng dụng console viết bằng C++ để quản lý chuyến bay, đặt vé, duyệt vé, xử lý trả vé và tra cứu thống kê.

Dự án được thực hiện trong khuôn khổ đồ án môn **Cấu trúc dữ liệu và giải thuật** (mã học phần `2611COMP101602`).

## Tính năng

### Người dùng

- Xem danh sách máy bay và chuyến bay.
- Chọn chuyến bay còn hoạt động.
- Chọn ghế trống bằng giao diện tương tác.
- Nhập và chuẩn hóa họ tên, số CCCD/CMND.
- Gửi yêu cầu đặt vé chờ duyệt.
- Nhấn `ESC` để thoát khỏi bước nhập liệu hoặc quay lại.

### Quản lý

- Đăng nhập bằng tài khoản trong `data/Admin.txt`.
- Duyệt đồng loạt các yêu cầu đặt vé.
- Trả vé theo mã vé.
- Thống kê:
  - Danh sách khách hàng của một chuyến bay.
  - Số ghế trống của một chuyến bay.
  - Số chuyến bay đã/đang sử dụng từng máy bay.

## Cấu trúc dữ liệu chính

| Thành phần | Vai trò |
|---|---|
| `BST.h` / `Tree<ChuyenBay>` | Cây AVL lưu và sắp xếp chuyến bay theo mã |
| `LinkedList.h` | Danh sách liên kết chứa vé đang chờ duyệt |
| `MayBay` | Thông tin máy bay và tổng số ghế |
| `ChuyenBay` | Thông tin chuyến bay, máy bay, trạng thái và ghế |
| `Ve` / `KhachHang` | Thông tin vé và hành khách |
| `FileStore` | Đọc dữ liệu nguồn và ghi dữ liệu vé |
| `ThongKe` | Xử lý các truy vấn thống kê |
| `UI_Menu` / `Validation` | Giao diện console, nhập liệu và kiểm tra dữ liệu |

## Yêu cầu môi trường

- Hệ điều hành **Windows**.
- Trình biên dịch `g++` của **MinGW-w64**.
- `g++` phải nằm trong biến môi trường `PATH`.
- Mã nguồn sử dụng chuẩn **C++11** trở lên.

Kiểm tra trình biên dịch:

```bat
g++ --version
```

## Cài đặt và chạy

Mở PowerShell hoặc Command Prompt tại thư mục gốc của dự án rồi chạy:

```bat
.\run.bat
```

`run.bat` thực hiện:

1. Biên dịch các tệp trong `src/`.
2. Liên kết với các khai báo trong `include/`.
3. Tạo `main.exe`.
4. Chạy chương trình nếu biên dịch thành công.

### Biên dịch thủ công

```bat
g++ -std=c++11 -Iinclude src/main.cpp src/UI_Menu.cpp src/MayBay.cpp src/ChuyenBay.cpp src/FileStore.cpp src/ThongKe.cpp src/KhachHang.cpp src/Ve.cpp src/Validation.cpp -o main.exe
```

Chạy chương trình:

```bat
.\main.exe
```

> Chương trình dùng đường dẫn tương đối `data/...`, nên phải chạy từ thư mục gốc dự án.

## Quy trình sử dụng

### 1. Đặt vé

1. Chọn **Đặt vé** từ menu chính.
2. Nhập mã chuyến bay.
3. Chọn một ghế trống.
4. Nhập họ tên.
5. Nhập CCCD/CMND gồm 12 ký tự và chỉ chứa chữ số.
6. Vé được đưa vào danh sách chờ duyệt.

### 2. Duyệt vé

1. Chọn **Quản lý**.
2. Đăng nhập bằng tài khoản trong `data/Admin.txt`.
3. Chọn **Xử lý đặt vé**.
4. Nhập mã vé để duyệt riêng vé đó, hoặc nhập `Y` để duyệt toàn bộ yêu cầu đang chờ.

### 3. Trả vé

1. Đăng nhập khu vực quản lý.
2. Chọn **Xử lý trả vé**.
3. Nhập mã vé cần trả, hoặc nhập `Y` để trả toàn bộ vé chưa thuộc chuyến bay đã hoàn tất.

Sau khi duyệt hoặc trả vé, dữ liệu được ghi lại vào `data/KhachHang.txt` và thư mục `data/DATA_VE/`.

## Dữ liệu

```text
data/
├── Admin.txt        Tài khoản quản lý
├── MayBay.txt       Danh sách máy bay và số ghế
├── ChuyenBay.txt    Danh sách chuyến bay
├── KhachHang.txt    Thông tin vé/hành khách đã duyệt
└── DATA_VE/         Tệp chi tiết từng vé
```

Định dạng dữ liệu quan trọng:

- `MayBay.txt`: `Mã_máy_bay Số_chỗ_ngồi`
- `ChuyenBay.txt`: `Mã_chuyến_bay Mã_máy_bay Ngày_giờ Sân_bay_đến Trạng_thái`
- `Admin.txt`: `Tài_khoản Mật_khẩu`

## Cấu trúc thư mục

```text
QuanLyChuyenBayNoiDia_PRO_CTDL_5/
├── data/                                      # Cơ sở dữ liệu dạng văn bản và tệp lưu thông tin vé
│   ├── DATA_VE/                               # Thư mục chứa các phiếu đặt vé riêng lẻ
│   │   └── ...                                # Lưu thông tin mã vé và hành khách
│   ├── Admin.txt                              # Lưu thông tin tài khoản quản lý
│   ├── MayBay.txt                             # Lưu thông tin số hiệu máy bay và số ghế
│   ├── ChuyenBay.txt                          # Lưu thông tin danh sách chuyến bay
│   └── KhachHang.txt                          # Lưu thông tin danh sách khách hàng đã đặt vé thành công
├── include/                                   # Thư mục chứa các tệp tiêu đề (.h)
│   ├── MayBay.h                               # Khai báo cấu trúc lớp Máy bay
│   ├── ChuyenBay.h                            # Khai báo cấu trúc lớp Chuyến bay
│   ├── KhachHang.h                            # Khai báo cấu trúc lớp Khách hàng
│   ├── Ve.h                                   # Khai báo cấu trúc lớp Vé
│   ├── BST.h                                  # Khai báo cấu trúc cây AVL để lưu trữ dữ liệu
│   ├── LinkedList.h                           # Khai báo cấu trúc danh sách liên kết đơn (Template)
│   ├── FileStore.h                            # Khai báo các chức năng đọc/ghi tệp tin và lưu dữ liệu
│   ├── ThongKe.h                              # Khai báo các chức năng truy vấn và hiển thị thống kê
│   ├── Validation.h                           # Khai báo các chức năng kiểm tra và chuẩn hóa dữ liệu nhập
│   └── UI_Menu.h                              # Khai báo giao diện người dùng console
├── src/                                       # Thư mục chứa các tệp mã nguồn (.cpp)
│   ├── MayBay.cpp                             # Định nghĩa các phương thức của lớp Máy bay
│   ├── ChuyenBay.cpp                          # Định nghĩa các phương thức của lớp Chuyến bay
│   ├── KhachHang.cpp                          # Định nghĩa các phương thức của lớp Khách hàng
│   ├── Ve.cpp                                 # Định nghĩa các phương thức của lớp Vé
│   ├── FileStore.cpp                          # Cài đặt chức năng đọc/ghi tệp tin và lưu dữ liệu
│   ├── ThongKe.cpp                            # Cài đặt chức năng truy vấn và hiển thị thống kê
│   ├── Validation.cpp                         # Cài đặt chức năng kiểm tra và chuẩn hóa dữ liệu nhập
│   ├── UI_Menu.cpp                            # Cài đặt giao diện người dùng console
│   └── main.cpp                               # Điểm khởi chạy và điều phối hoạt động chính của chương trình
├── docs/                                      # Tài liệu tham khảo của dự án
├── run.bat                                    # Tập lệnh biên dịch và chạy chương trình
├── main.exe                                   # Tệp thực thi
├── build_check.exe                            # Tệp thực thi dùng để kiểm tra dự án
└── README.md                                  # Giới thiệu dự án, hướng dẫn cài đặt và sử dụng
```

## Lưu ý

- Trạng thái chuyến bay trong phiên bản hiện tại được khởi tạo ngẫu nhiên khi chương trình chạy, không đọc trực tiếp giá trị trạng thái cuối dòng trong `ChuyenBay.txt`.
- Vé mẫu có thể được tạo khi khởi tạo dữ liệu chuyến bay.
- Các vé mới chỉ được lưu bền vững sau khi được duyệt.
- Khi thoát chương trình, hàm dọn dữ liệu vé có thể xóa các tệp vé trong bộ nhớ phiên làm việc. Vì vậy, trạng thái vé nên được xem là dữ liệu tạm theo phiên chạy.
- Thống kê chỉ phản ánh dữ liệu hiện có trong bộ nhớ của phiên chạy hiện tại.

## Công nghệ sử dụng

- Ngôn ngữ: C++
- Chuẩn: C++11
- Nền tảng: Windows Console
- API console: Windows API (`windows.h`, `conio.h`)
