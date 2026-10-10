#include "../include/KhachHang.h"
#include <iostream> 
#include <string> 
//Constructor - Minh Tien
// KhachHang::KhachHang(){
//     stt_ = -1; 
//     cmnd_ = "";
//     name_ = "";
// }

// KhachHang::KhachHang(int& stt, const std::string name, const std::string cmnd){
//     stt_ = stt; 
//     cmnd_ = cmnd; 
//     name_ = name; 
// }

//Getter/ setter - Mong Tien
// std::string KhachHang::getCmnd() const {
//     return cmnd_; 
// };
// std::string KhachHang::getName() const {
//     return name_; 
// } 
// int KhachHang::getStt() const{
//     return stt_; 
// }


//Ham Xu Ly
void KhachHang::xuat() const{ 
    std::cout<<stt_<<" Ho va ten: "<<name_<<" CMND: "<<cmnd_<<std::endl; 
}