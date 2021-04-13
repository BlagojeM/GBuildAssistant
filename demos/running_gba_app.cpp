#include "gba/app.hpp"

int main()
{

  gba::App app({ .window_width = 1024, .window_height = 768 });

  app.run();

  return 0;
}
