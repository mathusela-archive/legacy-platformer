#define DEV


// PLATFORMER
// Include


#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <iostream>
#include <vector>

#include "mainFunctions.hpp"
#include "loadScene.hpp"
#include "cameraController.hpp"
#include "classes/tile.hpp"
#include "classes/camera.hpp"
#include "classes/player.hpp"


// -----------------------------------------------------------------------------------------------------------
// Consts


const int WIDTH = 1000, HEIGHT = 700;

#ifndef DEV
    const char TITLE[] = "PLATFORMER";
#else
    const char TITLE[] = "PLATFORMER <DEV>";
#endif


// -----------------------------------------------------------------------------------------------------------
// Main loop


int main() {


    // -----------------------------------------------------------------------------------------------------------
    // Init


    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glViewport(0, 0, WIDTH, HEIGHT);


    // -----------------------------------------------------------------------------------------------------------
    // Initialize scene


    std::vector<float> quadMesh = readCSV<float>("../resources/meshes/quad.vao");
    std::vector<float> doubleQuadMesh = readCSV<float>("../resources/meshes/doublequad.vao");
    unsigned int solidShaderProgram = create_shader("../resources/shaders/solid/vertexShader.vert", "../resources/shaders/solid/fragmentShader.frag"); 

    Camera mainCamera(WIDTH, HEIGHT);
    mainCamera.set_pos(glm::vec2(0.0, 0.0));

    loadTileTextures();
    std::vector<Tile> tileList = loadScene("../resources/scenes/level1.lvl", &quadMesh, &solidShaderProgram);

    unsigned int playerTexture = create_texture("../resources/textures/sprites/player/idle/1.png", GL_RGBA);
    Player player(quadMesh, solidShaderProgram, playerTexture);
    player.set_pos(glm::vec2(500, 500));


    // -----------------------------------------------------------------------------------------------------------
    // Gameloop


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSwapInterval(1);

    glClearColor(0.0, 0.0, 0.0, 1.0);
    while (!glfwWindowShouldClose(window)) {

        glClear(GL_COLOR_BUFFER_BIT);

        player.controller(window);
        player.vel_tick();

        cameraController(&mainCamera, &player, WIDTH, HEIGHT);

        for (int i=0; i<tileList.size(); i++) {
            tileList[i].draw(mainCamera);
            tileList[i].collision(&player);
        }

        player.draw(mainCamera);

        glfwSwapBuffers(window);
        glfwPollEvents();

    }


    // -----------------------------------------------------------------------------------------------------------
    // Terminate


    glfwTerminate();
    return 0;

}
