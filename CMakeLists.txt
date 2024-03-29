cmake_minimum_required(VERSION 3.27)
project(SimpleGUI)

set(CMAKE_CXX_STANDARD 17)

add_executable(SimpleGUI
        main.cpp
        Actions/BrowserSrc/Browser/Browser.cpp
        Actions/BrowserSrc/Browser/Browser.h
        Actions/ActionSrc/Action/Action.cpp
        Actions/ActionSrc/Action/Action.h
        Actions/BrowserSrc/BrowserAction/BrowserAction.cpp
        Actions/BrowserSrc/BrowserAction/BrowserAction.h
        Actions/ExeSrc/Exe/Exe.cpp
        Actions/ExeSrc/Exe/Exe.h
        Actions/ExeSrc/ExeAction/ExeAction.cpp
        Actions/ExeSrc/ExeAction/ExeAction.h
        Api/KeyboardSrc/Keyboard/Keyboard.cpp
        Api/KeyboardSrc/Keyboard/Keyboard.h
        Api/MouseSrc/Mouse/Mouse.cpp
        Api/MouseSrc/Mouse/Mouse.h
        Api/ScreenSrc/Screen/Screen.cpp
        Api/ScreenSrc/Screen/Screen.h
        Api/KeyboardSrc/Mappers/Mapper/Mapper.cpp
        Api/KeyboardSrc/Mappers/Mapper/Mapper.h
        Api/KeyboardSrc/Mappers/MixedMapper/MixedMapper.cpp
        Api/KeyboardSrc/Mappers/MixedMapper/MixedMapper.h
        Utils/Json/JsonUtil.cpp
        Utils/Json/JsonUtil.h
        Api/BindSrc/Bind/Bind.cpp
        Api/BindSrc/Bind/Bind.h
        Actions/TextSrc/Text/Text.cpp
        Actions/TextSrc/Text/Text.h
        Actions/TextSrc/TextAction/TextAction.cpp
        Actions/TextSrc/TextAction/TextAction.h

)

include_directories(${CMAKE_SOURCE_DIR})

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(SimpleGUI PRIVATE nlohmann_json::nlohmann_json)