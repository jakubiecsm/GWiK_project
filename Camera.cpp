//
// Created by szymon on 11.04.2020.
//

#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, glm::vec3 front)
                : movementSpeed(SPEED), maxPitch(MAXPITCH), pitch(PITCH), yaw(YAW){
    this->position = position;
    this->worldUp = up;
    this->front = front;
    movingForward = false;
    movingBackward = false;
    movingLeft = false;
    movingRight = false;

    update();
}

void Camera::setMovingForward(bool isMoving) { movingForward = isMoving;}
void Camera::setMovingBackward(bool isMoving) {movingBackward = isMoving;}
void Camera::setMovingLeft(bool isMoving) { movingLeft = isMoving;}
void Camera::setMovingRight(bool isMoving) { movingRight = isMoving;}

glm::mat4 Camera::getViewMatrix(float deltaTime) {
    update(deltaTime);
    return glm::lookAt(position, position + front, up);
}

void Camera::keyboardInput(CameraMovement cameraMovement, float deltaTime) {
    if (cameraMovement == FORWARD)  setMovingForward(true);
    if (cameraMovement == BACKWARD) setMovingBackward(true);
    if (cameraMovement == LEFT)     setMovingLeft(true);
    if (cameraMovement == RIGHT)    setMovingRight(true);
}

void Camera::mouseInput(float x, float y) {

    yaw += x;
    pitch -= y;

    if (pitch > maxPitch) pitch = maxPitch;
    else if (pitch < -maxPitch) pitch = -maxPitch;

    update();
}

void Camera::move(float deltaTime) {
    float distance = movementSpeed * deltaTime;
    if (movingForward) position += front * distance;
    if (movingBackward) position -= front * distance;
    if (movingRight) position += right * distance;
    if (movingLeft) position -= right * distance;
}

void Camera::update(float deltaTime) {

    if (deltaTime != 0.0f) move(deltaTime);

    glm::vec3 tempFront;
    tempFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    tempFront.y = sin(glm::radians(pitch));
    tempFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(tempFront);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}