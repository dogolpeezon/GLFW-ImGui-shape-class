#ifndef _cube_h_
#define _cube_h_
#include "window.h"
#include <GL/glew.h>
#include <glm/glm.hpp>

class Cube : public Window {
public:
    Cube();

private:
    virtual void loop();
    void exit();

protected:
    GLuint programID;
    GLuint vao, vbo, ibo;

};
#endif
