#ifndef Shader_H
#define Shader_H

#include <string>
#include "Core/GLHeaders.h"
#include <vector>
#include <unordered_map>

class Shader
{
public:    
    Shader(const char *vertFilename, const char *fragFilename);
    void use() const;
    void remove() const;

    //オブジェクトの描画時に必要な関数群
    void SetMat4(const std::string& name, const glm::mat4& value);
    void SetMat3(const std::string& name, const glm::mat3& value);
    void SetVec3(const std::string& name, const glm::vec3& value);
    void SetInt(const std::string& name, const int value);
    void SetFloat(const std::string& name, const float value);
private:
    GLuint ID;
    
    // シェーダのソースファイルを読み込んでプログラムオブジェクトを作成する
    //  vertFilename: バーテックスシェーダのソースファイル名
    //  fragFilename: フラグメントシェーダのソースファイル名
    GLuint loadProgram(const char *vertFilename, const char *fragFilename);

    // プログラムオブジェクトを作成する関数
    //  vsrc: バーテックスシェーダのsource
    //  fsrc: フラグメントシェーダのsource
    GLuint createProgram(const char *vsrc, const char *fsrc);
    
    // シェーダのソースファイルを読み込んだメモリを返す
    //  filename: シェーダのソースファイル名
    //  buffer: 読み込んだソースファイルのテキスト
    bool readShaderSource(const char *filename, std::vector<GLchar> &buffer);

    // シェーダーのコンパイルエラーチェック
    void checkShaderCompilation(GLuint shader);

    // プログラムのリンクエラーチェック
    void checkProgramLinking(GLuint program);

    // shaderのuniform変数のキャッシュ
    std::unordered_map<std::string, GLint> uniformLocations;

    // キャッシュしてあるLocationならばそれを渡し、キャッシュしていなければ新たに作成したものを渡す
    GLint UniformLocation(const std::string& name);
};

#endif /* Shader_H */