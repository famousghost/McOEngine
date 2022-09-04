#pragma once
#include <GLFW/glfw3.h>
#include <string>
#define OPENGL_MAJOR_VERSION 4
#define OPENGL_MINOR_VERSION 2

namespace McOEngine
{
class GameWindow
{
    public:
    GameWindow(std::string p_gameWindowTitle, int p_width, int p_height);
    void Init();
    bool ShouldCloseWindow() const;
    GLFWwindow* GetWindowPointer() const;
    private:
    GLFWwindow* m_window;
    std::string m_gameWidnowTitle;
    int m_width;
    int m_height;
};
}//McOEngine

