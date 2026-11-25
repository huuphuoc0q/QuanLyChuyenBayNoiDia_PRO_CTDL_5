#include "../include/ThongKe.h"
#include <windows.h>


void displayKH(const std::vector<Ve>& dsVe_, const std::string& maCB) {
    std::system("cls"); 
    std::string enter; 
    UI_Menu::printTitle("DANH SÁCH KHÁCH HÀNG CHUYẾN BAY " + maCB); 
    UI_Menu::printTableDSKH(dsVe_); 
    if (!(UI_Menu::inputPrint_("Nhap phim bat ki/ ESC de thoat", enter))) return; 
}

void ThongKe::displayKHChuyenBay(Tree<ChuyenBay>& dsChuyenBay_, int sizeDSChuyenBay_){

    std::string maCB_enter; 

    while(true){
        std::system("cls"); 
        UI_Menu::printTitle("DANH SÁCH KHÁCH HÀNG CHUYẾN BAY"); 
        UI_Menu::printTableDSCB(dsChuyenBay_);
        if (!(UI_Menu::inputPrint_("Vui lòng nhập mã chuyến bay cần tìm thông tin khách hàng (Nhập ESC để thoát)", maCB_enter))) return; 
        maCB_enter = Validation::trimAndStandardizeSpace(Validation::toUpperCase(maCB_enter));

        ChuyenBay resCB_ = ChuyenBay(maCB_enter, nullptr, "", "","",0);
        Node<ChuyenBay>* res_ = dsChuyenBay_.search(resCB_);

        if(res_ == nullptr) {
            UI_Menu::showPopup("Chuyến bay không tồn tại. Vui lòng nhập lại!", UI_Menu::POPUP_WARNING);
            continue; 
        }
        resCB_ = res_->data_;
        
        switch (resCB_.getStatus()){
            case 0: 
                UI_Menu::showPopup("Chuyến bay đã bị huỷ, chưa có dữ liệu khách hàng!", UI_Menu::POPUP_WARNING);
                break;
            case 1:
            case 2:
            case 3: {
                const std::vector<Ve> dsVe_ = resCB_.getDSVe();
                if(dsVe_.empty()) {
                    UI_Menu::showPopup("Chuyến bay chưa có khách hàng!", UI_Menu::POPUP_WARNING);
                    break; 
                }
                std::cout<<"Danh sach khach hang cua chuyen bay co ma "<<resCB_.getMaCB()<<" la "<<std::endl;
                displayKH(dsVe_, maCB_enter);
                break;
            }
            default: 
                break;
        } 
    }
}

void ThongKe::displayDSGheTrong(Tree<ChuyenBay>& dsChuyenBay_, int sizeDSChuyenBay_){
    std::string maCB_enter; 
    while(true){
        std::system("cls"); 
        UI_Menu::printTitle("THÔNG TIN GHẾ TRỐNG CỦA CHUYẾN BAY"); 
        UI_Menu::printTableDSCB(dsChuyenBay_);
        if (!(UI_Menu::inputPrint_("Vui lòng nhập mã chuyến bay cần kiểm tra (Nhập ESC để thoát)", maCB_enter))) return; 
        maCB_enter = Validation::trimAndStandardizeSpace(Validation::toUpperCase(maCB_enter));

        ChuyenBay resCB_ = ChuyenBay(maCB_enter, nullptr, "", "","",0);
        Node<ChuyenBay>* res_ = dsChuyenBay_.search(resCB_);

        if(res_ == nullptr) {
            UI_Menu::showPopup("Chuyến bay không tồn tại. Vui lòng nhập lại!", UI_Menu::POPUP_WARNING);
            continue; 
        }

        resCB_ = res_->data_;
        if(resCB_.getStatus() != 1) {
            UI_Menu::showPopup("Chuyến bay " + resCB_.getMaCB() + " đã bị huỷ, hết vé hoặc đã hoàn tất!", UI_Menu::POPUP_WARNING);
            continue;
        }
        const std::vector<int>& dsGheTrong_ = resCB_.getDSGheTrong();
        UI_Menu::printDSGheTrong_(static_cast<int>(dsGheTrong_.size()), dsGheTrong_, resCB_.getMaCB());
    }
}

void ThongKe::displaySLChuyenBay(MayBay* dsMayBay_, int sizeDSMayBay_, std::vector<ChuyenBay*>& dsCB_, int sizeDSChuyenBay_){
    std::string userInput = "";
    while(true){
        std::system("cls"); 
        UI_Menu::printTitle("SỐ LƯỢNG CHUYẾN BAY CỦA MÁY BAY"); 
        UI_Menu::printTableDSMB(dsMayBay_, sizeDSMayBay_, dsCB_);
        if (!(UI_Menu::inputPrint_("Nhấn phím bất kì/ ESC để thoát!", userInput))) return; 
        return;
    }
}

