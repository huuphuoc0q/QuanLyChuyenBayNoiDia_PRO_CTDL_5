
#include<iostream> 
#include "../include/MayBay.h"
#include "../include/ChuyenBay.h"
#include "../include/Ve.h"
#include "../include/KhachHang.h"
#include "../include/ThongKe.h"
#include "../include/FileStore.h"
#include "../include/Validation.h"
#include "../include/LinkedList.h"
#include "../include/BST.h"
#include "../include/UI_Menu.h"

#include<vector> 
#include<fstream>
#include <cstdlib>
#include <windows.h>
#include <queue>
#include <ctime>
#include <iomanip>
#include <limits>


//Cau truc lua chon giao dien
std::vector<std::string> optMenuChinh_ = {
    "Hiển thị danh sách chuyến bay",
    "Đặt vé",
    "Quản lý"
};
std::vector<std::string> optQuanLy_ = {
    "Xử lý đặt vé", 
    "Xử lý trả vé", 
    "Thống kê"
};
std::vector<std::string> optThongKe_ = {
    "Hiển thị danh sách khách hàng của một chuyến bay",
    "Hiển thị số lượng ghế trống của một chuyến bay",
    "Thống kê số lượng chuyến bay của một báy bay"
};


void hienThiDSChuyenBay(Tree<ChuyenBay>& dsChuyenBay, int& sizeDSChuyenBay) {
    std::string q = "";
    std::system("cls"); 
    UI_Menu::printTitle("THÔNG TIN DANH SÁCH CHUYẾN BAY");
    UI_Menu::printTableDSCB(dsChuyenBay); 
    if (!UI_Menu::inputPrint_("Nhập kí tự bất kì/ ấn ESC để thoát", q, false)) return; 
}

void datVe(int& idx_, MayBay* dsMayBay,int& sizeDSMayBay, Tree<ChuyenBay>& dsChuyenBay, int& sizeDSChuyenBay, LinkedList<Ve>& tmpDSVe_) {
    std::vector<ChuyenBay*> dsCB_;
    dsChuyenBay.getList(dsCB_); 

    while (true) {
        std::system("cls");
        int tmpStatusCB = 0;
        int numCB = -1;
        std::string enter_maCB;

        UI_Menu::printTitle("ĐẶT VÉ CHUYẾN BAY NỘI ĐỊA");
        UI_Menu::printTable(dsCB_);

        //chon chuyen bay
        while(true) {
            if(!(UI_Menu::inputPrint_("Mã chuyến bay cần đặt (Nhập ESC để thoát)", enter_maCB))) return;
            if(enter_maCB == "0") return;
            for(int i = 0; i<sizeDSChuyenBay; i++){
                if(Validation::toUpperCase(enter_maCB) == dsCB_[i]->getMaCB()) {
                    numCB = i;
                    break;
                }
            }
            if (numCB == -1) {
                UI_Menu::showPopup("Không tồn tại chuyến bay. Vui lòng nhập lại.", UI_Menu::POPUP_WARNING);
                continue;
            }


            tmpStatusCB = dsCB_[numCB]->getStatus();
            if(tmpStatusCB == 1) break;
            switch(tmpStatusCB) {
                case 0: {
                    UI_Menu::showPopup("Chuyến bay đã bị huỷ. Vui lòng chọn chuyến bay khác.", UI_Menu::POPUP_WARNING);
                    break;
                }
                case 2: {
                    UI_Menu::showPopup("Chuyến bay đã hết vé. Vui lòng chọn chuyến bay khác.", UI_Menu::POPUP_WARNING);
                    break;
                }
                case 3: {
                    UI_Menu::showPopup("Chuyến bay đã hoàn tất. Vui lòng chọn chuyến bay khác.", UI_Menu::POPUP_WARNING);
                    break;
                }
                default:
                    break;
            }
        }
        ChuyenBay* cbUserChon_ = dsCB_[numCB];
        std::vector<int> dsGheTrong_ = dsCB_[numCB]->getDSGheTrong();

        //chon ghe
        int numGhe = UI_Menu::selectSeatInteractive(cbUserChon_->getMB()->getSoCho(), cbUserChon_->getDSGheTrong(), cbUserChon_->getMaCB());
        if (numGhe < 0) continue;

        //Kiem tra da het ghe hay chua
        if(cbUserChon_->getSoLuongGheTrong() == 0) cbUserChon_->setStatus(2);

        //Nhap thong tin khachhang - khoi tao ve:
        std::string nameKH_ = "";
        std::string cmndKH_ = "";

        while(Validation::empty(nameKH_)){
            if(!(UI_Menu::inputPrint_("Nhập họ và tên", nameKH_))) return;
        }
        while(Validation::empty(cmndKH_) || !Validation::validCMND(cmndKH_)){
            if(!(UI_Menu::inputPrint_("Nhập số căn cước công dân", cmndKH_))) return;
            if (!(Validation::validCMND(cmndKH_))) {
                UI_Menu::showPopup("CMND/CCCD phải đủ 12 ký tự và chỉ gồm chữ số.", UI_Menu::POPUP_WARNING);
            }
        }

        //Chuan hoa
        nameKH_ = Validation::trimAndStandardizeSpace(nameKH_);
        //khoi tao thong tin khach hang + ve
        idx_++;
        KhachHang KH_ = KhachHang(idx_, Validation::chuanHoa(nameKH_), Validation::trimAndStandardizeSpace(cmndKH_));
        Ve veKH_  = Ve(cbUserChon_->getMaCB() + (numGhe+1<10?"0":"") + std::to_string(numGhe+1), cbUserChon_->getMaCB(),cbUserChon_, numGhe, KH_);

        if (tmpDSVe_.push_back(veKH_)) {
            cbUserChon_->xoaGheTrong(numGhe); 
            UI_Menu::showPopup("Đặt vé thành công. Vé đang chờ duyệt!", true);
        }
        else {
            idx_--;
            UI_Menu::showPopup("Đặt vé không thành công!", false);
        }
    }
}

void xuLyDatVe(LinkedList<Ve>& tmpDSVe_, std::vector<Ve>& dsVe_){
    if (tmpDSVe_.empty()) {
        UI_Menu::showPopup("Hiện không có khách hàng đặt vé!", UI_Menu::POPUP_WARNING);
        return;
    }

    while (true) {
        UI_Menu::clearScreen();
        UI_Menu::printTitle("DANH SÁCH KHÁCH HÀNG ĐẶT VÉ");
        std::vector<Ve> pendingTickets;
        tmpDSVe_.getList(pendingTickets);
        UI_Menu::printTableVe(pendingTickets);

        std::string userInput;
        if (!(UI_Menu::inputPrint_("Nhập mã vé cần duyệt hoặc Y để duyệt tất cả (ESC để thoát)", userInput))) return;
        const std::string selection =
            Validation::trimAndStandardizeSpace(Validation::toUpperCase(userInput));
        int approvedCount = 0;
        int rejectedCount = 0;

        auto approveTicket = [&](const Ve& ticket) {
            ChuyenBay* flight = ticket.getCB();
            if (flight->getStatus() != 1) {
                rejectedCount++;
                return;
            }

            flight->themGheTrong(ticket.getSoGhe());
            flight->themVe(ticket);
            dsVe_.push_back(ticket);
            approvedCount++;
            if (flight->dayVe()) {
                flight->setStatus(2);
            }
        };

        if (selection == "Y") {
            while(!tmpDSVe_.empty()){
                listNode<Ve>* nodeVe_ = tmpDSVe_.popFront();
                Ve ticket = nodeVe_->data;
                delete nodeVe_;
                approveTicket(ticket);
            }
        }
        else {
            Ve selectedTicket;
            bool found = false;
            for (const Ve& ticket : pendingTickets) {
                if (ticket.getMaVe() == selection) {
                    selectedTicket = ticket;
                    found = true;
                    break;
                }
            }
            if (!found) {
                UI_Menu::showPopup("Không tìm thấy mã vé trong danh sách chờ duyệt.", UI_Menu::POPUP_WARNING);
                continue;
            }
            if (!tmpDSVe_.removeVe(selectedTicket)) {
                UI_Menu::showPopup("Không thể lấy vé khỏi danh sách chờ duyệt.", UI_Menu::POPUP_FAILURE);
                continue;
            }
            approveTicket(selectedTicket);
        }

        FileStore::luuVe(dsVe_);
        FileStore::luuThongTinKH(dsVe_);
        const std::string resultMessage = "Duyệt vé: " + std::to_string(approvedCount) +
            " thành công, " + std::to_string(rejectedCount) + " thất bại";
        UI_Menu::showPopup(resultMessage, rejectedCount == 0);
        if (selection == "Y" || tmpDSVe_.empty()) return;
    }
}

bool xuatDSVe_(std::vector<Ve>& dsVe_, int sizeDSVe_){
    if(sizeDSVe_ == 0){
        UI_Menu::showPopup("Hiện không có khách hàng đăng ký vé!", UI_Menu::POPUP_WARNING);
        return false;
    }
    UI_Menu::printTableVe(dsVe_); 
    return true; 
}

void xuLyTraVe(std::vector<Ve>& dsVe_){

    int sizeDSVe_ = dsVe_.size(); 
    int q ; 
    while(true){
        UI_Menu::clearScreen();
        std::string userInput = "";
        UI_Menu::printTitle("XỬ LÝ TRẢ VÉ");
        if (!xuatDSVe_(dsVe_, sizeDSVe_)) return; 

        q = -1;
        if (!(UI_Menu::inputPrint_("Nhập mã vé cần trả hoặc Y để trả tất cả (ESC để thoát)", userInput))) return;
        const std::string selection =
            Validation::trimAndStandardizeSpace(Validation::toUpperCase(userInput));

        if (selection == "Y") {
            int returnedCount = 0;
            int rejectedCount = 0;
            for (int i = sizeDSVe_ - 1; i >= 0; --i) {
                ChuyenBay* flight = dsVe_[i].getCB();
                if (flight->getStatus() == 3) {
                    rejectedCount++;
                    continue;
                }

                const std::string ticketCode = dsVe_[i].getMaVe();
                FileStore::xoaVe(ticketCode);
                flight->xoaVe(ticketCode);
                if (flight->getStatus() == 2) flight->setStatus(1);
                dsVe_.erase(dsVe_.begin() + i);
                sizeDSVe_--;
                returnedCount++;
            }

            FileStore::luuVe(dsVe_);
            FileStore::luuThongTinKH(dsVe_);
            const std::string resultMessage = "Trả vé: " + std::to_string(returnedCount) +
                " thành công, " + std::to_string(rejectedCount) +
                " thất bại (chuyến bay đã hoàn tất)";
            UI_Menu::showPopup(resultMessage, rejectedCount == 0);
            return;
        }

        for(int i = 0; i<sizeDSVe_; i++)    
            if (dsVe_[i].getMaVe() == selection)
                q = i; 
        
        if(q == -1) {
            UI_Menu::showPopup("Mã vé không hợp lệ!", UI_Menu::POPUP_WARNING);
        }
        else{ 
            ChuyenBay* tmp = dsVe_[q].getCB();
            if (tmp->getStatus() == 3) {
                UI_Menu::showPopup("Chuyến bay đã hoàn tất. Không thể trả vé!", false);
            }
            else {
                FileStore::xoaVe(dsVe_[q].getMaVe());
                tmp->xoaVe(dsVe_[q].getMaVe());
                if (tmp->getStatus() == 2) tmp->setStatus(1); 

                for(int i = 0; i<sizeDSVe_; i++){
                    if (dsVe_[i].getMaVe() == dsVe_[q].getMaVe()){
                        dsVe_.erase(dsVe_.begin() + i); 
                        sizeDSVe_--;
                        break;
                    }
                }
                
                FileStore::luuVe(dsVe_);
                FileStore::luuThongTinKH(dsVe_);
                UI_Menu::showPopup("Trả vé thành công!", true);
            }
        }
    };
}
void thongKe(Tree<ChuyenBay>& dsChuyenBay_, int sizeDSChuyenBay_, MayBay* dsMayBay_, int sizeDSMayBay_){
    std::string userInput = "";
    std::vector<ChuyenBay*> dsCB_; 
    dsChuyenBay_.getList(dsCB_); 
    while(true){
        std::system("cls");
        UI_Menu::printOption("THỐNG KÊ", optThongKe_);
        if (!(UI_Menu::inputPrint_("Bạn chọn", userInput))) return; 

        if( userInput == "1") ThongKe::displayKHChuyenBay(dsChuyenBay_, sizeDSChuyenBay_);
        else if( userInput == "2") ThongKe::displayDSGheTrong(dsChuyenBay_, sizeDSChuyenBay_); 
        else if( userInput == "3") ThongKe::displaySLChuyenBay(dsMayBay_, sizeDSMayBay_, dsCB_, sizeDSChuyenBay_);
        else return; 
    }
}

void quanLy(LinkedList<Ve>& tmpDSVe_, std::vector<Ve>& dsVe_, Tree<ChuyenBay>& dsChuyenBay_, int sizeDSChuyenBay_, MayBay* dsMayBay_, int sizeDSMayBay_) {
    std::system("cls");

    std::string user, pass; 
    FileStore::loadTaiKhoanAdmin(user, pass); 
    std::string user_enter, pass_enter;

    int cnt = 3; 
    while(cnt>0){
        UI_Menu::clearScreen(); 
        UI_Menu::printTitle("QUẢN LÝ HỆ THỐNG"); 
        while(Validation::empty(user_enter)) {
            if (!UI_Menu::inputPrint_("Nhập tài khoản", user_enter)) return;
        }
        while(Validation::empty(pass_enter)) {
            if (!UI_Menu::inputPrint_("Nhập mật khẩu", pass_enter, true)) return;
        }
        if (user_enter == user && pass_enter == pass){
            UI_Menu::showPopup("Đăng nhập thành công!", true);
            break;
        }
        else {
            cnt--; 
            if(cnt == 0) {
                UI_Menu::showPopup("Bạn đã nhập sai quá 3 lần!", false);
                return; 
            }
            UI_Menu::showPopup("Sai tài khoản hoặc mật khẩu!", false);
            user_enter.clear();
            pass_enter.clear();
        } 
    }
    
    std::string q; 
    while(true){
        UI_Menu::printTitle("QUẢN LÝ HỆ THỐNG");
        std::system("cls");
        UI_Menu::printOption("QUẢN LÝ HỆ THỐNG", optQuanLy_);
        if (!(UI_Menu::inputPrint_("Bạn chọn", q))) return;
        if (q == "1") xuLyDatVe(tmpDSVe_, dsVe_);
        else if( q == "2") xuLyTraVe(dsVe_); 
        else if ( q == "3") thongKe(dsChuyenBay_, sizeDSChuyenBay_, dsMayBay_, sizeDSMayBay_); 
        else return; 
    };
}

int main(){

    SetConsoleOutputCP(65001);
    srand(time(0));
    MayBay* dsMayBay = new MayBay[100];
    Tree<ChuyenBay> dsChuyenBay; 
    std::vector<Ve> dsVe_; 
    LinkedList<Ve> tmpDSVe_;

    int sizeDSMayBay_ = 0;
    int sizeDSChuyenBay_ = 0;

    FileStore::loadMayBay(dsMayBay, sizeDSMayBay_); 
    FileStore::loadChuyenBay(dsChuyenBay, sizeDSChuyenBay_, dsMayBay, sizeDSMayBay_); 

    std::string q = "";
    int cnt = 0;
    while(true){
        std::system("cls");
        UI_Menu::printHeader(); 
        UI_Menu::printOption("MENU CHỨC NĂNG", optMenuChinh_);
        // cnt++; 
        if(!UI_Menu::inputPrint_("Bạn chọn (Nhập ESC để thoát chương trình)", q, false)) break;

        if( q == "1") hienThiDSChuyenBay(dsChuyenBay, sizeDSChuyenBay_); 
        else if ( q == "2") datVe(cnt, dsMayBay, sizeDSMayBay_, dsChuyenBay, sizeDSChuyenBay_, tmpDSVe_);
        else if ( q == "3") quanLy(tmpDSVe_, dsVe_, dsChuyenBay, sizeDSChuyenBay_, dsMayBay, sizeDSMayBay_); 
        else break; 
    }

    FileStore::cleanVe(dsVe_); 
    delete[] dsMayBay; 
    return 0; 
}