#include "line.h"

line::line(){ Init(); }
line::line(std::vector<float> &vec) : vertices(vec){ Init(); }
line::~line() {
    glDeleteVertexArrays(1, &VAO);
}
void line::Init() {
    shader = ResourceManager::GetShader("line");
    createVertices();
}
void line::setColor(glm::vec3 a, size_t i) {
    vertices[i*6 + 3] = a.x;
    vertices[i*6 + 4] = a.y;
    vertices[i*6 + 5] = a.z;
}
void line::setPosition(glm::vec3 a, size_t i) {
    vertices[i*6] = a.x;
    vertices[i*6 + 1] = a.y;
    vertices[i*6 + 2] = a.z;
}
void line::Drow(glm::vec3 position, uint16_t mode) {
    glm::mat4 model(1.0);
    model = glm::translate(model, position);
    shader.Use();
    shader.SetMatrix4("transform", model);
    glBindVertexArray(VAO);
    glDrawArrays(mode, 0, vertices.size()/6);
    glBindVertexArray(0);
}
void line::bindVertices() {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

}
void line::createVertices() {
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

void line::setLineWidth(float width) {
    glLineWidth(width);
}
