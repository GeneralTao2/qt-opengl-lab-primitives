#ifndef POINT_H
#define POINT_H

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


class point
{
public:
    unsigned int VBO;
    unsigned int VAO;
    std::vector<float> vertices;

    Shader shader;
    point();
    point(std::vector<float> &vec);
    ~point();
    void bindVertices();
    void Init();
    void setColor(glm::vec3 a, size_t i = 0);
    void setPosition(glm::vec3 a, size_t i = 0);
    void setSize(float a, size_t i = 0);
    void Drow(glm::vec3 position);
    void createVertices();
};

#endif // POINT_H
