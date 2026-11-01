#include "UI_Menu.h"

void UI_Menu::setColor(int colorCode) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colorCode);
}

void UI_Menu::hideCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void UI_Menu::clearScreen() {
    system("cls");
}

void UI_Menu::showCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void UI_Menu::inLine(std::string kiTu, int size_, std::string backGround, std::string text, std::string align, int valueColor){
    std::cout<<backGround; 
    if(align == "left"){
        setColor(valueColor); 
        for(int i = 0; i<5; i++) std::cout<<kiTu; 
        std::cout<<text; 
        for(int i = 0; i<size_ - text.length() - 5; i++) std::cout<<kiTu; 
        std::cout << "\033[0m";
        return; 
    }
    int left = (size_/2 - (text.length()/2));
    for(int i = 0; i<left; i++) 
        std::cout<<kiTu; 
    for(int i = 0; i<text.length(); i++)
        {
            setColor(valueColor); 
            std::cout<<text[i]; 
        }
    std::cout<<backGround; 
    
    for(int i = left + text.length(); i<size_; i++) 
        std::cout<<kiTu; 
    std::cout << "\033[0m";
    
}

void UI_Menu::printHeader() {
    inLine("=", 120, "\033[1;33m","FITP_DSA 2611COMP101602","center", 14); std::cout<<std::endl; 
    // std::cout << "\033[1;36m";
    inLine(" ",120,"\033[1;36m","▄▄ ▄▄  ▄▄▄▄      ▄▄▄▄▄ ▄▄ ▄▄  ▄▄▄  ▄▄  ▄▄  ▄▄▄▄       ▄▄▄  ▄▄ ▄▄  ▄▄▄  ▄▄  ▄▄      ▄▄  ▄▄ ▄▄     ","center", 11); std::cout<<std::endl;
    inLine(" ",120,"\033[1;36m","██▄▄█ ▄█▀▀▀      ▀██▀▀ ██▄▄█ ▄█▀██ ███▄██ ▄█▀▀▀      ▄█▀██ ██ ██ ▄█▀█▄ ███▄██      ██  ▀█▄██     ","center", 11); std::cout<<std::endl;
    inLine(" ",120,"\033[1;36m","█▀▀██ ▓▓▀▀        ▒▒   █▀▀██ ▓▓ ▓▓ ▓▓ ▀▓▓ ▓▓ ▀▒      ▓▓▐▓▄ ▓▓ █▀ ▓▓▀▒▒ ▓▓ ▀▓▓      █▄▄  ▄▄▓      ","center", 11); std::cout<<std::endl;
    inLine(" ",120,"\033[1;36m","▀▀ ▀▀ ▀▀▀▀▀       ▀▀   ▀▀ ▀▀  ▀▀▀  ▀▀  ▀▀ ▀▀▀▀▀       ▀▀ ▀ ▀▀▀▀  ▀▀ ▀▀ ▀▀  ▀▀      ▀▀▀  ▀▀▀      ","center", 11); std::cout<<std::endl;
    inLine(" ",120,"\033[1;36m"," ▄▄▄▄ ▄▄ ▄▄ ▄▄ ▄▄ ▄▄ ▄▄  ▄▄▄▄ ▄▄  ▄▄      ▄▄▄▄   ▄▄▄  ▄▄ ▄▄      ▄▄  ▄▄  ▄▄▄  ▄▄      ▄▄▄▄  ▄▄  ▄▄▄ ","center", 11); std::cout<<std::endl;
    inLine(" ",120,"\033[1;36m","██▀██ ██▄▄█ ██ ██ ▀█▄██ ▄█▀▀▀ ███▄██      ██▄█▀ ▄█▀█▄ ▀█▄██      ███▄██ ▄█▀██ ▄▄      ██▀██ ▄▄ ▄█▀█▄","center", 11); std::cout<<std::endl;
    inLine(" ",120,"\033[1;36m","██ ▀▀ █▀▀██ ▓▓ █▀  ▄▄▓  ▓▓▀▀  ▓▓ ▀▓▓      ▒▒ ▒▒ ▓▓▀▒▒  ▄▄▓       ▓▓ ▀▓▓ ▓▓ ▓▓ ▓▓      ▓▓ ▓▓ ▓▓ ▓▓▀▒▒","center", 11); std::cout<<std::endl;
    inLine(" ",120,"\033[1;36m","▀▀▀▀▀ ▀▀ ▀▀ ▀▀▀▀   ▀▀▀  ▀▀▀▀▀ ▀▀  ▀▀      ▀▀▀▀▀ ▀▀ ▀▀  ▀▀▀       ▀▀  ▀▀  ▀▀▀  ▀▀      ▀▀▀▀  ▀▀ ▀▀ ▀▀","center", 11); std::cout<<std::endl;
    std::cout << "\033[0m";
}

void UI_Menu::printTitle(std::string title){
    title = Validation::toUpperCase(title);
    inLine("=", 120, "\033[1;33m", "FITP_DSA 2611COMP101602", "center", 14); std::cout<<std::endl;
    setColor(14); 
    std::cout<<"|";
    inLine(" ", 118, "\033[1;33m", title,"center", 14); 
    setColor(14); 
    std::cout<<"|";std::cout<<std::endl;
    inLine("=", 120, "\033[1;33m", ""); std::cout<<std::endl;
    std::cout << "\033[0m";
    setColor(7); 
} 

void UI_Menu::printOption(std::string title, std::vector<std::string>& option){
    printTitle(title);
    for(int i = 0; i<option.size(); i++){
        std::cout<<"\033[1;33m";
        setColor(14); 
        std::cout<<"|";
        inLine(" ", 118, "\033[1;33m", std::to_string(i+1) + ". " + option[i], "left", 177); 
        setColor(14); 
        std::cout<<"|"<<"\n";
    } 
    inLine("=", 120, "\033[1;33m", "");
    std::cout << "\033[0m";
    setColor(7); 
    std::cout<<"\n";
}

void UI_Menu::printTableDSCB(Tree<ChuyenBay>& dsChuyenBay){
    int wMa = 16, wNgay = 22, wSanBay = 15, wTrangThai = 15, wDSVe = 60;

    setColor(11);
    std::cout << "┌" << std::string(wMa, '-') << "┬" 
            << std::string(wNgay, '-') << "┬" 
            << std::string(wSanBay, '-') << "┬" 
            << std::string(wTrangThai, '-') <<"┬"
            << std::string(wDSVe, '-')<< "┐\n";

    std::cout << "│ " << std::left << std::setw(wMa + 2) << "Mã chuyến bay"
            << "│ " << std::setw(wNgay + 3) << "Ngày khởi hành"
            << "│ " << std::setw(wSanBay + 3) << "Sân bay đến"
            << "│ " << std::setw(wTrangThai + 2) << "Trạng thái"
            << "│ " << std::setw(wDSVe - 1) << "Danh sach ve"
            << "│\n";
    setColor(11);
    std::cout << "└" << std::string(wMa, '-') << "┴" 
            << std::string(wNgay, '-') << "┴" 
            << std::string(wSanBay, '-') << "┴" 
            << std::string(wTrangThai, '-') << "┴" 
            << std::string(wDSVe, '-') << "┘\n";
dsChuyenBay.xuat(); 
}

void UI_Menu::printTable(const std::vector<ChuyenBay*>& danhSach) {
    SetConsoleOutputCP(65001); 

    int wMa = 10, wNgay = 19, wSanBay = 13, wTrangThai = 13;

    setColor(11);
    std::cout << "┌" << std::string(wMa, '-') << "┬" 
            << std::string(wNgay, '-') << "┬" 
            << std::string(wSanBay, '-') << "┬" 
            << std::string(wTrangThai, '-') << "┐\n";

    std::cout << "│ " << std::left << std::setw(wMa) << "Mã CB"
            << "│ " << std::setw(wNgay + 3) << "Ngày khởi hành"
            << "│ " << std::setw(wSanBay + 3) << "Sân bay đến"
            << "│ " << std::setw(wTrangThai + 2) << "Trạng thái"
            << "│\n";

    std::cout << "├" << std::string(wMa, '-') << "┼" 
            << std::string(wNgay, '-') << "┼" 
            << std::string(wSanBay, '-') << "┼" 
            << std::string(wTrangThai, '-') << "┤\n";

    for (const auto& cb : danhSach) {
        int colorStatus = 15; 
        switch(cb->getStatus()) {
            case 0: 
                colorStatus = 12; 
                break;
            case 1: 
                colorStatus = 10;
                break;
            case 2: 
                colorStatus = 14;
                break;
            case 3: 
                colorStatus = 11;
                break;
            default: 
                break;
        };

        setColor(11); std::cout << "│ ";
        setColor(colorStatus); std::cout << std::left << std::setw(wMa - 1) << cb->getMaCB();
        
        setColor(11); std::cout << "│ ";
        setColor(15); std::cout << std::setw(wNgay - 1) << cb->getNgayKH();
        
        setColor(11); std::cout << "│ ";
        setColor(15); std::cout << std::setw(wSanBay - 1) << cb->getSanBD();

        setColor(11); std::cout << "│ ";
        // if (cb->getStatus() == 1) {
        //     // std::cout<<"\033[42;30m";
        //     setColor(32);
        // }      
        // else if (cb->getStatus() == 3) setColor(11);  // Cyan sáng
        // else if (cb->getStatus() == 2) setColor(14);    // Vàng sáng
        // else if (cb->getStatus() == 0) setColor(12); // Đỏ sáng
        // else setColor(15);

        std::string textStatus_ = "";
        switch(cb->getStatus()){
            case 0: 
                textStatus_ = "Huy chuyen";
                break;
            case 1:
                textStatus_ = "Con ve";
                break;
            case 2: 
                textStatus_ = "Het ve";
                break;
            case 3:
                textStatus_ = "Hoan tat";
                break;
            default: 
                break;
        }
        std::string colorCode = "\033[0m"; 

        if (textStatus_ == "Huy chuyen") {
            colorCode = "\033[41;37m"; // Nền Đỏ, chữ Trắng
        } else if (textStatus_ == "Con ve") {
            colorCode = "\033[42;30m"; // Nền Xanh lá, chữ Đen
        } else if (textStatus_ == "Het ve") {
            colorCode = "\033[43;30m"; // Nền Vàng, chữ Đen
        } else if (textStatus_ == "Hoan tat") {
            colorCode = "\033[44;37m"; // Nền Xanh dương, chữ Trắng
        }
        std::cout << colorCode << std::setw(wTrangThai - 1) << textStatus_;
        setColor(11); std::cout << "│\n";
    }

    setColor(11);
    std::cout << "└" << std::string(wMa, '-') << "┴" 
            << std::string(wNgay, '-') << "┴" 
            << std::string(wSanBay, '-') << "┴" 
            << std::string(wTrangThai, '-') << "┘\n";
            
    setColor(7); 
}

int UI_Menu::selectSeatInteractive(int totalSeats, const std::vector<int>& seatStatus) {
    int rows = (totalSeats + 5) / 6; // Dãy 6 ghế (A B C - D E F)
    int curRow = 0, curCol = 0;
    
    const int VISIBLE_ROWS = 10; 
    int startRow = 0;

    hideCursor();

    while (true) {
        clearScreen();
        
        if (curRow < startRow) {
            startRow = curRow;
        } else if (curRow >= startRow + VISIBLE_ROWS) {
            startRow = curRow - VISIBLE_ROWS + 1;
        }


        printTitle("SO DO CHON GHE");

        std::cout << "     A     B     C         D     E     F\n";
        std::cout << "   ┌─────┬─────┬─────┐   ┌─────┬─────┬─────┐\n";

        for (int r = startRow; r < startRow + VISIBLE_ROWS && r < rows; ++r) {
            std::cout << std::setw(3) << (r + 1) << "│";
            for (int c = 0; c < 6; ++c) {
                int seatIndex = r * 6 + c;

                if (seatIndex >= totalSeats) {
                    std::cout << "     "; 
                } else {
                    int isOccupied = seatStatus[seatIndex];
                    bool isSelected = (r == curRow && c == curCol);

                    if (isSelected) {
                        setColor(240); // Đang chọn
                        std::cout << (isOccupied ? "[ X ]" : "[ O ]");
                        setColor(7);
                    } else if (isOccupied) {
                        setColor(12);  // Đỏ: Đã đặt
                        std::cout << "  X  ";
                        setColor(7);
                    } else {
                        setColor(10);  // Xanh lá: Trống
                        std::cout << "  O  ";
                        setColor(7);
                    }
                }

                if (c == 2) std::cout << "│   │";
                else if (c < 5) std::cout << "│";
            }
            std::cout << "│\n";
        }
        std::cout << "   └─────┴─────┴─────┘   └─────┴─────┴─────┘\n";


        setColor(14);
        std::cout << "   ▲▼ [ Trang " << (startRow / VISIBLE_ROWS) + 1 << "/" << (rows + VISIBLE_ROWS - 1) / VISIBLE_ROWS 
                << " (Hang " << startRow + 1 << " -> " << std::min(startRow + VISIBLE_ROWS, rows) << " / " << rows << ") ]\n";
        setColor(7);

        std::cout << "\nGhi chu: ";
        setColor(10); std::cout << "O: Trong  ";
        setColor(12); std::cout << "X: Het cho ";
        setColor(240); std::cout << "[ ]: Dang chon";
        setColor(7); 
        std::cout << "\nDieu huong: [Phim mui ten 4 huong] | Chon: [ENTER] | Thoat: [ESC]\n";

        int key = _getch();
        if (key == 224) {
            key = _getch();
            if (key == KEY_UP && curRow > 0) {
                curRow--;
            } else if (key == KEY_DOWN && curRow < rows - 1) {
                curRow++;
            } else if (key == KEY_LEFT && curCol > 0) {
                curCol--;
            } else if (key == KEY_RIGHT && curCol < 5) {
                curCol++;
            }

            if (curRow * 6 + curCol >= totalSeats) {
                curCol = (totalSeats - 1) % 6;
            }
        } else if (key == KEY_ENTER) {
            int selectedSeatIndex = curRow * 6 + curCol;
            if (seatStatus[selectedSeatIndex] == 1) {
                // showPopupDialog("CANH BAO", "Ghe nay da co nguoi dat! Vui long chon ghe khac.");
                std::cout<<"Ghe nay da co nguoi dat"<<std::endl;
                Sleep(900); 
            } else {
                showCursor();
                return selectedSeatIndex;
            }
        } else if (key == KEY_ESC) {
            showCursor();
            return -1;
        }
    }
}
void UI_Menu::textInput(std::string text) {
    setColor(160); 
    std::cout<<"➜"<<text;
    setColor(7);
}

void UI_Menu::printTableVe() {
    int wMa = 10, wMaCB = 16, wSoGhe = 8, wKH = 25, wCMND = 14;

    setColor(11);
    std::cout << "┌" << std::string(wMa, '-') << "┬" 
            << std::string(wMaCB, '-') << "┬" 
            << std::string(wSoGhe, '-') << "┬" 
            << std::string(wKH, '-') << "┬" 
            << std::string(wCMND, '-') << "┐\n";
    
    std::cout << "│ " << std::left << std::setw(wMa - 1) << "Ma ve"
            << "│ " << std::setw(wMaCB - 1) << "Ma chuyen bay"
            << "│ " << std::setw(wSoGhe - 1) << "So ghe"
            << "│ " << std::setw(wKH - 1) << "Khach hang"
            << "│ " << std::setw(wCMND - 1) << "So CCCD"
            << "│\n";
    
    setColor(11);
    std::cout << "└" << std::string(wMa, '-') << "┴" 
            << std::string(wMaCB, '-') << "┴" 
            << std::string(wSoGhe, '-') << "┴" 
            << std::string(wKH, '-') << "┴" 
            << std::string(wCMND, '-') << "┘\n";
    
    setColor(7); 
}

void UI_Menu::printTableDSKH(const std::vector<Ve>& dsVe_) { 
    int sizeDSVe_ = dsVe_.size(); 

    int wStt = 5, wName = 25, wCMND = 14, wSoGhe = 8, wMaCB = 16; 

    setColor(11);
    std::cout << "┌" << std::string(wStt, '-') << "┬" 
            << std::string(wName, '-') << "┬" 
            << std::string(wCMND, '-') << "┬" 
            << std::string(wSoGhe, '-') << "┬" 
            << std::string(wMaCB, '-') << "┐\n";
    
    std::cout << "│ " << std::left << std::setw(wStt - 1) << "STT"
            << "│ " << std::setw(wName - 1) << "Ho va ten"
            << "│ " << std::setw(wCMND - 1) << "So CCCD"
            << "│ " << std::setw(wSoGhe - 1) << "So ghe"
            << "│ " << std::setw(wMaCB - 1) << "Ma chuyen bay"
            << "│\n";
    
    std::cout << "├" << std::string(wStt, '-') << "┼" 
            << std::string(wName, '-') << "┼" 
            << std::string(wCMND, '-') << "┼" 
            << std::string(wSoGhe, '-') << "┼"
            << std::string(wMaCB, '-') <<"┤\n";
    

    for (int i = 0; i<sizeDSVe_; i++) {

        setColor(11); std::cout << "│ ";
        setColor(7); std::cout << std::left << std::setw(wStt - 1) << i + 1;
        
        setColor(11); std::cout << "│ ";
        setColor(7); std::cout << std::setw(wName - 1) << dsVe_[i].getKhachHang().getName();
        
        setColor(11); std::cout << "│ ";
        setColor(7); std::cout << std::setw(wCMND - 1) << dsVe_[i].getKhachHang().getCmnd();

        setColor(11); std::cout << "│ ";
        setColor(7); std::cout << std::setw(wSoGhe - 1) << dsVe_[i].getSoGhe() + 1;
        
        setColor(11); std::cout << "│ ";
        setColor(7); std::cout << std::setw(wMaCB - 1) << dsVe_[i].getMaCB();
        setColor(11); std::cout << "|";

        std::cout<<"\n";
    }

    setColor(11);
    std::cout << "└" << std::string(wStt, '-') << "┴" 
            << std::string(wName, '-') << "┴" 
            << std::string(wCMND, '-') << "┴" 
            << std::string(wSoGhe, '-') << "┴" 
            << std::string(wMaCB, '-') << "┘\n";
}

void UI_Menu::printDSGheTrong_(int totalSeats, const std::vector<int>& seatStatus) {
    int rows = (totalSeats + 5) / 6; // Dãy 6 ghế (A B C - D E F)
    int curRow = 0, curCol = 0;
    
    const int VISIBLE_ROWS = 10; 
    int startRow = 0;

    hideCursor();

    while (true) {
        clearScreen();
        
        if (curRow < startRow) {
            startRow = curRow;
        } else if (curRow >= startRow + VISIBLE_ROWS) {
            startRow = curRow - VISIBLE_ROWS + 1;
        }


        printTitle("GHE CON TRONG CUA CHUYEN BAY ");

        std::cout << "     A     B     C         D     E     F\n";
        std::cout << "   ┌─────┬─────┬─────┐   ┌─────┬─────┬─────┐\n";

        for (int r = startRow; r < startRow + VISIBLE_ROWS && r < rows; ++r) {
            std::cout << std::setw(3) << (r + 1) << "│";
            for (int c = 0; c < 6; ++c) {
                int seatIndex = r * 6 + c;

                if (seatIndex >= totalSeats) {
                    std::cout << "     "; 
                } else {
                    int isOccupied = seatStatus[seatIndex];
                    bool isSelected = (r == curRow && c == curCol);

                    if (isSelected) {
                        setColor(240); // Đang chọn
                        std::cout << (isOccupied ? "[ X ]" : "[ O ]");
                        setColor(7);
                    } else if (isOccupied) {
                        setColor(12);  // Đỏ: Đã đặt
                        std::cout << "  X  ";
                        setColor(7);
                    } else {
                        setColor(10);  // Xanh lá: Trống
                        std::cout << "  O  ";
                        setColor(7);
                    }
                }

                if (c == 2) std::cout << "│   │";
                else if (c < 5) std::cout << "│";
            }
            std::cout << "│\n";
        }
        std::cout << "   └─────┴─────┴─────┘   └─────┴─────┴─────┘\n";


        setColor(14);
        std::cout << "   ▲▼ [ Trang " << (startRow / VISIBLE_ROWS) + 1 << "/" << (rows + VISIBLE_ROWS - 1) / VISIBLE_ROWS 
                << " (Hang " << startRow + 1 << " -> " << std::min(startRow + VISIBLE_ROWS, rows) << " / " << rows << ") ]\n";
        setColor(7);

        std::cout << "\nGhi chu: ";
        setColor(10); std::cout << "O: Trong  ";
        setColor(12); std::cout << "X: Het cho ";
        setColor(240); std::cout << "[ ]: Dang chon";
        setColor(7); 
        std::cout << "\nDieu huong: [Phim mui ten 4 huong] | Thoat: [ESC]\n";

        int key = _getch();
        if (key == 224) {
            key = _getch();
            if (key == KEY_UP && curRow > 0) {
                curRow--;
            } else if (key == KEY_DOWN && curRow < rows - 1) {
                curRow++;
            } else if (key == KEY_LEFT && curCol > 0) {
                curCol--;
            } else if (key == KEY_RIGHT && curCol < 5) {
                curCol++;
            }

            if (curRow * 6 + curCol >= totalSeats) {
                curCol = (totalSeats - 1) % 6;
            }
        } else if (key == KEY_ESC) {
            showCursor();
            return;
        }
    }
}

void UI_Menu::printTableDSMB(MayBay* dsMayBay_, int sizeDSMayBay_) {
    int wStt = 5, wSoHieu = 9;
    setColor(11);
    std::cout << "┌" << std::string(wStt, '-') << "┬" 
            << std::string(wSoHieu, '-') <<"┐\n";
    
    std::cout << "│ " << std::left << std::setw(wStt - 1) << "STT"
            << "│ " << std::setw(wSoHieu - 1) << "So hieu"
            << "│\n";
    
    std::cout << "├" << std::string(wStt, '-') << "┼" 
            << std::string(wSoHieu, '-') <<"┤\n";
    

    for (int i = 0; i<sizeDSMayBay_; i++) {

        setColor(11); std::cout << "│ ";
        setColor(7); std::cout << std::left << std::setw(wStt - 1) << i + 1;
        
        setColor(11); std::cout << "│ ";
        setColor(7); std::cout << std::setw(wSoHieu - 1) << dsMayBay_[i].getSoHieu();
        
        setColor(11); std::cout << "|";

        std::cout<<"\n";
    }

    setColor(11);
    std::cout << "└" << std::string(wStt, '-') << "┴" 
            << std::string(wSoHieu, '-') << "┘\n";
}