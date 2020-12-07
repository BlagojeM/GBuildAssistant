from conans import ConanFile, CMake

class GBuildAssistant(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = "fmt/7.1.2", "spdlog/1.8.1", "glad/0.1.34", "glfw/3.3.2"
    generators = "cmake", "virtualenv"
    # default_options = {"poco:shared": True, "openssl:shared": True}

    def package_info(self):
     self.env_info.CONAN_SYSREQUIRES_MODE = "enabled"

    def build(self):
        self.env_info.CONAN_SYSREQUIRES_MODE = "enabled"
        # tools.enviroment_append({"CONAN_SYSREQUIRES_MODE" : "enabled"})
        # print("HERE!!!!!!!!!: ", env_vars)
        # env_vars = tools.vcvars_dict(self)
        # print("HERE!!!!!!!!!: ", env_vars)

        # with tools.environment_append(env_vars):
        #     pass

        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        # cmake.test() # Build the "RUN_TESTS" or "test" target
