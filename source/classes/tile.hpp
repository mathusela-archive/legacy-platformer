#ifndef TILE_H
#define TILE_H


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
#include "player.hpp"


// -----------------------------------------------------------------------------------------------------------
// Tile class


class Tile: public Object {

    public:


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

        Tile(std::vector<float> mesh, unsigned int shaderProgram, unsigned int texture) {

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
        // Collision


        bool testCollision(Player* player) {

            const float tileSize = 25;

            if (((player -> loc.x + tileSize > loc.x - tileSize && player -> loc.x + tileSize < loc.x + tileSize) ||
                 (player -> loc.x - tileSize < loc.x + tileSize && player -> loc.x - tileSize > loc.x - tileSize)) &&
                ((player -> loc.y + tileSize > loc.y - tileSize && player -> loc.y + tileSize < loc.y + tileSize) ||
                 (player -> loc.y - tileSize < loc.y + tileSize && player -> loc.y - tileSize > loc.y - tileSize))) {
                return true;
            }
            else {
                return false;
            }

        }


        glm::vec2 collisionDirection(glm::vec2 direction) {

            glm::vec2 normalizedDirection = glm::normalize(direction);
            if (fabs(normalizedDirection.x) > fabs(normalizedDirection.y)) {
                return glm::normalize(glm::vec2(normalizedDirection.x, 0.0));
            }
            else {
                return glm::normalize(glm::vec2(0.0, normalizedDirection.y));
            }

        }


        glm::vec2 flipVector(glm::vec2 vector) {

            return glm::vec2(vector.y, vector.x);

        }


        void collision(Player* player) {

            if (testCollision(player)) {
                player -> set_vel(glm::vec2(player -> vel.x, player -> vel.y) * glm::vec2(fabs(flipVector(collisionDirection(player -> loc - loc)).x), fabs(flipVector(collisionDirection(player -> loc - loc)).y)));

                // std::cout << collisionDirection(player -> loc - loc).x << ", " << collisionDirection(player -> loc - loc).y << std::endl;

                if (collisionDirection(player -> loc - loc) == glm::vec2(0.0, 1.0)) {

                    player -> onGround = true;

                }

                while (testCollision(player))
                {

                    player -> move_pos(collisionDirection(player -> loc - loc) * glm::vec2(0.2));
                
                }
            }

        }

};


// -----------------------------------------------------------------------------------------------------------


#endif