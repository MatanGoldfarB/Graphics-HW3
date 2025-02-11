#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <Debugger.h>
#include <Shader.h>
#include "RubiksCube.h"
#include <random> // For random number generation


class Camera
{
    private:
        // View and Projection
        glm::mat4 m_View = glm::mat4(1.0f);
        glm::mat4 m_Projection = glm::mat4(1.0f);

        // View matrix paramters
        glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 m_Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);

        // Projection matrix parameters
        float m_Near = 0.1f; 
        float m_Far = 100.0f;
        int m_Width;
        int m_Height;

        // Orthographic Projection parameters
        float m_Left = -1.0f;
        float m_Right = 1.0f;
        float m_Bottom = -1.0f; 
        float m_Top = 1.0f;
        int rotFactor;

    public:
        // Prevent the camera from jumping around when first clicking left click
        double m_OldMouseX = 0.0;
        double m_OldMouseY = 0.0;
        double m_NewMouseX = 0.0;
        double m_NewMouseY = 0.0;
        Rubikscube* rubik = nullptr;
    public:
        Camera(int width, int height);

        // Update Projection matrix for Orthographic mode
        void SetOrthographic(float near, float far);

        // Handle camera inputs
        void EnableInputs(GLFWwindow* window);

        void SetPerspective(float fov, float aspectRatio, float near, float far);
        void SetPosition(const glm::vec3& position);

        inline glm::mat4 GetViewMatrix() const { return m_View; }
        inline glm::mat4 GetProjectionMatrix() const { return m_Projection; }
        inline glm::vec3 GetPosition() const { return m_Position; }
        void SetViewMatrix(glm::mat4 m_View);
        void SetRubiksCube(Rubikscube* rubiksCube);
        void SetRotationFactor(int factor);
        int GetRotationFactor();
};