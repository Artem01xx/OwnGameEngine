#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Renderer/Shader.h"
#include <string>
#include <iostream>

namespace VerticesData
{
    GLfloat points[] =
    {
        0.0f,  0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
       -0.5f, -0.5f, 0.0f
    };
    GLfloat colors[] =
    {
        1.0f, 0.0f, 0.0f,
        0.0f, 0.1f, 0.0f,
        0.0f, 0.0f, 1.0f,
    };

    const char* vertex_shaders =
        "#version 450\n"
        "layout(location = 0) in vec3 vertex_position;"
        "layout(location = 1) in vec3 vertex_color;"
        "out vec3 color;"
        "void main(){"
        "    color = vertex_color;"
        "    gl_Position = vec4(vertex_position, 1.0f);"
        "}";

    const char* fragment_shaders =
        "#version 450\n"
        "in vec3 color;"
        "out vec4 frag_color;"
        "void main(){"
        "   frag_color = vec4(color, 1.0f);"
        "}";
};

//Initialize glfw library
void initialize_glfw_library()
{
    if (!glfwInit()) {
        throw std::runtime_error("glfwInit Is Failed");
    }
}

// Create a window 
GLFWwindow* creating_window(int widthm, int height, const char* title)
{
    GLFWwindow* window = glfwCreateWindow(widthm, height, title, nullptr, nullptr);
    if (!window){
        glfwTerminate();
        throw std::runtime_error("Window is not created");
    }
    return window;
}

// Loading glad library
void load_glad_library()
{
    try{
        gladLoadGL();
    }
    catch (const std::runtime_error& e){
        std::cerr << "Throw Exception" << " " << e.what() << "\n";
    }
}


void window_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scanmode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}


// Check current opengl version
void show_opengl_current_version();


//______________________________SHADERS_______________________________///




void draw_triangle(GLuint vector_arr_obj)
{
    glBindVertexArray(vector_arr_obj);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}


int main()
{    
    initialize_glfw_library();

    int window_size_x = 840;
    int window_size_y = 480;
    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = creating_window(window_size_x, window_size_y, "2D-Game");
    glfwMakeContextCurrent(window);

    // Checking for window size updating
    glfwSetWindowSizeCallback(window, window_size_callback);
    // Checking for key callback
    glfwSetKeyCallback(window, key_callback);

    // Trying to load glad library
    load_glad_library();

    show_opengl_current_version();

    glClearColor(0, 1, 0, 1);

    //Created vertical and fragment shaders
    std::string vertex_shader = VerticesData::vertex_shaders;
    std::string fragment_shader = VerticesData::fragment_shaders;
    Renderer::Shader shader_programm(vertex_shader, fragment_shader);
    
    if (!shader_programm.IsCompiled()) {
        throw std::runtime_error("Shader not compiled");
    }

    GLuint point_vbo = 0;
    glGenBuffers(1, &point_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, point_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VerticesData::points),VerticesData::points, GL_STATIC_DRAW);

    GLuint color_vbo = 0;
    glGenBuffers(1, &color_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VerticesData::colors), VerticesData::colors, GL_STATIC_DRAW);

    GLuint vector_array_obj = 0;
    glGenVertexArrays(1, &vector_array_obj);
    glBindVertexArray(vector_array_obj);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, point_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        shader_programm.Use();
        // Draw triangle
        draw_triangle(vector_array_obj);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}


void show_opengl_current_version()
{
    std::cout << "OpenGl ver is - " << glGetString(GL_VERSION) << "\n";
}