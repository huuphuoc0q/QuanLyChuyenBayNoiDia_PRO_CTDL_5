@echo off
chcp 65001 > nul

cls
echo ===================================================
echo     DANG BIEN DICH DU AN QUAN LY CHUYEN BAY
echo ===================================================


g++ -std=c++11 -Iinclude src/main.cpp src/MayBay.cpp src/ChuyenBay.cpp src/FileStore.cpp src/ThongKe.cpp src/KhachHang.cpp src/Ve.cpp src/Validation.cpp -o main.exe
if %errorlevel% equ 0 (
    echo.
    echo [THANH CONG] Bien dich hoan tat!
    echo ===================================================
    echo Dang khoi chay chuong trinh...
    echo.
    main.exe
) else (
    echo.
    echo [THAT BAI] Co loi xay ra trong qua trinh bien dich!
    echo Vui long kiem tra lai thong bao loi o tren.
)

echo.
pause