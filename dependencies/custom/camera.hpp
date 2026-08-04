#ifndef CAMERA_H
#define CAMERA_H


#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"

class Camera{


    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    float roll = 0;
    float pitch = 0;
    float yaw = -90;

    glm::mat4 view;

    glm::vec3 direction;

    /*
    This is basically what the glm::lookAt function is doing to get a matrix we can use for translation/rotation n such
    //functionally our positive z axis
    glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);

    //do a cross product with an up vector to get our right (positive X)
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));

    //cross product again to get out positive y
    glm::vec3 cameraUp = glm::cross(cameraDirection,cameraRight);
    */
    public:
    Camera(){


        getViewMatrix();

        updateAngles();
    }

    void updatePos(glm::vec3 pos){
        cameraPos = pos;
        getViewMatrix();
    }

    void updateAngles(){

        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    }

    void setAngles(glm::vec3 desiredAngles){
        direction = desiredAngles;
    }

    void setFront(glm::vec3 front2){cameraFront = front2;}

    void setPitch(float pitch2){pitch = pitch2;}
    void setYaw(float yaw2){yaw = yaw2;}
    void setRoll(float roll2){roll = roll2;}

    float getPitch(){return pitch;}
    float getYaw(){return yaw;}
    float getRoll(){return roll;}

    glm::vec3 getCameraAngle(){
        return direction;
    }

    glm::vec3 getPos(){
        return cameraPos;
    }

    glm::vec3 getFront(){
        return cameraFront;
    }

    glm::vec3 getUp(){
        return cameraUp;
    }

    glm::mat4 getViewMatrix(){
        return view = glm::lookAt(
        cameraPos,
  	    cameraPos + cameraFront,
  	    cameraUp);
    }


    private:

};
#endif
