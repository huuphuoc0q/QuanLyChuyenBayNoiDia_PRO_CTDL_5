#ifndef THONGKE_H
#define THONGKE_H
#include "../include/KhachHang.h"
#include "../include/ChuyenBay.h"
#include "../include/Validation.h"
#include "../include/BST.h"
#include <iostream>
#include <vector>
#include <string>


namespace ThongKe{
    void displayKHChuyenBay(Tree<ChuyenBay>& dsChuyenBay_, int sizeDSChuyenBay_);
    void displayDSGheTrong(Tree<ChuyenBay>& dsChuyenBay_, int sizeDSChuyenBay_);
    void displaySLChuyenBay(MayBay* dsMayBay_, int sizeDSMayBay_, std::vector<ChuyenBay*>& dsCB_, int sizeDSChuyenBay_);
}

#endif 