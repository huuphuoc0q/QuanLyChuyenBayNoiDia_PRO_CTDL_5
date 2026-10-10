#ifndef THONGKE_H
#define THONGKE_
#include "../include/KhachHang.h"
#include "../include/ChuyenBay.h"
#include <iostream>
#include <vector>
#include <string>


namespace ThongKe{
    void displayKHChuyenBay(ChuyenBay* dsChuyenBay_, int sizeDSChuyenBay_);
    void displayDSGheTrong(ChuyenBay* dsChuyenBay_, int sizeDSChuyenBay_);
    void displaySLChuyenBay(MayBay* dsMayBay_, int sizeDSMayBay_, ChuyenBay* dsChuyenBay_, int sizeDSChuyenBay_);
}

#endif 