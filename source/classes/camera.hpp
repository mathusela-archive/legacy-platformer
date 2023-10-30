#ifndef CAMERA_H
#define CAMERA_H


// -----------------------------------------------------------------------------------------------------------
// Include


#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "object.hpp"


// -----------------------------------------------------------------------------------------------------------
// Camera class


class Camera: public Object {

    public:


        // -----------------------------------------------------------------------------------------------------------
        // Public vars


        glm::mat4 projection;


        // -----------------------------------------------------------------------------------------------------------
        // Constructor


        Camera(int WIDTH, int HEIGHT) {

            projection = glm::ortho(0.0f, (float)WIDTH, 0.0f, (float)HEIGHT, -1.0f, 1.0f);

        }

};


// -----------------------------------------------------------------------------------------------------------


#endif