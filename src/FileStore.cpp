#include "FileStore.h"

std::vector<KhachHang> dsKhachHang = {
    KhachHang(1, "Nguyen Minh Quan", "079204001234"),
    KhachHang(2, "Tran Thi Thanh Thao", "084305005678"),
    KhachHang(3, "Le Hoang Phuc", "001203009012"),
    KhachHang(4, "Pham Ngoc Mai Anh", "048304003456"),
    KhachHang(5, "Vo Quoc Bao", "092202007890")
};

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

void FileStore::loadChuyenBay(Tree<ChuyenBay>& dsChuyenBay, int& sizeDSChuyenBay, MayBay* &dsMayBay, int& sizeDSMayBay) {
    std::ifstream fi("data/ChuyenBay.txt");
    sizeDSChuyenBay = 0; 
    
    std::string maCB = "";
    std::string soHieu = "";
    std::string ngay = "";
    std::string sanDen = "";
    int st = 0; 

    while(fi>>maCB>>soHieu>>ngay>>sanDen>>st) {
        const int trangThai = rand() % 4;
        MayBay* mbCB = nullptr;
        for(int i = 0; i<sizeDSMayBay; i++){
            if(dsMayBay[i].getSoHieu() == soHieu){
                mbCB = &dsMayBay[i]; 
                break; 
            }
        } 
        ChuyenBay cbHienTai = ChuyenBay(maCB, mbCB, soHieu, ngay, sanDen, trangThai);
        if (mbCB == nullptr) continue;  
        int soCho_ = mbCB->getSoCho();
        cbHienTai.khoiTaoGheTrong(soCho_, 0);
        dsChuyenBay.insert(cbHienTai); 
        sizeDSChuyenBay++;

        if (trangThai == 0) continue;

        Node<ChuyenBay>* nodeCB = dsChuyenBay.search(cbHienTai);
        if (nodeCB == nullptr) continue;

        ChuyenBay& chuyenBayDaLuu = nodeCB->data_;
        const int soKhachMau = static_cast<int>(dsKhachHang.size()) < soCho_
            ? static_cast<int>(dsKhachHang.size())
            : soCho_;
        for (int i = 0; i < soKhachMau; ++i) {
            const int soGhe = i;
            Ve veMau(maCB + std::to_string(soGhe + 1), maCB, &chuyenBayDaLuu,
                     soGhe, dsKhachHang[i]);
            chuyenBayDaLuu.themVe(veMau);
        }

        if (trangThai == 2 || trangThai == 3) {
            for (int i = 0; i < soCho_; ++i) {
                if (chuyenBayDaLuu.kiemtraGheTrong(i)) {
                    chuyenBayDaLuu.xoaGheTrong(i);
                }
            }
        }
    }
    fi.close(); 
}

void FileStore::loadKhachHang(std::vector<KhachHang>& dsKhachHang, int& sizeKhachHang) {
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

void FileStore::luuThongTinKH(const std::vector<Ve>& dsVe_) {
    std::ofstream fo("data/KhachHang.txt", std::ios::out | std::ios::trunc); 
    for(int i = 0; i<dsVe_.size(); i++) {
        fo << dsVe_[i].getKhachHang().getStt()<< " "
        << dsVe_[i].getKhachHang().getName() <<" "
        << dsVe_[i].getKhachHang().getCmnd() <<" "
        << dsVe_[i].getMaVe() <<" "
        << dsVe_[i].getMaCB() <<" "
        << dsVe_[i].getSoGhe() + 1 <<" " <<std::endl;
    }
    fo.close(); 
}

void FileStore::luuVe(std::vector<Ve>& DSVe_) {
    for(int i=0;i<DSVe_.size(); i++){
        std::string nameVe_ = DSVe_[i].getMaVe();
        std::ofstream fo("data/DATA_VE/" + nameVe_ + ".txt",std::ios::out);  
            fo<<DSVe_[i].getMaVe()<<" "<<DSVe_[i].getSoGhe() + 1<<" "<<
                "["<<DSVe_[i].getKhachHang().getStt()<<" "<<
                DSVe_[i].getKhachHang().getName()<<" "<<
                DSVe_[i].getKhachHang().getCmnd()<<"]"<<std::endl;
        fo.close(); 
    }
}

void FileStore::xoaVe(std::string maVe_) {
    std::string duong_dan = "data/DATA_VE/" + maVe_ + ".txt";
    int tmp = std::remove(duong_dan.c_str());
}

void FileStore::cleanVe(std::vector<Ve>& dsVe){
    int sizeDSVe_ = dsVe.size();
    for(int i = 0; i<sizeDSVe_; i++) {
        xoaVe(dsVe[i].getMaVe());
    }
    std::ofstream("data/KhachHang.txt", std::ios::trunc);
}


void FileStore::loadTaiKhoanAdmin(std::string& user, std::string& pass){
    std::ifstream fi("data/Admin.txt"); 
    fi>>user>>pass; 
    fi.close(); 
}