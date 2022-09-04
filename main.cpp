#include <iostream>
#include "Material.h"
#include "GameWindow.h"
#include <glad.h>
#include <GLFW/glfw3.h>
#include "Math.h"
#include "Libs/glm-0.9.6.3/glm/glm/gtc/matrix_transform.hpp"
#include "Libs/glm-0.9.6.3/glm/glm/gtc/type_ptr.hpp"

#define OPENGL_MAJOR_VERSION 4
#define OPENGL_MINOR_VERSION 2

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define TITLE "GameEnginePrototype"

constexpr float NEAR_PLANE = 0.3f;
constexpr float FAR_PLANE = 1000.0f;

using namespace McOEngine;
using namespace Math;

int main()
{

    //Create Window
    GameWindow l_gameWindow(TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);

    //Init GLAD (OpenGL API)

    if (not gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {

        std::cerr << "Cannot initialize GLAD Fialed: " << glad_glGetError() << std::endl;
        return -1;
    }


    //Triangle with simple shader project init

    //Create Shaders
    std::shared_ptr<Shaders::Shader> l_fullScreenShader = std::make_shared<Shaders::Shader>("Shaders/Simple/FullScreen");

    //Create Material
    Material l_fullScreenMaterial;
    l_fullScreenMaterial.AttachShader(l_fullScreenShader);


    //Create Vertex Arrays

    float3 l_vertices[4]
    {
        float3(-1.0f, -1.0f, 0.0f),
        float3(-1.0f, 1.0f, 0.0f),
        float3(1.0f, 1.0f, 0.0f),
        float3(1.0f, -1.0f, 0.0f)
    };

    GLuint l_indices[6]
    {
        0, 3, 2,
        1, 2, 0
    };
    

    GLuint l_vao;
    GLuint l_vbo;
    GLuint l_ibo;

    glGenVertexArrays(1, &l_vao);
    
    glBindVertexArray(l_vao);

    glGenBuffers(1, &l_vbo);
    glGenBuffers(1, &l_ibo);

    glBindBuffer(GL_ARRAY_BUFFER, l_vao);

    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(float3), l_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float3), (GLvoid*)0);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, l_ibo);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(l_indices), l_indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    //Project Init End

    float2 screenResolution = float2(WINDOW_WIDTH, WINDOW_HEIGHT);

    float3 lightPos = float3(2.0f, 2.0f, 4.0f);

    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);



    glEnable(GL_DEPTH_TEST);
    float t = 0.0f;
    while (l_gameWindow.ShouldCloseWindow())
    {
        glfwPollEvents();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
        model = glm::rotate(model, glm::radians(t), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 view = glm::mat4(1.0f);

        view = glm::lookAt(cameraPos, cameraPos + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        glm::mat4 projection = glm::mat4(1.0f);

        projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / WINDOW_HEIGHT, NEAR_PLANE, FAR_PLANE);

        GLuint l_shaderProgramId = l_fullScreenMaterial.GetShaderProgramId();
        glUseProgram(l_shaderProgramId);

        unsigned int uniformLocationId = glGetUniformLocation(l_shaderProgramId, "MCOENGINE_MATRIX_M");
        glUniformMatrix4fv(uniformLocationId, 1, GL_FALSE, glm::value_ptr(model));


        uniformLocationId = glGetUniformLocation(l_shaderProgramId, "MCOENGINE_MATRIX_V");
        glUniformMatrix4fv(uniformLocationId, 1, GL_FALSE, glm::value_ptr(view));

        uniformLocationId = glGetUniformLocation(l_shaderProgramId, "MCOENGINE_MATRIX_P");
        glUniformMatrix4fv(uniformLocationId, 1, GL_FALSE, glm::value_ptr(projection));

        uniformLocationId = glGetUniformLocation(l_shaderProgramId, "MCScreenResolution");
        glUniform2fv(uniformLocationId, 1, &screenResolution.x);

        uniformLocationId = glGetUniformLocation(l_shaderProgramId, "MCWorldSpaceLightPos");
        glUniform3fv(uniformLocationId, 1, &lightPos.x);

        glUseProgram(0);

        glUseProgram(l_shaderProgramId);
        glBindVertexArray(l_vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, l_ibo);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glUseProgram(0);


        glfwSwapBuffers(l_gameWindow.GetWindowPointer());
        t += 0.01f;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }

    glDeleteVertexArrays(1, &l_vao);
    glDeleteBuffers(1, &l_vbo);
    glDeleteBuffers(1, &l_ibo);

    return 0;
}
