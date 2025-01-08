#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Debugger.h>
#include <VertexBuffer.h>
#include <VertexBufferLayout.h>
#include <IndexBuffer.h>
#include <VertexArray.h>
#include <Shader.h>
#include <Texture.h>
#include <Camera.h>
#include <Cube.h>
#include <vector>
#include <RubiksCube.h>


#include <iostream>


float cubeVertices[] = {
    // positions          // colors             // texCoords
    // Front face
    -0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,    0.0f, 0.0f,  // Bottom-left
     0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,    1.0f, 0.0f,  // Bottom-right
     0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,  // Top-right
    -0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // Top-left

    // Back face
    -0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,    0.0f, 0.0f,  // Bottom-left
     0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,    1.0f, 0.0f,  // Bottom-right
     0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,    1.0f, 1.0f,  // Top-right
    -0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,    0.0f, 1.0f,  // Top-left

    // Left face
    -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,    0.0f, 0.0f,  // Bottom-left
    -0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,    1.0f, 0.0f,  // Bottom-right
    -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,    1.0f, 1.0f,  // Top-right
    -0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f,    0.0f, 1.0f,  // Top-left

    // Right face
     0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 0.0f,    0.0f, 0.0f,  // Bottom-left
     0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 0.0f,    1.0f, 0.0f,  // Bottom-right
     0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,    1.0f, 1.0f,  // Top-right
     0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,    0.0f, 1.0f,  // Top-left

    // Top face
    -0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 1.0f,    0.0f, 0.0f,  // Bottom-left
     0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 1.0f,    1.0f, 0.0f,  // Bottom-right
     0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 1.0f,    1.0f, 1.0f,  // Top-right
    -0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 1.0f,    0.0f, 1.0f,  // Top-left

    // Bottom face
    -0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 1.0f,    0.0f, 0.0f,  // Bottom-left
     0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 1.0f,    1.0f, 0.0f,  // Bottom-right
     0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 1.0f,    1.0f, 1.0f,  // Top-right
    -0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 1.0f,    0.0f, 1.0f   // Top-left
};

unsigned int cubeIndices[] = {
    0, 1, 2,  2, 3, 0,  // Front face
    4, 5, 6,  6, 7, 4,  // Back face
    8, 9, 10, 10, 11, 8, // Left face
    12, 13, 14, 14, 15, 12, // Right face
    16, 17, 18, 18, 19, 16, // Top face
    20, 21, 22, 22, 23, 20  // Bottom face
};


/* Window size */
const unsigned int width = 800;
const unsigned int height = 800;
// const float FOVdegree = 45.0f;  // Field Of View Angle
const float near = 0.1f;
const float far = 100.0f;


int main(int argc, char* argv[])
{
    int cubeSize = 3;
    if(argc >= 2){
        cubeSize = std::stoi(argv[1]);
    }
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
    {
        return -1;
    }
    
    /* Set OpenGL to Version 3.3.0 */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "OpenGL", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Load GLAD so it configures OpenGL */
    gladLoadGL();

    /* Control frame rate */
    glfwSwapInterval(1);

    /* Print OpenGL version after completing initialization */
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    /* Set scope so that on widow close the destructors will be called automatically */
    {
        /* Blend to fix images with transperancy */
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        /* Create cube */
        //Cube cube = Cube();
        Texture texture("res/textures/plane.png");
        Shader shader("res/shaders/basic.shader");
            // Configure the shared VertexArray
        VertexArray va;
        VertexBuffer vb(cubeVertices, sizeof(cubeVertices));
        VertexBufferLayout layout;
        layout.Push<float>(3);  // Positions
        layout.Push<float>(3);  // Colors
        layout.Push<float>(2);  // Texture coordinates
        va.AddBuffer(vb, layout);  // Configure the VAO

        // Setup shared IndexBuffer
        IndexBuffer ib(cubeIndices, sizeof(cubeIndices));
        ib.Bind();  // Bind the IndexBuffer to the VAO
        Rubikscube rubik = Rubikscube(cubeSize, &shader, &texture, &va);
    
        /* Enables the Depth Buffer */
    	GLCall(glEnable(GL_DEPTH_TEST));

        /* Create camera */
        Camera camera(width, height);
        //Added
        const float FOVdegree = 45.0f;
        const float aspectRatio = static_cast<float>(width) / height;
        camera.SetPerspective(FOVdegree, aspectRatio, near, far);
        camera.SetPosition(glm::vec3(0.0f, 0.0f, 10.0f)); // Move the camera 10 units back
        //End
        camera.SetRubiksCube(&rubik);
        camera.EnableInputs(window);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {

            /* Initialize uniform color */
            glm::mat4 view = camera.GetViewMatrix();
            glm::mat4 proj = camera.GetProjectionMatrix();
            glm::mat4 mvp = proj * view;

            rubik.Render(mvp, window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}