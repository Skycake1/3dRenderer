#include "custom/camera.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/geometric.hpp"
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <iostream>

#include <custom/shaderClass.hpp>
#include <custom/texture2D.hpp>

#include <filesystem>

#define STB_IMAGE_IMPLEMENTATION
#include <STB/stb_image.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



void error_callback(int error, const char* description);

void framebuffer_size_callback(GLFWwindow* window, int scrWidth, int scrHeight);

bool initGlad();
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset,double yoffset);

Camera camera(glm::vec3(0,0,5.0));

const int scrWidth = 1920;
const int scrHeight = 1080;

float lastX = (float)scrWidth/2, lastY = (float)scrHeight/2;
bool firstMouse = true;

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f;

unsigned int vertexShader;
unsigned int fragmentShader;

float cameraSpeed = 0.0f;

std::string currentPath = std::filesystem::current_path();

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);


glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f,  2.0f, -2.5f),
    glm::vec3( 1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};



int main(int argc, char *argv[]){


    //the code file is run inside of 3dRenderer/build which is back bc we can't access the shader files
    //pop_back() is run 5 times, this solution IS NOT portable AT ALL and I need to find a better method but it works for now
    //FIX THIS WHEN I CAN
    //remove the "build" part from the current filepath
    for(int i = 0; i < 5 ; i++){
        currentPath.pop_back();
    }

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
        GLFWwindow* window = glfwCreateWindow(scrWidth, scrHeight, "Yo!", nullptr, nullptr);
        if(window != nullptr)
        {
            std::cout << "window created successfully \n";
        } else {
            std::cout << "window failed to open \n";
        }

        //makes glfw look at our current context
        glfwMakeContextCurrent(window);

        //Initialise glad so that way you can do cross platform stuff with opengl
         if(!initGlad())
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            glfwTerminate();
            return -1;
        } else {
            std::cout << "GLAD intialized correctly" << std::endl;
        }


        //basically our canvas size, and we want it to be the same as the window size
        glViewport(0, 0, scrWidth, scrHeight);
        //which is why we setup our callback function right here
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetScrollCallback(window, scroll_callback);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


        //enable depth test
        glEnable(GL_DEPTH_TEST);
        //shader setup

        Shader lightShader((currentPath + "shaders/vertex/vertexShader.vert").c_str(),(currentPath+ "shaders/fragment/fragmentShader.frag").c_str());
        Shader lightSourceShader((currentPath + "shaders/vertex/lightSourceShader.vert").c_str(),(currentPath+ "shaders/fragment/lightSourceShader.frag").c_str());
        const float colorScale = 255.0f;
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
    };

        unsigned int indices[] = {

            0, 1, 3, // first triangle
            1, 2, 3  // second triangle

        };

        const float textCoords[] = {
               0.0f, 0.0f,  // lower-left corner
               1.0f, 0.0f,  // lower-right corner
               0.5f, 1.0f   // top-center corner
        };




        //VBO is the vertex data being stored in gpu memory and VAOs manage the state and configuration of em
        //And EBO is basically a set indicies that tell opengl what points to draw and in what order
        // they are useful for if you want draw shapes that are made of triangles but are not triangles
        //(eg: a square is made of 2 triangles and we don't wanna waste resources drawing the second half of them)

        //basically, raw corner data, how to confiure those corners and their state, and a best way to draw them
         // first, configure the cube's VAO (and VBO)
    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    // we only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need (it's already bound, but we do it again for educational purposes)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        //textures
        //-------------------------------------------------------------------------------

        //set our parameters for texture loading


        int width, height, nrChannels;

        Texture2D container(width,height,nrChannels,0,(currentPath + "assets/container.jpg"));
        container.initTexture(GL_REPEAT, GL_RGB);

        Texture2D awesomeFace(width,height,nrChannels,0,(currentPath + "assets/awesomeface.png"));
        awesomeFace.initTexture(GL_REPEAT, GL_RGBA, true);


        // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
        // -------------------------------------------------------------------------------------------
        lightShader.use(); // don't forget to activate/use the shader before setting uniforms!
        // either set it manually like so:

        //---------------------------------------------------------------------------------------

            //translation stuffs



        glm::mat4 model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 view          = glm::mat4(1.0f);
        glm::mat4 projection    = glm::mat4(1.0f);



        while(!glfwWindowShouldClose(window))
        {
            //input
            //Rendering Commands Here

            float currentFrame = static_cast<float>(glfwGetTime());
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            cameraSpeed = 2.5 * deltaTime;

            processInput(window);


            glClearColor( 0.16f, 0.01f, 0.11f, 0.5f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            //shaders goes here
            // don’t forget to use the corresponding shader program first
            lightShader.use();
            lightShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
            lightShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);


            projection = glm::perspective(glm::radians(camera.getFov()), (float)scrWidth / (float)scrHeight , 0.1f, 100.0f);
            lightShader.setMat4("projection", projection);

            view = camera.getViewMatrix();
            lightShader.setMat4("view", view);

            glm::mat4 model = glm::mat4(1.0f);
            lightShader.setMat4("model", model);

            glBindVertexArray(cubeVAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);

                   // also draw the lamp object
            lightSourceShader.use();
            lightSourceShader.setMat4("projection", projection);
            lightSourceShader.setMat4("view", view);

            model = glm::mat4(1.0f);
            model = glm::translate(model, lightPos);
            model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube

            lightSourceShader.setMat4("model", model);

            glBindVertexArray(lightCubeVAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);


            //check and call events and swap buffers
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

           // ------------------------------------------------------------------------
            glDeleteVertexArrays(1, &cubeVAO);
            glDeleteVertexArrays(1, &lightCubeVAO);
            glDeleteBuffers(1, &VBO);
            //glDeleteBuffers(1, &EBO);
            glDeleteProgram(lightShader.shaderProgramID);

        std::cout<< "\n-----------------------------------------------------------\n";
        glfwTerminate();
        return 0;
    }

}

void error_callback(int error, const char* description){
    std::cerr << "Error: " << description << "\n";
}

void framebuffer_size_callback(GLFWwindow* window, int scrWidth, int scrHeight)
{
    glViewport(0, 0, scrWidth, scrHeight);
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
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.setPos(camera.getPos() + cameraSpeed * camera.getFront());
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.setPos(camera.getPos() - cameraSpeed * camera.getFront());
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.setPos(camera.getPos() - glm::normalize(glm::cross(camera.getFront(), camera.getUp()))* cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.setPos(camera.getPos() + glm::normalize(glm::cross(camera.getFront(), camera.getUp()))* cameraSpeed);

}


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.processMouse(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset,double yoffset){
    camera.processScroll(yoffset);
}
