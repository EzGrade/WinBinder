//
// Created by abore on 14.02.2024.
//

#ifndef SIMPLEGUI_JSONUTIL_H
#define SIMPLEGUI_JSONUTIL_H

#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"
#include <vector>

using json = nlohmann::json;

class JsonUtil {
private:
public:
    static json read(const std::string &path);

    static int write(const std::string &path, const std::string &content);

};


#endif //SIMPLEGUI_JSONUTIL_H
