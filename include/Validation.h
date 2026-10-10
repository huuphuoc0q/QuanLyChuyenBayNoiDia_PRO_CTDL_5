#ifndef VALIDATION_H
#define VALIDATION_H

#include <string>

namespace Validation {

    bool empty(const std::string& s);

    bool validCMND(const std::string& cmnd);

    std::string trimAndStandardizeSpace(const std::string& s);

    std::string toUpperCase(std::string s);

    bool validSoHieuMB(const std::string& soHieuMB);

}

#endif
