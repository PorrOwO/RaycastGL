#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//abstract movement option from window specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

//default camera attributes
const float YAW         = -90.0f;
const float PITCH       = 0.0f;
const float SPEED       = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM        = 45.0f;

class Camera {
  public:
    //camera attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    //euler angles
    float Yaw;
    float Pitch;
    //camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    //vector constructor 
    Camera(glm::vec3 = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 = glm::vec3(0.0f, 1.0f, 0.0f), float = YAW, float = PITCH);
    //float constructor
    Camera(float, float, float, float, float, float, float, float);
    //returns view matrix
    glm::mat4 getViewMatrix();
    //process input
    void processKeyboard(Camera_Movement, float);
    void processMouseMovement(float, float, GLboolean = true);
    void processMouseScroll(float);

  private:
    //update camera vectors
    void updateCameraVectors();
    //calculate front vector from yaw and pitch
};
#endif
