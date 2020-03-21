#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <iostream>
#include <cmath>
#include <settings/libs/glad/glad.h>
#include <settings/libs/glm/glm.hpp>
#include <settings/libs/glm/gtc/matrix_transform.hpp>
#include "../classes/shader.h"
#include "../classes/resource_manager.h"
#include "../tools/main_tool.h"

using std::cout;
using std::endl;

class triangle
{
public:
    unsigned int VBO;
    unsigned int VAO;
    std::vector<float> vertices;

    Shader shader;
    triangle();
    triangle(std::vector<float> &vec);
    ~triangle();
    void bindVertices();
    void Init();
    void setColor(glm::vec3 a, size_t i = 0);
    void setPosition(glm::vec3 a, size_t i = 0);
    void Drow(glm::vec3 position, glm::vec3 scale = glm::vec3(1), uint16_t mode = GL_TRIANGLES);
    void createVertices();

    static void setLineWidth(float width);
};

#endif // TRIANGLE_H
