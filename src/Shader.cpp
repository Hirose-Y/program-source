#include "Shader.h"

#include "GLHeaders.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>

Shader::Shader(const char *vertFilename, const char *fragFilename)
{
    ID = loadProgram(vertFilename, fragFilename);
}

void Shader::use() const
{
    glUseProgram(ID);
}

void Shader::remove() const
{
    glDeleteProgram(ID);
}

GLuint Shader::loadProgram(const char *vertFilename, const char *fragFilename)
{
    // シェーダのソースファイルを読み込む
    std::vector<GLchar> vsrc;
    const bool vstat(readShaderSource(vertFilename, vsrc));
    std::vector<GLchar> fsrc;
    const bool fstat(readShaderSource(fragFilename, fsrc));

    if(vstat && fstat){
        return createProgram(vsrc.data(), fsrc.data());
    }

    return 0;
}

GLuint Shader::createProgram(const char *vsrc, const char *fsrc)
{
    // シェーダーのコンパイル
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vsrc, NULL);
    glCompileShader(vertexShader);
    checkShaderCompilation(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fsrc, NULL);
    glCompileShader(fragmentShader);
    checkShaderCompilation(fragmentShader);

    // シェーダープログラムの作成とリンク
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    checkProgramLinking(shaderProgram);

    // コンパイル済みシェーダーの削除（不要になったため）
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

bool Shader::readShaderSource(const char *filename, std::vector<GLchar> &buffer)
{
    // ファイル名が NULL だった
    if (filename == NULL) return false;

    // ソースファイルを開く
    std::ifstream file(filename, std::ios::binary);
    if (file.fail())
    {
        // 開けなかった
        std::cerr << "Error: Can't open source file: " << filename << std::endl;
        return false;
    }

    // ファイルの末尾に移動し現在位置(=ファイルサイズ)を得る
    file.seekg(0L, std::ios::end);
    GLsizei length = static_cast<GLsizei>(file.tellg());

    // ファイルのメモリを確保
    buffer.resize(length + 1);

    // ファイルを先頭から読み込む
    file.seekg(0L, std::ios::beg);
    file.read(buffer.data(), length);
    buffer[length] = '\0';

    if (file.fail())
    {
        // うまく読み込めなかった
        std::cerr << "Error: Could not read source file: " << filename << std::endl;
        file.close();
        return false;
    }

    // 読み込み成功
    file.close();
    return true;
}

void Shader::checkShaderCompilation(GLuint shader)
{
    GLint success;
    GLchar infoLog[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        std::cerr << "Shader Compilation Error: " << infoLog << std::endl;
    }
}

void Shader::checkProgramLinking(GLuint program)
{
    GLint success;
    GLchar infoLog[1024];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 1024, NULL, infoLog);
        std::cerr << "Program Linking Error: " << infoLog << std::endl;
    }
}

GLint Shader::UniformLocation(const std::string& name)
{
    if (uniformLocations.count(name)) {
        return uniformLocations[name];
    }
    GLint location = glGetUniformLocation(ID, name.c_str());

    if (location == -1) {
        std::cerr << "Error: Uniform '" << name << "' not found in shader program." << std::endl;
        assert(false && "Uniform not found!");
    }

    uniformLocations[name] = location;
    return location;
}

void Shader::SetMat4(const std::string& name, const glm::mat4& value)
{
    glUniformMatrix4fv(UniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetMat3(const std::string& name, const glm::mat3& value)
{
    glUniformMatrix3fv(UniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetVec3(const std::string& name, const glm::vec3& value)
{
    glUniform3fv(UniformLocation(name), 1, glm::value_ptr(value));
}

void Shader::SetInt(const std::string& name, const int value)
{
    glUniform1i(UniformLocation(name), value);
}