#ifndef GBA_APP_HPP
#define GBA_APP_HPP
#include <string_view>

namespace gba {

struct AppParams
{
    std::string_view window_name = "GBuildAssistant App";
    int window_width             = 800;
    int window_height            = 600;
};

class App
{
  public:
    App(AppParams params);
    static void run();
    ~App();
};

} // namespace gba

#endif
