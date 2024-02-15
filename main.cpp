#include "Api/KeyboardSrc/Keyboard/Keyboard.h"
#include "Api/BindSrc/Bind/Bind.h"

int main() {
    Keyboard keyboard = Bind::setBinds();
    keyboard.keysLister();
};