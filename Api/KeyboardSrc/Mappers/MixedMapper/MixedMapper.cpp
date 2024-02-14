//
// Created by abore on 14.02.2024.
//

#include "MixedMapper.h"
#include "../Mapper/Mapper.h"

std::vector<int> MixedMapper::mapMixed(const std::string &key) {
    std::vector<int> keys;
    if (key == "!") {
        keys.push_back(Mapper::mapKeys("lshift"));
        keys.push_back(Mapper::mapKeys("1"));
    } else if (key == "@") {
        keys.push_back(Mapper::mapKeys("lshift"));
        keys.push_back(Mapper::mapKeys("2"));
    } else if (key == "#") {
        keys.push_back(Mapper::mapKeys("lshift"));
        keys.push_back(Mapper::mapKeys("3"));
    } else if (key == "$") {
        keys.push_back(Mapper::mapKeys("lshift"));
        keys.push_back(Mapper::mapKeys("4"));
    } else if (key == "%") {
        keys.push_back(Mapper::mapKeys("lshift"));
        keys.push_back(Mapper::mapKeys("5"));
    } else if (key == "^") {
        keys.push_back(Mapper::mapKeys("lshift"));
        keys.push_back(Mapper::mapKeys("6"));
    } else if (key == "&") {
        keys.push_back(Mapper::mapKeys("lshift"));
        keys.push_back(Mapper::mapKeys("7"));
    } else if (key == "*") {
        keys.push_back(Mapper::mapKeys("lshift"));
        keys.push_back(Mapper::mapKeys("8"));
    } else if (key == "(") {
        keys.push_back(Mapper::mapKeys("lshift"));
        keys.push_back(Mapper::mapKeys("9"));
    } else if (key == ")") {
        keys.push_back(Mapper::mapKeys("lshift"));
        keys.push_back(Mapper::mapKeys("0"));
    } else if (key == "_") {
        keys.push_back(Mapper::mapKeys("lshift"));
        keys.push_back(Mapper::mapKeys("-"));
    } else if (key == "+") {
        keys.push_back(Mapper::mapKeys("lshift"));
        keys.push_back(Mapper::mapKeys("="));
    } else if (key == "{") {
        keys.push_back(Mapper::mapKeys("lshift"));
        keys.push_back(Mapper::mapKeys("["));
    } else if (key == "}") {
        keys.push_back(Mapper::mapKeys("lshift"));
        keys.push_back(Mapper::mapKeys("]"));
    } else if (key == "|") {
        keys.push_back(Mapper::mapKeys("lshift"));
        keys.push_back(Mapper::mapKeys("\\"));
    } else if (key == ":") {
        keys.push_back(Mapper::mapKeys("lshift"));
        keys.push_back(Mapper::mapKeys(";"));
    } else if (key == "\"") {
        keys.push_back(Mapper::mapKeys("lshift"));
        keys.push_back(Mapper::mapKeys("'"));
    } else if (key == "<") {
        keys.push_back(Mapper::mapKeys("lshift"));
        keys.push_back(Mapper::mapKeys(","));
    } else if (key == ">") {
        keys.push_back(Mapper::mapKeys("lshift"));
        keys.push_back(Mapper::mapKeys("."));
    } else if (key == "?") {
        keys.push_back(Mapper::mapKeys("lshift"));
        keys.push_back(Mapper::mapKeys("/"));
    }
    return keys;
}