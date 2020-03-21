#include "resource_manager.h"

std::map<std::string, Shader>              ResourceManager::Shaders;
std::map<std::string, std::vector<float>>  ResourceManager::Vertices;
std::string                                ResourceManager::path;
std::string                                ResourceManager::toShaders;
std::string                                ResourceManager::toVertices;
std::string                                ResourceManager::toTextures;
Shader ResourceManager::LoadShader(std::string vShaderFile, std::string fShaderFile, std::string gShaderFile, std::string name)
{
    Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return Shaders[name];
}

Shader ResourceManager::GetShader(std::string name)
{
    return Shaders[name];
}

std::vector<float> ResourceManager::LoadVertices(std::string file, std::string name) {
    Vertices[name] = loadVerticesFromFile(file);
    return Vertices[name];
}
std::vector<float>  ResourceManager::GetVertices(std::string name) {
    return Vertices[name];
}
void ResourceManager::Clear()
{
    // (Properly) delete all shaders
    for (auto iter : Shaders)
        glDeleteProgram(iter.second.ID);
}

Shader ResourceManager::loadShaderFromFile(std::string vShaderFile, std::string fShaderFile, std::string gShaderFile)
{
    // 1. Retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    try
    {
        // Open files
        std::ifstream vertexShaderFile(path + toShaders + vShaderFile);
        std::ifstream fragmentShaderFile(path + toShaders + fShaderFile);
        if(!vertexShaderFile.is_open() || !fragmentShaderFile.is_open())
            throw std::exception();
        std::stringstream vShaderStream, fShaderStream;
        // Read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // Convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // If geometry shader path is present, also load a geometry shader
        if (gShaderFile != "")
        {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    const GLchar *vShaderCode = vertexCode.c_str();
    const GLchar *fShaderCode = fragmentCode.c_str();
    const GLchar *gShaderCode = geometryCode.c_str();
    Shader shader;
    shader.Compile(vShaderCode, fShaderCode, gShaderFile != "" ? gShaderCode : nullptr);
    return shader;
}

std::vector<float>  ResourceManager::loadVerticesFromFile(std::string file) {
    std::vector<float> vertices;
    try {
        std::ifstream in(path + toVertices + file);
        if(!in.is_open())
            throw std::exception();
        float v;
        while(in >> v) {
            vertices.push_back(v);
        }
    } catch (std::exception e) {
        std::cout << "ERROR::VERTICES: Failed to read shader files" << std::endl;
    }
    return vertices;
}
