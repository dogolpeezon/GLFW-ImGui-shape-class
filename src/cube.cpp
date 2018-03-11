#include "../include/cube.h"
#include "../include/shader.h"
#include "../include/include.h"
// Settings
GLuint programID, VertexArrayID, MatrixID, vertexbufferID, colorbufferID;
glm::mat4 projection, view, model, modelView, rotate;
// Timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

Cube::Cube() : Window() {
    programID = LoadShaders( "../shaders/cube.vs", "../shaders/cube.fs" );
    // Verices and colors for cube
    static const GLfloat vertexData[] = {
        // Face 0
        -0.5f, 0.5f, -0.5f,  0.5f, 0.5f, -0.5f,    -0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,   -0.5f, -0.5f, -0.5f,   0.5f, -0.5f, -0.5f,
        // Face 1
        -0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f,   0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, -0.5f,   0.5f, -0.5f, 0.5f,    0.5f, 0.5f, -0.5f,
        // Face 2
        0.5f, -0.5f, 0.5f,    0.5f, 0.5f, -0.5f,    0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, -0.5f,    0.5f, 0.5f, 0.5f,    -0.5f, 0.5f, -0.5f,
        // Face 3
        0.5f, 0.5f, 0.5f,     -0.5f, 0.5f, -0.5f,  -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, -0.5f,   -0.5f, 0.5f, 0.5f,   -0.5f, -0.5f, -0.5f,
        // Face 4
        -0.5f, 0.5f, 0.5f,   -0.5f, -0.5f, -0.5f,   -0.5, -0.5f, 0.5f,
        -0.5f, -0.5f, -0.5f,  -0.5f, -0.5f, 0.5f,	0.5f, -0.5f, 0.5f,
        // Face 5
        -0.5f, -0.5f, 0.5f,  0.5f, -0.5f, 0.5f,    -0.5f, 0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,   -0.5f, 0.5f, 0.5f,    0.5f, 0.5f, 0.5f
    };
    static const GLfloat colorData[] = {
        // Face 0
        0.0f,  1.0f,  0.0f,   	1.0f,  1.0f,  0.0f,		0.0f,  0.0f,  0.0f,
        1.0f,  1.0f,  0.0f,		0.0f,  0.0f,  0.0f,		1.0f,  0.0f,  0.0f,
        // Face 1
        0.0f,  0.0f,  0.0f,		1.0f,  0.0f,  0.0f,		1.0f,  0.0f,  1.0f,
        1.0f,  0.0f,  0.0f,		1.0f,  0.0f,  1.0f,		1.0f,  1.0f,  0.0f,
        // Face 2
        1.0f,  0.0f,  1.0f,		1.0f,  1.0f,  0.0f,		1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  0.0f,		1.0f,  1.0f,  1.0f,		0.0f,  1.0f,  0.0f,
        // Face 3
        1.0f,  1.0f,  1.0f,		0.0f,  1.0f,  0.0f,		0.0f,  1.0f,  1.0f,
        0.0f,  1.0f,  0.0f,		0.0f,  1.0f,  1.0f,		0.0f,  0.0f,  0.0f,
        // Face 4
        0.0f,  1.0f,  1.0f,		0.0f,  0.0f,  0.0f,		0.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  0.0f,		0.0f,  0.0f,  1.0f,		1.0f,  0.0f,  1.0f,
        // Face 5
        0.0f,  0.0f,  1.0f,		1.0f,  0.0f,  1.0f,		0.0f,  1.0f,  1.0f,
        1.0f,  0.0f,  1.0f,		0.0f,  1.0f,  1.0f,		1.0f,  1.0f,  1.0f
    };

    // Make and bind VAO
    glGenVertexArrays( 1, &VertexArrayID );
    glBindVertexArray( VertexArrayID );

    // Make and bind VBO for vertices
    glGenBuffers( 1, &vertexbufferID );
    glBindBuffer( GL_ARRAY_BUFFER, vertexbufferID );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertexData ),
        vertexData, GL_STATIC_DRAW );

    // Make and bind VBO for colors
    glGenBuffers( 1, &colorbufferID );
    glBindBuffer( GL_ARRAY_BUFFER, colorbufferID );
    glBufferData( GL_ARRAY_BUFFER, sizeof( colorData ),
        colorData, GL_STATIC_DRAW );

    model = glm::translate( model, glm::vec3(0.0f, 0.0f, -5.0f) );
}

void Cube::loop() {
    if( glfwWindowShouldClose( getWindow() ))
         exit();

    // set deltaTime
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // // configure transformation matrices
    glm::mat4 projection = glm::perspective( glm::radians(45.0f), (float)640 / (float)480, 0.1f, 1000.0f );
    // glm::mat4 view = camera.GetViewMatrix();

    // UniformLocation to send to shaders
    GLuint projLoc = glGetUniformLocation( programID, "projection" );
    GLuint viewLoc = glGetUniformLocation( programID, "view" );
    GLuint timeLoc = glGetUniformLocation( programID, "time" );

    // Uniform the matrices
    glUniformMatrix4fv( viewLoc, 1, GL_FALSE, glm::value_ptr( view ));
    glUniformMatrix4fv( projLoc, 1, GL_FALSE, glm::value_ptr( projection ));
    glUniform1f( timeLoc, currentFrame );

    // Run shader program
    glUseProgram( programID );

    // Transform cube
    model = glm::rotate( model, 0.01f, glm::vec3( -1.0f, -1.0f, 0.0f ) );

    GLuint modelLoc = glGetUniformLocation( programID, "model" );
    glUniformMatrix4fv( modelLoc, 1, GL_FALSE, glm::value_ptr( model ));

    // Vertex attrib 0
    glEnableVertexAttribArray(0);
    glBindBuffer( GL_ARRAY_BUFFER, vertexbufferID ) ;
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );
    // Color attrib 1
    glEnableVertexAttribArray(1);
    glBindBuffer( GL_ARRAY_BUFFER, colorbufferID );
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );
    // Draw
    glDrawArrays( GL_TRIANGLES, 0, 12*3 );

}

void Cube::exit() {
    // Clean up
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glfwTerminate();
}
