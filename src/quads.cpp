#include "../include/quads.h"
#include "../include/shader.h"
#include "../include/include.h"

Quads::Quads() : Window() {
    // Load the shader files.
    programID = LoadShaders( "../quads/shader.vs", "../quads/shader.fs" );

    // Create array of quad shapes.
    glm::vec2 trans[100];
    int index = 0;
    float offset = 1.0f;
    for( int y = -10; y < 10; y += 2 ){
        for( int x = -10; x < 10; x += 2 ){
            glm::vec2 tran;
            tran.x = ( float )x / 10.0f + offset;
            tran.y = ( float )y / 10.0f + offset;
            trans[index++] = tran;
        }
    }

    // Quad data
    float vertices[] = {
        // positions     // colors
        -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
         0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
        -0.05f, -0.05f,  0.0f, 0.0f, 1.0f,

        -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
         0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
         0.05f,  0.05f,  0.0f, 1.0f, 1.0f
    };

    std::cout << "[Info] Vertices = " << sizeof( vertices ) << '\n';
    std::cout << "[Info] Index = " << index << '\n';

    // ibo
    glGenBuffers( 1, &ibo );
    glBindBuffer( GL_ARRAY_BUFFER, ibo );
    glBufferData( GL_ARRAY_BUFFER, sizeof( glm::vec2 ) * 100, &trans[0],
                GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );

    // vbo and vao
    glGenBuffers( 1, &vbo );
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );
    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices,
                GL_STATIC_DRAW  );

    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray( 2 );
    glBindBuffer( GL_ARRAY_BUFFER, ibo );
    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float),
                        (void*)0);
    glVertexAttribDivisor( 2, 1 );

}

void Quads::loop(){

    // Close window when button pressed.
    if( glfwWindowShouldClose( getWindow() ))
         exit();

    // Clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set matrices and uniform data.
    glm::mat4 transform;
    transform = glm::translate(transform, glm::vec3(-0.9f, -0.9f, -1.0f));

    GLuint transformLocation = glGetUniformLocation(programID, "transform");
    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transform));

    // Use shader program.
    glUseProgram( programID );

    // Bind and draw.
    glBindVertexArray( vao );
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100);
    glBindVertexArray(0);
}

void Quads::exit(){
    // Clean up
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glfwTerminate();
}
