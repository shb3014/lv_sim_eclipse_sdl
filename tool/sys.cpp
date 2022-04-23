//
// Created by sungaoran on 2022/4/23.
//

#include "sys.h"
#include "sstream"
#include "iomanip"

std::string double_to_string(double value, int precision) {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(precision) << value;
    return stream.str();
}
