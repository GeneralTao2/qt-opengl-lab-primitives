#include "point.h"

point::point(){ Init(); }
point::point(std::vector<float> &vec) : vertices(vec){ Init(); }
point::~point() {
    glDeleteVertexArrays(1, &VAO);
}
void point::Init() {
    glEnable(GL_PROGRAM_POINT_SIZE);
    shader = ResourceManager::GetShader("point");
    createVertices();
}
void point::setColor(glm::vec3 a, size_t i) {
    vertices[i*7 + 3] = a.x;
    vertices[i*7 + 4] = a.y;
    vertices[i*7 + 5] = a.z;
}
void point::setPosition(glm::vec3 a, size_t i) {
    vertices[i*7] = a.x;
    vertices[i*7 + 1] = a.y;
    vertices[i*7 + 2] = a.z;
}
void point::setSize(float a, size_t i) {
    vertices[i*7 + 6] = a;
}
void point::Drow(glm::vec3 position) {
    glm::mat4 model(1.0);
    model = glm::translate(model, position);
    shader.Use();
    shader.SetMatrix4("transform", model);
    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS , 0, vertices.size()/7);
    glBindVertexArray(0);
}
void point::bindVertices() {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

}
void point::createVertices() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    bindVertices();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}
