#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <settings/libs/glad/glad.h>
#include "shader.h"

class ResourceManager
{
public:
    static std::string path;
    static std::string toShaders;
    static std::string toVertices;
    static std::string toTextures;
    static std::map<std::string, Shader>    Shaders;
    static std::map<std::string, std::vector<float>> Vertices;
    static Shader   LoadShader(std::string vShaderFile, std::string fShaderFile, std::string gShaderFile, std::string name);
    static Shader   GetShader(std::string name);
    static std::vector<float> LoadVertices(std::string file, std::string name);
    static std::vector<float> GetVertices(std::string name);
    static void      Clear();
    ResourceManager() { }
    static Shader    loadShaderFromFile(std::string vShaderFile, std::string fShaderFile, std::string gShaderFile = nullptr);
    static std::vector<float> loadVerticesFromFile(std::string file);
};

#endif // RESOURCE_MANAGER_H
