#ifndef UI_MENU_H
#define UI_MENU_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <windows.h>
#include <conio.h>

#include "Validation.h"
#include "ChuyenBay.h"
#include "BST.h"
#include "MayBay.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_ESC 27

class UI_Menu {
    public: 
        enum PopupType {
            POPUP_SUCCESS,
            POPUP_FAILURE,
            POPUP_WARNING
        };

        UI_Menu() = delete; 
        UI_Menu(const UI_Menu&) = delete; 
        UI_Menu& operator=(const UI_Menu&) = delete;  

        static void setColor(int colorCode);
        static void hideCursor();
        static void clearScreen();
        static void showCursor();

        static void inLine(std::string kiTu, int size_, std::string backGround, std::string text, std::string align = "center", int valueColor = 7);
        static void printHeader();
        static void printTitle(std::string title);
        static void printTitle_Menu(std::string title);
        static void printOption(std::string title, std::vector<std::string>& option);
        static std::string repeatStr(const std::string& str, int count);
        static void printInput(const std::string& text, std::string& data_) {
            setColor(12);
            std::cout << "| ";
            setColor(14);
            std::cout << text <<":"<<"\n";
            setColor(12); 
            std::cout<<"| -> ";
            setColor(7);
            std::getline(std::cin, data_);
            setColor(7);
        }
    
        static bool inputPrint_(const std::string& text, std::string& value, bool hideInput = false) {
            value.clear();
            setColor(12);
            std::cout << "| ";
            setColor(14);
            std::cout << text <<":"<<"\n";
            setColor(12); 
            std::cout<<"| -> ";
            setColor(7);
            while (true) {
                int key = _getch();

                if (key == KEY_ESC) {
                    std::cout << '\n';
                    return false; 
                }

                if (key == 0 || key == 224) {
                    _getch(); 
                    continue;
                }

                if (key == KEY_ENTER) {
                    std::cout << '\n';
                    return true;
                }

                if (key == 8) { 
                    if (!value.empty()) {
                        value.pop_back();
                        std::cout << "\b \b";
                    }
                    continue;
                }

                if (key >= 32 && key <= 126) {
                    value.push_back(static_cast<char>(key));
                    std::cout << (hideInput ? '*' : static_cast<char>(key));
                }
            }
        }  
        static void printTableDSCB(Tree<ChuyenBay>& dsChuyenBay);
        static void printTableDSKH(const std::vector<Ve>& dsVe_); 
        static void printTable(const std::vector<ChuyenBay*>& danhSach);
        static void printTableVe(const std::vector<Ve>& dsVe); 
        static void printDSGheTrong_(int totalSeats, const std::vector<int>& seatStatus, const std::string& maCB = "");
        static void printTableDSMB(MayBay* dsMayBay_, int sizeDSMayBay_, std::vector<ChuyenBay*>& dsCB_);
        static int selectSeatInteractive(int totalSeats, const std::vector<int>& seatStatus, const std::string& maCB);
        static void textInput(std::string text);
        static void showPopup(const std::string& message, bool isSuccess = true);
        static void showPopup(const std::string& message, PopupType type);


};

#endif