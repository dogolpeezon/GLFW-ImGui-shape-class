#include "../include/include.h"
#include "../include/window.h"
#include "../include/manager.h"
#include "../include/quads.h"
#include "../include/cube.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw_gl3.h"

Manager::Manager() : Window(), window(glfwGetCurrentContext()) {

    std::cout << "[Info] ImGui Init.. " << '\n';
    // Setup ImGui binding
    if( !ImGui_ImplGlfwGL3_Init( window, true ) ){
        glfwTerminate();
        throw std::runtime_error( "imgui failed to init.." );
    }
}

void Manager::loop(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ImGui_ImplGlfwGL3_NewFrame();

        // This is a better but more complicated way to init the menu.
        // static bool showQuads = false;
        // if (ImGui::BeginMainMenuBar()) {
        //     if (ImGui::BeginMenu("Menu")) {
        //         ImGui::MenuItem("Quads", &showQuads );
        //         ImGui::EndMenu();
        //     }
        //     ImGui::EndMainMenuBar();
        // }

        // This is simpler way but less control maybe??
        ImGui::Begin("My Shapes");
        ImGui::Text("Draw quads..");
        if(ImGui::Button("Quads..", ImVec2(75, 25))){
            drawQuads();
        }
        ImGui::Text("Draw cube..");
        if(ImGui::Button("Cube..", ImVec2(75, 25))){
            drawCube();
        }
        ImGui::End();
    ImGui::Render();

}

bool Manager::drawQuads(){
    std::cout << "In drawQuads.." << '\n';
    // need to delete the current quads obj before calling new cube obj??
    static Quads *quads = NULL;
    if ( quads == NULL ){
        quads = new Quads();
        quads->run();
    }
    return false;
}

bool Manager::drawCube(){
    std::cout << "In drawCube.." << '\n';
    static Cube *cube = NULL;
    if ( cube == NULL ){
        cube = new Cube();
        cube->run();
    }
    return false;
}

void Manager::exit(){
    // Clean up.
    GLFWwindow *window = glfwGetCurrentContext();
    glfwDestroyWindow( window );
    ImGui_ImplGlfwGL3_Shutdown();
}
