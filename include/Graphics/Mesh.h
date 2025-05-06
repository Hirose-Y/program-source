#ifndef MESH_H
#define MESH_H

#include <vector>
#include "GLHeaders.h"

class Shader;

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

class Mesh {
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    void draw(Shader* shader);

private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    GLuint VAO, VBO, EBO;
    void setupMesh();
};

#endif /* MESH_H */