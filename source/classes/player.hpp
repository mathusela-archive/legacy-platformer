#ifndef PLAYER_H
#define PLAYER_H


// -----------------------------------------------------------------------------------------------------------
// Include


#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "object.hpp"
#include "camera.hpp"


// -----------------------------------------------------------------------------------------------------------
// Player class


class Player: public Object {

    protected:

        float lastFrame = 0.0;
        float currentFrame;
        float deltaTime;

    public:

        glm::vec2 vel = glm::vec2(0.0, 0.0);
        bool onGround = false;


        // -----------------------------------------------------------------------------------------------------------
        // Constructor


        void init() {

            glGenVertexArrays(1, &VAO);
		    glBindVertexArray(VAO);

            unsigned int VBO;
            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, mesh.size()*sizeof(float), &mesh[0], GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*5, (void*)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float)*5, (void*)(sizeof(float)*3));
            glEnableVertexAttribArray(1);
        
        }

        Player(std::vector<float> mesh, unsigned int shaderProgram, unsigned int texture) {

            this -> mesh = mesh;
            this -> shaderProgram = shaderProgram;
            this -> texture = texture;

            init();

        }


        // -----------------------------------------------------------------------------------------------------------
        // Draw


        void draw(Camera camera) {

            glUseProgram(shaderProgram);
            glBindVertexArray(VAO);

            glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "world"), 1, GL_FALSE, glm::value_ptr(pos));
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(camera.pos));
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(camera.projection));

            glUniform1i(glGetUniformLocation(shaderProgram, "diffusionMap"), 0);
			glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture);

            glDrawArrays(GL_TRIANGLES, 0, mesh.size());

        }


        // -----------------------------------------------------------------------------------------------------------
        // Velocity


        void set_vel(glm::vec2 vel) {

            this -> vel = vel;

        };

        void add_vel(glm::vec2 vel) {

            this -> vel += vel;

        }

        void vel_tick() {

            const float groundDecel = 200.0;
            const float airDecel = 100.0;
            const float gravStrength = 1500.0;
            const float terminalVelocity = 1000;

            const float limit0 = 2;

            // Delta time
            currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            // Move vel
            move_pos(vel * deltaTime);

            // Gravity
            add_vel(glm::vec2(0.0, -gravStrength*deltaTime));

            // Terminal velocity
            if (vel.y < -terminalVelocity) {vel.y = -terminalVelocity;}
            
            // Decel
            // std::cout << "test" << std::endl;
            if (onGround) {
                if (vel.x != 0.0) {add_vel(-glm::normalize(glm::vec2(vel.x, 0.0))*groundDecel*deltaTime);}
            }
            else {
                if (vel.x != 0.0) {add_vel(-glm::normalize(glm::vec2(vel.x, 0.0))*airDecel*deltaTime);}
            }

            // Limit x vel approching 0
            if (vel.x < limit0 && vel.x > -limit0) {vel.x = 0;}

        }


        // -----------------------------------------------------------------------------------------------------------
        // Controller


        void controller(GLFWwindow* window) {

            const float jumpStrength = 800.0;

            const float accel = 350.0;
            const float walkSpeed = 125.0;
            const float runSpeed = 250.0;
            float playerSpeed = walkSpeed;

            if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) {playerSpeed = runSpeed;}

            if (glfwGetKey(window, GLFW_KEY_A)) {if (fabs(vel.x) < playerSpeed) {add_vel(glm::vec2(-accel * deltaTime, 0.0));}}
            if (glfwGetKey(window, GLFW_KEY_D)) {if (fabs(vel.x) < playerSpeed) {add_vel(glm::vec2(accel * deltaTime, 0.0));}}

            std::cout << onGround << std::endl;
            if (glfwGetKey(window, GLFW_KEY_W)) {if (onGround) {add_vel(glm::vec2(0.0, jumpStrength));}}

            onGround = false;

        }


};


// -----------------------------------------------------------------------------------------------------------


#endif