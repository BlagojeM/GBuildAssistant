// Modified version of example:
// https://learnopengl.com/code_viewer_gh.php?code=src/1.getting_started/2.2.hello_triangle_indexed/hello_triangle_indexed.cpp

/* Enable including glfw/glad headers in any order */
#define GLFW_INCLUDE_NONE

#include <array>
#include <chrono>
#include <cstdlib>
#include <string>
#include <string_view>

#include <GLFW/glfw3.h>
#include <fmt/format.h>
#include <glad/glad.h>
#include <spdlog/spdlog.h>

constexpr unsigned msg_len      = 512U;
constexpr unsigned screen_width = 800U, screen_height = 600U;

void die(std::string_view msg)
{
    spdlog::error(msg);
    exit(EXIT_FAILURE);
}

template<typename T, std::size_t N>
std::size_t sizeof_array_data(const std::array<T, N> &arr)
{
    return arr.size() * sizeof(T);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    GLFWwindow *window =
      glfwCreateWindow(screen_width, screen_height, "Triangles", nullptr, nullptr);
    if (window == nullptr) {
        glfwTerminate();
        die("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(
      window, [](GLFWwindow * /*win*/, int width, int height) { glViewport(0, 0, width, height); });

    // glad: load all OpenGL function pointers
    if (!static_cast<bool>(gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))) {
        die("Failed to initialize GLAD");
    }

    const GLubyte *version = glGetString(GL_VERSION);
    spdlog::warn("{}\n", version);

    constexpr const char *vertex_shader_source =
      "#version 330 core\n"
      "layout (location = 0) in mediump vec3 aPos;\n"
      "void main()\n"
      "{\n"
      "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
      "}\0";

    constexpr const char *fragment_shader_source =
      "#version 330 core\n"
      "out mediump vec4 FragColor;\n"
      "void main()\n"
      "{\n"
      "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
      "}\n\0";

    // build and compile our shader program
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, nullptr);
    glCompileShader(vertex_shader);
    // check for shader compile errors
    int success{ 0 };
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!static_cast<bool>(success)) {
        std::array<char, msg_len> info_log{};
        glGetShaderInfoLog(vertex_shader, msg_len, nullptr, info_log.data());
        die(fmt::format("VERTEX SHADER COMPILATION FAILED\n{}\n", info_log.data()));
    }
    // fragment shader
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, nullptr);
    glCompileShader(fragment_shader);
    // check for shader compile errors
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!static_cast<bool>(success)) {
        std::array<char, msg_len> info_log{};
        glGetShaderInfoLog(fragment_shader, msg_len, nullptr, info_log.data());
        die(fmt::format("FRAGMENT SHADER COMPILATION FAILED\n{}\n", info_log.data()));
    }
    // link shaders
    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    // check for linking errors
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!static_cast<bool>(success)) {
        std::array<char, msg_len> info_log{};
        glGetProgramInfoLog(shader_program, msg_len, nullptr, info_log.data());
        die(fmt::format("SHADER VERTEX COMPILATION FAILED\n{}\n", info_log.data()));
    }
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    constexpr std::array vertices{
        -0.75F, -0.75F,
        0.0F, // bottom-left
        -0.75F, 0.75F,
        0.0F, // top-left
        0.0F, 0.0F,
        0.0F, // middle
        0.75F, -0.75F,
        0.0F, // bottom-right
        0.75F, 0.75F,
        0.0F, // top-right
    };
    constexpr std::array indices{
        0U, 1U,
        2U, // triangle1
        2U, 3U,
        4U, // triangle2
    };

    unsigned vbo{ 0U };
    unsigned vao{ 0U };
    unsigned ebo{ 0U };
    glGenVertexArrays(1U, &vao);
    glGenBuffers(1U, &vbo);
    glGenBuffers(1U, &ebo);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,
      static_cast<GLsizei>(sizeof_array_data(vertices)),
      vertices.data(),
      GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
      static_cast<GLsizei>(sizeof_array_data(indices)),
      indices.data(),
      GL_STATIC_DRAW);

    glVertexAttribPointer(0U, 3, GL_FLOAT, GL_FALSE, 3U * sizeof(float), nullptr);
    glEnableVertexAttribArray(0U);

    glBindBuffer(GL_ARRAY_BUFFER, 0U);
    glBindVertexArray(0U);
    glClearColor(0.2F, 0.3F, 0.3F, 1.0F);

    auto curr_time       = std::chrono::system_clock::now();
    auto prev_time       = curr_time;
    unsigned frame_count = 0U;
    glfwSwapInterval(0); // assert swap interval is not binded to 60 fps
    spdlog::info("Entering render LOOP");
    while (!static_cast<bool>(glfwWindowShouldClose(window))) {
        // input
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, 1);
        }

        // Calculate FPS to display every 1s
        curr_time = std::chrono::system_clock::now();
        frame_count++;
        if ((curr_time - prev_time) >= std::chrono::seconds(1)) {
            spdlog::info("Frames per second: {}", frame_count);
            frame_count = 0U;
            prev_time   = curr_time;
        }

        glClear(GL_COLOR_BUFFER_BIT);
        // Drawing two trangles
        glUseProgram(shader_program);
        glBindVertexArray(vao); // seeing as we only have a single VAO there's no need to bind it
                                // every time, but we'll do so to keep things a bit more organized
        glDrawElements(GL_TRIANGLES, 6U, GL_UNSIGNED_INT, nullptr);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1U, &vao);
    glDeleteBuffers(1U, &vbo);
    glDeleteBuffers(1U, &ebo);
    glDeleteProgram(shader_program);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    spdlog::info("Terminating program");
    glfwTerminate();

    return 0;
}
