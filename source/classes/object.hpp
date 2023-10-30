#ifndef OBJECT_H
#define OBJECT_H


// -----------------------------------------------------------------------------------------------------------
// Include


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>


// -----------------------------------------------------------------------------------------------------------
// Object class


class Object {

    protected:

        unsigned int shaderProgram;
        unsigned int VAO;
        std::vector<float> mesh;
        unsigned int texture;

    public:

        glm::vec2 loc;
        glm::mat4 pos;

        void set_pos(glm::vec2 setLoc) {

            loc = setLoc;
            pos = glm::mat4(1.0);
            pos = glm::translate(pos, glm::vec3(loc, 0.0));

        }

        void move_pos(glm::vec2 setLoc) {

            set_pos(loc + setLoc);

        }

};


// -----------------------------------------------------------------------------------------------------------


#endif