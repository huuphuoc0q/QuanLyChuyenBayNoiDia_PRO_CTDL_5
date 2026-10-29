#include "../include/ThongKe.h"
#include <windows.h>

void ThongKe::displayKHChuyenBay(Tree<ChuyenBay>& dsChuyenBay_, int sizeDSChuyenBay_){
    std::cout<<"Vui long nhap ma CB can hien thi thong tin KH: "<<std::endl;
    dsChuyenBay_.xuat();
    std::string maCB_enter; 
    while(true){
        std::cin>>maCB_enter; maCB_enter = Validation::trimAndStandardizeSpace(maCB_enter);
        if (maCB_enter == "2204") break;  

        ChuyenBay resCB_ = ChuyenBay(maCB_enter, nullptr, "", "","",0);
        Node<ChuyenBay>* res_ = dsChuyenBay_.search(resCB_);

        if(res_ == nullptr) {
            std::cout<<"Chuyen bay khong ton tai!"; 
            continue; 
        }
        resCB_ = res_->data_;
        
        switch (resCB_.getStatus()){
            case 0: 
                std::cout<<"Chuyen bay da bi huy!"; 
                break;
            case 1: {
                if(resCB_.getDSVe().size() == 0) {
                    std::cout<<"Chuyen bay chua co khach hang! "; 
                    break; 
                }
                std::cout<<"Danh sach khach hang cua chuyen bay co ma "<<resCB_.getMaCB()<<" la "<<std::endl;
                const std::vector<Ve>& dsVe_ = resCB_.getDSVe();
                int sizeDSVe_ = dsVe_.size(); 
                for(int i = 0; i<sizeDSVe_ ; i++){
                    std::cout<<i+1<<": "
                    <<"name: "<<dsVe_[i].getKhachHang().getName()
                    <<" cmnd: "<<dsVe_[i].getKhachHang().getCmnd()
                    <<std::endl; 
                }
                std::cout<<"Nhap ma chuyen bay khac hoac 2204 de thoat"<<std::endl;
                break;
            }
            case 2: 
                std::cout<<"Chuyen bay da het ve!";
                break;
            case 3:
                std::cout<<"Chuyen bay da hoan tat!"; 
                break;
            default: 
                break;
        } 
    }
    std::cout<<"Dang thoat chuc nang..."; 
    Sleep(2000); 
}

void ThongKe::displayDSGheTrong(Tree<ChuyenBay>& dsChuyenBay_, int sizeDSChuyenBay_){
    std::cout<<"Vui long chon CB can hien thi thong tin ghe trong: "<<std::endl;
    dsChuyenBay_.xuat();

    std::string maCB_enter; 
    while(true){
        std::cin>>maCB_enter; 

        if (maCB_enter == "2204") break;  

        ChuyenBay resCB_ = ChuyenBay(maCB_enter, nullptr, "", "","",0);
        Node<ChuyenBay>* res_ = dsChuyenBay_.search(resCB_);

        if(res_ == nullptr) {
            std::cout<<"Chuyen bay khong ton tai!"; 
            continue; 
        }

        resCB_ = res_->data_;
        if(resCB_.getStatus() != 1) {
            std::cout<<"Chuyen bay "<<resCB_.getMaCB()<<" da bi huy chuyen, het ve hoac bi hoan! Vui long chon chuyen bay khac!"<<std::endl;
            continue;
        }
        std::cout<<"Danh sach ghe trong cua chuyen bay co ma "<<resCB_.getMaCB()<<" la "<<std::endl;
        const std::vector<int>& dsGheTrong_ = resCB_.getDSGheTrong(); 
        int sizeDSGheTrong_ = dsGheTrong_.size(); 
        for(int i = 0; i<sizeDSGheTrong_; i++){
            if(dsGheTrong_[i] == 0) std::cout<<i+1<<" ";
        }; 
        std::cout<<"Chon may bay khac hoac 2204 de thoat"<<std::endl; 
    }
    std::cout<<"Dang thoat chuc nang...";
    Sleep(2000); 
}

void ThongKe::displaySLChuyenBay(MayBay* dsMayBay_, int sizeDSMayBay_, std::vector<ChuyenBay*>& dsCB_, int sizeDSChuyenBay_){
    std::cout<<"Vui long chon MB can hien thi thong tin so luong CB: "<<std::endl;
    for(int i = 0; i<sizeDSMayBay_; i++){
        std::cout<<i+1<<": "<<dsMayBay_[i].getSoHieu()<<
        std::endl;
    }

    int q; 
    while(true){
        std::cin>>q; 
        if(q>0 && q<=sizeDSMayBay_){
            int cnt = 0;
            for(int i = 0; i<sizeDSChuyenBay_; i++)
                if(dsCB_[i]->getSoHieuMB() == dsMayBay_[q-1].getSoHieu()) cnt++; 
            std::cout<<"So luong chuyen bay thuc hien cua may bay "
            <<dsMayBay_[q-1].getSoHieu()<<" la "
            <<cnt<<std::endl; 
            std::cout<<"Chon chuyen bay khac hoac 2204 de thoat"<<std::endl;
        }
        else if (q!=2204){
            std::cout<<"Gia tri khong phu hop! Nhap 2204 de thoat, hoac chon lai!"<<std::endl;
        }
        else if (q==2204) break; 
    }
    Sleep(2000); 
}

