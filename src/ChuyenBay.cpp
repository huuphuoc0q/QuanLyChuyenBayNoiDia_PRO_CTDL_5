#include "../include/ChuyenBay.h"
#include<iostream>
#include<string>
#include "../include/LinkedList.h"


ChuyenBay::ChuyenBay() {
    maChuyenBay_ = "";
    mbCB_ = nullptr;
    soHieuMayBay_ = "";
    ngayKhoiHanh_ = "";
    sanBayDen_ = "";
    trangThai_ = -1;
}

ChuyenBay::ChuyenBay(const std::string& maCB_, MayBay* mbChuyenBay_, const std::string& soHieuMB_, 
const std::string& ngayKH_, const std::string& sanBD_, const int& status_) {
    maChuyenBay_ = maCB_;
    mbCB_ = mbChuyenBay_;
    soHieuMayBay_ = soHieuMB_;
    ngayKhoiHanh_ = ngayKH_;
    sanBayDen_ = sanBD_;
    trangThai_ = status_;
}


//getter/setter - Mong Tien
std::string  ChuyenBay::getMaCB() const {
    return maChuyenBay_;
}
std::string ChuyenBay::getSoHieuMB() const{
    return soHieuMayBay_;
} 
std::string ChuyenBay::getNgayKH() const{
    return ngayKhoiHanh_;
} 
std::string ChuyenBay::getSanBD() const {
    return sanBayDen_;
}
int ChuyenBay::getStatus() const {
    return trangThai_;
}

std::vector<int> ChuyenBay::getDSGheTrong() const{
    return dsGheTrong_; 
}

std::vector<Ve> ChuyenBay::getDSVe() const{
    return dsVe_; 
}

int ChuyenBay::getSoLuongGheTrong() const {
    return soLuongGheTrong_; 
}

MayBay* ChuyenBay::getMB() const {
    return mbCB_; 
}

void ChuyenBay::setStatus(int newStatus_){
    trangThai_ = newStatus_; 
}

//Ham xu ly
void ChuyenBay::xuat() const { 
    std::cout<<"Thong tin chuyen bay "<<maChuyenBay_<<std::endl; 
    std::cout<<"So hieu May Bay: "<<soHieuMayBay_<<std::endl; 
    std::cout<<"Ngay khoi hanh: "<<ngayKhoiHanh_<<std::endl; 
    std::cout<<"San Bay Den: "<<sanBayDen_<<std::endl; 
    std::cout<<"Trang thai: "<<trangThai_<<std::endl; 
    std::cout<<"------------------------------------"<<std::endl; 
}

void ChuyenBay::khoiTaoGheTrong(int soCho_, int val) {
    dsGheTrong_.assign(soCho_, val); 
    if(val == 0) soLuongGheTrong_ = soCho_; 
    else soLuongGheTrong_ = 0; 
}

bool ChuyenBay::kiemtraGheTrong(int idGhe_) const{
    return dsGheTrong_[idGhe_] == 0; 
}

bool ChuyenBay::dayVe() const {
    return (soLuongGheTrong_ == 0);
}

void ChuyenBay::xoaGheTrong(int idGhe_){
    dsGheTrong_[idGhe_] = 1; 
    soLuongGheTrong_--; 
}
void ChuyenBay::themGheTrong(int idGhe_) {
    dsGheTrong_[idGhe_]  = 0; 
    soLuongGheTrong_++; 
}
void ChuyenBay::themVe(const Ve& ve_){
    dsVe_.push_back(ve_); 
    xoaGheTrong(ve_.getSoGhe());
}

void ChuyenBay::xoaVe( const std::string& maVe_){
    int idx = -1;
    for(int i = 0; i<dsVe_.size(); i++){
        if (dsVe_[i].getMaVe() == maVe_) {
            idx = i; 
            break; 
        }
    }
    if(idx == -1) return; 
    themGheTrong(dsVe_[idx].getSoGhe());
    dsVe_.erase(dsVe_.begin() + idx);
}

bool ChuyenBay::operator<(const ChuyenBay& other) const {
    return maChuyenBay_ < other.maChuyenBay_; 
}

bool ChuyenBay::operator==(const ChuyenBay& other) const { 
    return maChuyenBay_ == other.maChuyenBay_; 
}

bool ChuyenBay::operator>(const ChuyenBay& other) const {
    return maChuyenBay_ > other.maChuyenBay_;
}


std::ostream& operator<<(std::ostream& os, const ChuyenBay& cb) {
    std::string textStatus_ = "";
    switch(cb.trangThai_){
        case 0: 
            textStatus_ = "Huy chuyen";
            break;
        case 1:
            textStatus_ = "Con ve";
            break;
        case 2: 
            textStatus_ = "Het ve";
            break;
        case 3:
            textStatus_ = "Hoan tat";
            break;
        default: 
            break;
    }
    std::string colorCode = "\033[0m"; // Mặc định reset

    if (textStatus_ == "Huy chuyen") {
        colorCode = "\033[41;37m"; // Nền Đỏ, chữ Trắng
    } else if (textStatus_ == "Con ve") {
        colorCode = "\033[42;30m"; // Nền Xanh lá, chữ Đen
    } else if (textStatus_ == "Het ve") {
        colorCode = "\033[43;30m"; // Nền Vàng, chữ Đen
    } else if (textStatus_ == "Hoan tat") {
        colorCode = "\033[44;37m"; // Nền Xanh dương, chữ Trắng
    }

    std::string resetCode = "\033[0m";
    std::string textDSVe_ = ""; 
    for(auto i: cb.dsVe_){
        textDSVe_ += (i.getMaVe() + " "); 
    }
    // 2. Chèn colorCode ở ĐẦU và resetCode ở CUỐI lệnh in
    os << colorCode
    << std::setw(16) << cb.maChuyenBay_
    << std::setw(22) << cb.ngayKhoiHanh_
    << std::setw(15) << cb.sanBayDen_
    << std::setw(15) << textStatus_
    << std::setw(15) << textDSVe_
    << resetCode;
    return os;
}