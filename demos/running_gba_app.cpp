#include "gba/app.hpp"

int main()
{

    gba::App app({ .window_width = 1024, .window_height = 768 });

    gba::App::run();

    return 0;
}
