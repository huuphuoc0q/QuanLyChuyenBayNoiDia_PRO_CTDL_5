#ifndef VE_H
#define VE_H

#include <iostream> 
#include <string> 
#include "KhachHang.h"
#include "ChuyenBay.h"

class ChuyenBay;
class Ve { 
    private: 
        std::string maVe_, maChuyenBay_;
        KhachHang khachHang_; 
        ChuyenBay* cb_; 
        int soGhe_; 
    public: 
        //Constructor 
        Ve(); 
        Ve(std::string maVe, std::string maChuyenBay, ChuyenBay* cb_, int soGhe, KhachHang khachHang); 

        //Getter/ Setter
        std::string getMaVe() const; 
        KhachHang getKhachHang() const; 
        int getSoGhe() const; 
        std::string getMaCB() const; 
        ChuyenBay* getCB() const; 

        //Xuat thong tin ve
        void xuat() const; 
};

#endif 