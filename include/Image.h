#ifndef IMAGE_H
#define IMAGE_H
#include <string>
#include "GLHeaders.h"

class Shader;

class Image {
public:
    Image(const std::string& filepath);
    ~Image();

    void draw(Shader* shader, const glm::vec2& position, const glm::vec2& scale);

    void bind(unsigned int slot = 0) const;
    void unbind() const;

    int getWidth() const { return width; }
    int getHeight() const { return height; }

private:
    unsigned int textureID;
    int width, height, channels;

    unsigned int VAO = 0, VBO, EBO;
};

#endif /* IMAGE_H */