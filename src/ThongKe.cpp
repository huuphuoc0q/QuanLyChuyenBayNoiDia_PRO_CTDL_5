#include "../include/ThongKe.h"
#include <windows.h>


void ThongKe::displayKHChuyenBay(Tree<ChuyenBay>& dsChuyenBay_, int sizeDSChuyenBay_){
    std::system("cls"); 
    UI_Menu::printTitle("DANH SACH KHACH HANG CHUYEN BAY"); 
    UI_Menu::printTableDSCB(dsChuyenBay_);
    std::string maCB_enter; 

    while(true){
        if (!(UI_Menu::inputPrint_("Vui long nhap ma CB can hien thi thong tin KH (Hoac nhap ECS de thoat)", maCB_enter))) return; 
        maCB_enter = Validation::trimAndStandardizeSpace(Validation::toUpperCase(maCB_enter));

        ChuyenBay resCB_ = ChuyenBay(maCB_enter, nullptr, "", "","",0);
        Node<ChuyenBay>* res_ = dsChuyenBay_.search(resCB_);

        if(res_ == nullptr) {
            std::cout<<"Chuyen bay khong ton tai!" << "\n"; 
            continue; 
        }
        resCB_ = res_->data_;
        
        switch (resCB_.getStatus()){
            case 0: 
                std::cout<<"Chuyen bay chua co thong tin khach hang!" <<"\n"; 
                break;
            case 1: {
                if(resCB_.getDSVe().size() == 0) {
                    std::cout<<"Chuyen bay chua co khach hang! "<<"\n"; 
                    break; 
                }
                std::cout<<"Danh sach khach hang cua chuyen bay co ma "<<resCB_.getMaCB()<<" la "<<std::endl;
                const std::vector<Ve>& dsVe_ = resCB_.getDSVe();
                UI_Menu::printTableDSKH(dsVe_); 
                break;
            }
            case 2: 
                std::cout<<"Chuyen bay chua co thong tin khach hang!"<<"\n";
                break;
            case 3:
                std::cout<<"Chuyen bay chua co thong tin khach hang!"<<"\n"; 
                break;
            default: 
                break;
        } 
    }
}

void ThongKe::displayDSGheTrong(Tree<ChuyenBay>& dsChuyenBay_, int sizeDSChuyenBay_){
    std::system("cls"); 
    UI_Menu::printTitle("DANH SACH GHE TRONG CUA CHUYEN BAY"); 
    UI_Menu::printTableDSCB(dsChuyenBay_);
    std::string maCB_enter; 

    while(true){
        if (!(UI_Menu::inputPrint_("Vui long chon CB can hien thi thong tin ghe trong", maCB_enter))) return; 
        maCB_enter = Validation::trimAndStandardizeSpace(Validation::toUpperCase(maCB_enter));

        ChuyenBay resCB_ = ChuyenBay(maCB_enter, nullptr, "", "","",0);
        Node<ChuyenBay>* res_ = dsChuyenBay_.search(resCB_);

        if(res_ == nullptr) {
            std::cout<<"Chuyen bay khong ton tai!" <<"\n"; 
            continue; 
        }

        resCB_ = res_->data_;
        if(resCB_.getStatus() != 1) {
            std::cout<<"Chuyen bay "<<resCB_.getMaCB()<<" da bi huy chuyen, het ve hoac hoan tat! Vui long chon chuyen bay khac!"<<std::endl;
            continue;
        }
        std::cout<<"Danh sach ghe trong cua chuyen bay co ma "<<resCB_.getMaCB()<<" la: "<<std::endl;
        const std::vector<int>& dsGheTrong_ = resCB_.getDSGheTrong(); 
        int sizeDSGheTrong_ = dsGheTrong_.size(); 
        for(int i = 0; i<sizeDSGheTrong_; i++){
            if(dsGheTrong_[i] == 0) std::cout<<i+1<<" ";
        };
        std::cout<<"\n";
    }
}

void ThongKe::displaySLChuyenBay(MayBay* dsMayBay_, int sizeDSMayBay_, std::vector<ChuyenBay*>& dsCB_, int sizeDSChuyenBay_){
    // std::cout<<"Vui long chon MB can hien thi thong tin so luong CB: "<<std::endl;
    std::system("cls"); 
    UI_Menu::printTitle("SO LUONG CHUYEN BAY CUA MAY BAY"); 
    UI_Menu::printTableDSMB(dsMayBay_, sizeDSMayBay_);
    
    std::string userInput = "";
    int q; 
    while(true){
        q = -1; 
        if (!(UI_Menu::inputPrint_("Vui long nhap so hieu may bay can hien thi thong tin so luong CB", userInput))) return; 
        userInput = Validation::trimAndStandardizeSpace(Validation::toUpperCase(userInput));

        for (int i = 0; i<sizeDSChuyenBay_; i++) {
            if (dsCB_[i]->getSoHieuMB() == userInput) q = i;
        }
        
        if(q != -1){
            int cnt = 0;
            for(int i = 0; i<sizeDSChuyenBay_; i++)
                if(dsCB_[i]->getSoHieuMB() == userInput) cnt++; 
            std::cout<<"So luong chuyen bay thuc hien cua may bay "
            <<userInput<<" la: "
            <<cnt<<std::endl; 
        }
        else 
            std::cout<<"So hieu may bay khong hop le!";
    }
}

