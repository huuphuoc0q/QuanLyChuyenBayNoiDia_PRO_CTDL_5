#ifndef KHACHHANG_H
#define KHACHHANG_H

#include<iostream> 
#include<string> 

class KhachHang {
    private: 
        int stt_; 
        std::string cmnd_, name_; 
    public: 
        //Constructor - Tien
        KhachHang(); 
        KhachHang(int& stt, const std::string name, const std::string cmnd); 

        //Getter, Setter - Mong Tien
        std::string getCmnd() const;
        std::string getName() const; 
        int getStt() const; 
        
        //Xuat thong tin khach hang
        void xuat() const; 
};

#endif