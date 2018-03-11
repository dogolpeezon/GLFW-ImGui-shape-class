#ifndef _quads_h_
#define _quads_h_
#include "window.h"
#include <GL/glew.h>
#include <glm/glm.hpp>

class Quads : public Window {
public:
    Quads();

protected:
    virtual void loop();
    void exit();

private:
    GLuint programID;
    GLuint vao, vbo, ibo;

};

#endif
