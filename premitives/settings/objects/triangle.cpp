#include "triangle.h"

triangle::triangle(){ Init(); }
triangle::triangle(std::vector<float> &vec) : vertices(vec){ Init(); }
triangle::~triangle() {
    glDeleteVertexArrays(1, &VAO);
}
void triangle::Init() {
    shader = ResourceManager::GetShader("triangle");
    createVertices();
}
void triangle::setColor(glm::vec3 a, size_t i) {
    vertices[i*6 + 3] = a.x;
    vertices[i*6 + 4] = a.y;
    vertices[i*6 + 5] = a.z;
}
void triangle::setPosition(glm::vec3 a, size_t i) {
    vertices[i*6] = a.x;
    vertices[i*6 + 1] = a.y;
    vertices[i*6 + 2] = a.z;
}
void triangle::Drow(glm::vec3 position, glm::vec3 scale, uint16_t mode) {
    glm::mat4 model(1.0);
    model = glm::translate(model, position);
    model = glm::scale(model, scale);
    shader.Use();
    shader.SetMatrix4("transform", model);
    glBindVertexArray(VAO);
    glDrawArrays(mode, 0, vertices.size()/6);
    glBindVertexArray(0);
}
void triangle::bindVertices() {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

}
void triangle::createVertices() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    bindVertices();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void triangle::setLineWidth(float width) {
    glLineWidth(width);
}
