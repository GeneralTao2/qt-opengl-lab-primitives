#include "commet.h"

commet::commet()
{
    std::vector<float> one = {0,0,0, 0.95,0.93,0.08, 2};
    kernel = new point(one);
    std::vector<float> two = {0,0,0,        0.97,0.75,0.31,
                               0.5, 0.5, 0,  0.06,0.03,0.07};
    tail = new line(two);
}
commet::~commet() {
    delete kernel;
    delete tail;
}
void commet::generate(glm::vec3 Position) {
    position = Position;
}
void commet::Drow(float dx) {
    if(position.y < -0.8) {
        generate({(rand()%2500)/1000.0 - 1.25, 1.1, 0});
    }
    position = glm::vec3(position.x+dx, position.y+dx, 0);
    kernel->Drow(position);
    tail->Drow(position);
}
