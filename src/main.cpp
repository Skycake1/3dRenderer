#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void error_callback(int error, const char* description);


void framebuffer_size_callback(GLFWwindow* window, int width, int height);

bool initGlad();
void processInput(GLFWwindow *window);

const int width = 640;
const int height = 480;

int main(int argc, char *argv[]){

    glfwSetErrorCallback(error_callback);



    if(glfwInit() == 0){

	    std::cout << "glfw Initialisation failed";
        glfwTerminate();
    } else {




	    std::cout<<"glfw init sucessful yoohoo! \n";

        //window hint functionally act as little settings for the window
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        //this creates a pointer to our window and then checks if the window was created correctly
        GLFWwindow* window = glfwCreateWindow(width, height, "Yo!", nullptr, nullptr);
        if(window != nullptr)
        {
            std::cout << "window created successfully";
        } else {
            std::cout << "window failed to open";
        }

        //makes glfw look at our current context
        glfwMakeContextCurrent(window);

        //Initialise glad so that way you can do cross platform stuff with opengl
         if(!initGlad())
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            glfwTerminate();
            return -1;
        }

        //basically our canvas size, and we want it to be the same as the window size
        glViewport(0, 0, width, height);
        //which is why we setup our callback function right here
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


        //Render Loop
        while(!glfwWindowShouldClose(window))
        {
            //input
            processInput(window);

            //Rendering Commands Here
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            //check and call events and swap buffers
            glfwSwapBuffers(window);
            glfwPollEvents();
        }



        glfwTerminate();
        return 0;
    }

}

void error_callback(int error, const char* description){
    std::cerr << "Error: " << description << "\n";
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

bool initGlad(){
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    } else {
    return true;
    }
}


void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
