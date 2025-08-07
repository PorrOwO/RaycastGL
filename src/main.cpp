#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "headers/shader.h"
#include "headers/camera.h"
#include "headers/stb_image.h"

// CONSTANTS
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// FUNCTION PROTOTYPES
void frame_buffer_size_callback(GLFWwindow*, int, int);
void mouse_callback(GLFWwindow*, double, double);
void scroll_callback(GLFWwindow*, double, double);
void processInput(GLFWwindow*);


// DATA
// camera
Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = WINDOW_WIDTH / 2.0f;
float lastY = WINDOW_HEIGHT / 2.0f;
bool firstMouse = true;

// time
float deltaTime = 0.0f; // time between current frame and last frame
float lastFrame = 0.0f; 

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

glm::vec3 cubePositions[] = {
  glm::vec3( 0.0f,  0.0f,  0.0f), 
  glm::vec3( 2.0f,  5.0f, -15.0f), 
  glm::vec3(-1.5f, -2.2f, -2.5f),  
  glm::vec3(-3.8f, -2.0f, -12.3f),  
  glm::vec3( 2.4f, -0.4f, -3.5f),  
  glm::vec3(-1.7f,  3.0f, -7.5f),  
  glm::vec3( 1.3f, -2.0f, -2.5f),  
  glm::vec3( 1.5f,  2.0f, -2.5f), 
  glm::vec3( 1.5f,  0.2f, -1.5f), 
  glm::vec3(-1.3f,  1.0f, -1.5f)  
};

int main(int arc, char* argv[]) {
  //GLFW initialization
  if(!glfwInit()){
    std::cerr << "error: GLFW init failed" << std::endl;
    return -1;
  }
  GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_WIDTH, "OpenGL Window", nullptr, nullptr);
  if(!window){
    std::cerr << "error: GLFW window creation failed" << std::endl;
    glfwTerminate();
    return -1;
  }
  
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  //initialize GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }  
  
  glEnable(GL_DEPTH_TEST);
  //shader building and compilation
  Shader shader = Shader("/home/porrowo/Documents/computer_graphics/raycasterGL/src/shaders/vShader.glsl","/home/porrowo/Documents/computer_graphics/raycasterGL/src/shaders/fShader.glsl");
  //generate vertex buffer object
  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
    
  //bind VAO
  glBindVertexArray(VAO);
   //bind VBO to array buffer
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


  //position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  //texture attribute
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
 
  //texture loading
  unsigned int texture1, texture2;
  //texture1
  glGenTextures(1, &texture1);
  glBindTexture(GL_TEXTURE_2D, texture1);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int width, height, nrChannels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char* data = stbi_load("/home/porrowo/Documents/computer_graphics/raycasterGL/src/textures/wall.jpg", &width, &height, &nrChannels, 0);
  if(data){
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }else{
    std::cerr<< "Failed to load texture" << std::endl;
  }
  stbi_image_free(data);
  //texture2
  glGenTextures(1, &texture2);
  glBindTexture(GL_TEXTURE_2D, texture2);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  data = stbi_load("/home/porrowo/Documents/computer_graphics/raycasterGL/src/textures/awesomeface.png", &width, &height, &nrChannels, 0);
  if(data){
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }else{
    std::cerr<< "Failed to load texture" << std::endl;
  }
  stbi_image_free(data);
  
  shader.use();
  shader.setInt("texture1", 0);
  shader.setInt("texture2", 1);
  //render loop
  while(!glfwWindowShouldClose(window)){
    //time management
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    //input processing
    processInput(window);
  
    //rendering
    glClearColor(0.1f, 0.2f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //bind textures
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    
    //activate shader
    shader.use();
  
    //pass projection matrix to shader
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WINDOW_WIDTH/ (float)WINDOW_HEIGHT, 0.1f, 100.0f);
    shader.setMat4("projection", projection);
    
    //camera/view matrix transformation
    glm::mat4 view = camera.getViewMatrix();
    shader.setMat4("view", view);

    //render cubes
    glBindVertexArray(VAO);
    for(int i = 0; i < 10; i++){
      glm::mat4 model = glm::mat4(1.0f);
      model = glm::translate(model, cubePositions[i]);
      float angle = 20.0f * i;
      model = glm::rotate(model, glm::radians(angle * (float)glfwGetTime()), glm::vec3(1.0f, 0.3f, 0.5f));
      shader.setMat4("model", model);

      glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    //check events and swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
 
  //cleanup
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glfwTerminate();
  return 0;
}

//callback to adjust viewport on window resize
void frame_buffer_size_callback(GLFWwindow* win, int width, int height){
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* win){
  if(glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS){
    glfwSetWindowShouldClose(win, true);
  }
  if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS)
    camera.processKeyboard(FORWARD, deltaTime);
  if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)
    camera.processKeyboard(BACKWARD, deltaTime);
  if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS)
    camera.processKeyboard(LEFT, deltaTime);
  if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS)
    camera.processKeyboard(RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* win, double xposIn, double yposIn){
  float xPos = static_cast<float>(xposIn);
  float yPos = static_cast<float>(yposIn);

  if(firstMouse){
    lastX = xPos;
    lastY = yPos;
    firstMouse = false;
  }
  
  float xOffset = xPos - lastX;
  float yOffset = lastY - yPos; // reversed since y-coordinates go from bottom to top
  lastX = xPos;
  lastY = yPos;

  camera.processMouseMovement(xOffset, yOffset);
}

void scroll_callback(GLFWwindow* win, double xoffset, double yoffset){
  camera.processMouseScroll(static_cast<float>(yoffset));
} 
