#ifndef CAMERA_H
#define CAMERA_H


#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include <cmath>
#include <iostream>
#include <ostream>



const float YAW = -90.0f;
const float PITCH = 0.0f;
const float ROLL = 0.0f;
const float SPEED = 2.5f;
const float SENS = 0.1f;
const float ZOOM = 120.0f;



class Camera{

    glm::vec3 camPos;
    glm::vec3 camFront;
    glm::vec3 camUp;
    glm::vec3 camRight;
    glm::vec3 worldUp;

    float Yaw;
    float Pitch;
    float Roll;

    float Sens;
    float Fov;

    /*
    This is basically what the glm::lookAt function is doing to get a matrix we can use for translation/rotation n such
    //functionally our positive z axis
    glm::vec3 cameraDirection = glm::normalize(camPos - cameraTarget);

    //do a cross product with an up vector to get our right (positive X)
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));

    //cross product again to get out positive y
    glm::vec3 camUp = glm::cross(cameraDirection,cameraRight);
    */

    public:

    Camera(glm::vec3 startingPos = glm::vec3(0,0,0), glm::vec3 up = glm::vec3(0,1.0,0),float yaw = YAW, float pitch = PITCH, float roll = ROLL)
        :
        camFront(glm::vec3 (0,0,-1)),
        Roll(ROLL),
        Sens(SENS),
        Fov(ZOOM)
    {
        std::cout << Sens << "\n";
        camPos=startingPos;
        worldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        Roll = roll;

        updateCamVectors();
    }

    void processMouse(float xoffset,float yoffset){

    xoffset *= Sens;
    yoffset *= Sens;

    setYaw(getYaw() + xoffset);
    setPitch(getPitch() + yoffset);

    if(getPitch() > 89.0f)
        setPitch(89.0f);
    if(getPitch() < -89.0f)
        setPitch(-89.0f);

    updateCamVectors();
    }

    void processScroll(float yOffset){
        Fov -= (float)yOffset;
        if (Fov < 1.0f)
            Fov = 1.0f;
        if (Fov > 120.0f)
            Fov = 120.0f;
    }

    //setters

    void setPos(glm::vec3 pos){
        camPos = pos;
        getViewMatrix();
    }
    void setFront(glm::vec3 front2){camFront = front2;}
    void setUp(glm::vec3 up){camUp = up;}


    void setPitch(float pitch2){Pitch = pitch2;}
    void setYaw(float yaw2){Yaw = yaw2;}
    void setRoll(float roll2){Roll = roll2;}

    //getters

    float getPitch(){return Pitch;}
    float getYaw(){return Yaw;}
    float getRoll(){return Roll;}

    float getFov(){return Fov;}

    glm::vec3 getPos(){return camPos;}
    glm::vec3 getFront(){return camFront;}
    glm::vec3 getUp(){return camUp;}


    glm::mat4 getViewMatrix(){
        return glm::lookAt(
        camPos,
  	    camPos + camFront,
  	    camUp);
    }


    private:

    void updateCamVectors(){
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        camFront = glm::normalize(front);
        // also re-calculate the Right and Up vector
        camRight = glm::normalize(glm::cross(camFront, worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        camUp    = glm::normalize(glm::cross(camRight, camFront));
    }

    void updateCamVectorsPlane(){
    // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        camFront = glm::normalize(front);
        // also re-calculate the Right and Up vector
        camRight = glm::normalize(glm::cross(camFront, worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        camUp    = glm::normalize(glm::cross(camRight, camFront));
    }

};
#endif
