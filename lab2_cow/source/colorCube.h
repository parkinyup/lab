#pragma once

#include <GL/gl3w.h>

class ColorCube
{
private:
    GLuint vaoHandle;
    GLuint vbo_cube_vertices, vbo_cube_colors;
    GLuint ibo_cube_elements;
    
    void setup();   // 생성자에서 호출

public:
    ColorCube();    // 생성자
    void draw();    // 매 프레임 호출
};

