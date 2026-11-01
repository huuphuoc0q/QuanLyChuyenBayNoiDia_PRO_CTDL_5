#ifndef VE_H
#define VE_H

#include <iostream> 
#include <string> 
#include <iomanip>
#include "KhachHang.h"


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
        friend std::ostream& operator<<(std::ostream& out, const Ve& obj);
        //qua tai toan tu 
        bool operator==(const Ve& other) const;
        bool operator!=(const Ve& other) const;
};

#endif 