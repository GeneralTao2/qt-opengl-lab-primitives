//Подключение GLAD
#ifdef _WIN32
    #define APIENTRY __stdcall
#endif
#include <settings/libs/src/glad.c>
#ifdef _WINDOWS_
#endif
#define GLEW_STATIC
#include <settings/libs/glad/glad.h>
#include <glfw3.h>

//Подключение встроенных библиотек
#include <iostream>
#include <windows.h>
#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>
#include <utility>

//Подключение менеджеров и объектов
#include <settings/classes/shader.h>
#include <settings/classes/resource_manager.h>
#include "settings/objects/point.h"
#include "settings/objects/line.h"
#include "settings/objects/triangle.h"
#include "settings/objects/circle.h"
#include "settings/objects/commet.h"


const GLuint SCREEN_WIDTH = 700;
const GLuint SCREEN_HEIGHT = 700;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
int main()
{
    //Иницализация GLFW и создание окна
    glfwInit();
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER  , GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL", nullptr, nullptr);

    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //Установка глобальных и локальных путей
    ResourceManager::path = "C://Users//ar725//Desktop//GC//qtside//premitives_lab2//premitives//";
    ResourceManager::toShaders = "settings//shaders//";
    ResourceManager::toTextures = "settings//textures//";
    ResourceManager::toVertices = "settings//vertices//";

    //Загрузка шейдера точки
    ResourceManager::LoadShader("point//point.vert", "point//point.frag", "", "point");

    //Загрузка шейдера линии
    ResourceManager::LoadShader("line//line.vert", "line//line.frag", "", "line");

    //Загрузка шейдера триугольника
    ResourceManager::LoadShader("triangle//triangle.vert", "triangle//triangle.frag", "", "triangle");

    //Загрузка шейдера круга
    ResourceManager::LoadShader("circle//circle.vert", "circle//circle.frag", "", "circle");

    //Загрузка вершин ёлки
    std::vector<float> spruces_vertices = ResourceManager::loadVerticesFromFile("spruce");

    //Загрузка вершин камня
    std::vector<float> sone_vertices = ResourceManager::loadVerticesFromFile("stone");

    //Генерация вершин звёзд
    std::vector<float> stars_vertices(7000);
    for(size_t i=0; i<7000; i+=7) {
        //Задание рандомных координат, цветов и размеров звёзд
        stars_vertices[i] = (rand()%2000)/1000.0 - 1;
        stars_vertices[i+1] = (rand()%1200)/1000.0 - 0.2;
        stars_vertices[i+2] = 0;
        stars_vertices[i+3] = (rand()%500)/1000.0 +0.5;
        stars_vertices[i+4] = (rand()%500)/1000.0 +0.5;
        stars_vertices[i+5] = (rand()%500)/1000.0 +0.5;
        stars_vertices[i+6] = rand()%2+1;
    }

    //Задаю вершины для земли
    std::vector<float> earth_vertices = {
        //Координаты    //Цвета
        -1, -0.2, 0,    0.2, 0.37, 0.1,
        -1, -1,   0,    0.2, 0.2,  0.1,
         1, -1,   0,    0.2, 0.2,  0.1,

        -1, -0.2, 0,    0.2, 0.37, 0.1,
         1, -0.2, 0,    0.2, 0.37, 0.1,
         1, -1,   0,    0.2, 0.2,  0.1,
    };

    //Задаю вершины для гор
    std::vector<float> mountaine_vertices = {
        //Координаты    //Цвета
        0,    1, 0,     0.41, 0.41, 0.45,
        -0.5, 0, 0,     0.2,  0.18, 0.1,
        0.5,  0, 0,     0.2,  0.18, 0.1,
    };

    //Задаю координаты и размер гор
    std::vector< std::pair<glm::vec3, glm::vec3> > mountaine_cords = {
          //Координаты
        { glm::vec3(-0.7, -0.2, 0), glm::vec3(0.4) },
        { glm::vec3(-0.9, -0.2, 0), glm::vec3(0.6) },
        { glm::vec3(0.6,  -0.2, 0), glm::vec3(0.3) },
        { glm::vec3(0.7,  -0.2, 0), glm::vec3(0.6) },
        { glm::vec3(0.9,  -0.2, 0), glm::vec3(0.5) }
    };

    //Генерирую рандомны координаты камней
    std::vector <glm::vec3> stones_cords;
    for(size_t i=0; i<50; i++) {
        stones_cords.push_back({
                           (rand()%2000)/1000.0 - 1,
                           (rand()%800)/1000.0 - 1, 0
                       });
        for(size_t j=0; j<i; j++) {
            double k = (rand()%(800))/1000.0 - 0.01*(50-i);
            if(k < -0.2)
            stones_cords.push_back({
                               (rand()%2000)/1000.0 - 1, k, 0
                           });
        }
    }
    //Генерирую рандомные координаты деревьев
    std::vector <glm::vec3> spruces_cords;
    for(size_t i=0; i<100; i++) {
        spruces_cords.push_back({
                           (rand()%2000)/1000.0 - 1,
                           (rand()%800)/1000.0 - 1, 0
                       });
        for(size_t j=0; j<i; j++) {
            double k = (rand()%(800))/1000.0 - 0.01*(100-i);
            if(k < -0.2)
            spruces_cords.push_back({
                               (rand()%2000)/1000.0 - 1, k, 0
                           });
        }
    }

    //Сортирую деревья
    for(size_t i = 1; i < spruces_cords.size(); ++i)
    {
        for(size_t r = 0; r < spruces_cords.size()-i; r++)
        {
            if(spruces_cords[r].y > spruces_cords[r+1].y)
            {
                std::swap(spruces_cords[r], spruces_cords[r+1]);
            }
        }
    }

    //Создаю объекты
    triangle spruce(spruces_vertices);
    triangle earth(earth_vertices);
    triangle stone(sone_vertices);
    point star(stars_vertices);
    triangle mountain(mountaine_vertices);
    circle moon({0.02, 0.02}, 100);
    circle bigstar({{0.02, 0.02}, 100});
    commet comm;

    //Задаю цвета вершинам круга для получения луны
    moon.rebindVertices([](circle *this_){
        this_->setColor({0.2, 0.2, 0.2}, 0);
        for ( int i = 1; i < this_->numberOfSides+2; i++ )
        {
            double pas = sin(i*2*M_PI/(this_->numberOfSides)-M_PI/2)*0.7 + 0.3;
            if(pas < 0) pas = 0;
                this_->setColor({0.06 + 0.8*pas, 0.03 + 0.8*pas, 0.08 + 0.8*pas}, i);
        }
    });

    //Задаю цвета вершинам круга для получения крупной звезды
    bigstar.rebindVertices([](circle *this_){
        this_->setColor({0.03, 1, 0.61}, 0);
        for ( int i = 1; i < this_->numberOfSides+2; i++ )
        {
           this_->setColor({0.06, 0.03, 0.07}, i);
        }
    });


    glEnable(GL_DEPTH_TEST);

    //Цикл отрисовки
    while (!glfwWindowShouldClose(window))
    {
        float time = glfwGetTime();
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        //Задаю тёмный фон
        glClearColor(0.06f, 0.03f, 0.07f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Анимация колыхания ёлок (Сдвиг)
        for(size_t i=0; i<spruce.vertices.size(); i+=6) {
            if(spruce.vertices[i+1]+0.7 > 0)
                spruce.vertices[i] += (spruce.vertices[i+1]+0.7)*cos(time)/1000;
        }
        spruce.bindVertices();

        //Отрисовка ёлок
        for(auto st: spruces_cords)
            spruce.Drow(st, glm::vec3(-(st.y + 0.01)/8));

        //Отрисовка камней
        for(auto st: stones_cords)
            stone.Drow(st, glm::vec3(-(st.y + 0.01)/10));

        //Отрисовка земли
        earth.Drow(glm::vec3(0));

        //Отрисовка гор
        for(auto mount: mountaine_cords)
            mountain.Drow(mount.first, mount.second);

        //Отрисовка кометы, одновремено с рассчётом анимации (Перемещение)
        comm.Drow(-0.04);

        //Анимация луны (Вращение)
        moon.rotation( {0,0,1}, -time/100);
        moon.translate({-0.6, 0.8, 0});
        moon.rotation({0,0,1}, time/100);
        //Отрисовка луны
        moon.Drow();

        //Анимация переменного света большой звезды (Масштабирование)
        bigstar.translate({0.8, 0.8, 0});
        //Отрисовка большой звезды
        bigstar.Drow(glm::vec3(sin(time)/10 + 0.3));

        //Отрисовка звёзд
        star.Drow(glm::vec3(0));
        glfwSwapBuffers(window);
    }
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

