from conans import ConanFile, CMake, tools

class ImGuiGlfwConan(ConanFile):
    name = "imgui-glfw"
    version = "0.5.2"
    license = "MIT"
    url = "https://github/com/nkoturovic"
    description = "ImGui GLFW"

    settings = "os", "compiler", "arch", "build_type"
    generators = "cmake"
    exports_sources = "CMakeLists.txt", "LICENSE"

    requires = "imgui/[>=1.79]", "glfw/[>=3.3.2]"

    def source(self):
        tools.download("https://raw.githubusercontent.com/ocornut/imgui/master/backends/imgui_impl_glfw.h", "imgui_impl_glfw.h")
        tools.download("https://raw.githubusercontent.com/ocornut/imgui/master/backends/imgui_impl_glfw.cpp", "imgui_impl_glfw.cpp")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        self.copy("*.h", dst="include", keep_path=True)
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.includedirs = ["include"]
        self.cpp_info.libs = ["imgui-glfw"]
