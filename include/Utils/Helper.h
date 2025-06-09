#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <iostream>
#include "Core/GLHeaders.h"

class Helper
{
public:
    static void printStr(const std::string& classname, const std::string& str)
    {
        #ifdef DEBUG_MODE

        std::cout << "[Class::" << classname << "] " << str << std::endl;

        #endif
    }

    static void printMatrix(const std::string& classname, const std::string& subject, const glm::mat4& mat)
    {
        #ifdef DEBUG_MODE

        std::cout << "[Class::" << classname << "] " << subject << std::endl;
        for (int i = 0; i < 4; ++i)
        {
            std::cout << "[ ";
            for (int j = 0; j < 4; ++j)
            {
                std::cout << mat[i][j] << " ";
            }
            std::cout << "]" << std::endl;
        }

        #endif
    }

    static void printVec3(const std::string& classname, const std::string& subject, const glm::vec3& vector)
    {
        
        #ifdef DEBUG_MODE

        std::cout << "[Class::" << classname << "] " << subject << ": ( "
         << vector.x << ", " << vector.y << ", " << vector.z << " )" << std::endl;

        #endif
    }

    static glm::vec3 NormalizeOrZero(const glm::vec3& v, float epsilon = 1e-5f)
    {
        float len = glm::length(v);
        return (len < epsilon) ? glm::vec3(0.0f) : v / len;
    }

    static glm::vec3 RoundToZero(const glm::vec3& v, float epsilon = 1e-5f)
    {
        glm::vec3 result = v;
        if (std::abs(result.x) < epsilon) result.x = 0.0f;
        if (std::abs(result.y) < epsilon) result.y = 0.0f;
        if (std::abs(result.z) < epsilon) result.z = 0.0f;
        return result;
    }

    static glm::vec3 KeepMaxComponent(const glm::vec3& v)
    {
        float absX = std::abs(v.x);
        float absY = std::abs(v.y);
        float absZ = std::abs(v.z);

        if (absX >= absY && absX >= absZ)
            return glm::vec3(v.x, 0.0f, 0.0f);
        else if (absY >= absX && absY >= absZ)
            return glm::vec3(0.0f, v.y, 0.0f);
        else
            return glm::vec3(0.0f, 0.0f, v.z);
    }

    static void angleBetweenVectors(const glm::vec3& a, const glm::vec3& b) 
    {
        float dot = glm::dot(glm::normalize(a), glm::normalize(b));
        // クリッピング（誤差対策:-1.0fから1.0fに収める）
        dot = glm::clamp(dot, -1.0f, 1.0f);

        float angleRadians = acos(dot); // ラジアン
        float angleDegrees = glm::degrees(angleRadians); // 度数法に変換

        std::cout << " Degree " << angleDegrees << std::endl;
    }

    static float GetSignedAngleBetweenVectors(const glm::vec3& a, const glm::vec3& b, const glm::vec3& refAxis)
{
    glm::vec3 na = glm::normalize(a);
    glm::vec3 nb = glm::normalize(b);

    float dot = glm::clamp(glm::dot(na, nb), -1.0f, 1.0f);
    float angle = glm::degrees(acos(dot)); // 0〜180度

    glm::vec3 cross = glm::cross(na, nb);

    // 回転軸との向きをチェックして符号をつける
    if (glm::dot(cross, refAxis) < 0)
        angle = -angle;

    return angle;
}

};

#endif /* HELPER_H */