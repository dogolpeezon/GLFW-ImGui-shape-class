#ifndef _manager_h_
#define _manager_h_
#include "window.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Manager : public Window {
public:
    Manager();
    GLFWwindow* window;
    static bool showQuads;

private:
    static bool drawQuads();
    static bool drawCube();

protected:
    virtual void loop();
    void exit();

};
#endif
