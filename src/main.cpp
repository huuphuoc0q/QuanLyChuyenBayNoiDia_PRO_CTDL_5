
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
    "Hien thi dsChuyenBay",
    "Dat ve",
    "Quan ly",
    "Thoat chuong trinh (Hoac an ESC)"
};
std::vector<std::string> optQuanLy_ = {
    "Xu ly dat ve", 
    "Xu ly tra ve", 
    "Thong ke"
};
std::vector<std::string> optThongKe_ = {
    "Hien thi danh sach khach hang cua mot chuyen bay",
    "Hien thi danh sach ghe con trong cua mot chuyen bay",
    "Thong ke so luong chuyen bay cua mot may bay"
};


void hienThiDSChuyenBay(Tree<ChuyenBay>& dsChuyenBay, int& sizeDSChuyenBay) {
    std::string q = "";
    std::system("cls"); 
    UI_Menu::printTitle("THONG TIN DANH SACH CHUYEN BAY");
    UI_Menu::printTableDSCB(dsChuyenBay); 
    if (!UI_Menu::inputPrint_("Nhap phim bat ki/ ESC de thoat", q, false)) return; 
}

void datVe(int& idx_, MayBay* dsMayBay,int& sizeDSMayBay, Tree<ChuyenBay>& dsChuyenBay, int& sizeDSChuyenBay, LinkedList<Ve>& tmpDSVe_) {
    std::system("cls");
    
    int tmpStatusCB = 0; 
    int numCB = -1;
    std::string enter_maCB; 
    std::vector<ChuyenBay*> dsCB_;
    dsChuyenBay.getList(dsCB_); 
    
    UI_Menu::printTitle("DAT VE CHUYEN BAY NOI DIA");
    UI_Menu::printTable(dsCB_); 

    //chon chuyen bay
    while(true) {
        if(!(UI_Menu::inputPrint_("Mã chuyến bay cần đặt (Nhập 0 để quay lại)", enter_maCB))) return;
        if(enter_maCB == "0") return; 
        for(int i = 0; i<sizeDSChuyenBay; i++){
            if(Validation::toUpperCase(enter_maCB) == dsCB_[i]->getMaCB()) {
                numCB = i; 
                break;
            }
        }
        if (numCB == -1) {
            std::cout<<"Khong co chuyen bay nay! Vui long nhap lai"<<std::endl;
            continue; 
        }


        tmpStatusCB = dsCB_[numCB]->getStatus(); 
        if(tmpStatusCB == 1) break;
        switch(tmpStatusCB) {
            case 0: {
                std::cout<<"Chuyen bay da bi huy! Vui long chon chuyen bay khac."<<std::endl;
                break;
            }
            case 2: {
                std::cout<<"Chuyen bay da het ve! Vui long chon chuyen bay khac."<<std::endl;
                break;
            }
            case 3: {
                std::cout<<"Chuyen bay da hoan tat! Vui long chon chuyen bay khac."<<std::endl; 
                break;
            }
            default: 
                break;
        }
    }
    ChuyenBay* cbUserChon_ = dsCB_[numCB]; 
    std::vector<int> dsGheTrong_ = dsCB_[numCB]->getDSGheTrong(); 

    //chon ghe
    int numGhe = UI_Menu::selectSeatInteractive(cbUserChon_->getMB()->getSoCho(), cbUserChon_->getDSGheTrong()); 
    if (numGhe < 0) return; 

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
        if (!(Validation::validCMND(cmndKH_))) std::cout<<"So can cuoc cong dan phai du 12 ki tu, bao gom ki tu so"<<"\n";
    }

    //Chuan hoa
    nameKH_ = Validation::trimAndStandardizeSpace(nameKH_);
    //khoi tao thong tin khach hang + ve
    KhachHang KH_ = KhachHang(idx_, Validation::chuanHoa(nameKH_), Validation::trimAndStandardizeSpace(cmndKH_));
    Ve veKH_  = Ve(cbUserChon_->getMaCB() + std::to_string(numGhe+1), cbUserChon_->getMaCB(),cbUserChon_, numGhe, KH_);
    

    if (tmpDSVe_.push_back(veKH_)) {
        std::cout<<"Dat ve thanh cong!"<<std::endl;

    }
    else std::cout<<"Dat ve khong thanh cong!";
    Sleep(3000);
    std::system("cls");
}

void xuLyDatVe(LinkedList<Ve>& tmpDSVe_, std::vector<Ve>& dsVe_){
    UI_Menu::printTitle("XU LY DAT VE"); 
    std::string userInput; 

    if(tmpDSVe_.empty()) {
        // std::cout<<"Hien tai chua co khach hang dat ve!";
        if (!(UI_Menu::inputPrint_("Hien tai chua co khach hang dat ve, nhap ESC de thoat", userInput))) return; 
        // Sleep(2000); 
        return;
    }    

    
    std::cout<<"So khach hang da dat ve: "<<tmpDSVe_.getSize()<<std::endl;
    UI_Menu::printTableVe(); 
    tmpDSVe_.display(); 

    
    while (true) {
        if (!(UI_Menu::inputPrint_("Nhap Y de duyet tat ca!", userInput))) return; 
        if(Validation::toUpperCase(userInput) == "Y") {
            while(!tmpDSVe_.empty()){
                listNode<Ve>* nodeVe_ = tmpDSVe_.popFront(); 
                Ve nowVe_ = nodeVe_->data; delete nodeVe_; 

                ChuyenBay* cbVe_  = nowVe_.getCB(); 
                if(cbVe_->getStatus() != 1) {
                    std::cout<<"Chuyen bay ve "<<nowVe_.getMaVe()<<" bi huy hoac da hoan thanh! Khong the duyet ve!"<<std::endl;
                    continue; 
                } 
                if (cbVe_->kiemtraGheTrong(nowVe_.getSoGhe()) == false) {
                    std::cout<<"Ve "<<nowVe_.getMaVe()<<" da bi huy vi khong con ghe trong"<<std::endl;
                    continue;
                }
                //Kiem tra ve do co phai la cuoi cung hay khong
                if (cbVe_->dayVe()) {
                    cbVe_->setStatus(2);
                }
                cbVe_->themVe(nowVe_);
                dsVe_.push_back(nowVe_);
            }
            FileStore::luuVe(dsVe_);
            FileStore::luuThongTinKH(dsVe_);
            if (!(UI_Menu::inputPrint_("Da duyet ve thanh cong, nhap phim bat ki de thoat", userInput))) return; 
            else return; 
        }
        else {
            std::cout<<"Thao tac chua duoc thuc hien!"<<"\n";
        }
    }
}

bool xuatDSVe_(std::vector<Ve>& dsVe_, int sizeDSVe_){
    if(sizeDSVe_ == 0){
        UI_Menu::setColor(14); 
        std::cout<<"KHONG CO KHACH HANG DANG KI VE!"<<std::endl;
        UI_Menu::setColor(7); 
        return false;
    }
    UI_Menu::printTableVe(); 
    for(int i = 0; i<sizeDSVe_; i++) {
        std::cout<<dsVe_[i];
    }
    return true; 
}

void xuLyTraVe(std::vector<Ve>& dsVe_){
    std::string userInput = "";
    UI_Menu::printTitle("XU LY TRA VE");
    int sizeDSVe_ = dsVe_.size(); 
    int q ; 
    while(true){
        if (!xuatDSVe_(dsVe_, sizeDSVe_)) {
            if(!UI_Menu::inputPrint_("Nhap phim bat ki/ ESC de thoat", userInput)) return; 
            else return; 
        } 

        q = -1;
        if (!(UI_Menu::inputPrint_("Vui long nhap ma ve can tra ve", userInput))) return; 
        for(int i = 0; i<sizeDSVe_; i++)    
            if (dsVe_[i].getMaVe() == Validation::trimAndStandardizeSpace(Validation::toUpperCase(userInput)))
                q = i; 
        
        if(q == -1) {
            std::cout<<"Gia tri khong hop le!"<<std::endl;
        }
        else{ 
            ChuyenBay* tmp = dsVe_[q].getCB();
            if (tmp->getStatus() == 3) {
                std::cout<<"Chuyen bay da hoan tat! Khong the huy ve"<<std::endl;
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
                std::cout<<"Xoa ve thanh cong!"<<std::endl; 
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
        UI_Menu::printOption("THONG KE", optThongKe_);
        if (!(UI_Menu::inputPrint_("Ban chon", userInput))) return; 

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
        UI_Menu::printTitle("QUAN LY HE THONG"); 
        while(Validation::empty(user_enter)) {
            if (!UI_Menu::inputPrint_("Nhap tai khoan", user_enter)) return;
        }
        while(Validation::empty(pass_enter)) {
            if (!UI_Menu::inputPrint_("Nhap mat khau", pass_enter, true)) return;
        }
        if (user_enter == user && pass_enter == pass){
            std::cout<<"Dang nhap thanh cong!";
            Sleep(2000); 
            std::system("cls");
            break;
        }
        else {
            cnt--; 
            if(cnt == 0) {
                std::cout<<"Ban da nhap qua 3 lan!";
                Sleep(2000); 
                std::system("cls");
                return; 
            }
            std::cout<<"Nhap sai tai khoan! Vui long nhap lai!";
            Sleep(2000); 
            std::system("cls");
            user_enter.clear();
            pass_enter.clear();
        } 
    }
    
    std::string q; 
    while(true){
        UI_Menu::printTitle("QUAN LY HE THONG");
        std::system("cls");
        UI_Menu::printOption("QUAN LY HE THONG", optQuanLy_);
        if (!(UI_Menu::inputPrint_("Ban chon", q))) return;
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
        UI_Menu::printOption("VUI LONG CHON OPTION", optMenuChinh_);
        cnt++; 
        if(!UI_Menu::inputPrint_("Ban chon", q, false)) break;

        if( q == "1") hienThiDSChuyenBay(dsChuyenBay, sizeDSChuyenBay_); 
        else if ( q == "2") datVe(cnt, dsMayBay, sizeDSMayBay_, dsChuyenBay, sizeDSChuyenBay_, tmpDSVe_);
        else if ( q == "3") quanLy(tmpDSVe_, dsVe_, dsChuyenBay, sizeDSChuyenBay_, dsMayBay, sizeDSMayBay_); 
        else break; 
    }

    FileStore::cleanVe(dsVe_); 
    delete[] dsMayBay; 
    return 0; 
}