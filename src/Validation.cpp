#include "Validation.h"
#include <cctype>
#include <sstream>

namespace Validation {

    bool empty(const std::string& s) {
        if (s.empty()) {
            return true;
        }
        for (char c : s) {
            if (!std::isspace(static_cast<unsigned char>(c))) {
                return false;
            }
        }
        return true;
    }

    bool validCMND(const std::string& cmnd) {
        if (cmnd.length() != 12) {
            return false;
        }
        for (char c : cmnd) {
            if (!std::isdigit(static_cast<unsigned char>(c))) {
                return false;
            }
        }
        return true;
    }

    std::string trimAndStandardizeSpace(const std::string& s) {
        std::stringstream ss(s);
        std::string word;
        std::string kq = "";
        while (ss >> word) {
            if (!kq.empty()) {
                kq += " ";
            }
            kq += word;
        }
        return kq;
    }

    std::string toUpperCase(std::string s) {
        for (char& c : s) {
            c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
        }
        return s;
    }

    bool validSoHieuMB(const std::string& soHieuMB) {
        if (soHieuMB.empty()) {
            return false;
        }
        for (char c : soHieuMB) {
            if (!std::isalnum(static_cast<unsigned char>(c)) || c != '-') {
                return false;
            }
        }
        return true;
    }

}
