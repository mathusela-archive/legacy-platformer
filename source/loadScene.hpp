#ifndef LOADSCENE_H
#define LOADSCENE_H


// -----------------------------------------------------------------------------------------------------------
// Include


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "mainFunctions.hpp"
#include "classes/tile.hpp"


// -----------------------------------------------------------------------------------------------------------
// Consts


const int FORMAT_SIZE = 3;


// -----------------------------------------------------------------------------------------------------------
// Load textures


unsigned int grassTexture;
unsigned int dirtTexture;

void loadTileTextures() {

    grassTexture = create_texture("../resources/textures/tiles/grass.png", GL_RGB);
    dirtTexture = create_texture("../resources/textures/tiles/dirt.png", GL_RGB);

}


// -----------------------------------------------------------------------------------------------------------
// Tile texture cast


unsigned int tileTextureCast(int id) {

    switch (id) {

        case 0:
            return dirtTexture;
        
        case 1:
            return grassTexture;

    } 

}


// -----------------------------------------------------------------------------------------------------------
// Load scene function


std::vector<Tile> loadScene(std::string filePath, std::vector<float>* mesh, unsigned int* shaderProgram) {

    std::vector<int> tilePos = readCSV<int> (filePath);

    std::vector<Tile> tileList;

    for (int i=0; i<tilePos.size()/FORMAT_SIZE; i++) {

        Tile newTile = Tile(*mesh, *shaderProgram, tileTextureCast(tilePos[(i*FORMAT_SIZE)+2]));
        newTile.set_pos(glm::vec2(tilePos[i*FORMAT_SIZE]*50+25, tilePos[(i*FORMAT_SIZE)+1]*50+25));

        tileList.push_back(newTile);

    }

    return tileList;

}


// -----------------------------------------------------------------------------------------------------------


#endif