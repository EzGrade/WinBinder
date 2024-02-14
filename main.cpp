#include <memory>
#include "Api/KeyboardSrc/Keyboard/Keyboard.h"
#include "Actions/BrowserSrc/BrowserAction/BrowserAction.h"

int main() {
    Keyboard keyboard;
    keyboard.setDelay(0);
    std::unique_ptr<Action> browser = std::make_unique<BrowserAction>("https://www.google.com");
    keyboard.addBindAction("ctrl+shift+o", browser.get());
    keyboard.keysLister();
};