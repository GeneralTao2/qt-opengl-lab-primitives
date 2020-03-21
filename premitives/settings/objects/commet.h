#ifndef COMMET_H
#define COMMET_H
#include "point.h"
#include "line.h"

class commet
{
public:
    point *kernel;
    line *tail;
    glm::vec3 position;
    commet();
    ~commet();
    void generate(glm::vec3 position);
    void Drow(float dx);
};

#endif // COMMET_H
