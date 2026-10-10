#ifndef MAYBAY_H
#define MAYBAY_H

#include<iostream>
#include<string> 
#include<fstream>

class MayBay{
    private: 
        std::string soHieu_;
        int soCho_; 
        int soCB_;
    public: 
        //constructor - Minh Tien
        MayBay(); 
        MayBay(const std::string& soHieu_, const int& soCho_); 

        //Getter, setter -  Mong Tien
        std::string getSoHieu() const; 
        int getSoCho() const; 

        void xuat() const; 

        //Destructor
        // ~MayBay(); 
}; 

#endif
