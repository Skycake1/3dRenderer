#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <string>
#include <iostream>
#include <STB/stb_image.h>

//Incomplete color channel implementation

class Texture2D{

    public:
        int height,width,nrChannels,reqComp;
        std::string filePath;
        unsigned char *data;
        unsigned int texture;


        Texture2D(int width, int height, int nrChannels, int reqComp, std::string filePath){

            this->height = height;
            this->width = width;
            this->nrChannels = nrChannels;
            this->reqComp = reqComp;
            this->filePath = filePath;

        }

        void initTexture(unsigned int edgecontrol, unsigned int internalFormat){
            data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, reqComp);

            genTextures();
            setTexParameters(edgecontrol);
            genMipmaps(internalFormat);

        }


        void genTextures(){
            //generate and bind texture
            glGenTextures(1,&texture);
            glBindTexture(GL_TEXTURE_2D, texture);
        }

        void setTexParameters(unsigned int edgecontrol){
            //set the texture parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, edgecontrol);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, edgecontrol);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        }

        void genMipmaps(unsigned int internalFormat){
            //actually generate the texture and make its mipmap
            if(data){

            glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, internalFormat, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            } else {
                std::cout << "Texture " << filePath << " failed to load";
            }

            stbi_image_free(data);
        }

        void useTexture(int textureUnit){
            glActiveTexture(textureUnit); // activate the texture unit first before binding texture
            glBindTexture(GL_TEXTURE_2D, texture);
        }

};
#endif
