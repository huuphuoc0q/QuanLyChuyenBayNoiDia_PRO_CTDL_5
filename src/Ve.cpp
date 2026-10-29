#include "../include/Ve.h"

//Constructor - Minh Tien 
Ve::Ve(){
    maVe_ = "";
    maChuyenBay_ = "";
    cb_ = nullptr;
    soGhe_ = -1; 
    khachHang_ = KhachHang(); 
}
Ve::Ve(std::string maVe, std::string maChuyenBay,ChuyenBay* cb, int soGhe, KhachHang khachHang){
    maVe_ = maVe;
    maChuyenBay_ = maChuyenBay;
    cb_ = cb; 
    soGhe_ = soGhe; 
    khachHang_ = khachHang; 
} 

//Getter/ Setter - Mong Tien
std::string Ve::getMaVe() const {
    return maVe_; 
}
KhachHang Ve::getKhachHang() const {
    return khachHang_; 
}
int Ve::getSoGhe() const {
    return soGhe_; 
} 
std::string Ve::getMaCB() const {
    return maChuyenBay_; 
}
ChuyenBay* Ve::getCB() const {
    return cb_; 
}

//Xuat xu ly
void Ve::xuat() const {
    std::cout<<"Ma ve: "<<maVe_
    <<" Ma Chuyen Bay: "<<maChuyenBay_
    <<" So ghe "<<soGhe_ + 1
    <<" KH: "<<khachHang_.getName()
    <<" CMND: "<<khachHang_.getCmnd()<<std::endl;
}

std::ostream& operator<<(std::ostream& out, const Ve& p){
    out<<"Ma ve: "<<p.maVe_<<" Ma Chuyen Bay: "<<p.maChuyenBay_<<" So ghe "<<p.soGhe_ + 1<<" KH: "<<p.khachHang_.getName()<<std::endl;
    return out; 
}

bool Ve::operator==(const Ve& other) const {
    return maVe_ == other.maVe_; 
}

bool Ve::operator!=(const Ve& other) const {
    return !(*this==other); 
}
