#include "Cube.h"

#include <glm/gtc/matrix_transform.hpp>

Cube::Cube(Shader* shader, Texture* texture, VertexArray* va)
    : m_VA(va),
      m_Texture(texture),
      m_Shader(shader),  // Use external shader
      m_ModelMatrix(1.0f) {
}

Cube::~Cube() {
}

// Rendering the cube
void Cube::Render(glm::mat4 mvp, glm::vec4 color) {
    glm::mat4 mvp1 = mvp * m_ModelMatrix;
    m_Texture->Bind(0);
    m_Shader->Bind();
    m_Shader->SetUniform4f("u_Color", color);
    m_Shader->SetUniformMat4f("u_MVP", mvp1);
    m_Shader->SetUniform1i("u_Texture", 0);
    m_VA->Bind();
    GLCall(glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr));
}

void Cube::SetPosition(const glm::vec3& position) {
    m_ModelMatrix = glm::translate(glm::mat4(1.0f), position);
}

void Cube::SetModelMatrix(glm::mat4 modelMatrix){
    m_ModelMatrix = modelMatrix;
}

glm::mat4 Cube::GetModelMatrix(){
    return m_ModelMatrix;
}