#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H


// -----------------------------------------------------------------------------------------------------------
// Include


#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "classes/camera.hpp"
#include "classes/player.hpp"


// -----------------------------------------------------------------------------------------------------------
// Camera controller function


void cameraController(Camera* camera, Player* player, const int width, const int height) {

    // camera -> set_pos(glm::vec2(-(player -> loc).x+(width/2), -(player -> loc).y+(height/2)));
    camera -> set_pos(glm::vec2(-(player -> loc).x+(width/2), camera -> loc.y));

}


// -----------------------------------------------------------------------------------------------------------


#endif