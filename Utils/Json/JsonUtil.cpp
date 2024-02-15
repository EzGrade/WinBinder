#include "JsonUtil.h"

json JsonUtil::read(const std::string &path) {
    std::ifstream file(path);
    json j;
    file >> j;
    return j;
}