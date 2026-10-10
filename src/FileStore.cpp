#include "FileStore.h"
#include<string>
#include<iostream>
#include<fstream>
#include<vector>


void FileStore::loadMayBay(MayBay* dsMayBay, int& sizeDSMayBay) {
    std::ifstream fi("data/MayBay.txt"); 
    sizeDSMayBay = 0; 
    std::string tmpSoHieu_ = "";
    int tmpSoCho_ = 0; 
    while(fi>>tmpSoHieu_ >> tmpSoCho_){
        dsMayBay[sizeDSMayBay++] = MayBay(tmpSoHieu_, tmpSoCho_); 
    }
    fi.close(); 
}

void FileStore::loadChuyenBay(ChuyenBay* dsChuyenBay, int& sizeDSChuyenBay, MayBay* dsMayBay, int& sizeDSMayBay) {
    std::ifstream fi("data/ChuyenBay.txt");
    
    sizeDSChuyenBay = 0; 
    std::string maCB = "";
    std::string soHieu = "";
    std::string ngay = "";
    std::string sanDen = "";
    int st = 0; 

    while(fi>>maCB>>soHieu>>ngay>>sanDen>>st) {
        int ranDomST = rand() % 4 + 1; 
        MayBay* mbCB = nullptr;
        for(int i = 0; i<sizeDSMayBay; i++){
            if(dsMayBay[i].getSoHieu() == soHieu){
                mbCB = &dsMayBay[i]; 
                break; 
            }
        } 
        dsChuyenBay[sizeDSChuyenBay++] = ChuyenBay(maCB,mbCB, soHieu, ngay, sanDen, ranDomST - 1);
        ChuyenBay& cbHienTai = dsChuyenBay[sizeDSChuyenBay - 1];
        if (mbCB == nullptr) continue;  
        int soCho_ = mbCB->getSoCho();

        switch(ranDomST - 1){
            case 0: //Huy chuyen
                break;
            case 1: { // Con ve 
                cbHienTai.khoiTaoGheTrong(soCho_, 0);
                for(int i = 0; i<soCho_/2; i++){
                    int ranDomSoGhe_ = rand() % soCho_ + 1; 
                    cbHienTai.xoaGheTrong(ranDomSoGhe_-1);
                }
                break; 
            }
            case 2: //Het ve
                {
                    cbHienTai.khoiTaoGheTrong(soCho_, 1);
                    break;
                }
            case 3: //Hoan tat
                break;
            default: 
                break;
        }
    }
    fi.close(); 
}

void FileStore::loadKhachHang(std::vector<KhachHang> dsKhachHang, int& sizeKhachHang) {
    std::ifstream fi("data/KhachHang.txt"); 
    sizeKhachHang = 0; 
    int stt = 0; 
    std::string cmnd = "";
    std::string name = "";
    while(fi>>stt>>name>>cmnd){
        dsKhachHang.push_back(KhachHang(stt, name, cmnd)); 
        sizeKhachHang++; 
    }

    fi.close(); 
}

// void FileStore::loadVe(std::vector<Ve> dsVe,int& sizeDSVe_){
//     std::ifstream fi("data/Ve.txt"); 
//     sizeDSVe_ = 0; 
    
//     std::string maVe = "";
//     int soGhe;
//     while(fi>>maVe>>soGhe){
//         dsVe.push_back(Ve(sizeDSVe_+1, )); 
//         sizeDSVe_++; 
//     }
//     fi.close(); 
// }

void FileStore::luuThongTinKH(const KhachHang& khachHang_) {
    std::ofstream fo("data/KhachHang.txt", std::ios::app); 
    fo<<khachHang_.getStt()<<" "<<khachHang_.getName()<<" "<<khachHang_.getCmnd()<<std::endl;
    fo.close(); 
}

void FileStore::luuVe(std::vector<Ve> DSVe_) {
    std::ofstream fo("data/Ve.txt"); 
    for(int i=0;i<DSVe_.size(); i++)
        fo<<DSVe_[i].getMaVe()<<" "<<DSVe_[i].getSoGhe()<<" "<<
            "["<<DSVe_[i].getKhachHang().getStt()<<" "<<
            DSVe_[i].getKhachHang().getName()<<" "<<
            DSVe_[i].getKhachHang().getCmnd()<<"]"<<std::endl;
    fo.close(); 
}


void FileStore::loadTaiKhoanAdmin(std::string& user, std::string& pass){
    std::ifstream fi("data/Admin.txt"); 
    fi>>user>>pass; 
    fi.close(); 
}