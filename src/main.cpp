
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

#include<vector> 
#include<fstream>
#include <cstdlib>
#include <windows.h>
#include <queue>
#include <ctime>
#include <iomanip>

void hienThiDSChuyenBay(Tree<ChuyenBay>& dsChuyenBay, int& sizeDSChuyenBay) {
    int q = -1; 
    while(q<0){
        std::system("cls"); 
        std::cout << "====================================================================================\n";
        std::cout << "                             DANH SACH CHUYEN BAY                                   \n";
        std::cout << "====================================================================================\n";
            std::cout << std::left 
                    << std::setw(16) << "Ma chuyen bay"
                    << std::setw(22) << "Ngay khoi hanh"
                    << std::setw(15) << "San bay den"
                    << std::setw(15) << "Trang thai"
                    << std::setw(15) << "Danh sach ve" << "\n";
            std::cout << std::string(83, '-') << "\n";
        dsChuyenBay.xuat(); 
        std::cin>>q; 
    }
    
}
void datVe(int& idx_, MayBay* dsMayBay,int& sizeDSMayBay, Tree<ChuyenBay>& dsChuyenBay, int& sizeDSChuyenBay, LinkedList<Ve>& tmpDSVe_) {
    std::system("cls");
    int tmpStatusCB = 0; 
    int numCB;
    std::vector<ChuyenBay*> dsCB_;
    dsChuyenBay.getList(dsCB_); 

    //chon chuyen bay
    while(true) {
        std::cout<<"Chon chuyen bay: "<<std::endl;
        for(int i = 0; i < dsCB_.size(); i++){
            std::cout<<i+1<<": "<<dsCB_[i]->getMaCB() << " SBD: "<< dsCB_[i]->getSanBD()<<"Status: "<<dsCB_[i]->getStatus()<<std::endl;
        }
        std::cin>>numCB;
        if (numCB<=0 || numCB>sizeDSChuyenBay) {
            std::cout<<"Chuyen bay lua chon khong phu hop! Nhap 2204 de thoat"<<std::endl;
            if(numCB == 2204) return; 
            continue;
        }
        numCB-=1;
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
    int numGhe = -1; 
    while(true){
        std::cout<<"Danh sach ghe trong hien tai: ";
        int count = 1; 
        for(int i: dsGheTrong_) {
            if( i == 0 ) {
                std::cout<<count<<" ";
            }
            count++; 
        }
        
        while(numGhe<0 || numGhe > dsCB_[numCB]->getMB()->getSoCho()) {
            std::cout<<std::endl<<"Ghe ban chon la: "; 
            std::cin>>numGhe; 
        }
        numGhe--;
        if (dsGheTrong_[numGhe] == 0) break;
        else {
            std::cout<<"Ghe chon khong phu hop! Vui long chon lai"<<std::endl;
        }
    } 
    std::cin.ignore(10000, '\n');

    //Kiem tra da het ghe hay chua
    if(cbUserChon_->getSoLuongGheTrong() == 0) cbUserChon_->setStatus(2); 

    //Nhap thong tin khachhang - khoi tao ve: 
    std::string nameKH_ = ""; 
    std::string cmndKH_ = ""; 
    
    while(Validation::empty(nameKH_)){
        std::cout<<"Nhap ho va ten: "; 
        std::getline(std::cin, nameKH_);
    }
    while(Validation::empty(cmndKH_) || !Validation::validCMND(cmndKH_)){
        std::cout<<"Nhap CMND: "; 
        std::cin>>cmndKH_;
    }

    //Chuan hoa
    nameKH_ = Validation::trimAndStandardizeSpace(nameKH_);
    //khoi tao thong tin khach hang + ve
    KhachHang KH_ = KhachHang(idx_, Validation::chuanHoa(nameKH_), Validation::trimAndStandardizeSpace(cmndKH_));
    Ve veKH_  = Ve(cbUserChon_->getMaCB() + std::to_string(numGhe + 1), cbUserChon_->getMaCB(),cbUserChon_, numGhe, KH_);
    

    if (tmpDSVe_.push_back(veKH_)) {
        std::cout<<"Dat ve thanh cong! SL="<<tmpDSVe_.getSize()<<std::endl;
    }
    else std::cout<<"Dat ve khong thanh cong!";
    Sleep(3000);
    std::system("cls");
}

void xuLyDatVe(LinkedList<Ve>& tmpDSVe_, std::vector<Ve>& dsVe_){
    if(tmpDSVe_.empty()) {
        std::cout<<"Hien tai chua co khach hang dat ve!";
        Sleep(2000); 
        return;
    }    

    std::cout<<"So khach hang da dat ve: "<<tmpDSVe_.getSize()<<std::endl;
    tmpDSVe_.display(); 
    

    std::cout<<"Nhap 'ok' de duyet tat ca! "<<std::endl; 
    std::string text; std::cin>>text; 
    if(text == "ok") {
        while(!tmpDSVe_.empty()){
            listNode<Ve>* nodeVe_ = tmpDSVe_.popFront(); 
            Ve nowVe_ = nodeVe_->data; delete nodeVe_; 

            ChuyenBay* cbVe_  = nowVe_.getCB(); 
            if(cbVe_->getStatus() != 1) {
                std::cout<<"Ve "<<nowVe_.getMaVe()<<" da het ve, bi huy hoac da hoan thanh! Khong the duyet ve!"<<std::endl;
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
        std::cout<<"Da duyet tat ca";
    }
    else {
        std::cout<<"Thao tac chua duoc thuc hien"; 
    }
    Sleep(2000); 
}

void xuatDSVe_(std::vector<Ve>& dsVe_, int sizeDSVe_){
    if(sizeDSVe_ == 0){
        std::cout<<"KHONG CO KHACH HANG DANG KI VE!"<<std::endl;
        return;
    }
    std::cout<<"DS Ve:"<<std::endl;
    for(int i = 0; i<sizeDSVe_; i++) {
            std::cout<<i+1<<": ";
            dsVe_[i].xuat(); 
        }
}
void xuLyTraVe(std::vector<Ve>& dsVe_){
    int sizeDSVe_ = dsVe_.size(); 
    if(sizeDSVe_ == 0){
        std::cout<<"Chua co ve nao duoc duyet!"<<std::endl;
        Sleep(2000); 
        return;
    }
    xuatDSVe_(dsVe_, sizeDSVe_); 
    int q; 
    while(true){
        std::cin>>q; 
        if(q!=2204){
            if(q>sizeDSVe_ || q <= 0) {
                std::cout<<"Gia tri khong hop le!"<<std::endl;
            }
            else{ 
                ChuyenBay* tmp = dsVe_[q-1].getCB();
                if (tmp->getStatus() == 3) {
                    std::cout<<"Chuyen bay da hoan tat! Khong the huy ve"<<std::endl;
                }
                else {
                    FileStore::xoaVe(dsVe_[q-1].getMaVe());
                    tmp->xoaVe(dsVe_[q-1].getMaVe());
                    for(int i = 0; i<sizeDSVe_; i++){
                        if (dsVe_[i].getMaVe() == dsVe_[q-1].getMaVe()){
                            dsVe_.erase(dsVe_.begin() + i); 
                            sizeDSVe_--;
                            break;
                        }
                    }
                    FileStore::luuVe(dsVe_);
                    std::cout<<"Xoa ve thanh cong!"<<std::endl; 
                    xuatDSVe_(dsVe_, sizeDSVe_); 
                }
            }
        }
        else break;
    }
    Sleep(2000); 
}
void thongKe(Tree<ChuyenBay>& dsChuyenBay_, int sizeDSChuyenBay_, MayBay* dsMayBay_, int sizeDSMayBay_){
    int q; 
    std::vector<ChuyenBay*> dsCB_; 
    dsChuyenBay_.getList(dsCB_); 
    while(true){
        std::system("cls");
        std::cout<<"Vui long chon option: "<<std::endl<<
            "1. Hien thi danh sach khach hang cua mot chuyen bay"<<std::endl<<
            "2. Hien thi danh sach ghe con trong cua mot chuyen bay "<<std::endl<<
            "3. Thong ke so luong chuyen may cua mot may bay"<<std::endl;
        std::cin>>q;

        if(q==1) ThongKe::displayKHChuyenBay(dsChuyenBay_, sizeDSChuyenBay_);
        else if(q==2) ThongKe::displayDSGheTrong(dsChuyenBay_, sizeDSChuyenBay_); 
        else if(q==3) ThongKe::displaySLChuyenBay(dsMayBay_, sizeDSMayBay_, dsCB_, sizeDSChuyenBay_);
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
        while(Validation::empty(user_enter)) {
            std::cout<<"Nhap tai khoan: "; std::cin>>user_enter; 
        }
        while(Validation::empty(pass_enter)) {
            std::cout<<"Nhap mat khau: "; std::cin>>pass_enter;
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
        if (q == 1) xuLyDatVe(tmpDSVe_, dsVe_);
        else if(q==2) xuLyTraVe(dsVe_); 
        else if (q==3) thongKe(dsChuyenBay_, sizeDSChuyenBay_, dsMayBay_, sizeDSMayBay_); 
        else return; 
    };
}

int main(){
    srand(time(0));
    MayBay* dsMayBay = new MayBay[100];
    Tree<ChuyenBay> dsChuyenBay; 
    // std::vector<KhachHang> dsKhachHang; 
    std::vector<Ve> dsVe_; 
    LinkedList<Ve> tmpDSVe_;

    int sizeDSMayBay_ = 0;
    int sizeDSChuyenBay_ = 0;

    FileStore::loadMayBay(dsMayBay, sizeDSMayBay_); 
    FileStore::loadChuyenBay(dsChuyenBay, sizeDSChuyenBay_, dsMayBay, sizeDSMayBay_); 

    int q = 0; 
    int cnt = 0;
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
        else if (q==3) quanLy(tmpDSVe_, dsVe_, dsChuyenBay, sizeDSChuyenBay_, dsMayBay, sizeDSMayBay_); 
        else break; 
    }

    FileStore::cleanVe(dsVe_); 
    delete[] dsMayBay; 
    return 0; 
}