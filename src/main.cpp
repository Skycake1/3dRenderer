#include <GLFW/glfw3.h>
#include <iostream>

void error_callback(int error, const char* description);

const int width = 640;
const int height = 480;

int main(int argc, char *argv[]){

    glfwSetErrorCallback(error_callback);

    if(glfwInit() == 0){

	    std::cout << "glfw Initialisation failed";
        glfwTerminate();

    } else {

	    std::cout<<"glfw init sucessful yoohoo! \n";

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow* window = glfwCreateWindow(width, height, "Yo!", nullptr, nullptr);
        if(window != nullptr)
        {
            std::cout << "window created successfully";
        } else {
            std::cout << "window failed to open";
        }

    }

}

void error_callback(int error, const char* description){
    std::cerr << "Error: " << description << "\n";
}
