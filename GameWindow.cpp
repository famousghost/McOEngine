#include "GameWindow.h"
#include <iostream>
namespace McOEngine
{
GameWindow::GameWindow(std::string p_gameWindowTitle, int p_width, int p_height)
    :m_gameWidnowTitle(p_gameWindowTitle), m_width(p_width), m_height(p_height)
{
    Init();
}

void GameWindow::Init()
{
    if (not glfwInit())
    {
        std::cerr << "Cannot initialize GLFW error" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VERSION);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VERSION);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(m_width, m_height, m_gameWidnowTitle.c_str(), nullptr, nullptr);

    if (not m_window)
    {
        std::cerr << "Cannot create window" << std::endl;
        return;
    }

    glfwMakeContextCurrent(m_window);
}

bool GameWindow::ShouldCloseWindow() const
{
    return not glfwWindowShouldClose(m_window);
}

GLFWwindow * GameWindow::GetWindowPointer() const
{
    return m_window;
}


}//McOEngine