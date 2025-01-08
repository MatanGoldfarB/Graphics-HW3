#include "RubiksCube.h"

Rubikscube::Rubikscube(int size, Shader* shader, Texture* texture, VertexArray* va)
    : m_Size(size), m_ModelMatrix(glm::mat4(1.0f)), m_CubeMatrix(size, std::vector<std::vector<Cube*>>(size, std::vector<Cube*>(size, nullptr))), clock(false), centerRotation(std::vector<int>(3,1)), locker(std::vector<int>(m_Size,0)), axisLocker('\0'){
    float offset = 1.0f;  // Adjust to ensure cubes are spaced correctly
    float centerOffset = (size - 1) / 2.0f;
    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; ++y) {
            for (int z = 0; z < size; ++z) {
                if(x==0 || y==0 || z==0 || x==size-1 || y==size-1 || z==size-1){ // Skip center cubes
                    Cube* cube = new Cube(shader, texture, va); // Dynamically allocate cube
                    // Calculate position relative to the center
                    glm::vec3 position = glm::vec3(
                        (x - centerOffset) * offset,
                        (y - centerOffset) * offset,
                        (z - centerOffset) * offset
                    );
                    cube->SetPosition(position);
                    m_CubeMatrix[x][y][z] = cube;
                }
            }
        }
    }
}

// Rendering each cube and the back scene
void Rubikscube::Render(const glm::mat4& viewProjectionMatrix, GLFWwindow* window) {
    GLCall(glClearColor(1.0f, 1.0f, 1.0f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    for (int x = 0; x < m_Size; ++x) {
        for (int y = 0; y < m_Size; ++y) {
            for (int z = 0; z < m_Size; ++z) {
                if (m_CubeMatrix[x][y][z] != nullptr) {
                    glm::mat4 mvp = viewProjectionMatrix * m_ModelMatrix;  // Apply global transforms
                    m_CubeMatrix[x][y][z]->Render(mvp, glm::vec4(1.0f));  // Default color
                }
            }
        }
    }
    /* Swap front and back buffers */
    glfwSwapBuffers(window);
}

// Rotates the whole rubiks cube 
void Rubikscube::Rotate(const float Xangle, const float Yangle){
    glm::mat4 globalRotation = glm::mat4(1.0f);
    globalRotation = glm::rotate(globalRotation, glm::radians(-Xangle), glm::vec3(0.0f, 1.0f, 0.0f));
    globalRotation = glm::rotate(globalRotation, glm::radians(-Yangle), glm::vec3(1.0f, 0.0f, 0.0f));
    m_ModelMatrix = globalRotation * m_ModelMatrix;
}

Rubikscube::~Rubikscube() {
    for (int x = 0; x < m_Size; ++x) {
        for (int y = 0; y < m_Size; ++y) {
            for (int z = 0; z < m_Size; ++z) {
                if (m_CubeMatrix[x][y][z] != nullptr) {
                    delete m_CubeMatrix[x][y][z];
                    m_CubeMatrix[x][y][z] = nullptr; // Optional: set to nullptr after deletion
                }
            }
        }
    }
}

// Rotates a specific wall dependent on layer index, axis
void Rubikscube::RotateWall45(int layerIndex, glm::vec3& axis, const glm::mat4& viewProjectionMatrix, GLFWwindow* window, float sensitivity) {
    float angle = 45.0f;
    float dtheta = sensitivity;
    // Checking if all walls in past rotations are back to didnt stop at 45 degrees
    bool allZero = true;
    for(int i=0; i<locker.size(); i++){
        if(locker[i]!=0){
            allZero=false;
        }
    }
    // if true reset the axis to be none 
    // else check if the axis is not locked
    if(allZero){
        axisLocker='\0';
    } else if((axis.x==1.0f && axisLocker!='x') || (axis.y==1.0f && axisLocker!='y')||(axis.z==1.0f && axisLocker!='z')){
        std::cout << "dont change!" << std::endl;
        return;
    }
    // Lock the axis and update the layer index dependent on the center of rotation
    if(axis.x == 1.0f){
        layerIndex+=centerRotation[0];
        if(axisLocker=='x' || axisLocker=='\0'){
            axisLocker='x';
        }
    } else if(axis.y == 1.0f){
        layerIndex+=centerRotation[1];
        if(axisLocker=='y' || axisLocker=='\0'){
            axisLocker='y';
        }
    } else if(axis.z == 1.0f){
        layerIndex+=centerRotation[2];
        if(axisLocker=='z' || axisLocker=='\0'){
            axisLocker='z';
        }
    } else{
        throw std::invalid_argument("Not an axis vector"); 
    }

    // Consider limitations of layer index
    if(layerIndex==-1){
        layerIndex=0;
    } else if(layerIndex==m_Size){
        layerIndex=m_Size-1;
    }

    // Rotate indecies only after a full 90 degrees rotation
    int pastRot = locker[layerIndex];
    if(clock){
        locker[layerIndex] = (pastRot+1)%2;
        if(pastRot==1){
            indexCounterClockWise(layerIndex, axis);
        }
    } else{
        locker[layerIndex] = (pastRot-1)%2;
        if(pastRot==-1){
            indexClockWise(layerIndex, axis);
        }
        dtheta= -1*dtheta;
    }

    // Animate the rotation by seperating it to small rotations
    while(angle>0.0f){
        for (int y = 0; y < m_Size; ++y) {
            for (int z = 0; z < m_Size; ++z) {
                Cube* cube = nullptr;
                if(axis.x == 1.0f){
                    cube = m_CubeMatrix[layerIndex][y][z];
                } else if(axis.y == 1.0f){
                    cube = m_CubeMatrix[y][layerIndex][z];
                } else if(axis.z == 1.0f){
                    cube = m_CubeMatrix[y][z][layerIndex];
                } else{
                    throw std::invalid_argument("Not an axis vector"); 
                }
                if (cube) {
                    glm::mat4 modelMatrix = cube->GetModelMatrix();
                    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(dtheta), axis);
                    cube->SetModelMatrix(rotation * modelMatrix);
                }
            }
        }
        angle-=sensitivity;
        Render(viewProjectionMatrix, window);
    }
}

// Changing cube index for a specific wall clock wise
void Rubikscube::indexClockWise(int layerIndex, glm::vec3& axis){
    std::vector<std::vector<std::vector<Cube*>>> temp = m_CubeMatrix;
    bool loop;
    int i, j,limit;
    for(int radius=0; radius<(m_Size/2); radius++){
        loop = true;
        limit = m_Size-radius-1;
        i=radius;
        j=radius;
        while(loop){
            if(j==radius && i != limit){
                if(axis.x == 1.0f){
                    m_CubeMatrix[layerIndex][i][j] = temp[layerIndex][limit-j+radius][i];
                } else if(axis.y == 1.0f){
                    m_CubeMatrix[i][layerIndex][j] = temp[j][layerIndex][limit-i+radius];
                } else if(axis.z == 1.0f){
                    m_CubeMatrix[i][j][layerIndex] = temp[limit-j+radius][i][layerIndex];
                } else{
                    throw std::invalid_argument("Not an axis vector"); 
                }
                i++;
            } else if(i==limit && j != limit){
                if(axis.x == 1.0f){
                    m_CubeMatrix[layerIndex][i][j] = temp[layerIndex][limit-j+radius][i];
                } else if(axis.y == 1.0f){
                    m_CubeMatrix[i][layerIndex][j] = temp[j][layerIndex][limit-i+radius];
                } else if(axis.z == 1.0f){
                    m_CubeMatrix[i][j][layerIndex] = temp[limit-j+radius][i][layerIndex];
                } else{
                    throw std::invalid_argument("Not an axis vector"); 
                }
                j++;
            } else if(j==limit && i != radius){
                if(axis.x == 1.0f){
                    m_CubeMatrix[layerIndex][i][j] = temp[layerIndex][limit-j+radius][i];
                } else if(axis.y == 1.0f){
                    m_CubeMatrix[i][layerIndex][j] = temp[j][layerIndex][limit-i+radius];
                } else if(axis.z == 1.0f){
                    m_CubeMatrix[i][j][layerIndex] = temp[limit-j+radius][i][layerIndex];
                } else{
                    throw std::invalid_argument("Not an axis vector"); 
                }
                i--;
            } else if(i==radius){
                if(axis.x == 1.0f){
                    m_CubeMatrix[layerIndex][i][j] = temp[layerIndex][limit-j+radius][i];
                } else if(axis.y == 1.0f){
                    m_CubeMatrix[i][layerIndex][j] = temp[j][layerIndex][limit-i+radius];
                } else if(axis.z == 1.0f){
                    m_CubeMatrix[i][j][layerIndex] = temp[limit-j+radius][i][layerIndex];
                } else{
                    throw std::invalid_argument("Not an axis vector"); 
                }
                j--;
                if(j==radius){
                    loop = false;
                }
            }
        }
    }
}

// Changing cube index for a specific wall counter clock wise
void Rubikscube::indexCounterClockWise(int layerIndex, glm::vec3& axis){
    std::vector<std::vector<std::vector<Cube*>>> temp = m_CubeMatrix;
    bool loop;
    int i, j,limit;
    for(int radius=0; radius<(m_Size/2); radius++){
        loop = true;
        limit = m_Size-radius-1;
        i=radius;
        j=radius;
        while(loop){
            if(j==radius && i != limit){
                if(axis.x == 1.0f){
                    m_CubeMatrix[layerIndex][limit-j+radius][i] = temp[layerIndex][i][j];
                } else if(axis.y == 1.0f){
                    m_CubeMatrix[j][layerIndex][limit-i+radius] = temp[i][layerIndex][j];
                } else if(axis.z == 1.0f){
                    m_CubeMatrix[limit-j+radius][i][layerIndex] = temp[i][j][layerIndex];
                } else{
                    throw std::invalid_argument("Not an axis vector"); 
                }
                i++;
            } else if(i==limit && j != limit){
                if(axis.x == 1.0f){
                    m_CubeMatrix[layerIndex][limit-j+radius][i] = temp[layerIndex][i][j];
                } else if(axis.y == 1.0f){
                    m_CubeMatrix[j][layerIndex][limit-i+radius] = temp[i][layerIndex][j];
                } else if(axis.z == 1.0f){
                    m_CubeMatrix[limit-j+radius][i][layerIndex] = temp[i][j][layerIndex];
                } else{
                    throw std::invalid_argument("Not an axis vector"); 
                }
                j++;
            } else if(j==limit && i != radius){
                if(axis.x == 1.0f){
                    m_CubeMatrix[layerIndex][limit-j+radius][i] = temp[layerIndex][i][j];
                } else if(axis.y == 1.0f){
                    m_CubeMatrix[j][layerIndex][limit-i+radius] = temp[i][layerIndex][j];
                } else if(axis.z == 1.0f){
                    m_CubeMatrix[limit-j+radius][i][layerIndex] = temp[i][j][layerIndex];
                } else{
                    throw std::invalid_argument("Not an axis vector"); 
                }
                i--;
            } else if(i==radius){
                if(axis.x == 1.0f){
                    m_CubeMatrix[layerIndex][limit-j+radius][i] = temp[layerIndex][i][j];
                } else if(axis.y == 1.0f){
                    m_CubeMatrix[j][layerIndex][limit-i+radius] = temp[i][layerIndex][j];
                } else if(axis.z == 1.0f){
                    m_CubeMatrix[limit-j+radius][i][layerIndex] = temp[i][j][layerIndex];
                } else{
                    throw std::invalid_argument("Not an axis vector"); 
                }
                j--;
                if(j==radius){
                    loop = false;
                }
            }
        }
    }
}

void Rubikscube::setClockWise(){
    clock = !clock;
}

// Getting an axis and moving one step in that direction
void Rubikscube::setCenterRotation(glm::vec3& axis){
    if(axis.x != 0.0f){
        centerRotation[0]+=axis.x;
    } else if(axis.y != 0.0f){
        centerRotation[1]+=axis.y;
    } else if(axis.z != 0.0f){
        centerRotation[2]+=axis.z;
    } else{
        throw std::invalid_argument("Not an axis vector"); 
    }
    if(centerRotation[0]==-1){
        centerRotation[0]=0;
    } else if(centerRotation[1]==-1){
        centerRotation[1]=0;
    } else if(centerRotation[2]==-1){
        centerRotation[2]=0;
    } else if(centerRotation[0]==m_Size){
        centerRotation[0]=m_Size-1;
    } else if(centerRotation[1]==m_Size){
        centerRotation[1]=m_Size-1;
    } else if(centerRotation[2]==m_Size){
        centerRotation[2]=m_Size-1;
    }
    std::cout << "Center of rotation is: " << centerRotation[0] << " " << centerRotation[1] << " " << centerRotation[2] << std::endl;
}

int Rubikscube::getSize(){
    return m_Size;
}