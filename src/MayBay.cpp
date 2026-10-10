#include "MayBay.h"
#include<iostream>
#include<string> 


//Constructor - Minh Tien
// MayBay::MayBay(){
//     soHieu_ = ""; 
//     soCho_ = 0; 
// }

// MayBay::MayBay(const std::string& soHieu_, const int& soCho_) : soHieu_(soHieu_), soCho_(soCho_) {}; 

//Getter, Setter - Mong Tien
// std::string MayBay::getSoHieu() const{
//     return  soHieu_; 
// }

// int MayBay::getSoCho() const{ 
//     return soCho_; 
// }

//Ham xu ly
void MayBay::xuat() const { 
    std::cout<<"Ma so hieu: "<<soHieu_<<" - So luong cho ngoi la "<<soCho_<<std::endl;
}

// MayBay::~MayBay(){}; 