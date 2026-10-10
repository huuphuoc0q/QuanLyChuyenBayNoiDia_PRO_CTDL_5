#include "../include/Ve.h"
// std::string maVe_, maChuyenBay_;
// KhachHang khachHang_; 
// int soGhe_; 
//Constructor - Minh Tien 
// Ve::Ve(){
//     maVe_ = "";
//     maChuyenBay_ = "";
//     cb_ = nullptr; ;
//     soGhe_ = -1; 
//     khachHang_ = KhachHang(); 
// }
// Ve::Ve(std::string maVe, std::string maChuyenBay,ChuyenBay* cb, int soGhe, KhachHang khachHang){
//     maVe_ = maVe;
//     maChuyenBay_ = maChuyenBay;
//     cb_ = cb; 
//     soGhe_ = soGhe; 
//     khachHang_ = khachHang; 
// } 

//Getter/ Setter - Mong Tien
// std::string Ve::getMaVe() const {
//     return maVe_; 
// }
// KhachHang Ve::getKhachHang() const {
//     return khachHang_; 
// }
// int Ve::getSoGhe() const {
//     return soGhe_; 
// } 
// std::string Ve::getMaCB() const {
//     return maChuyenBay_; 
// }
// ChuyenBay* Ve::getCB() const {
//     return cb_; 
// }

//Xuat xu ly
void Ve::xuat() const {
    std::cout<<"Ma ve: "<<maVe_<<" Ma Chuyen Bay: "<<maChuyenBay_<<" So ghe "<<soGhe_ + 1<<" KH: "<<khachHang_.getName()<<std::endl;
}