#include <iostream>
#include "ShaderLoader.h"
#include <glad.h>
#include <GLFW/glfw3.h>
#include "Libs/glm-0.9.6.3/glm/glm/gtc/matrix_transform.hpp"
#include "Libs/glm-0.9.6.3/glm/glm/gtc/type_ptr.hpp"

#define OPENGL_MAJOR_VERSION 3
#define OPENGL_MINOR_VERSION 3

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define TITLE "GameEnginePrototype"

struct float3
{
    float3(float x, float y, float z)
        :x(x), y(y), z(z)
    {}

    float x;
    float y;
    float z;
};

int main()
{
    if (not glfwInit())
    {
        std::cerr << "Cannot initialize GLFW error" << std::endl;
        exit(0);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VERSION);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VERSION);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, TITLE, nullptr, nullptr);

    if (not window)
    {
        std::cerr << "Cannot create window" << std::endl;
        exit(0);
    }

    glfwMakeContextCurrent(window);

    if (not gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {

        std::cerr << "Cannot initialize GLAD Fialed: " << glad_glGetError() << std::endl;
        exit(0);
    }

    //Triangle with simple shader project init

    //Load Shader
    McOEngine::Shaders::ShaderLoader l_ShaderLoader;

    l_ShaderLoader.loadShaders("Shaders/Simple/Triangle.vs", "Shaders/Simple/Triangle.fs");

    l_ShaderLoader.displayShaders();


    //Create Shader program
    GLuint l_vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    GLuint l_fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

    const char * l_vertexShaderSource = l_ShaderLoader.getVertexShaderSource();
    const char * l_fragmentShaderSrouce = l_ShaderLoader.getFragmentShaderSource();

    glShaderSource(l_vertexShaderId, 1, &l_vertexShaderSource, NULL);

    glCompileShader(l_vertexShaderId);

    char l_errBuf[512];
    int l_success;

    glGetShaderiv(l_vertexShaderId, GL_COMPILE_STATUS, &l_success);

    if (not l_success)
    {
        glGetShaderInfoLog(l_vertexShaderId, 512, NULL, l_errBuf);
        std::cerr << "Cannot compile vertex shader " << l_errBuf << std::endl;
        exit(0);
    }

    glShaderSource(l_fragmentShaderId, 1, &l_fragmentShaderSrouce, NULL);

    glCompileShader(l_fragmentShaderId);

    glGetShaderiv(l_fragmentShaderId, GL_COMPILE_STATUS, &l_success);

    if (not l_success)
    {
        glGetShaderInfoLog(l_fragmentShaderId, 512, NULL, l_errBuf);
        std::cerr << "Cannot compile fragment shader " << l_errBuf << std::endl;
        exit(0);
    }

    GLuint l_shaderProgramId = glCreateProgram();
    
    glAttachShader(l_shaderProgramId, l_vertexShaderId);
    glAttachShader(l_shaderProgramId, l_fragmentShaderId);

    glLinkProgram(l_shaderProgramId);

    glGetProgramiv(l_shaderProgramId, GL_LINK_STATUS, &l_success);

    if (not l_success)
    {
        glGetProgramInfoLog(l_shaderProgramId, 512, NULL, l_errBuf);
        std::cerr << "Cannot link shader program " << l_errBuf << std::endl;
        exit(0);
    }

    //Create Vertex Arrays

    float3 l_vertices[3]
    {
        float3(-1.0f, -1.0f, 0.0f),
        float3(0.0f, 1.0f, 0.0f),
        float3(1.0f, -1.0f, 0.0f)
    };

    GLuint l_indices[3]
    {
        0, 1, 2
    };
    

    GLuint l_vao;
    GLuint l_vbo;
    GLuint l_ibo;

    glGenVertexArrays(1, &l_vao);
    
    glBindVertexArray(l_vao);

    glGenBuffers(1, &l_vbo);
    glGenBuffers(1, &l_ibo);

    glBindBuffer(GL_ARRAY_BUFFER, l_vao);

    glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float3), l_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float3), (GLvoid*)0);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, l_ibo);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(l_indices), l_indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    //Project Init End


    glm::vec3 cameraPos = glm::vec3(2.0f, 2.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    float t = 0.0f;
    while (not glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
        model = glm::rotate(model, glm::radians(t), glm::vec3(0.0f, 1.0f, 0.0f));
        //model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
        glm::mat4 view = glm::mat4(1.0f);

        view = glm::lookAt(cameraPos, cameraPos + glm::vec3(-0.5f, -0.5f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        glm::mat4 projection = glm::mat4(1.0f);

        projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / WINDOW_HEIGHT, 0.3f, 1000.0f);

        glUseProgram(l_shaderProgramId);

        unsigned int uniformLocationId = glGetUniformLocation(l_shaderProgramId, "MCOENGINE_MATRIX_M");
        glUniformMatrix4fv(uniformLocationId, 1, GL_FALSE, glm::value_ptr(model));


        uniformLocationId = glGetUniformLocation(l_shaderProgramId, "MCOENGINE_MATRIX_V");
        glUniformMatrix4fv(uniformLocationId, 1, GL_FALSE, glm::value_ptr(view));

        uniformLocationId = glGetUniformLocation(l_shaderProgramId, "MCOENGINE_MATRIX_P");
        glUniformMatrix4fv(uniformLocationId, 1, GL_FALSE, glm::value_ptr(projection));

        glUseProgram(0);

        glUseProgram(l_shaderProgramId);
        glBindVertexArray(l_vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, l_ibo);

        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glUseProgram(0);


        glfwSwapBuffers(window);
        t += 0.1f;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }

    glDeleteVertexArrays(1, &l_vao);
    glDeleteBuffers(1, &l_vbo);
    glDeleteBuffers(1, &l_ibo);
    glDeleteProgram(l_shaderProgramId);
    glDeleteShader(l_vertexShaderId);
    glDeleteShader(l_fragmentShaderId);

    return 0;
}
