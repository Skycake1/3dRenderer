#ifndef SHADER_H
#define SHADER_H

#include "glm/ext/matrix_float4x4.hpp"
#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:

    unsigned int shaderProgramID;

    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath){

        this->vertexPath = vertexPath;
        this->fragmentPath = fragmentPath;
        //1. get our shadercode

        //Setup our objects to take input
        std::string vertexShadercode;
        std::string fragmentShadercode;

        std::ifstream vertexShaderFile;
        std::ifstream fragmentShaderFile;


        //throw exceptions
        vertexShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        fragmentShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

        try{
            //open the files

            vertexShaderFile.open(vertexPath);
            fragmentShaderFile.open(fragmentPath);
            std::stringstream vertexShaderStream, fragmentShaderStream;

            //read the files buffer contents into stream
            vertexShaderStream << vertexShaderFile.rdbuf();
            fragmentShaderStream << fragmentShaderFile.rdbuf();

            vertexShaderFile.close();
            fragmentShaderFile.close();

            vertexShadercode = vertexShaderStream.str();
            fragmentShadercode = fragmentShaderStream.str();


        } catch (std::ifstream::failure& e)
        {
            std::cout << "\n ----------------------------------------------------------------------------- \n";
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
            std::cout << "\n ----------------------------------------------------------------------------- \n";


        }

        const char* vertexShaderCode = vertexShadercode.c_str();
        const char* fragmentShaderCode = fragmentShadercode.c_str();
        //2. compile shaders

        unsigned int vertexShader,fragmentShader;

                    //vertex Shader--------------------------------------------------------------------

                vertexShader = glCreateShader(GL_VERTEX_SHADER);
                glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
                glCompileShader(vertexShader);

                checkCompileErrors(vertexShader, "VERTEX");

            //fragment shader-------------------------------------------------------------------

                fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
                glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
                glCompileShader(fragmentShader);

                checkCompileErrors(fragmentShader, "FRAGMENT");



        //shader program(basically linking these the fragment and vertex shader together)

            shaderProgramID = glCreateProgram();

            glAttachShader(shaderProgramID, vertexShader);
            glAttachShader(shaderProgramID, fragmentShader);
            glLinkProgram(shaderProgramID);

            checkCompileErrors(shaderProgramID, "PROGRAM");


        //we delete the shaders once we are done so they don't take up any more space
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);


    }
    // use/activate the shader
    void use()
    {
        glUseProgram(shaderProgramID);
    }
    // utility uniform functions
    void setBool(const std::string &name, bool value) const
    {
        glUniform1i(glGetUniformLocation(shaderProgramID,name.c_str()), (int)value);
    }
    void setInt(const std::string &name, int value) const
    {
        glUniform1i(glGetUniformLocation(shaderProgramID,name.c_str()), value);

    }
    void setFloat(const std::string &name, float value) const
    {
        glUniform1f(glGetUniformLocation(shaderProgramID,name.c_str()), value);

    }
       void setMat4(const std::string &name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }



private:

    const char* vertexPath;
    const char* fragmentPath;
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(unsigned int shader, std::string type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {

                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;

                std::cout << "vertex file path: " << vertexPath << "\n";
                std::cout << "fragment file path: " << fragmentPath << "\n";

            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }


};

#endif
