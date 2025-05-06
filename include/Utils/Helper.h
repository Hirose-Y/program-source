#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <string>
#include "GLHeaders.h"

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
};

#endif /* HELPER_H */