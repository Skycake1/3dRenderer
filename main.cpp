#include <GLFW/glfw3.h>
#include <cstdio>
#include <iostream>

void error_callback(int error, const char* description);

int main(int argc, char *argv[]){

    glfwSetErrorCallback(error_callback);

    if(!glfwInit()){

	    std::cout << "glfw Initialisation failed";
        glfwTerminate();

    } else {

	    std::cout<<"glfw init sucessful yoohoo!";

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        
        GLFWwindow* window = glfwCreateWindow(640, 480, "Yo!", NULL, NULL);
        if(!window)
        {
            std::cout << "window failed to open";
        }
    
    }

}

void error_callback(int error, const char* description){
    fprintf(stderr, "Error: %s\n", description);
}
