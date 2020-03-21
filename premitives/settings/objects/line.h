#ifndef LINE_H
#define LINE_H

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

class line
{
public:
    unsigned int VBO;
    unsigned int VAO;
    std::vector<float> vertices;

    Shader shader;
    line();
    line(std::vector<float> &vec);
    ~line();
    void bindVertices();
    void Init();
    void setColor(glm::vec3 a, size_t i = 0);
    void setPosition(glm::vec3 a, size_t i = 0);
    void Drow(glm::vec3 position, uint16_t mode = GL_LINES);
    void createVertices();

    static void setLineWidth(float width);
};

#endif // LINE_H
