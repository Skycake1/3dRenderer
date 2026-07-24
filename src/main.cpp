#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void error_callback(int error, const char* description);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

bool initGlad();
void processInput(GLFWwindow *window);

const int width = 640;
const int height = 480;

unsigned int vertexShader;
unsigned int fragmentShader;
unsigned int shaderProgram;


// These 2 will later disappear and become seperate files
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";


const char *fragmentShaderSource = "#version 330 core \n"
    "out vec4 FragColor; \n"
    "void main()\n"
    "{\n"
        "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";



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
        glViewport(0, 0, width, height);
        //which is why we setup our callback function right here
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


        //shader setup

            //vertex Shader--------------------------------------------------------------------

                vertexShader = glCreateShader(GL_VERTEX_SHADER);
                glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
                glCompileShader(vertexShader);

            int  success;
            char infoLog[512];
                glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

                if(!success)
                {
                    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
                    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
                } else {
                    std::cout << "Vertex Shader Loaded Successfully" << '\n';
                }

            //fragment shader-------------------------------------------------------------------

                fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
                glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
                glCompileShader(fragmentShader);


                glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

                if(!success)
                {
                    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
                    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
                } else {
                    std::cout << "Fragment Shader Loaded Successfully" << '\n';
                }


        //shader program(basically linking these the fragment and vertex shader together)

            shaderProgram = glCreateProgram();

            glAttachShader(shaderProgram, vertexShader);
            glAttachShader(shaderProgram, fragmentShader);
            glLinkProgram(shaderProgram);



            glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
            if(!success) {
                glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
            }else {
                std::cout << "Shader Program Linked Successfully" << '\n';
            }

            //we delete the shaders once we are done so they don't take up any more space
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

        const float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
        };

        //VBO is the literal data and VAO is how to process it

        unsigned int VBO, VAO;

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


        //basically a rough explanation of the vertexes that we are tossing in (size of the vertices, what type and if they are normalised)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);


        //Render Loop
        while(!glfwWindowShouldClose(window))
        {
            //input
            processInput(window);

            //Rendering Commands Here
            glUseProgram(shaderProgram);

            //clear colour goes first because otheriwse it covers the screen
            glClearColor( 0.16f, 0.01f, 0.11f, 0.5f);
            glClear(GL_COLOR_BUFFER_BIT);


            glBindVertexArray(VAO);


            glDrawArrays(GL_TRIANGLES, 0, 3);





            //check and call events and swap buffers
            glfwSwapBuffers(window);
            glfwPollEvents();
        }



        std::cout<< "\n-----------------------------------------------------------\n";
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
