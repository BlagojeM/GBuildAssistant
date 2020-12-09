// Modified version of example:
// https://learnopengl.com/code_viewer_gh.php?code=src/1.getting_started/2.2.hello_triangle_indexed/hello_triangle_indexed.cpp

#include <cstdlib>
#include <string_view>
#include <chrono>

#include "fmt/format.h"
#include "spdlog/spdlog.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

void die(std::string_view msg) {
    spdlog::error(msg);
    exit(EXIT_FAILURE);
}

int main() {
    glfwInit();
    // Hint to use GLES 3.0 instead of OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    GLFWwindow* window = glfwCreateWindow(800, 600, "Triangles", nullptr, nullptr);
    if (window == nullptr) {
        glfwTerminate();
        die("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* /*win*/, int width, int height) {
        glViewport(0, 0, width, height);
    });

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        die("Failed to initialize GLAD");

    const GLubyte * version = glGetString(GL_VERSION);
    spdlog::warn("{}\n", version);

    constexpr const char* vertex_shader_source =
        "#version 300 es\n"
        "layout (location = 0) in mediump vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    constexpr const char* fragment_shader_source =
        "#version 300 es\n"
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
    int success;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(vertex_shader, 512, nullptr, infoLog);
        die(fmt::format("VERTEX SHADER COMPILATION FAILED\n{}\n", infoLog));
    }
    // fragment shader
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, nullptr);
    glCompileShader(fragment_shader);
    // check for shader compile errors
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(fragment_shader, 512, nullptr, infoLog);
        die(fmt::format("FRAGMENT SHADER COMPILATION FAILED\n{}\n", infoLog));
    }
    // link shaders
    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    // check for linking errors
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shader_program, 512, nullptr, infoLog);
        die(fmt::format("SHADER VERTEX COMPILATION FAILED\n{}\n", infoLog));
    }
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    float vertices[] = {
        -0.75f, -0.75f, 0.0f, // bottom-left
        -0.75f, 0.75f, 0.0f,  // top-left
         0.0f, 0.0f, 0.0f,    // middle
         0.75f, -0.75f, 0.0f, // bottom-right
         0.75f, 0.75f, 0.0f,  // top-right
    };
    unsigned int indices[] = {
        0, 1, 2,  // triangle1
        2, 3, 4,  // triangle2
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    auto curr_time = std::chrono::system_clock::now(), prev_time = curr_time;
    int frame_count = 0;
    glfwSwapInterval(0); // assert swap interval is not binded to 60 fps
    spdlog::info("Entering render LOOP");
    while (!glfwWindowShouldClose(window)) {
        // input
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

       // Calculate FPS to display every 1s
        curr_time = std::chrono::system_clock::now();
        frame_count++;
        if (curr_time - prev_time >= std::chrono::seconds(1)) {
            spdlog::info("Frames per second: {}", frame_count);
            frame_count = 0;
            prev_time = curr_time;
        }

        glClear(GL_COLOR_BUFFER_BIT);
        // Drawing two trangles
        glUseProgram(shader_program);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shader_program);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    spdlog::info("Terminating program");
    glfwTerminate();

    return 0;
}
