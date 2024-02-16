#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>



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

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

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