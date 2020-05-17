//
// Created by szymon on 11.04.2020.
//

#ifndef OPENGL_CAMERA_H
#define OPENGL_CAMERA_H

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>

//Define possible movement options
enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

//Constant values
const float SPEED       =   1.0f;
const float MAXPITCH    =   25.0f;
const float PITCH       =   0.0f;
const float YAW         =   0.0f;

class Camera {

private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float pitch; //up or down (corresponds to X axis)
    float yaw; //left or right (corresponds to Y axis)
    // There's also roll (corresponds to Z axis)

    bool movingForward;
    bool movingBackward;
    bool movingLeft;
    bool movingRight;

    float movementSpeed;
    float mouseSpeed;
    float maxPitch;

    void update( float deltaTime = 0.0f );
    void move(float deltaTime  );

public:
    Camera( glm::vec3 position = glm::vec3(0.0f, 2.0f, 0.0f),
            glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
            glm::vec3 front = glm::vec3(0.0f, 2.0f, -10.0f));

    //setters
    void setMovingForward(bool isMoving = false);
    void setMovingBackward(bool isMoving = false);
    void setMovingLeft(bool isMoving = false);
    void setMovingRight(bool isMoving = false);

    glm::mat4 getViewMatrix(float deltaTime = 0.0f);

    void keyboardInput(CameraMovement cameraMovement, float deltaTime);
    void mouseInput(float xOffset, float yOffset);

};
#endif //OPENGL_CAMERA_H
