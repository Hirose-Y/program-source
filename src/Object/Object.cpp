#include "GLHeaders.h"
#include "Object/Object.h"
#include <string>
#include <iostream>

Object::Object(const std::string& path)
{
    LoadModel(path);
    SetupBuffers();
    //std::cout << "[Object] VAO: " << &VAO << " VBO: " << &VBO << std::endl; 
}

Object::~Object()
{
    // 頂点配列オブジェクトを削除する
    glDeleteVertexArrays(1, &VAO);

    // 頂点バッファオブジェクトを削除する
    glDeleteBuffers(1, &VBO);

    // 法線バッファオブジェクトを削除する
    glDeleteBuffers(1, &NBO);
}

bool Object::LoadModel(const std::string& path)
{
    Assimp::Importer importer;
    
    // ファイルをロードし、三角形化＆UV反転を適用
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || !scene->mRootNode || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) {
        std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return false;
    }

    aiMesh* mesh = scene->mMeshes[0];  // 最初のメッシュのみ
    // 頂点データをvectorに入れる
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        vertices.push_back(mesh->mVertices[i].x);
        vertices.push_back(mesh->mVertices[i].y);
        vertices.push_back(mesh->mVertices[i].z);
    }

    // 法線の取得（修正：mNumVertices を使用）
    if (mesh->HasNormals()) {  // 法線データがあるか確認
        //法線データがあればvectorに入れる
        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            normals.push_back(mesh->mNormals[i].x);
            normals.push_back(mesh->mNormals[i].y);
            normals.push_back(mesh->mNormals[i].z);
        }
    } else {
        std::cerr << "Warning: Mesh has no normal data!" << std::endl;
    }

    return true;
}


void Object::SetupBuffers()
{
    // VAO（頂点配列オブジェクト）と VBO（頂点バッファオブジェクト）の作成
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &NBO);  // 法線バッファ用

    // VAO にバインド（VBO の設定を記録）
    glBindVertexArray(VAO);

    // VBO に頂点データをバインドして送信
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // 頂点属性（位置情報）を設定(in変数にデータを入れる)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 法線データをNBOにバインドして送信
    glBindBuffer(GL_ARRAY_BUFFER, NBO);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STATIC_DRAW);

    // 法線属性（面ごとの法線を設定）
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    // VAO のバインド解除
    glBindVertexArray(0);
}