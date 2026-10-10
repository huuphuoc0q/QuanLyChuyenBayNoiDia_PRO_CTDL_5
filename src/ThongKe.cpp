#include "../include/ThongKe.h"
#include <windows.h>

void ThongKe::displayKHChuyenBay(ChuyenBay* dsChuyenBay_, int sizeDSChuyenBay_){
    std::cout<<"Vui long chon CB can hien thi thong tin KH: "<<std::endl;
    for(int i = 0; i<sizeDSChuyenBay_; i++){
        std::cout<<i+1<<": "<<dsChuyenBay_[i].getMaCB()<<
        " SOLUONG KH: "<<
        dsChuyenBay_[i].getDSVe().size()<<
        std::endl;
    }
    int q; 
    while(true){
        std::cin>>q; 
        if(q>0 && q<=sizeDSChuyenBay_){
            std::cout<<"Danh sach khach hang cua chuyen bay co ma "<<dsChuyenBay_[q-1].getMaCB()<<" la "<<std::endl;
            const std::vector<Ve>& dsVe_ = dsChuyenBay_[q-1].getDSVe();
            int sizeDSVe_ = dsVe_.size(); 
            for(int i = 0; i<sizeDSVe_ ; i++){
                std::cout<<i+1<<": "
                <<"name: "<<dsVe_[i].getKhachHang().getName()
                <<"cmnd: "<<dsVe_[i].getKhachHang().getCmnd()
                <<std::endl; 
            }
            std::cout<<"Chon chuyen bay khac hoac 2204 de thoat"<<std::endl;
        }
        else if (q!=2204) {
            std::cout<<"Gia tri khong phu hop! Nhap 2204 de thoat, hoac chon lai!"<<std::endl;
        }
        else if(q==2204) break; 
    }
    Sleep(2000); 
}

void ThongKe::displayDSGheTrong(ChuyenBay* dsChuyenBay_, int sizeDSChuyenBay_){
    std::cout<<"Vui long chon CB can hien thi thong tin ghe trong: "<<std::endl;
    for(int i = 0; i<sizeDSChuyenBay_; i++){
        std::cout<<i+1<<": "<<dsChuyenBay_[i].getMaCB()<<
        " SO LUONG GHE TRONG: "<<
        dsChuyenBay_[i].getSoLuongGheTrong()<<
        std::endl;
    }

    int q; 
    while(true){
        std::cin>>q; 
        if(q>0 && q<=sizeDSChuyenBay_){
            std::cout<<"Danh sach ghe trong cua chuyen bay co ma "<<dsChuyenBay_[q-1].getMaCB()<<" la "<<std::endl;
            const std::vector<int>& dsGheTrong_ = dsChuyenBay_[q-1].getDSGheTrong(); 
            int sizeDSGheTrong_ = dsGheTrong_.size(); 
            for(int i = 0; i<sizeDSGheTrong_; i++){
                if(dsGheTrong_[i] == 0) std::cout<<i+1<<" ";
            }; 
            std::cout<<"Chon may bay khac hoac 2204 de thoat"<<std::endl;
        }
        else if (q!=2204){
            std::cout<<"Gia tri khong phu hop! Nhap 2204 de thoat, hoac chon lai!"<<std::endl;
        }
        else if (q==2204) break; 
    }
    Sleep(2000); 
}

void ThongKe::displaySLChuyenBay(MayBay* dsMayBay_, int sizeDSMayBay_, ChuyenBay* dsChuyenBay_, int sizeDSChuyenBay_){
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
                if(dsChuyenBay_[i].getSoHieuMB() == dsMayBay_[q-1].getSoHieu()) cnt++; 
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

