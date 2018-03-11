#ifndef _window_h_
#define _window_h_
#include <string>

class GLFWwindow;

class Window {
public:
    Window();
    static Window& getInstance();
    // Get window ID.
    GLFWwindow* getWindow() const;
    // Window information.
    int getWidth();
    int getHeight();
    // Window control.
    void exit();
    // Window run.
    void run();

private:
    // Copy assignment.
    Window& operator=( const Window& ){ return *this; }
    // Window ID pointer.
    GLFWwindow* window;
    int width, height;

protected:
    // Overloaded constructor.
    Window( const Window& ){};
    std::string title;
    virtual void loop();
};

#endif
