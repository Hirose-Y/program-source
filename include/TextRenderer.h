#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include <map>
#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "GLHeaders.h"

class Shader;

struct Character {
    GLuint TextureID;
    glm::ivec2 Size;
    glm::ivec2 Bearing;
    GLuint Advance;
};

class TextRenderer {
public:
    TextRenderer();
    ~TextRenderer();

    bool LoadFont(const std::string& fontPath, int pixelSize = 48);
    void RenderText(const std::string& text, float x, float y, float scale, Shader* shader);
    void SetProjection(const glm::mat4& projection);

private:
    std::map<char, Character> Characters;
    GLuint VAO, VBO;
    glm::mat4 projection;
};

#endif /* TEXTRENDERER_H */