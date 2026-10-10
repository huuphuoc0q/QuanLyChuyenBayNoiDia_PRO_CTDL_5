#ifndef CHUYENBAY_H
#define CHUYENBAY_H

#include<iostream>
#include<string>
#include<vector>
#include "Ve.h"
#include "MayBay.h"
class ChuyenBay {
    private: 
        std::string maChuyenBay_, soHieuMayBay_, ngayKhoiHanh_, sanBayDen_;
        int trangThai_, soLuongGheTrong_; 
        std::vector<Ve> dsVe_; 
        std::vector<int> dsGheTrong_;
        MayBay* mbCB_; 
    public: 
        //Constructor
        ChuyenBay(); 
        ChuyenBay(const std::string maCB_,MayBay* mbChuyenBay_, const std::string soHieuMB_, const std::string ngayKH_, const std::string sanBD_,  int status_);

        //getter/ setter
        std::string getMaCB() const; 
        std::string getSoHieuMB() const; 
        std::string getNgayKH() const; 
        std::string getSanBD() const; 
        int getStatus() const; 
        void setStatus(int newTrangThai_);
        std::vector<int> getDSGheTrong() const; 
        std::vector<Ve> getDSVe() const; 
        int getSoLuongGheTrong() const; 
        MayBay* getMB() const;
        
        //Ham xu ly
        void khoiTaoGheTrong(int soCho_, int val); 
        bool kiemtraGheTrong(int idGhe_) const; 
        void xoaGheTrong(int idGhe_); 
        void themGheTrong(int idGhe_); 
        void themVe(const Ve& ve_);
        void xoaVe(const std::string& maVe_);
        void xuat() const; 


        //~Destructor

};

#endif