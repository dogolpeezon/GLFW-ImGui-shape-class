cmake_minimum_required( VERSION 2.8 )
project(shape)
# Compiler debug flags
add_definitions(-Wall -Werror -g)
# Set source file directory
file(GLOB src_files ${PROJECT_SOURCE_DIR}/src/*)
# Set ImGui Libaries
#file(GLOB dep_files ${PROJECT_SOURCE_DIR}/imgui/*)
# Compile Makefile
add_executable(main ${src_files} ${dep_files})
# Libaries
target_link_libraries( main ${usr/lib} GL GLEW glfw3 X11 Xrandr
Xinerama Xxf86vm Xcursor pthread dl)
