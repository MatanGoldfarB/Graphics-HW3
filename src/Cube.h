#pragma once

#include <glm/glm.hpp>
#include <Shader.h>
#include <VertexArray.h>
#include <VertexBuffer.h>
#include <IndexBuffer.h>
#include <Texture.h>

class Cube {
private:
    VertexArray* m_VA;
    Texture* m_Texture;
    Shader* m_Shader;

    glm::mat4 m_ModelMatrix;

public:
    Cube(Shader* shader, Texture* texture, VertexArray* va);
    ~Cube();

    void Render(glm::mat4 mvp, glm::vec4 color);
    void SetPosition(const glm::vec3& position);
    void SetModelMatrix(glm::mat4 modelMatrix);
    glm::mat4 GetModelMatrix();
};