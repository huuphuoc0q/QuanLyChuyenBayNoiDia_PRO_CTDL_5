#ifndef FILESTORE_H
#define FILESTORE_H

#include<fstream>
#include<string>
#include<cstdio>
#include<iostream>
#include<vector>

#include "MayBay.h"
#include "ChuyenBay.h"
#include "KhachHang.h"
#include "Ve.h"
#include "BST.h"
namespace FileStore {
    void loadMayBay(MayBay* dsMayBay, int& sizeMayBay_) ;
    void loadChuyenBay(Tree<ChuyenBay>& dsChuyenBay, int& sizeDSChuyenBay, MayBay* &dsMayBay, int& sizeDSMayBay);
    void loadKhachHang( std::vector<KhachHang>& dsKhachHang, int& sizeKhachHang_);

    void luuThongTinKH(const std::vector<Ve>& dsVe_);  
    void luuVe(std::vector<Ve>& dsVe);
    void xoaVe(std::string maVe_);
    void cleanVe(std::vector<Ve>& dsVe); 
    void loadTaiKhoanAdmin(std::string& user, std::string& pass); 
}



#endif