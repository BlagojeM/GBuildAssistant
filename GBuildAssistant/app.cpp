#include "gba/app.hpp"
#include "gba/debug.hpp"

#include <fmt/format.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

template <typename T, std::size_t N>
std::size_t sizeof_array_data(const std::array<T,N> &arr) {
    return arr.size() * sizeof(T);
}

static GLFWwindow * window = nullptr;
static GLuint shader_program = 0;
static unsigned VBO{0u}, VAO{0u}, EBO{0u};
static const char * glsl_version = "#version 330 core";

namespace gba {
App::App(AppParams params) {
    constexpr unsigned msg_len = 512u;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    window = glfwCreateWindow(params.window_height, params.window_height, "Triangles", nullptr, nullptr);
    if (window == nullptr) {
        glfwTerminate();
        gba::die("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* /*win*/, int width, int height) {
        glViewport(0, 0, width, height);
    });

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        gba::die("Failed to initialize GLAD");

    const GLubyte * version = glGetString(GL_VERSION);
    gba::warn("{}\n", version);

    constexpr const char* vertex_shader_source =
        "#version 330 core\n"
        "layout (location = 0) in mediump vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    constexpr const char* fragment_shader_source =
        "#version 330 core\n"
        "out mediump vec4 FragColor;\n"
        "uniform mediump vec3 triangles_color;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(triangles_color, 1.0f);\n"
        "}\n\0";

    // build and compile our shader program
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, nullptr);
    glCompileShader(vertex_shader);
    // check for shader compile errors
    int success{0};
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        std::array<char, msg_len> infoLog{};
        glGetShaderInfoLog(vertex_shader, msg_len, nullptr, infoLog.data());
        gba::die(fmt::format("VERTEX SHADER COMPILATION FAILED\n{}\n", infoLog.data()));
    }
    // fragment shader
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, nullptr);
    glCompileShader(fragment_shader);
    // check for shader compile errors
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        std::array<char, msg_len> infoLog{};
        glGetShaderInfoLog(fragment_shader, msg_len, nullptr, infoLog.data());
        gba::die(fmt::format("FRAGMENT SHADER COMPILATION FAILED\n{}\n", infoLog.data()));
    }
    // link shaders
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    // check for linking errors
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        std::array<char, msg_len> infoLog{};
        glGetProgramInfoLog(shader_program, msg_len, nullptr, infoLog.data());
        gba::die(fmt::format("SHADER VERTEX COMPILATION FAILED\n{}\n", infoLog.data()));
    }
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    constexpr std::array vertices {
        -0.75f, -0.75f, 0.0f, // bottom-left
        -0.75f, 0.75f, 0.0f,  // top-left
         0.0f, 0.0f, 0.0f,    // middle
         0.75f, -0.75f, 0.0f, // bottom-right
         0.75f, 0.75f, 0.0f,  // top-right
    };
    constexpr std::array indices {
        0u, 1u, 2u,  // triangle1
        2u, 3u, 4u,  // triangle2
    };

    glGenVertexArrays(1u, &VAO);
    glGenBuffers(1u, &VBO);
    glGenBuffers(1u, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,
            static_cast<GLsizei>(sizeof_array_data(vertices)), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
            static_cast<GLsizei>(sizeof_array_data(indices)), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0u, 3, GL_FLOAT, GL_FALSE, 3u * sizeof(float), nullptr);
    glEnableVertexAttribArray(0u);

    glBindBuffer(GL_ARRAY_BUFFER, 0u);
    glBindVertexArray(0u);
}

void App::run() {
    std::array triangles_color {1.0f, 0.5f, 0.2f};
    std::array bg_color {0.2f, 0.3f, 0.3f};
    glClearColor(bg_color[0], bg_color[1], bg_color[2], 1.0f);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);


    auto curr_time = std::chrono::system_clock::now(), prev_time = curr_time;
    long int fps = 0;
    glfwSwapInterval(0); // assert swap interval is not binded to 60 fps
    info("Entering render LOOP");
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        // feed inputs to dear imgui, start new frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::SetNextWindowPos({ 0, 0 }, ImGuiCond_Once);
        ImGui::SetNextWindowSize({ 400, 100 }, ImGuiCond_Once);
        ImGui::Begin("Controls");
        ImGui::Text("Rendering at %ld frames per second", fps);
        ImGui::ColorEdit3("Background color", bg_color.data());
        ImGui::ColorEdit3("Triangles color", triangles_color.data());
        ImGui::End();
        ImGui::Render();

        // Drawing two trangles
        glClearColor(bg_color[0], bg_color[1], bg_color[2], 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shader_program);

        int triangles_color_loc = glGetUniformLocation(shader_program, "triangles_color");
        glUniform3f(triangles_color_loc, triangles_color[0], triangles_color[1], triangles_color[2]);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6u, GL_UNSIGNED_INT, nullptr);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);

        curr_time = std::chrono::system_clock::now();
        fps = std::chrono::seconds(1)/(curr_time - prev_time);
        prev_time = curr_time;
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1u, &VAO);
    glDeleteBuffers(1u, &VBO);
    glDeleteBuffers(1u, &EBO);
    glDeleteProgram(shader_program);
}

App::~App() {
    // glfw: terminate, clearing all previously allocated GLFW resources.
    gba::warn("Terminating program");
    glfwTerminate();
}

}
