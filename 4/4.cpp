// Maxwell Bohn
// AERSP 424 HW2 #4

#include <GL/glew.h>
#include <GLFW/glfw3.h> 
#include <cmath> 
#include <iostream> 

int main() {
  // Initialize the GLFW library
  if (!glfwInit()) {
    // If initialization fails, print an error message and exit with code -1
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  // Create a GLFW window with dimensions 500x500 pixels and title "Drag vs Mach Number"
  GLFWwindow* window = glfwCreateWindow(500, 500, "Drag vs Mach Number", NULL, NULL);
  // Check if window creation failed
  if (!window) {
    // If window creation fails, print an error message, terminate GLFW, and exit with code -1
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  // Make the OpenGL context of the window current on the calling thread
  glfwMakeContextCurrent(window);

  // Initialize GLEW
  if (glewInit() != GLEW_OK) {
    // If GLEW initialization fails, print an error message and exit with code -1
    std::cerr << "Failed to initialize GLEW" << std::endl;
    return -1;
  }

  // Set the clear color to black
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  // Enter the rendering loop until the user closes the window
  while (!glfwWindowShouldClose(window)) {
    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Begin drawing axes
    glBegin(GL_LINES);

    // Set color to white for the axes
    glColor3f(1.0, 1.0, 1.0);

    // Draw X axis
    glVertex2f(-1.0f, 0.0f); // Start at the left
    glVertex2f(1.0f, 0.0f);  // End at the right

    // Draw Y axis
    glVertex2f(0.0f, -1.0f); // Start at the bottom
    glVertex2f(0.0f, 1.0f);  // End at the top

    // End drawing axes
    glEnd();

    // Begin drawing a line strip
    glBegin(GL_LINE_STRIP);
    // Set the color to red
    glColor3f(1.0, 0.0, 0.0);

    // Loop to plot Drag vs Mach Number to illustrate Mach divergence
    for (float M = 0.0f; M <= 2.0f; M += 0.01f) {
      float CD; // Drag coefficient
      // Calculate drag coefficient based on Mach number
      if (M < 1.0f) {
        // Before Mach 1.0, use a linear relationship for drag increase
        CD = 0.02 + M * 0.02;
      } else {
        // After Mach 1.0, simulate a quadratic increase in drag to represent Mach divergence
        CD = 0.02 + M * 0.02 + (M - 1.0f) * (M - 1.0f) * 0.1;
      }
      // Plot the point with adjusted coordinates for visualization
      glVertex2f(M - 1.0f, CD - 0.04f);
    }

    // End drawing
    glEnd();

    // Swap the front and back buffers
    glfwSwapBuffers(window);
    // Poll for and process events
    glfwPollEvents();
  }

  // Cleanup GLFW resources
  glfwTerminate();
  return 0; // Exit the program successfully
}