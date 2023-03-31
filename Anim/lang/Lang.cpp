//
// Created by Gordon on 2023/2/17.
//
#include "Lang.h"

template<>
std::string toString<std::string>(std::string value) {
    return value;
};