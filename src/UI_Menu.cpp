#include "UI_Menu.h"

#include <algorithm>

const INT SIZE_KHUNG = 150; 
const std::string MENU_COLOR = "\033[38;5;154m";
const std::string MAU_RESET = "\033[38;5;231m";
namespace {
std::size_t displayWidth(const std::string& text) {
    std::size_t width = 0;
    for (unsigned char ch : text) {
        if ((ch & 0xC0) != 0x80) {
            ++width;
        }
    }
    return width;
}

size_t utf8Length(const std::string& str) {
    size_t len = 0;
    for (unsigned char c : str) {
        if ((c & 0xC0) != 0x80) { 
            len++;
        }
    }
    return len;
}

std::string padRightUTF8(const std::string& str, size_t width) {
    size_t realLen = utf8Length(str);
    if (realLen >= width) return str;
    return str + std::string(width - realLen, ' ');
}

std::string centeredPadding(const std::string& text, int width) {
    const int padding = (width - static_cast<int>(displayWidth(text))) / 2;
    return std::string(padding > 0 ? padding : 0, ' ');
}

std::vector<std::string> wrapText(const std::string& text, int width) {
    std::vector<std::string> lines;
    std::string line;
    std::string word;

    auto flushWord = [&]() {
        if (word.empty()) return;
        int lineWidth = static_cast<int>(displayWidth(line));
        int wordWidth = static_cast<int>(displayWidth(word));
        if (!line.empty() && lineWidth + 1 + wordWidth <= width) {
            line += " " + word;
        } else if (line.empty() && wordWidth <= width) {
            line = word;
        } else {
            if (!line.empty()) {
                lines.push_back(line);
                line.clear();
            }
            if (wordWidth <= width) {
                line = word;
            } else {
                std::string part;
                for (std::size_t i = 0; i < word.size();) {
                    unsigned char ch = static_cast<unsigned char>(word[i]);
                    std::size_t charSize = 1;
                    if ((ch & 0xF8) == 0xF0) charSize = 4;
                    else if ((ch & 0xF0) == 0xE0) charSize = 3;
                    else if ((ch & 0xE0) == 0xC0) charSize = 2;
                    std::string nextChar = word.substr(i, charSize);
                    if (!part.empty() && static_cast<int>(displayWidth(part + nextChar)) > width) {
                        lines.push_back(part);
                        part.clear();
                    }
                    part += nextChar;
                    i += charSize;
                }
                if (!part.empty()) line = part;
            }
        }
        word.clear();
    };

    for (std::size_t i = 0; i < text.size();) {
        unsigned char ch = static_cast<unsigned char>(text[i]);
        std::size_t charSize = 1;
        if ((ch & 0xF8) == 0xF0) charSize = 4;
        else if ((ch & 0xF0) == 0xE0) charSize = 3;
        else if ((ch & 0xE0) == 0xC0) charSize = 2;
        std::string nextChar = text.substr(i, charSize);
        i += charSize;

        if (nextChar == " ") {
            flushWord();
        } else {
            word += nextChar;
        }
    }
    flushWord();
    if (!line.empty()) lines.push_back(line);
    if (lines.empty()) lines.push_back("");
    return lines;
}
}

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
    const int textWidth = static_cast<int>(displayWidth(text));
    if(align == "left"){
        // setColor(valueColor); 
        for(int i = 0; i<5; i++) std::cout<<kiTu; 
        std::cout<<text; 
        for(int i = 0; i<size_ - textWidth - 5; i++) std::cout<<kiTu;
        std::cout << "\033[0m";
        return; 
    }
    int left = (size_ - textWidth) / 2;
    if (left < 0) left = 0;
    for(int i = 0; i<left; i++) 
        std::cout<<kiTu; 
    // setColor(valueColor);
    std::cout<<backGround; 
    std::cout<<text;
    std::cout<<backGround; 
    // setColor()
    // std::cout<<MAU_RESET; 
    
    for(int i = left + textWidth; i<size_; i++)
        std::cout<<kiTu; 
    std::cout << "\033[0m";
    
}

void UI_Menu::printHeader() {
    // inLine("═", SIZE_KHUNG, "\033[1;33m","FITP_DSA 2611COMP101602","center", 14); std::cout<<std::endl; 
    inLine(" ",SIZE_KHUNG,"\033[1;36m","▄▄ ▄▄  ▄▄▄▄      ▄▄▄▄▄ ▄▄ ▄▄  ▄▄▄  ▄▄  ▄▄  ▄▄▄▄       ▄▄▄  ▄▄ ▄▄  ▄▄▄  ▄▄  ▄▄      ▄▄  ▄▄ ▄▄     ","center", 11); std::cout<<std::endl;
    inLine(" ",SIZE_KHUNG,"\033[1;36m","██▄▄█ ▄█▀▀▀      ▀██▀▀ ██▄▄█ ▄█▀██ ███▄██ ▄█▀▀▀      ▄█▀██ ██ ██ ▄█▀█▄ ███▄██      ██  ▀█▄██     ","center", 11); std::cout<<std::endl;
    inLine(" ",SIZE_KHUNG,"\033[1;36m","█▀▀██ ▓▓▀▀        ▒▒   █▀▀██ ▓▓ ▓▓ ▓▓ ▀▓▓ ▓▓ ▀▒      ▓▓▐▓▄ ▓▓ █▀ ▓▓▀▒▒ ▓▓ ▀▓▓      █▄▄  ▄▄▓      ","center", 11); std::cout<<std::endl;
    inLine(" ",SIZE_KHUNG,"\033[1;36m","▀▀ ▀▀ ▀▀▀▀▀       ▀▀   ▀▀ ▀▀  ▀▀▀  ▀▀  ▀▀ ▀▀▀▀▀       ▀▀ ▀ ▀▀▀▀  ▀▀ ▀▀ ▀▀  ▀▀      ▀▀▀  ▀▀▀      ","center", 11); std::cout<<std::endl;
    inLine(" ",SIZE_KHUNG,"\033[1;36m"," ▄▄▄▄ ▄▄ ▄▄ ▄▄ ▄▄ ▄▄ ▄▄  ▄▄▄▄ ▄▄  ▄▄      ▄▄▄▄   ▄▄▄  ▄▄ ▄▄      ▄▄  ▄▄  ▄▄▄  ▄▄      ▄▄▄▄  ▄▄  ▄▄▄ ","center", 11); std::cout<<std::endl;
    inLine(" ",SIZE_KHUNG,"\033[1;36m","██▀██ ██▄▄█ ██ ██ ▀█▄██ ▄█▀▀▀ ███▄██      ██▄█▀ ▄█▀█▄ ▀█▄██      ███▄██ ▄█▀██ ▄▄      ██▀██ ▄▄ ▄█▀█▄","center", 11); std::cout<<std::endl;
    inLine(" ",SIZE_KHUNG,"\033[1;36m","██ ▀▀ █▀▀██ ▓▓ █▀  ▄▄▓  ▓▓▀▀  ▓▓ ▀▓▓      ▒▒ ▒▒ ▓▓▀▒▒  ▄▄▓       ▓▓ ▀▓▓ ▓▓ ▓▓ ▓▓      ▓▓ ▓▓ ▓▓ ▓▓▀▒▒","center", 11); std::cout<<std::endl;
    inLine(" ",SIZE_KHUNG,"\033[1;36m","▀▀▀▀▀ ▀▀ ▀▀ ▀▀▀▀   ▀▀▀  ▀▀▀▀▀ ▀▀  ▀▀      ▀▀▀▀▀ ▀▀ ▀▀  ▀▀▀       ▀▀  ▀▀  ▀▀▀  ▀▀      ▀▀▀▀  ▀▀ ▀▀ ▀▀","center", 11); std::cout<<std::endl;
    std::cout << "\033[0m";
}
// Hàm lặp chuỗi UTF-8 n lần
std::string UI_Menu::repeatStr(const std::string& str, int count) {
    std::string result;
    result.reserve(str.size() * count);
    for (int i = 0; i < count; ++i) {
        result += str;
    }
    return result;
}
void UI_Menu::printTitle(std::string title){
    title = Validation::toUpperCase(title);
    std::cout<<"\033[1;33m";
    std::cout<<"╔";
    inLine("═", SIZE_KHUNG - 2, "\033[1;33m", "FITP_DSA 2611COMP101602", "center", 14); 
        std::cout<<"\033[1;33m";

    std::cout<<"╗";
    std::cout<<std::endl;

    std::cout<<"\033[1;33m";

    std::cout<<"║";
    inLine(" ", SIZE_KHUNG - 2, "\033[38;2;251;191;36m", title,"center", 14); 
    std::cout<<"\033[1;33m";

    std::cout<<"║";std::cout<<std::endl;

    std::cout<<"\033[1;33m";

    std::cout<<"╚";
    inLine("═", SIZE_KHUNG - 2, "\033[1;33m", ""); 
    std::cout<<"\033[1;33m";

    std::cout<<"╝";
    std::cout<<std::endl;
    std::cout << "\033[0m";
    setColor(7); 
} 
void UI_Menu::printTitle_Menu(std::string title){
    title = Validation::toUpperCase(title);
    std::cout<<"\033[1;33m";
    std::cout<<"╔";
    inLine("═", SIZE_KHUNG - 2, "\033[1;33m", "FITP_DSA 2611COMP101602", "center", 14); 
        std::cout<<"\033[1;33m";

    std::cout<<"╗";
    std::cout<<std::endl;

    std::cout<<"\033[1;33m";
    std::cout<<"║";
    inLine(" ", SIZE_KHUNG - 2, "\033[38;2;251;191;36m", title,"center", 14); 
    std::cout<<"\033[1;33m";

    std::cout<<"║";std::cout<<std::endl;

    std::cout<<"\033[1;33m";

    std::cout<<"║";
    inLine("═", SIZE_KHUNG - 2, "\033[1;33m", ""); 
    std::cout<<"\033[1;33m";

    std::cout<<"║";
    std::cout<<std::endl;
    std::cout << "\033[0m";
    setColor(7); 
} 

void UI_Menu::printOption(std::string title, std::vector<std::string>& option){
    printTitle_Menu(title);
    for(int i = 0; i<option.size(); i++){
        std::cout<<"\033[1;33m";
        setColor(14); 
        std::cout<<"║";
        inLine(" ", SIZE_KHUNG - 2, MENU_COLOR, std::to_string(i+1) + ". " + option[i], "left", 177); 
        setColor(14); 
        std::cout<<"║"<<"\n";
    } 
    std::cout<<"\033[1;33m";
    std::cout<<"╚";
    inLine("═", SIZE_KHUNG - 2, "\033[1;33m", "");
    std::cout<<"\033[1;33m";
    std::cout<<"╝";
    std::cout << "\033[0m";
    setColor(7); 
    std::cout<<"\n";
}

void UI_Menu::printTableDSCB(Tree<ChuyenBay>& dsChuyenBay){
    SetConsoleOutputCP(65001); 
    const INT pad = 3;
    int wStt = 6, wMa = 16, wNgay = 22, wSanBay = 15, wTrangThai = 15, wDSVe = 63;

    setColor(11);
    std::cout << std::string(pad, ' ')
              << "┌" << repeatStr("─", wStt) << "┬"
              << repeatStr("─", wMa) << "┬"
              << repeatStr("─", wNgay) << "┬"
              << repeatStr("─", wSanBay) << "┬"
              << repeatStr("─", wTrangThai) << "┬"
              << repeatStr("─", wDSVe) << "┐\n";

    std::cout << std::string(pad, ' ')
              << "│ " << std::left << std::setw(wStt - 1) << "STT"
              << "│ " << std::setw(wMa + 2) << "Mã chuyến bay"
              << "│ " << std::setw(wNgay + 3) << "Ngày khởi hành"
              << "│ " << std::setw(wSanBay + 3) << "Sân bay đến"
              << "│ " << std::setw(wTrangThai + 2) << "Trạng thái"
              << "│ " << std::setw(wDSVe + 1) << "Danh sách vé"
              << "│\n";
              

    setColor(11);
    std::cout << std::string(pad, ' ')
              << "├" << repeatStr("─", wStt) << "┼"
              << repeatStr("─", wMa) << "┼"
              << repeatStr("─", wNgay) << "┼"
              << repeatStr("─", wSanBay) << "┼"
              << repeatStr("─", wTrangThai) << "┼"
              << repeatStr("─", wDSVe) << "┤\n";

    std::vector<ChuyenBay*> danhSach;
    dsChuyenBay.getList(danhSach);
    int stt = 1;
    for (const auto& cb : danhSach) {
        int colorStatus = 15; 
        std::cout<<std::string(pad, ' ');
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
        setColor(15); std::cout << std::left << std::setw(wStt - 1) << stt++;

        setColor(11); std::cout << "│ ";
        setColor(colorStatus); 
        // std::cout << std::left << std::setw(wMa - 1) << cb->getMaCB();
        inLine(" ", wMa - 1, "", cb->getMaCB());
        
        setColor(11); std::cout << "│ ";
        setColor(15); 
        // std::cout << std::setw(wNgay - 1) << cb->getNgayKH();
        inLine(" ", wNgay - 1, "", cb->getNgayKH());

        
        setColor(11); std::cout << "│ ";
        setColor(15); 
        // std::cout << std::setw(wSanBay - 1) << cb->getSanBD();
        inLine(" ", wSanBay - 1, "", cb->getSanBD());

        setColor(11); std::cout << "│";

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
        std::cout << colorCode << std::setw(wTrangThai) << textStatus_;

        const std::vector<Ve> dsVe = cb->getDSVe();
        std::string dsVe_Str = "";
        if (dsVe.empty()) dsVe_Str = "Không có thông tin";
        else {
            for(int i = 0; i<dsVe.size() - 1; i++) {
                if (i == 6) break;
                dsVe_Str = dsVe_Str + dsVe[i].getMaVe() + ", ";
            }
            if (dsVe.size()>=7) 
                dsVe_Str += dsVe[6].getMaVe(); 
            else 
                dsVe_Str += dsVe[dsVe.size() - 1].getMaVe(); 
        }


        setColor(11); std::cout << "│ ";
        setColor(15); std::cout << padRightUTF8(dsVe_Str, wDSVe - 1);
        
        setColor(11); std::cout << "│\n";
    }

    setColor(11);
    std::cout<<std::string(pad, ' '); 
    std::cout << "└" << repeatStr("─", wStt) << "┴"
            << repeatStr("─", wMa) << "┴" 
            << repeatStr( "─", wNgay) << "┴" 
            << repeatStr("─", wSanBay) << "┴" 
            << repeatStr("─", wTrangThai) << "┴"
            << repeatStr("─", wDSVe) << "┘\n";
            
    setColor(7); 
}

void UI_Menu::printTable(const std::vector<ChuyenBay*>& danhSach) {
    const INT pad = 37; 
    int wStt = 6, wMa = 16, wNgay = 22, wSanBay = 15, wTrangThai = 15;
    setColor(11);
    std::cout << std::string(pad, ' ')
              << "┌" << repeatStr("─", wStt) << "┬"
              << repeatStr("─", wMa) << "┬"
              << repeatStr("─", wNgay) << "┬"
              << repeatStr("─", wSanBay) << "┬"
              << repeatStr("─", wTrangThai) << "┐\n";

    std::cout << std::string(pad, ' ')
              << "│ " << std::left << std::setw(wStt - 1) << "STT"
              << "│ " << std::setw(wMa + 2) << "Mã chuyến bay"
              << "│ " << std::setw(wNgay + 3) << "Ngày khởi hành"
              << "│ " << std::setw(wSanBay + 3) << "Sân bay đến"
              << "│ " << std::setw(wTrangThai + 2) << "Trạng thái"
              << "│\n";

    setColor(11);
    std::cout << std::string(pad, ' ')
              << "├" << repeatStr("─", wStt) << "┼"
              << repeatStr("─", wMa) << "┼"
              << repeatStr("─", wNgay) << "┼"
              << repeatStr("─", wSanBay) << "┼"
              << repeatStr("─", wTrangThai) << "┤\n";

    int stt = 1;
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
        std::cout<<std::string(pad, ' '); 
        setColor(11); std::cout << "│ ";
        setColor(15); std::cout << std::left << std::setw(wStt - 1) << stt++;

        setColor(11); std::cout << "│ ";
        setColor(colorStatus); 
        // std::cout << std::left << std::setw(wMa - 1) << cb->getMaCB();
        inLine(" ", wMa - 1, "", cb->getMaCB());

        setColor(11); std::cout << "│ ";
        setColor(15); std::cout << std::setw(wNgay - 1) << cb->getNgayKH();
        
        setColor(11); std::cout << "│ ";
        setColor(15);
        // std::cout << std::setw(wSanBay - 1) << cb->getSanBD();
        inLine(" ", wSanBay - 1, "", cb->getSanBD());
        setColor(11); std::cout << "│";

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
        std::cout << colorCode << std::setw(wTrangThai) << textStatus_;
        setColor(11); std::cout << "│\n";
    }
    std::cout<<std::string(pad, ' '); 

    setColor(11);
    std::cout << "└" << repeatStr("─", wStt) << "┴"
            << repeatStr("─", wMa) << "┴" 
            << repeatStr( "─", wNgay) << "┴" 
            << repeatStr("─", wSanBay) << "┴" 
            << repeatStr("─", wTrangThai) << "┘\n";
            
    setColor(7); 
}

int UI_Menu::selectSeatInteractive(int totalSeats, const std::vector<int>& seatStatus, const std::string& maCB) {
    int rows = (totalSeats + 5) / 6; // Dãy 6 ghế (A B C - D E F)
    int curRow = 0, curCol = 0;
    
    const int VISIBLE_ROWS = 10; 
    const int SEAT_MAP_WIDTH = 44;
    const std::string seatMapIndent((SIZE_KHUNG - SEAT_MAP_WIDTH) / 2, ' ');
    int startRow = 0;

    hideCursor();

    while (true) {
        clearScreen();
        
        if (curRow < startRow) {
            startRow = curRow;
        } else if (curRow >= startRow + VISIBLE_ROWS) {
            startRow = curRow - VISIBLE_ROWS + 1;
        }


        printTitle("SƠ ĐỒ CHỌN GHẾ MÁY BAY " + maCB);

        std::cout << seatMapIndent << "      A     B     C         D     E     F \n";
        std::cout << seatMapIndent << "   ┌─────┬─────┬─────┐   ┌─────┬─────┬─────┐\n";

        for (int r = startRow; r < startRow + VISIBLE_ROWS && r < rows; ++r) {
            std::cout << seatMapIndent << std::setw(3) << (r + 1) << "│";
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
        std::cout << seatMapIndent << "   └─────┴─────┴─────┘   └─────┴─────┴─────┘\n";


        setColor(14);
        const std::string pageInfo = "▲▼ [ Trang " + std::to_string((startRow / VISIBLE_ROWS) + 1) + "/" +
                std::to_string((rows + VISIBLE_ROWS - 1) / VISIBLE_ROWS) + " (Hàng " +
                std::to_string(startRow + 1) + " -> " +
                std::to_string(std::min(startRow + VISIBLE_ROWS, rows)) + " / " +
                std::to_string(rows) + ") ]";
        std::cout << centeredPadding(pageInfo, SIZE_KHUNG) << pageInfo << "\n";
        setColor(7);

        const std::string legend = "Ghi chú: O: Trong  X: Hết chỗ [ ]: Đang chọn";
        std::cout << "\n" << centeredPadding(legend, SIZE_KHUNG) << "Ghi chú: ";
        setColor(10); std::cout << "O: Trống  ";
        setColor(12); std::cout << "X: Hết chỗ ";
        setColor(240); std::cout << "[ ]: Đang chọn";
        setColor(7); 
        const std::string navigation = "Điều hướng: [Phím mũi tên 4 hướng] | Chọn: [ENTER] | Thoát: [ESC]";
        std::cout << "\n" << centeredPadding(navigation, SIZE_KHUNG) << navigation << "\n";

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
                showPopup("Ghế này đã có người đặt. Vui lòng chọn ghế khác.", POPUP_WARNING);
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

void UI_Menu::showPopup(const std::string& message, bool isSuccess) {
    showPopup(message, isSuccess ? POPUP_SUCCESS : POPUP_FAILURE);
}

void UI_Menu::showPopup(const std::string& message, PopupType type) {
    std::cout.flush();
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screenInfo;
    if (!GetConsoleScreenBufferInfo(hConsole, &screenInfo)) {
        std::cerr << "Lỗi popup: không thể đọc thông tin màn hình console.\n";
        return;
    }

    CONSOLE_CURSOR_INFO originalCursorInfo;
    if (!GetConsoleCursorInfo(hConsole, &originalCursorInfo)) {
        std::cerr << "Lỗi popup: không thể đọc trạng thái con trỏ console.\n";
        return;
    }

    SMALL_RECT windowRegion = screenInfo.srWindow;
    const int viewportWidth = windowRegion.Right - windowRegion.Left + 1;
    const int viewportHeight = windowRegion.Bottom - windowRegion.Top + 1;
    if (viewportWidth < 12 || viewportHeight < 7) {
        std::cerr << "Lỗi popup: cửa sổ console quá nhỏ để hiển thị popup.\n";
        return;
    }

    const SHORT popupWidth = static_cast<SHORT>(std::min(54, viewportWidth));
    const int popupInnerWidth = popupWidth - 2;
    const int messageWidth = popupInnerWidth - 4;
    std::vector<std::string> messageLines = wrapText(message, messageWidth);
    const int maxMessageLines = viewportHeight - 6;
    if (static_cast<int>(messageLines.size()) > maxMessageLines) {
        messageLines.resize(maxMessageLines);
        std::string& lastLine = messageLines.back();
        auto removeLastCodePoint = [](std::string& line) {
            if (line.empty()) return;
            std::size_t start = line.size() - 1;
            while (start > 0 &&
                   (static_cast<unsigned char>(line[start]) & 0xC0) == 0x80) {
                --start;
            }
            line.erase(start);
        };
        while (!lastLine.empty() &&
               static_cast<int>(displayWidth(lastLine)) + 3 > messageWidth) {
            removeLastCodePoint(lastLine);
        }
        lastLine += "...";
    }

    const SHORT popupHeight = static_cast<SHORT>(messageLines.size() + 6);
    const SHORT startX = static_cast<SHORT>(
        windowRegion.Left + (viewportWidth - popupWidth) / 2);
    const SHORT startY = static_cast<SHORT>(
        windowRegion.Top + (viewportHeight - popupHeight) / 2);
    SMALL_RECT popupRegion = {
        startX,
        startY,
        static_cast<SHORT>(startX + popupWidth - 1),
        static_cast<SHORT>(startY + popupHeight - 1)
    };

    COORD snapshotSize = {popupWidth, popupHeight};
    COORD snapshotOrigin = {0, 0};
    std::vector<CHAR_INFO> screenSnapshot(
        static_cast<std::size_t>(popupWidth) * popupHeight);
    if (!ReadConsoleOutputW(hConsole, screenSnapshot.data(), snapshotSize,
                            snapshotOrigin, &popupRegion)) {
        std::cerr << "Lỗi popup: không thể lưu vùng màn hình phía sau popup.\n";
        return;
    }

    const std::string title = type == POPUP_SUCCESS
        ? "THÀNH CÔNG"
        : (type == POPUP_WARNING ? "CẢNH BÁO" : "THẤT BẠI");
    const WORD borderColor = static_cast<WORD>(
        type == POPUP_SUCCESS ? 10 : (type == POPUP_WARNING ? 14 : 12));
    const WORD buttonColor = static_cast<WORD>(
        (type == POPUP_SUCCESS ? 2 : (type == POPUP_WARNING ? 6 : 4)) << 4);
    const WORD textColor = 7;

    auto moveToPopupRow = [&](SHORT rowOffset) {
        std::cout.flush();
        COORD position = {startX, static_cast<SHORT>(startY + rowOffset)};
        SetConsoleCursorPosition(hConsole, position);
    };
    auto applyColor = [&](WORD color) {
        std::cout.flush();
        SetConsoleTextAttribute(hConsole, color);
    };
    auto centeredLine = [](const std::string& text, int width) {
        const std::string left = centeredPadding(text, width);
        const int rightLength =
            width - static_cast<int>(displayWidth(text)) - static_cast<int>(left.size());
        return left + text + std::string(std::max(0, rightLength), ' ');
    };

    CONSOLE_CURSOR_INFO hiddenCursorInfo = originalCursorInfo;
    hiddenCursorInfo.bVisible = FALSE;
    if (!SetConsoleCursorInfo(hConsole, &hiddenCursorInfo)) {
        std::cerr << "Lỗi popup: không thể ẩn con trỏ console.\n";
        return;
    }

    SHORT currentRow = 0;
    std::cout.flush();
    applyColor(borderColor);
    moveToPopupRow(currentRow++);
    std::cout << "╔" << repeatStr("═", popupInnerWidth) << "╗";

    moveToPopupRow(currentRow++);
    std::cout << "║" << centeredLine(title, popupInnerWidth) << "║";

    moveToPopupRow(currentRow++);
    std::cout << "╠" << repeatStr("═", popupInnerWidth) << "╣";

    for (const std::string& messageLine : messageLines) {
        moveToPopupRow(currentRow++);
        applyColor(borderColor);
        std::cout << "║";
        applyColor(textColor);
        std::cout << " " << centeredLine(messageLine, popupInnerWidth - 2) << " ";
        applyColor(borderColor);
        std::cout << "║";
    }

    moveToPopupRow(currentRow++);
    applyColor(borderColor);
    std::cout << "╠" << repeatStr("═", popupInnerWidth) << "╣";

    const std::string okText = "[ OK ]";
    const std::string okPadding = centeredPadding(okText, popupInnerWidth);
    const int okRightLength = popupInnerWidth -
        static_cast<int>(displayWidth(okText)) - static_cast<int>(okPadding.size());
    moveToPopupRow(currentRow++);
    applyColor(borderColor);
    std::cout << "║";
    applyColor(textColor);
    std::cout << okPadding;
    applyColor(buttonColor);
    std::cout << okText;
    applyColor(textColor);
    std::cout << std::string(std::max(0, okRightLength), ' ');
    applyColor(borderColor);
    std::cout << "║";

    moveToPopupRow(currentRow);
    std::cout << "╚" << repeatStr("═", popupInnerWidth) << "╝";
    std::cout.flush();

    while (true) {
        int key = _getch();
        if (key == KEY_ENTER || key == KEY_ESC) break;
        if (key == 0 || key == 224) _getch();
    }

    const BOOL screenRestored = WriteConsoleOutputW(
        hConsole, screenSnapshot.data(), snapshotSize, snapshotOrigin, &popupRegion);
    const BOOL attributesRestored =
        SetConsoleTextAttribute(hConsole, screenInfo.wAttributes);
    const BOOL cursorPositionRestored =
        SetConsoleCursorPosition(hConsole, screenInfo.dwCursorPosition);
    const BOOL cursorRestored = SetConsoleCursorInfo(hConsole, &originalCursorInfo);

    if (!screenRestored || !attributesRestored ||
        !cursorPositionRestored || !cursorRestored) {
        std::cerr << "Lỗi popup: không thể khôi phục đầy đủ trạng thái console.\n";
    }
}

void UI_Menu::printTableVe(const std::vector<Ve>& dsVe) {
    int wSTT = 5, wMa = 10, wMaCB = 16, wSoGhe = 8, wKH = 25, wCMND = 14;
    const INT pad = 35;
    setColor(11);
    std::cout << std::string(pad, ' ')
              << "┌" << repeatStr("─", wSTT) << "┬"
              << repeatStr("─", wMa) << "┬"
              << repeatStr("─", wMaCB) << "┬"
              << repeatStr("─", wSoGhe) << "┬"
              << repeatStr("─", wKH) << "┬"
              << repeatStr("─", wCMND) << "┐\n";
    
    std::cout << std::string(pad, ' ')
            << "│ " << std::left << std::setw(wSTT - 1) << "STT"
            << "│ " << std::left << std::setw(wMa + 1) << "Mã vé"
            << "│ " << std::setw(wMaCB + 2) << "Mã chuyến bay"
            << "│ " << std::setw(wSoGhe + 3) << "Số ghế"
            << "│ " << std::setw(wKH + 1) << "Khách hàng"
            << "│ " << std::setw(wCMND + 1) << "Số CCCD"
            << "│\n";

    setColor(11);
    std::cout << std::string(pad, ' ')
            << "├" << repeatStr("─", wSTT) << "┼" 
            << repeatStr( "─", wMa) << "┼" 
            << repeatStr( "─", wMaCB) << "┼" 
            << repeatStr("─", wSoGhe) << "┼" 
            << repeatStr("─", wKH) << "┼" 
            << repeatStr("─", wCMND) << "┤\n";
            
    int cnt = 0;
    for (const auto& Ve : dsVe) {
        // int colorStatus = 15; 
        std::cout<<std::string(pad, ' ');

        setColor(11); std::cout << "│ ";
        std::cout << MAU_RESET << std::left << std::setw(wSTT - 1) << cnt+1;
        
        setColor(11); std::cout << "│ ";
        std::cout << MAU_RESET<< std::setw(wMa - 1) << Ve.getMaVe();
        
        setColor(11); std::cout << "│ ";
        std::cout << MAU_RESET<< std::setw(wMaCB - 1) << Ve.getMaCB();

        setColor(11); std::cout << "│ ";
        std::string soGhe = std::to_string(Ve.getSoGhe() + 1);
        if (Ve.getSoGhe() < 10) soGhe = "0" + soGhe;
        std::cout << MAU_RESET<< std::setw(wSoGhe - 1) << soGhe;

        setColor(11); std::cout << "│ ";
        std::cout << MAU_RESET<< std::setw(wKH - 1) << Ve.getKhachHang().getName();

        setColor(11); std::cout << "│ ";
        std::cout << MAU_RESET<< std::setw(wCMND - 1) << Ve.getKhachHang().getCmnd();

        setColor(11); std::cout << "│\n";
        ++cnt;
    }

    setColor(11);
    std::cout << std::string(pad, ' ')
            << "└" << repeatStr("─", wSTT) << "┴" 
            << repeatStr( "─", wMa) << "┴" 
            << repeatStr( "─", wMaCB) << "┴" 
            << repeatStr("─", wSoGhe) << "┴" 
            << repeatStr("─", wKH) << "┴" 
            << repeatStr("─", wCMND) << "┘\n";
            
    setColor(7); 
}

void UI_Menu::printTableDSKH(const std::vector<Ve>& dsVe_) { 
    int sizeDSVe_ = dsVe_.size(); 
    const INT pad = 35; 
    int wStt = 5, wName = 25, wCMND = 14, wSoGhe = 8, wMaCB = 16; 

    
    setColor(11);
    std::cout << std::string(pad, ' ')
              << "┌" << repeatStr("─", wStt) << "┬"
              << repeatStr("─", wName) << "┬"
              << repeatStr("─", wCMND) << "┬"
              << repeatStr("─", wSoGhe) << "┬"
              << repeatStr("─", wMaCB) << "┐\n";
    
    std::cout << std::string(pad, ' ')
            << "│ " << padRightUTF8("STT", wStt - 1)
            << "│ " << padRightUTF8("Họ và tên", wName - 1)
            << "│ " << padRightUTF8("Số CCCD", wCMND - 1)
            << "│ " << padRightUTF8("Số ghế", wSoGhe - 1)
            << "│ " << padRightUTF8("Mã chuyến bay", wMaCB - 1)
            << "│\n";

    setColor(11);
    std::cout << std::string(pad, ' ')
            << "├" << repeatStr("─", wStt) << "┼" 
            << repeatStr( "─", wName) << "┼" 
            << repeatStr( "─", wCMND) << "┼" 
            << repeatStr("─", wSoGhe) << "┼" 
            << repeatStr("─", wMaCB) << "┤\n";


    for (int i = 0; i<sizeDSVe_; i++) {
        std::cout << std::string(pad, ' ');

        setColor(11); std::cout << "│ ";
        setColor(7); 
        // std::cout << padRightUTF8(std::to_string(i+1), wStt - 1);
        inLine(" ", wStt - 1, "", std::to_string(i+1));
        
        setColor(11); std::cout << "│ ";
        setColor(7); std::cout << padRightUTF8(dsVe_[i].getKhachHang().getName(), wName - 1);
        
        setColor(11); std::cout << "│ ";
        setColor(7); std::cout << padRightUTF8(dsVe_[i].getKhachHang().getCmnd(), wCMND - 1);

        setColor(11); std::cout << "│ ";
        std::string soGhe = std::to_string(dsVe_[i].getSoGhe() + 1);
        if (dsVe_[i].getSoGhe() < 10) soGhe = "0" + soGhe;
        setColor(7); 
        inLine(" ", wSoGhe - 1, "", soGhe);
        // std::cout << padRightUTF8(soGhe, wSoGhe - 1);
        
        setColor(11); std::cout << "│ ";
        setColor(7); 
        inLine(" ", wMaCB - 1, "", dsVe_[i].getMaCB());
        // std::cout << padRightUTF8(dsVe_[i].getMaCB(), wMaCB - 1);
        setColor(11); std::cout << "│";

        std::cout<<"\n";
    }

    setColor(11);
    std::cout << std::string(pad, ' ');
    std::cout << "└" << repeatStr("─", wStt) << "┴" 
            << repeatStr( "─", wName) << "┴" 
            << repeatStr("─", wCMND) << "┴" 
            << repeatStr("─", wSoGhe) << "┴" 
            << repeatStr("─", wMaCB) << "┘\n";
            
}

void UI_Menu::printDSGheTrong_(int totalSeats, const std::vector<int>& seatStatus, const std::string& maCB) {
    int rows = (totalSeats + 5) / 6; // Dãy 6 ghế (A B C - D E F)
    int curRow = 0, curCol = 0;
    
    const int VISIBLE_ROWS = 10; 
    const int SEAT_MAP_WIDTH = 44;
    const std::string seatMapIndent((SIZE_KHUNG - SEAT_MAP_WIDTH) / 2, ' ');
    int startRow = 0;

    hideCursor();

    while (true) {
        clearScreen();
        
        if (curRow < startRow) {
            startRow = curRow;
        } else if (curRow >= startRow + VISIBLE_ROWS) {
            startRow = curRow - VISIBLE_ROWS + 1;
        }


        printTitle(maCB.empty()
            ? "GHẾ CÒN TRỐNG CỦA CHUYẾN BAY"
            : "GHẾ CÒN TRỐNG CỦA CHUYẾN BAY " + maCB);

        std::cout << seatMapIndent << "      A     B     C         D     E     F\n";
        std::cout << seatMapIndent << "   ┌─────┬─────┬─────┐   ┌─────┬─────┬─────┐\n";

        for (int r = startRow; r < startRow + VISIBLE_ROWS && r < rows; ++r) {
            std::cout << seatMapIndent << std::setw(3) << (r + 1) << "│";
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
        std::cout << seatMapIndent << "   └─────┴─────┴─────┘   └─────┴─────┴─────┘\n";


        setColor(14);
        const std::string pageInfo = "▲▼ [ Trang " + std::to_string((startRow / VISIBLE_ROWS) + 1) + "/" +
                std::to_string((rows + VISIBLE_ROWS - 1) / VISIBLE_ROWS) + " (Hàng " +
                std::to_string(startRow + 1) + " -> " +
                std::to_string(std::min(startRow + VISIBLE_ROWS, rows)) + " / " +
                std::to_string(rows) + ") ]";
        std::cout << centeredPadding(pageInfo, SIZE_KHUNG) << pageInfo << "\n";
        setColor(7);

        std::cout << "\n" << centeredPadding("Ghi chú: O: Trống  X: Hết chỗ [ ]: Đang chọn", SIZE_KHUNG) << "Ghi chú: ";
        setColor(10); std::cout << "O: Trống  ";
        setColor(12); std::cout << "X: Hết chỗ ";
        setColor(240); std::cout << "[ ]: Đang chọn";
        setColor(7); 
        const std::string navigation = "Điều hướng: [Phím mũi tên 4 hướng] | Thoát: [ESC]";
        std::cout << "\n" << centeredPadding(navigation, SIZE_KHUNG) << navigation << "\n";

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

void UI_Menu::printTableDSMB(MayBay* dsMayBay_, int sizeDSMayBay_, std::vector<ChuyenBay*>& dsCB_) {
    int wStt = 5, wSoHieu = 17, wSoLuot = 15;
    const INT pad = 55;
    
    setColor(11);
    std::cout << std::string(pad, ' ')
              << "┌" << repeatStr("─", wStt) << "┬"
              << repeatStr("─", wSoHieu) << "┬"
              << repeatStr("─", wSoLuot) << "┐\n";
    
    std::cout << std::string(pad, ' ')
            << "│ " << padRightUTF8("STT", wStt - 1)
            << "│ " << padRightUTF8("Số hiệu máy bay", wSoHieu - 1)
            << "│ " << padRightUTF8("Số chuyến bay", wSoLuot - 1)
            << "│\n";

    setColor(11);
    std::cout << std::string(pad, ' ')
            << "├" << repeatStr("─", wStt) << "┼" 
            << repeatStr( "─", wSoHieu) << "┼" 
            << repeatStr("─", wSoLuot) << "┤\n";


    for (int i = 0; i<sizeDSMayBay_; i++) {
        std::cout << std::string(pad, ' ');

        setColor(11); std::cout << "│ ";
        setColor(7); std::cout << std::left << std::setw(wStt - 1) << i + 1;
        
        setColor(11); std::cout << "│ ";
        inLine(" ", wSoHieu - 1, MAU_RESET, dsMayBay_[i].getSoHieu(), "center");

        int cnt = 0; 
        for(int j = 0; j<dsCB_.size(); j++) {
            if (dsMayBay_[i].getSoHieu() == dsCB_[j]->getSoHieuMB()) cnt++; 
        }
        setColor(11); std::cout << "│ ";
        inLine(" ", wSoLuot - 1, MAU_RESET, std::to_string(cnt), "center");
        setColor(11); std::cout << "│";

        std::cout<<"\n";
    }
        std::cout << std::string(pad, ' ');

    setColor(11);
    std::cout << "└" << repeatStr("─", wStt) <<  "┴" 
            << repeatStr("─", wSoHieu) <<"┴"<< repeatStr("─", wSoLuot) << "┘\n";
}