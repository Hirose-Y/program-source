#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include "Core/GLHeaders.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>

#include "Object/ObjectInfo.h"

class Camera;
class Collider;
class Light;

class Object
{
public:
    Object(const std::string& path);
    virtual ~Object();

    bool LoadModel(const std::string& path);

    virtual void SetupBuffers();

    virtual void Initialize() = 0;
    virtual void Update(float deltaTime) {}
    virtual void draw(Camera* camera, Light* light) = 0;

    virtual Collider* GetCollider() const { return nullptr; }
    virtual glm::mat4 GetDeltaMatrix() const = 0;
    virtual ObjectType GetObjectType() const = 0;
    virtual bool IsTransparent() const { return false; }
    virtual int GetObjectID() const = 0;

    virtual void Transparent(bool flag) {};
protected:
    GLuint VAO; // 頂点配列オブジェクト名
    GLuint VBO; // 頂点バッファオブジェクト名
    GLuint NBO; // 法線バッファオブジェクト名

    std::vector<float> vertices;
    std::vector<float> normals; //法線
    std::vector<unsigned int> indices;
};

#endif /* OBJECT_H */


