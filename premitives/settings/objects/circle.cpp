#include "circle.h"

circle::circle(){ Init(); }
circle::circle(glm::vec2 Size, GLint Sides) : numberOfSides(Sides), size(Size){ Init(); }
circle::~circle() {
    glDeleteVertexArrays(1, &VAO);
}
void circle::Init() {
    glEnable(GL_PROGRAM_POINT_SIZE);
    shader = ResourceManager::GetShader("circle");
    generateVertices();
    bindVertices();
}
void circle::setColor(glm::vec3 a, size_t i) {
    vertices[i*6 + 3] = a.x;
    vertices[i*6 + 4] = a.y;
    vertices[i*6 + 5] = a.z;
}
void circle::setPosition(glm::vec3 a, size_t i) {
    vertices[i*6] = a.x;
    vertices[i*6 + 1] = a.y;
    vertices[i*6 + 2] = a.z;
}
void circle::rotation(glm::vec3 factor, float angle) {
    model = glm::rotate(model, angle, factor);
}
void circle::translate(glm::vec3 position) {
    model = glm::translate(model, position);
}
void circle::Drow(glm::vec3 scale) {
    model = glm::scale(model, scale);
    shader.Use();
    shader.SetMatrix4("transform", model);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size()/6);
    glBindVertexArray(0);
    model = glm::mat4(1.0);
}
void circle::rebindVertices(std::function<void (circle *this_)> ColorCallback) {
    generateVertices(ColorCallback);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

}
void circle::bindVertices() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    rebindVertices();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}
void circle::generateVertices(std::function<void (circle *this_)> ColorCallback) {
    int numberOfVertices = numberOfSides + 2;

    GLfloat twicePi = 2.0f * M_PI;

    GLfloat circleVerticesX[numberOfVertices];
    GLfloat circleVerticesY[numberOfVertices];
    GLfloat circleVerticesZ[numberOfVertices];

    circleVerticesX[0] = 0;
    circleVerticesY[0] = 0;
    circleVerticesZ[0] = 0;

    for ( int i = 1; i < numberOfVertices; i++ )
    {
        circleVerticesX[i] = 2 * size.x * cos( i *  twicePi / numberOfSides );
        circleVerticesY[i] = 2 * size.y * sin( i * twicePi / numberOfSides );
        circleVerticesZ[i] = 0;
    }
    vertices = std::vector<float>(numberOfVertices*6);

    vertices[0] = vertices[1] = vertices[2] = 0;
    for ( int i = 1; i < numberOfVertices; i++ )
    {
        vertices[i * 6] = circleVerticesX[i];
        vertices[( i * 6 ) + 1] = circleVerticesY[i];
        vertices[( i * 6 ) + 2] = circleVerticesZ[i];
    }
    if(ColorCallback) {
        ColorCallback(this);
    } else {
        setColor({1, 1, 1}, 0);
        for ( int i = 1; i < numberOfVertices; i++ )
        {
            setColor({1, 1, 1}, i);
        }
    }
}
