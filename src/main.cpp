#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// CONSTANTS
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define MAP_SIZE 8

// STRUCTS
struct Map {
  int cellSize = 64;
  int data[MAP_SIZE][MAP_SIZE] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 1},
    {1, 1, 0, 0, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1}
  };
};

struct Player {
  float x = 0.6f;
  float y = 0.6f;
  //float angle = 0.0f; // in radians
};

// FUNCTION PROTOTYPES
void frame_buffer_size_callback(GLFWwindow*, int, int);

int main(int arc, char* argv[]) {
  Map map;
  Player player;

  if(!glfwInit()){
    std::cerr << "error: GLFW init failed" << std::endl;
    return -1;
  }
  GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL Window", nullptr, nullptr);
  if(!window){
    std::cerr << "error: GLFW window creation failed" << std::endl;
    glfwTerminate();
    return -1;
  }
  
  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }  

  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);

  //render loop
  while(!glfwWindowShouldClose(window)){
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  




  glfwTerminate();
  return 0;
}

//callback to adjust viewport on window resize
void frame_buffer_size_callback(GLFWwindow* win, int width, int height){
  glViewport(0, 0, width, height);
}
