
#include <neko/gui/real_window.hpp>
using namespace neko;

int main(){

    gui::RealWindow window ({400, 200});
    for (;;){
        window.Draw();
    }
}
