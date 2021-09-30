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

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

constexpr unsigned msg_len      = 512U;
constexpr unsigned screen_width = 800U, screen_height = 600U;

//  Log error messages and exit
void die(std::string_view msg)
{
    spdlog::error(msg);
    exit(EXIT_FAILURE);
}

//  Returns the size of any array in bytes
template<typename T, std::size_t N>
std::size_t sizeof_array_data(const std::array<T, N> &arr)
{
    return arr.size() * sizeof(T);
}

static unsigned int CompileShader(unsigned int type, const std::string &source)
{
    unsigned int id = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);

    glCompileShader(id);
    

    //  Error handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE) { 
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        glDeleteShader(id);
        die(message);
    }

    return id;
}

static unsigned int createShader(const std::string &vertexShader, const std::string &fragmentShader) 
{
    unsigned int program = glCreateProgram();
    unsigned int vs      = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs      = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);



    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}


int main()
{
    glfwInit();
    // Hint to use OpenGL 3.3
    // These are not platform specific
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    const char *glsl_version = "#version 330 core";

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif


    //  Creating a window
    GLFWwindow *window = glfwCreateWindow(screen_width, screen_height, "Transparent Cube", nullptr, nullptr);
    if (window == nullptr) {
        glfwTerminate();
        die("Failed to create GLFW window");
    }

    //  Make this window relevant
    glfwMakeContextCurrent(window);
    //  This lambda function is called on window resize
    glfwSetFramebufferSizeCallback(
      window, [](GLFWwindow * /*win*/, int width, int height) { glViewport(0, 0, width, height); });

    //  glad: load all OpenGL function pointers
    if (!static_cast<bool>(gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))) {
        die("Failed to initialize GLAD");
    }

    const GLubyte *version = glGetString(GL_VERSION);
    spdlog::info("{}\n", version);








    





       //  Shader is a program that is running on our GPU
    //  We are provaiding it as a string

    //  There are vertix and fragmet shaders
    //  There are more, but these are most important

    //  Vertix shaders:
    //  Tell OpenGl where to draw a vertex

    

    

    // Values that stay constant for the whole mesh.
    


        
    std::string vertexShader =
      "#version 330 core\n"
      "\n"
      "layout(location = 0) in vec3 vertexPosition_modelspace;\n"
      "\n"
      "uniform mat4 MVP;\n"
      "void main()\n"
      "{\n"
      "   gl_Position = MVP * vec4(vertexPosition_modelspace, 1);"
      "}\n";


    //  Fragment shaders:
    //  Runns for eatch pixel and decides what to do

    std::string fragmentShader =
      "#version 330 core\n"
      "\n"
      "layout(location = 0) out vec4 color;\n"
      "\n"
      "void main()\n"
      "{\n"
      "   color = vec4(1.0f, 0.5f, 0.2f, 0.5f);\n"
      "}\n";

    unsigned int shader = createShader(vertexShader, fragmentShader);
    glClearColor(0.2F, 0.3F, 0.3F, 1.0F);
    glUseProgram(shader);

    // izgleda da treba da se ukljuci perspektiva
    float positions[108] = { 
    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end

     1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end

     1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
     1.0f,-1.0f,-1.0f,

     1.0f, 1.0f,-1.0f,
     1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,

    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,

     1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,

    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
     1.0f,-1.0f, 1.0f,

     1.0f, 1.0f, 1.0f,
     1.0f,-1.0f,-1.0f,
     1.0f, 1.0f,-1.0f,

     1.0f,-1.0f,-1.0f,
     1.0f, 1.0f, 1.0f,
     1.0f,-1.0f, 1.0f,

     1.0f, 1.0f, 1.0f,
     1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,

     1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,

     1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
     1.0f,-1.0f, 1.0f

    };

    unsigned vao{ 0U };
    glGenVertexArrays(1U, &vao);

    glBindVertexArray(vao);
    //  possibly good docs
    //  docs.gl
    //  Data that will be stored in GPU
    unsigned int buffer = 0u;
    glGenBuffers(1, &buffer);
    //  We binded a buffer (selected) so this is the buffer that is affected by  glDrawArrays()
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 108 * sizeof(float), positions, GL_STATIC_DRAW);

    //  We need just 1 attribute because we have just position in positions, insted of textures, etc..
    //  Basicly we are telling OpenGL how our data is arranged
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);





    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    glm::mat4 Projection = glm::perspective(
      glm::radians(45.0f), (float)screen_width / (float)screen_height, 0.1f, 100.0f);

    // Or, for an ortho camera :
    // glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world
    // coordinates

    // Camera matrix
    glm::mat4 View = glm::lookAt(glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
      glm::vec3(0, 0, 0), // and looks at the origin
      glm::vec3(0, 1, 0) // Head is up (set to 0,-1,0 to look upside-down)
    );

    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model = glm::mat4(1.0f);
    // Our ModelViewProjection : multiplication of our 3 matrices
    glm::mat4 mvp =
      Projection * View * Model; // Remember, matrix multiplication is the other way around


    // Get a handle for our "MVP" uniform
    // Only during the initialisation
    GLuint MatrixID = glGetUniformLocation(shader, "MVP");

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // This is done in the main loop since each model will have a different MVP matrix (At least for
    // the M part)



    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    float tmp = 3;
    float tmp1 = 0.001
        ;
    glfwSwapInterval(0); // assert swap interval is not binded to 60 fps
    spdlog::info("Entering render LOOP");
    while (!static_cast<bool>(glfwWindowShouldClose(window))) {
        glfwPollEvents();
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, 1);
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        //glDrawElements(GL_LINE_STRIP, 8U, GL_UNSIGNED_INT, nullptr);
        View = glm::lookAt(glm::vec3(tmp, tmp/5, 3), // Camera is at (4,3,3), in World Space
          glm::vec3(0, 0, 0), // and looks at the origin
          glm::vec3(0, 1, 0) // Head is up (set to 0,-1,0 to look upside-down)
        );
        mvp  = Projection * View * Model;

         if (tmp >= 3 || tmp <= -3)
            tmp1 *= -1;
         tmp += tmp1;
        glfwSwapBuffers(window);
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    spdlog::info("Terminating program");

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

