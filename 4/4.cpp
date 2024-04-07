// Maxwell Bohn
// AERSP 424 HW2 #4 (change to different equation and get it running)

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

int main() {
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  GLFWwindow* window = glfwCreateWindow(500, 500, "Drag vs Mach Number", NULL, NULL);
  if (!window) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  if (glewInit() != GLEW_OK) {
    std::cerr << "Failed to initialize GLEW" << std::endl;
    return -1;
  }

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINE_STRIP);
    glColor3f(1.0, 0.0, 0.0); // Red color

    // Plotting Drag vs Mach Number to illustrate Mach divergence
    for (float M = 0.0f; M <= 2.0f; M += 0.01f) {
      // Simplified representation of drag increasing, especially after Mach 1
      float CD;
      if (M < 1.0f) {
        CD = 0.02 + M * 0.02; // Before Mach divergence, linear increase
      } else {
        // After Mach divergence, quadratic increase to simulate sharp rise in drag
        CD = 0.02 + M * 0.02 + (M - 1.0f) * (M - 1.0f) * 0.1;
      }
      glVertex2f(M - 1.0f, CD - 0.04f); // Adjusted for visualization
    }

    glEnd();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}