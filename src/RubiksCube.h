#pragma once
#define GLM_ENABLE_EXPERIMENTAL

#include <vector>
#include "Cube.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <GLFW/glfw3.h>
//#include <algorithm>

class Rubikscube {
private:
    int m_Size;                // Dimension of the Rubik's Cube (e.g., 3 for 3x3x3)
    glm::mat4 m_ModelMatrix;   // For global transformations
    std::vector<std::vector<std::vector<Cube*>>> m_CubeMatrix; // 3D matrix of cube pointers
    bool clock;
    std::vector<int> centerRotation;
    std::vector<int> locker;
    char axisLocker;


public:
    Rubikscube(int size, Shader* shader, Texture* texture, VertexArray* va);
    void Render(const glm::mat4& viewProjectionMatrix, GLFWwindow* window);
    void RotateWall(const std::string& wall, float angle);
    void SetGlobalTransform(const glm::mat4& transform);
    void Rotate(const float Xangle, const float Yangle);
    ~Rubikscube(); 
    void RotateWall45(int layerIndex, glm::vec3& axis, const glm::mat4& viewProjectionMatrix, GLFWwindow* window, float sensitivity);
    void indexClockWise(int layerIndex, glm::vec3& axis);
    void indexCounterClockWise(int layerIndex, glm::vec3& axis);
    void setClockWise();
    void setCenterRotation(glm::vec3& axis);
    int getSize();
};
