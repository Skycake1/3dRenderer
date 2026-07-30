#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <iostream>

#include <custom/shaderClass.h>
#include <custom/texture2D.h>

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

const int scrWidth = 640;
const int scrHeight = 480;

unsigned int vertexShader;
unsigned int fragmentShader;

std::string currentPath = std::filesystem::current_path();




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


        //shader setup

        Shader ourShader((currentPath + "shaders/vertex/vertexShader.vs").c_str(),(currentPath+ "shaders/fragment/fragmentShader.fs").c_str());

        const float colorScale = 255.0f;

        float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
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
        unsigned int VBO, VAO,EBO;


        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        //glGenBuffers(1,&EBO);

        glBindVertexArray(VAO);



        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        /*
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
*/
        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        /*
        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        */
         // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);


        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        //textures
        //-------------------------------------------------------------------------------

        //set our parameters for texture loading

        int width, height, nrChannels;

        Texture2D container(width,height,nrChannels,0,(currentPath + "assets/container.jpg"));
        container.initTexture(GL_MIRRORED_REPEAT, GL_RGB);

        Texture2D awesomeFace(width,height,nrChannels,0,(currentPath + "assets/awesomeface.png"));
        stbi_set_flip_vertically_on_load(true);
        awesomeFace.initTexture(GL_REPEAT, GL_RGBA);


        // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
        // -------------------------------------------------------------------------------------------
        ourShader.use(); // don't forget to activate/use the shader before setting uniforms!
        // either set it manually like so:
        glUniform1i(glGetUniformLocation(ourShader.shaderProgramID, "texture1"), 0);
        // or set it via the texture class
        ourShader.setInt("texture2", 1);

        //---------------------------------------------------------------------------------------

            //translation stuffs

        glm::mat4 model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 view          = glm::mat4(1.0f);
        glm::mat4 projection    = glm::mat4(1.0f);


        unsigned int modelLoc;
        unsigned int viewLoc;

        //Render Loop
        float opacity = 0.2f;
        unsigned int transformLoc;
        while(!glfwWindowShouldClose(window))
        {
            //input
            processInput(window);

            //Rendering Commands Here



            ourShader.use();



            //clear colour goes first because otheriwse it covers the screen
            glClearColor( 0.16f, 0.01f, 0.11f, 0.5f);
            glClear(GL_COLOR_BUFFER_BIT);

            if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
                opacity -= 0.05;
            }

            if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
                opacity += 0.05;
            }

            if(glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS){
                opacity = 0.2;
            }


            //Matrix transformations

            model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            view          = glm::mat4(1.0f);
            projection    = glm::mat4(1.0f);

            //rotate the model 55 degrees around the x axis
            //model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
            //move the world forward 3 units
            view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

            //define our projetion matrix
            projection = glm::perspective(glm::radians(45.0f), (float)scrWidth / (float)scrHeight , 0.1f, 100.0f);


            modelLoc = glad_glGetUniformLocation(ourShader.shaderProgramID, "model");
            viewLoc = glad_glGetUniformLocation(ourShader.shaderProgramID, "view");

            //first way to pass to shaders
            glUniformMatrix4fv(modelLoc,1,GL_FALSE, glm::value_ptr(model));
            //second way
            glUniformMatrix4fv(viewLoc,1,GL_FALSE, &view[0][0]);
            //third way
            ourShader.setMat4("projection", projection);

            ourShader.setFloat("opacity", opacity);
            container.useTexture(GL_TEXTURE0);
            awesomeFace.useTexture(GL_TEXTURE1);



            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);




            //check and call events and swap buffers
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

           // ------------------------------------------------------------------------
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);
            //glDeleteBuffers(1, &EBO);
            glDeleteProgram(ourShader.shaderProgramID);

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
}
