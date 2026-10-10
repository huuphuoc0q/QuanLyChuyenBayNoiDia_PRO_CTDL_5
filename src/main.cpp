
#include<iostream> 
#include "../include/MayBay.h"
#include "../include/ChuyenBay.h"
#include "../include/Ve.h"
#include "../include/KhachHang.h"
#include "../include/ThongKe.h"
#include "../include/FileStore.h"

#include<vector> 
#include<fstream>
#include <cstdlib>
#include <windows.h>
#include <queue>
#include <ctime>

void xoaKhachHang(std::vector<KhachHang>& dsKhachHang_, std::string cmndKH_){
    int sizeDSKhachHang_ = dsKhachHang_.size(); 
    for(int i = 0; i<sizeDSKhachHang_; i++) {
        if (cmndKH_ == dsKhachHang_[i].getCmnd()) {
            dsKhachHang_.erase(dsKhachHang_.begin() + i); 
            return; 
        }
    }
}

void hienThiDSChuyenBay(ChuyenBay* dsChuyenBay, int& sizeDSChuyenBay) {
    for(int i = 0; i<sizeDSChuyenBay; i++) {
        std::cout<<"STT: "<<i+1<<" ";
        dsChuyenBay[i].xuat();
    }
    Sleep(5000);
    std::system("cls");
}
void datVe(int idx_, MayBay* dsMayBay,int& sizeDSMayBay, ChuyenBay* dsChuyenBay, int& sizeDSChuyenBay, std::queue<Ve>& tmpDSVe_) {
    std::system("cls");
    int tmpStatusCB = 0; 
    int numCB;
    //chon chuyen bay
    while(tmpStatusCB == 0 || tmpStatusCB == 3) {
        std::cout<<"Chon chuyen bay: "; 
        for(int i = 0; i<sizeDSChuyenBay; i++) {
            if(dsChuyenBay[i].getStatus() != 1) continue; 
            std::cout<<i+1<<": "<<dsChuyenBay[i].getMaCB()<<std::endl;
        }
        std::cin>>numCB; numCB-=1;
        tmpStatusCB = dsChuyenBay[numCB].getStatus(); 
        
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
    ChuyenBay& cbUserChon_ = dsChuyenBay[numCB]; 
    std::vector<int> dsGheTrong_ = dsChuyenBay[numCB].getDSGheTrong(); 
    //chon ghe
    int numGhe = -1; 
    while(true){
        std::cout<<"Danh sach ghe trong hien tai: ";
        int count = 1; 
        for(int i: dsGheTrong_) {
            if(i==0) {
                std::cout<<count<<" ";
            }
            count++; 
        }
        std::cin>>numGhe; numGhe--;
        if (dsGheTrong_[numGhe]==0) break;
        else {
            std::cout<<"Ghe chon khong phu hop! Vui long chon lai"<<std::endl;
        }
    } 
    std::cin.ignore(10000, '\n');
    //Kiem tra da het ghe hay chua
    if(cbUserChon_.getSoLuongGheTrong() == 0) cbUserChon_.setStatus(2); 

    //Nhap thong tin khachhang - khoi tao ve: 
    std::string nameKH_; 
    std::string cmndKH_; 
    
    std::cout<<"Nhap ho va ten: "; 
    std::getline(std::cin, nameKH_);
    std::cout<<"Nhap CMND: "; std::cin>>cmndKH_;

    //khoi tao thong tin khach hang + ve
    KhachHang KH_ = KhachHang(idx_, nameKH_, cmndKH_);
    Ve veKH_  = Ve(cbUserChon_.getMaCB() + std::to_string(numGhe + 1), cbUserChon_.getMaCB(),&cbUserChon_, numGhe, KH_);
    

    tmpDSVe_.push(veKH_); 
    std::cout<<"Dat ve thanh cong!";
    Sleep(3000);
    std::system("cls");
}

void xuLyDatVe(std::queue<Ve>& tmpDSVe_, std::vector<KhachHang>& dsKhachHang_, std::vector<Ve>& dsVe_){
    if(tmpDSVe_.size() == 0) {
        std::cout<<"Hien tai chua co khach hang dat ve!";
        Sleep(2000); 
        return;
    }    

    std::cout<<"So khach hang da dat ve: "<<tmpDSVe_.size()<<std::endl;
    std::queue<Ve> copyDSVe_ = tmpDSVe_; 
    while(!tmpDSVe_.empty()) {
        Ve& tmp = tmpDSVe_.front(); 
        tmp.getKhachHang().xuat();
        // std::cout<<"Ve da dat "<<tmp.getMaVe()<<" "<<tmp.getSoGhe()<<std::endl;
        tmp.xuat(); 
        tmpDSVe_.pop(); 
    }

    std::cout<<"Nhap 'ok' de duyet tat ca! "<<std::endl; 
    std::string text; std::cin>>text; 
    if(text == "ok") {
        while(!copyDSVe_.empty()){
            Ve& nowVe_ = copyDSVe_.front(); copyDSVe_.pop(); 
            ChuyenBay* cbVe_  = nowVe_.getCB(); 
            if (cbVe_->kiemtraGheTrong(nowVe_.getSoGhe()) == false) {
                std::cout<<"Ve "<<nowVe_.getMaVe()<<" da bi huy vi khong con ghe trong"<<std::endl;
                continue;
            }
            cbVe_->themVe(nowVe_);
            cbVe_->xoaGheTrong(nowVe_.getSoGhe()); 
            dsVe_.push_back(nowVe_); 
            dsKhachHang_.push_back(nowVe_.getKhachHang()); 
        }
        std::cout<<"Da duyet tat ca";
    }
    else {
        std::cout<<"Thao tac chua duoc thuc hien"; 
        tmpDSVe_ = copyDSVe_; 
    }
    Sleep(2000); 
}
void xuLyTraVe(std::vector<Ve>& dsVe_, std::vector<KhachHang>& dsKhachHang_){
    int sizeDSVe_ = dsVe_.size(); 
    if(sizeDSVe_ == 0){
        std::cout<<"Chua co ve nao duoc duyet!"<<std::endl;
        Sleep(2000); 
        return;
    }
    std::cout<<"Chon ve can tra ve hoac nhap '2204' de thoat chuc nang"<<std::endl;
    for(int i = 0; i<sizeDSVe_; i++) {
        std::cout<<i+1<<": ";
        dsVe_[i].xuat(); 
    }
    int q; 
    while(true){
        std::cin>>q; 
        if(q!=2204){
            if(q>sizeDSVe_) {
                std::cout<<"Gia tri khong hop le!"<<std::endl;
            }
            else{ 
                ChuyenBay* tmp = dsVe_[q-1].getCB();
                if (tmp->getStatus() == 3) {
                    std::cout<<"Chuyen bay da hoan tat! Khong the huy ve"<<std::endl;
                }
                else {
                    tmp->xoaVe(dsVe_[q-1].getMaVe());
                    for(int i = 0; i<sizeDSVe_; i++){
                        if (dsVe_[i].getMaVe() == dsVe_[q-1].getMaVe()){
                            dsVe_.erase(dsVe_.begin() + i); 
                            sizeDSVe_--;
                            xoaKhachHang(dsKhachHang_, dsVe_[q-1].getKhachHang().getCmnd());
                            break;
                        }
                    }
                    std::cout<<"Xoa ve thanh cong! Chon ve can xoa hoac nhap '2204' de thoat"
                    <<std::endl; 
                }
            }
        }
        else break;
    }
    Sleep(2000); 
}
void thongKe(std::vector<KhachHang>& dsKhachHang_, ChuyenBay* dsChuyenBay_, int sizeDSChuyenBay_, MayBay* dsMayBay_, int sizeDSMayBay_){
    int q; 
    while(true){
        std::system("cls");
        std::cout<<"Vui long chon option: "<<std::endl<<
            "1. Hien thi danh sach khach hang cua mot chuyen bay"<<std::endl<<
            "2. Hien thi danh sach ghe con trong cua mot chuyen bay "<<std::endl<<
            "3. Thong ke so luong chuyen may cua mot may bay"<<std::endl;
        std::cin>>q;
        if(q==1) ThongKe::displayKHChuyenBay(dsChuyenBay_, sizeDSChuyenBay_);
        else if(q==2) ThongKe::displayDSGheTrong(dsChuyenBay_, sizeDSChuyenBay_); 
        else if(q==3) ThongKe::displaySLChuyenBay(dsMayBay_, sizeDSMayBay_, dsChuyenBay_, sizeDSChuyenBay_);
        else return; 
    }
}

void quanLy(std::queue<Ve>& tmpDSVe_, std::vector<KhachHang>& dsKhachHang_, std::vector<Ve>& dsVe_, ChuyenBay* dsChuyenBay_, int sizeDSChuyenBay_, MayBay* dsMayBay_, int sizeDSMayBay_) {
    std::system("cls");

    std::string user, pass; 
    FileStore::loadTaiKhoanAdmin(user, pass); 
    std::string user_enter, pass_enter;
    int cnt = 3; 
    while(cnt>0){
        std::cout<<"Nhap tai khoan: "; std::cin>>user_enter; 
        std::cout<<"Nhap mat khau: "; std::cin>>pass_enter;
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
        } 
    }
    
    int q;
    while(true){
        std::system("cls");
        std::cout<<"Vui long chon option: "<<std::endl<<
            "1. Xu ly dat ve"<<std::endl<<
            "2. Xu ly tra ve"<<std::endl<<
            "3. Thong ke"<<std::endl;
        std::cin>>q;
        if (q == 1) xuLyDatVe(tmpDSVe_, dsKhachHang_, dsVe_);
        else if(q==2) xuLyTraVe(dsVe_, dsKhachHang_); 
        else if (q==3) thongKe(dsKhachHang_, dsChuyenBay_, sizeDSChuyenBay_, dsMayBay_, sizeDSMayBay_); 
        else return; 
    };
}

int main(){
    srand(time(0));
    MayBay* dsMayBay = new MayBay[100];
    ChuyenBay* dsChuyenBay = new ChuyenBay[100];
    std::vector<KhachHang> dsKhachHang; 
    std::vector<Ve> dsVe_; 

    int sizeDSMayBay_ = 0;
    int sizeDSChuyenBay_ = 0;

    FileStore::loadMayBay(dsMayBay, sizeDSMayBay_); 
    FileStore::loadChuyenBay(dsChuyenBay, sizeDSChuyenBay_, dsMayBay, sizeDSMayBay_); 

    int q = 0; 
    int cnt = 0;
    std::queue<Ve> tmpDSVe_; 
    while(true){
        std::system("cls");

        cnt++; 
        std::cout<<"Vui long chon option: "<<std::endl<<
            "1. Hien thi dsChuyenBay"<<std::endl<<
            "2. Dat ve"<<std::endl<<
            "3. Quan ly"<<std::endl;
        std::cin>>q; 
        if(q==1) hienThiDSChuyenBay(dsChuyenBay, sizeDSChuyenBay_); 
        else if (q==2) datVe(cnt, dsMayBay, sizeDSMayBay_, dsChuyenBay, sizeDSChuyenBay_, tmpDSVe_);
        else if (q==3) quanLy(tmpDSVe_, dsKhachHang, dsVe_, dsChuyenBay, sizeDSChuyenBay_, dsMayBay, sizeDSMayBay_); 
        else break; 
    }

    delete[] dsMayBay; 
    delete[] dsChuyenBay; 
    return 0; 
}