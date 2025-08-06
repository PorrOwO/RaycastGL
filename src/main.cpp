#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "headers/shader.h"

// CONSTANTS
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define MAP_SIZE 8

// DATA
float vertices[] = {
   0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, //top right
   0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, //bottom right
  -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, //bottom left
  //-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, //top left
};

unsigned int indices[] = {
  0, 1, 3, //first triangle
  1, 2, 3  //second triangle  
};

// FUNCTION PROTOTYPES
void frame_buffer_size_callback(GLFWwindow*, int, int);
void processInput(GLFWwindow*);


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
  
  //initialize GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }  

  //shader class initialization
  Shader shader = Shader("/home/porrowo/Documents/computer_graphics/raycasterGL/src/shaders/vShader.glsl", 
                      "/home/porrowo/Documents/computer_graphics/raycasterGL/src/shaders/fShader.glsl");
  
  //generate vertex buffer object
  unsigned int VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  
  glGenBuffers(1, &VBO);
  //glGenBuffers(1, &EBO);
    
  //bind VAO
  glBindVertexArray(VAO);
  //bind VBO to array buffer
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  //position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  //color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);


  //render loop
  while(!glfwWindowShouldClose(window)){
    //input processing
    processInput(window);
  
    //rendering
    glClearColor(0.1f, 0.2f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    //draw triangle
    shader.use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
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
}
