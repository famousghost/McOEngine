#include <iostream>
#include <vector>
#include "Material.h"
#include "GameWindow.h"
#include "VertexArrayObject.h"
#include "TextureLoader.h"
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

    //Create Shaders
    std::shared_ptr<Shaders::Shader> l_fullScreenShader = std::make_shared<Shaders::Shader>("Shaders/Simple/Cube");

    //Create Material
    Material l_fullScreenMaterial;
    l_fullScreenMaterial.AttachShader(l_fullScreenShader);


    //Create Vertex Arrays

    std::vector<Vertex> l_vertex = 
    {
        // position, normal, color, uv
        //Front
        Vertex(glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)), // 0
        Vertex(glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)), // 1
        Vertex(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)), // 2
        Vertex(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)), // 3

        //Back
        Vertex(glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)), // 4
        Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)), // 5
        Vertex(glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)), // 6
        Vertex(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)), // 7

        //Right
        Vertex(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)), // 8
        Vertex(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)), // 9
        Vertex(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)), // 10
        Vertex(glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)), // 11

        //Left
        Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)), // 12
        Vertex(glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)), // 13
        Vertex(glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)), // 14
        Vertex(glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)), // 15

        //Top
        Vertex(glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)), // 16
        Vertex(glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)), // 17
        Vertex(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)), // 18
        Vertex(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)), // 19
        
        //Bottom
        Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec2(0.0f, 1.0f)), // 20
        Vertex(glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec2(0.0f, 0.0f)), // 21
        Vertex(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec2(1.0f, 0.0f)), // 22
        Vertex(glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec2(1.0f, 1.0f)), // 23
    };

    std::vector<unsigned int> l_indices = 
    {
        0, 3, 2,
        1, 0, 2,
        4, 6, 7,
        5, 6, 4,
        8, 11, 10,
        9, 8, 10,
        12, 15, 14,
        13, 12, 14,
        16, 19, 18,
        17, 16, 18,
        20, 23, 22,
        21, 20, 22

    };

    VertexArrayObject l_vao;

    l_vao.AddValuesToAtrribPointer(l_vertex);
    l_vao.AddIndices(l_indices);

    //Create Vertex Arrays

    //Load Textures
    TextureLoader l_textureLoader;
    l_textureLoader.fetchChannelFormat(3);
    GLuint l_brickTexture = l_textureLoader.loadTexture("Textures/Bricks.jpg", GL_REPEAT, GL_LINEAR);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, l_brickTexture);

    unsigned int l_shaderProgramId = l_fullScreenMaterial.GetShaderProgramId();
    glUseProgram(l_shaderProgramId);
    unsigned int l_brickId = glGetUniformLocation(l_shaderProgramId, "Texture0");
    glUniform1i(l_brickId, 0);
    glUseProgram(0);
    //Load Textures

    //Project Init End

    float2 screenResolution = float2(WINDOW_WIDTH, WINDOW_HEIGHT);

    float3 lightPos = float3(2.0f, 2.0f, 4.0f);

    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);


    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
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

        //Update Material properties
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
        //Update Material properties

        //Draw Cube
        glUseProgram(l_shaderProgramId);
        l_vao.BindVAO();
        l_vao.BindEBO();

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        l_vao.UnbindEBO();
        l_vao.UnbindVAO();
        glUseProgram(0);
        //Draw Cube


        glfwSwapBuffers(l_gameWindow.GetWindowPointer());
        t += 0.01f;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }

    return 0;
}
