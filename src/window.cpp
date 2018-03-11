#include "../include/include.h"
#include "../include/quads.h"
#include "../include/window.h"

using namespace std;
// Current window pointer.
Window* c_Window = NULL;

Window& Window::getInstance(){
    if( c_Window )
        return *c_Window;
    else
        throw std::runtime_error( " No window.. " );
}

GLFWwindow* Window::getWindow() const{
    return window;
}

Window::Window():width( 640 ), height( 480 ), title( "Window" ){
    c_Window = this;

    std::cout << "[Info] GLFW Init.." << '\n';
    // Init glfw library.
    if( !glfwInit() ){
        throw std::runtime_error( "GLFW failed to init.." );
    }
    // Setting opengl version.
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 2 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    // Create glfw window and context.
    window = glfwCreateWindow( width, height, title.c_str(), NULL, NULL );
    if( !window ){
        glfwTerminate();
        throw std::runtime_error( "Window failed to create.." );
    }
    glfwMakeContextCurrent( window );

    std::cout << "[Info] GLEW Init.." << '\n';
    // Init glew library.
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if( err != GLEW_OK ){
        glfwTerminate();
        throw std::runtime_error(string( "GLEW failed to init.. error = " )+( const char*)glewGetErrorString( err ));
    }
    // Print version info.
    const GLubyte* renderer = glGetString( GL_RENDERER );
    const GLubyte* version = glGetString( GL_VERSION );
    std::cout << "[Info] Renderer: " << renderer << '\n';
    std::cout << "[Info] OpenGL version supported: " << version << '\n';
    // Opengl config.. depth testing and as closer.
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_LESS );
    // vsync.
    glfwSwapInterval( true );
}

int Window::getWidth(){
    return width;
}

int Window::getHeight(){
    return height;
}

void Window::run(){
    glfwMakeContextCurrent( window );
    while( !glfwWindowShouldClose( getWindow() )){
        loop();
        glfwSwapBuffers( window );
        if ( GLFW_PRESS == glfwGetKey( window, GLFW_KEY_ESCAPE )){
            glfwSetWindowShouldClose( window, 1 );
        }
        glfwPollEvents();
    }
}

void Window::loop(){
    std::cout << "[Info] : loop.." << '\n';
}

void Window::exit(){
    GLFWwindow *window = glfwGetCurrentContext();
    glfwDestroyWindow( window );
}
