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


        Texture2D(int height, int width, int nrChannels, int reqComp, std::string filePath){

            this->height = height;
            this->width = width;
            this->nrChannels = nrChannels;
            this->reqComp = reqComp;
            this->filePath = filePath;

            unsigned char *data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, reqComp);


            //generate and bind texture
            unsigned int texture;
            glGenTextures(1,&texture);
            glBindTexture(GL_TEXTURE_2D, texture);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            //actually generate the texture and make its mipmap
            if(data){
                //make sure to implement some way to either automatically detect for GL_RBGA or GL_RGB
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            } else {
                std::cout << "Texture " << filePath << " failed to load";
            }

            stbi_image_free(data);
        }

};
#endif
