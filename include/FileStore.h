#ifndef FILESTORE_H
#define FILESTORE_H

#include<fstream>
#include<string>
#include<iostream>
#include "MayBay.h"
#include "ChuyenBay.h"
#include "KhachHang.h"
#include "Ve.h"


namespace FileStore {
    void loadMayBay(MayBay* dsMayBay, int& sizeMayBay_) ;
    void loadChuyenBay(ChuyenBay* dsChuyenBay, int& sizeDSChuyenBay, MayBay* dsMayBay, int& sizeDSMayBay);
    void loadKhachHang( std::vector<KhachHang> dsKhachHang, int& sizeKhachHang_);
    void loadVe(std::vector<Ve> dsVe, int& sizeDSVe_);

    void luuThongTinKH(const KhachHang& khachHang_);  
    void luuVe(std::vector<Ve> dsVe);

    void loadTaiKhoanAdmin(std::string& user, std::string& pass); 
}



#endif