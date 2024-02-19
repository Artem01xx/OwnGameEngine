#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Renderer/Shader.h"
#include "resources/ResourceManager.h"
#include "renderer/texture_2d.h"
#include <string>
#include <iostream>

namespace Data
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

    GLfloat textures[] =
    {
        0.5f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
    };
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



int main(int argc, char** argv)
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
    {
        ResourceManager rm(argv[0]);
        auto default_shader_program = rm.load_shaders("DefaultShader", "res/shaders/vertex_shader.txt", "res/shaders/fragment_shader.txt");
        if (!default_shader_program) {
            throw std::runtime_error("Cannot Load Shader");
        }

        auto texture = rm.LoadTexture("DefaultShader", "res/textures/map_16x16.png");

        GLuint point_vbo = 0;
        glGenBuffers(1, &point_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, point_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Data::points), Data::points, GL_STATIC_DRAW);

        GLuint color_vbo = 0;
        glGenBuffers(1, &color_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Data::colors), Data::colors, GL_STATIC_DRAW);

        GLuint textures_vbo = 0;
        glGenBuffers(1, &textures_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, textures_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Data::textures), Data::textures, GL_STATIC_DRAW);

        GLuint vector_array_obj = 0;
        glGenVertexArrays(1, &vector_array_obj);
        glBindVertexArray(vector_array_obj);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, point_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, textures_vbo);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        default_shader_program->Use();
        default_shader_program->SetId("tex", 0);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            glBindVertexArray(vector_array_obj);
            texture->bind();
            glDrawArrays(GL_TRIANGLES, 0, 3);
            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}


void show_opengl_current_version()
{
    std::cout << "OpenGl ver is - " << glGetString(GL_VERSION) << "\n";
}