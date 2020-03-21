#ifndef CIRCLE_H
#define CIRCLE_H

#include <iostream>
#include <functional>
#include <cmath>
#include <settings/libs/glad/glad.h>
#include <settings/libs/glm/glm.hpp>
#include <settings/libs/glm/gtc/matrix_transform.hpp>
#include "../classes/shader.h"
#include "../classes/resource_manager.h"
#include "../tools/main_tool.h"

using std::cout;
using std::endl;

class circle
{
public:
    unsigned int VBO;
    unsigned int VAO;
    std::vector<float> vertices;
    GLint numberOfSides;
    glm::vec2 size;
    glm::mat4 model;

    Shader shader;
    circle();
    circle(glm::vec2 Size, GLint sides = 360);
    ~circle();
    void rebindVertices(std::function<void (circle *this_)> ColorCallback = nullptr);
    void Init();
    void setColor(glm::vec3 a, size_t i = 0);
    void setPosition(glm::vec3 a, size_t i = 0);
    void rotation(glm::vec3 factor, float angle);
    void translate(glm::vec3 position);
    void Drow(glm::vec3 scale = glm::vec3(1));
    void bindVertices();
    void generateVertices(std::function<void (circle *this_)>ColorCallback = nullptr);

    void (*colorCallback)();
};


#endif // CIRCLE_H
