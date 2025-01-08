#include "Camera.h"

Camera::Camera(int width, int height)
    : m_Width(width), m_Height(height), rotFactor(2){};

void Camera::SetOrthographic(float near, float far)
{
    m_Near = near;
    m_Far = far;

    // Rest Projection and View matrices
    m_Projection = glm::ortho(m_Left, m_Right, m_Bottom, m_Top, near, far);
    m_View = glm::lookAt(m_Position, m_Position + m_Orientation, m_Up);
}

/////////////////////
// Input Callbacks //
/////////////////////

void KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
    Camera* camera = (Camera*) glfwGetWindowUserPointer(window);
    if (!camera) {
        std::cout << "Warning: Camera wasn't set as the Window User Pointer! KeyCallback is skipped" << std::endl;
        return;
    }

    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        switch (key)
        {
            case GLFW_KEY_R:
                std::cout << "R Pressed" << std::endl;
                // Rotate the Rubik's Cube right wall
                if (camera->rubik) {
                    glm::vec3 rotationAxis = glm::vec3(1.0f, 0.0f, 0.0f);
                    glm::mat4 mvp = camera->GetProjectionMatrix() * camera->GetViewMatrix();
                    for(int i=1; i<=camera->GetRotationFactor();i++){
                        camera->rubik->RotateWall45(1, rotationAxis, mvp, window, 1.0f);
                    }
                }
                break;
            case GLFW_KEY_L:
                std::cout << "L Pressed" << std::endl;
                // Rotate the Rubik's Cube left wall
                if (camera->rubik) {
                    glm::vec3 rotationAxis = glm::vec3(1.0f, 0.0f, 0.0f);
                    glm::mat4 mvp = camera->GetProjectionMatrix() * camera->GetViewMatrix();
                    for(int i=1; i<=camera->GetRotationFactor();i++){
                        camera->rubik->RotateWall45(-1, rotationAxis, mvp, window, 1.0f);
                    }
                }
                break;
            case GLFW_KEY_U:
                std::cout << "U Pressed" << std::endl;
                // Rotate the Rubik's Cube up wall
                if (camera->rubik) {
                    glm::vec3 rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
                    glm::mat4 mvp = camera->GetProjectionMatrix() * camera->GetViewMatrix();
                    for(int i=1; i<=camera->GetRotationFactor();i++){
                        camera->rubik->RotateWall45(1, rotationAxis, mvp, window, 1.0f);
                    }
                }
                break;
            case GLFW_KEY_D:
                std::cout << "D Pressed" << std::endl;
                // Rotate the Rubik's Cube down wall
                if (camera->rubik) {
                    glm::vec3 rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
                    glm::mat4 mvp = camera->GetProjectionMatrix() * camera->GetViewMatrix();
                    for(int i=1; i<=camera->GetRotationFactor();i++){
                        camera->rubik->RotateWall45(-1, rotationAxis, mvp, window, 1.0f);
                    }
                }
                break;
            case GLFW_KEY_B:
                std::cout << "B Pressed" << std::endl;
                // Rotate the Rubik's Cube back wall
                if (camera->rubik) {
                    glm::vec3 rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
                    glm::mat4 mvp = camera->GetProjectionMatrix() * camera->GetViewMatrix();
                    for(int i=1; i<=camera->GetRotationFactor();i++){
                        camera->rubik->RotateWall45(-1, rotationAxis, mvp, window, 1.0f);
                    }
                }
                break;
            case GLFW_KEY_F:
                std::cout << "F Pressed" << std::endl;
                // Rotate the Rubik's Cube front wall
                if (camera->rubik) {
                    glm::vec3 rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
                    glm::mat4 mvp = camera->GetProjectionMatrix() * camera->GetViewMatrix();
                    for(int i=1; i<=camera->GetRotationFactor();i++){
                        camera->rubik->RotateWall45(1, rotationAxis, mvp, window, 1.0f);
                    }
                }
                break;
            case GLFW_KEY_SPACE:
                std::cout << "Space Pressed" << std::endl;
                // Set clockwise/counter clockwise rotations
                if (camera->rubik) {
                    camera->rubik->setClockWise();
                }
                break;
            case GLFW_KEY_LEFT:
                std::cout << "Left Pressed" << std::endl;
                // Changing the center of rotation to the left once
                if (camera->rubik) {
                    glm::vec3 rotationAxis = glm::vec3(-1.0f, 0.0f, 0.0f);
                    camera->rubik->setCenterRotation(rotationAxis);
                }
                break;
            case GLFW_KEY_RIGHT:
                std::cout << "Right Pressed" << std::endl;
                // Changing the center of rotation to the right once
                if (camera->rubik) {
                    glm::vec3 rotationAxis = glm::vec3(1.0f, 0.0f, 0.0f);
                    camera->rubik->setCenterRotation(rotationAxis);
                }
                break;
            case GLFW_KEY_UP:
                std::cout << "Up Pressed" << std::endl;
                // Changing the center of rotation to the up once
                if (camera->rubik) {
                    glm::vec3 rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
                    camera->rubik->setCenterRotation(rotationAxis);
                }
                break;
            case GLFW_KEY_DOWN:
                std::cout << "Down Pressed" << std::endl;
                // Changing the center of rotation to the down once
                if (camera->rubik) {
                    glm::vec3 rotationAxis = glm::vec3(0.0f, -1.0f, 0.0f);
                    camera->rubik->setCenterRotation(rotationAxis);
                }
                break;
            case GLFW_KEY_I:
                std::cout << "I Pressed" << std::endl;
                // Changing the center of rotation to the in once
                if (camera->rubik) {
                    glm::vec3 rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
                    camera->rubik->setCenterRotation(rotationAxis);
                }
                break;
            case GLFW_KEY_O:
                std::cout << "O Pressed" << std::endl;
                // Changing the center of rotation to the out once
                if (camera->rubik) {
                    glm::vec3 rotationAxis = glm::vec3(0.0f, 0.0f, -1.0f);
                    camera->rubik->setCenterRotation(rotationAxis);
                }
                break;
            case GLFW_KEY_Z:
                std::cout << "Z Pressed" << std::endl;
                // Deviding the rotation factor by 2
                if (camera && camera->GetRotationFactor()!=1) {
                    camera->SetRotationFactor(camera->GetRotationFactor()/2);
                }
                break;
            case GLFW_KEY_A:
                std::cout << "A Pressed" << std::endl;
                // Multiply the rotation factor by 2
                if (camera && camera->GetRotationFactor()!=4) {
                    camera->SetRotationFactor(camera->GetRotationFactor()*2);
                }
                break;
            case GLFW_KEY_M:
                std::cout << "M Pressed" << std::endl;
                // Mixing the Rubiks cube
                if (camera->rubik) {
                    if(camera->rubik->getSize()==3){
                        std::random_device rd;  // Random device (seed generator)
                        std::mt19937 gen(rd()); // Mersenne Twister random number generator

                        // Define the range [1, 100]
                        std::uniform_int_distribution<> dist(1, 6);
                        int randomNumber;
                        glm::vec3 rotationAxis;
                        glm::mat4 mvp;
                        for(int i=0; i<100; i++){
                            randomNumber = dist(gen);
                            switch (randomNumber)
                            {
                                // Getting a random wall to rotate and rotating it by 90 degrees with the sensitivity of 45 degrees so it happens fast
                                case 1:
                                    rotationAxis = glm::vec3(1.0f, 0.0f, 0.0f);
                                    mvp = camera->GetProjectionMatrix() * camera->GetViewMatrix();
                                    camera->rubik->RotateWall45(1, rotationAxis, mvp, window, 45.0f);
                                    camera->rubik->RotateWall45(1, rotationAxis, mvp, window, 45.0f);
                                    break;
                                case 2:
                                    rotationAxis = glm::vec3(1.0f, 0.0f, 0.0f);
                                    mvp = camera->GetProjectionMatrix() * camera->GetViewMatrix();
                                    camera->rubik->RotateWall45(-1, rotationAxis, mvp, window, 45.0f);
                                    camera->rubik->RotateWall45(-1, rotationAxis, mvp, window, 45.0f);
                                    break;
                                case 3:
                                    rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
                                    mvp = camera->GetProjectionMatrix() * camera->GetViewMatrix();
                                    camera->rubik->RotateWall45(1, rotationAxis, mvp, window, 45.0f);
                                    camera->rubik->RotateWall45(1, rotationAxis, mvp, window, 45.0f);
                                    break;
                                case 4:
                                    rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
                                    mvp = camera->GetProjectionMatrix() * camera->GetViewMatrix();
                                    camera->rubik->RotateWall45(-1, rotationAxis, mvp, window, 45.0f);
                                    camera->rubik->RotateWall45(-1, rotationAxis, mvp, window, 45.0f);
                                    break;
                                case 5:
                                    rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
                                    mvp = camera->GetProjectionMatrix() * camera->GetViewMatrix();
                                    camera->rubik->RotateWall45(1, rotationAxis, mvp, window, 45.0f);
                                    camera->rubik->RotateWall45(1, rotationAxis, mvp, window, 45.0f);
                                    break;
                                case 6:
                                    rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
                                    mvp = camera->GetProjectionMatrix() * camera->GetViewMatrix();
                                    camera->rubik->RotateWall45(-1, rotationAxis, mvp, window, 45.0f);
                                    camera->rubik->RotateWall45(-1, rotationAxis, mvp, window, 45.0f);
                                    break;

                                default:
                                    break;
                            }
                        }
                    } else{
                        std::cout << "Feature only for 3x3 Rubiks Cube";
                    }
                }
                break;
            default:
                break;
        }
    }
}

void MouseButtonCallback(GLFWwindow* window, double currMouseX, double currMouseY)
{
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        std::cout << "MOUSE LEFT Click" << std::endl;
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        std::cout << "MOUSE RIGHT Click" << std::endl;
    }
}

void CursorPosCallback(GLFWwindow* window, double currMouseX, double currMouseY)
{
    Camera* camera = (Camera*) glfwGetWindowUserPointer(window);
    if (!camera) {
        std::cout << "Warning: Camera wasn't set as the Window User Pointer! KeyCallback is skipped" << std::endl;
        return;
    }

    camera->m_NewMouseX = camera->m_OldMouseX - currMouseX;
    camera->m_NewMouseY = camera->m_OldMouseY - currMouseY;
    camera->m_OldMouseX = currMouseX;
    camera->m_OldMouseY = currMouseY;

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        // Rotate Rubiks cube based on mouse movement
        camera->rubik->Rotate((float)camera->m_NewMouseX * 0.1f, (float)camera->m_NewMouseY * 0.1f);
        std::cout << "MOUSE LEFT Motion" << std::endl;
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        // Translate camera based on mouse movement
        glm::vec3 newPosition = camera->GetPosition();
        newPosition.x -= static_cast<float>(camera->m_NewMouseX) * 0.01f;  // Adjust sensitivity
        newPosition.y += static_cast<float>(camera->m_NewMouseY) * 0.01f;  // Invert for screen-to-world mapping
        camera->SetPosition(newPosition);
        std::cout << "MOUSE RIGHT Motion" << std::endl;
    }
}

void ScrollCallback(GLFWwindow* window, double scrollOffsetX, double scrollOffsetY)
{
    Camera* camera = (Camera*) glfwGetWindowUserPointer(window);
    if (!camera) {
        std::cout << "Warning: Camera wasn't set as the Window User Pointer! ScrollCallback is skipped" << std::endl;
        return;
    }
    glm::vec3 newPosition = camera->GetPosition();
    newPosition.z -= static_cast<float>(scrollOffsetY) * 0.5f;
    // Adjust sensitivity as needed
    camera->SetPosition(newPosition);
    std::cout << "SCROLL Motion" << std::endl;
}

void Camera::SetPerspective(float fov, float aspectRatio, float near, float far)
{
    m_Projection = glm::perspective(glm::radians(fov), aspectRatio, near, far);
    m_View = glm::lookAt(m_Position, m_Position + m_Orientation, m_Up);
}

void Camera::SetPosition(const glm::vec3& position)
{
    m_Position = position;
    m_View = glm::lookAt(m_Position, m_Position + m_Orientation, m_Up); // Update the view matrix
}



void Camera::EnableInputs(GLFWwindow* window)
{
    // Set camera as the user pointer for the window
    glfwSetWindowUserPointer(window, this);

    // Handle key inputs
    glfwSetKeyCallback(window, (void(*)(GLFWwindow *, int, int, int, int)) KeyCallback);

    // Handle cursor buttons
    glfwSetMouseButtonCallback(window, (void(*)(GLFWwindow *, int, int, int)) MouseButtonCallback);

    // Handle cursor position and inputs on motion
    glfwSetCursorPosCallback(window , (void(*)(GLFWwindow *, double, double)) CursorPosCallback);

    // Handle scroll inputs
    glfwSetScrollCallback(window, (void(*)(GLFWwindow *, double, double)) ScrollCallback);
}

void Camera::SetViewMatrix(glm::mat4 new_view){
    m_View = new_view;
}

void Camera::SetRubiksCube(Rubikscube* rubiksCube) {
    rubik = rubiksCube;
}

void Camera::SetRotationFactor(int factor){
    rotFactor=factor;
}

int Camera::GetRotationFactor(){
    return rotFactor;
}