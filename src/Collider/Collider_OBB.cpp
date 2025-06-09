#include "Core/GLHeaders.h"
#include "Collider/Collider_OBB.h"

#include <iostream>

#include "Utils/Helper.h"

OBB::OBB(const glm::mat4 model)
{
    modelMatrix = model;
    bool success = glm::decompose(modelMatrix, extractedScale, orientation, extractedTranslation, skew, perspective);

    if(success)
    {
        center = extractedTranslation;
        
        rotation = glm::mat3_cast(orientation);

        for(int i = 0; i < 3; ++i)
        {
            axes[i] = rotation[i];
        }

        halfSizes = glm::vec3(
            glm::length(rotation[0]) * extractedScale.x * 0.5f,
            glm::length(rotation[1]) * extractedScale.y * 0.5f,
            glm::length(rotation[2]) * extractedScale.z * 0.5f
        ); 
    }
    previousCenter = center;
}

void OBB::Update(const glm::mat4 model)
{
    previousCenter = center;
    prevModelMatrix = modelMatrix;
    modelMatrix = model;
    bool success = glm::decompose(modelMatrix, extractedScale, orientation, extractedTranslation, skew, perspective);

    if(success)
    { 
        center = extractedTranslation;

        //回転行列を作成する
        rotation = glm::mat3_cast(orientation);

        //OBBの軸ベクトルを更新
        for(int i = 0; i < 3; ++i)
        {
            axes[i] = rotation[i];
        }
        
        halfSizes = glm::vec3(
            glm::length(rotation[0]) * extractedScale.x * 0.5f,
            glm::length(rotation[1]) * extractedScale.y * 0.5f,
            glm::length(rotation[2]) * extractedScale.z * 0.5f
        );
    }
}

bool OBB::checkCollision(const Collider& other) const
{
    const OBB& obb = static_cast<const OBB&>(other);

    const glm::vec3& c1 = center;
    const glm::vec3& c2 = obb.Center();

    const glm::vec3* axis1 = axes; // this->axes[0], [1], [2] = ローカル軸（正規化）
    const glm::vec3* axis2 = obb.axes;   // obb.axes[0], [1], [2]

    const glm::vec3 D = c2 - c1; // 中心間ベクトル

    // OBB Aの軸に対するDの射影
    float EPSILON = 1e-5f;

    // 15軸についてチェック
    for (int i = 0; i < 3; ++i)
    {
        if (!testAxis(axis1[i], *this, obb, D)) return false;
        if (!testAxis(axis2[i], *this, obb, D)) return false;
    }

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            glm::vec3 axis = glm::cross(axis1[i], axis2[j]);
            if (glm::dot(axis, axis) > EPSILON) // ゼロベクトル回避
            {
                axis = glm::normalize(axis);
                if (!testAxis(axis, *this, obb, D)) return false;
            }
        }
    }

    return true; // すべての軸で分離していない → 衝突している
}

glm::vec3 OBB::resolveCollision(const Collider& other)
{
    const OBB& obb = static_cast<const OBB&>(other);

    const glm::vec3& c1 = center;
    const glm::vec3& c2 = obb.Center();

    const glm::vec3* axis1 = axes;
    const glm::vec3* axis2 = obb.axes;
    const glm::vec3 D = c2 - c1;

    float EPSILON = 1e-5f;

    // 最小の重なり量と軸を保存
    float minOverlap = std::numeric_limits<float>::max();
    glm::vec3 smallestAxis;

    // 15軸全てについてテスト
    for (int i = 0; i < 3; ++i)
    {
        glm::vec3 axis = axis1[i];
        if (glm::dot(axis, axis) > EPSILON)
        {
            axis = glm::normalize(axis);
            float rA = std::abs(glm::dot(axis, axes[0]) * halfSizes.x)
                     + std::abs(glm::dot(axis, axes[1]) * halfSizes.y)
                     + std::abs(glm::dot(axis, axes[2]) * halfSizes.z);
            float rB = std::abs(glm::dot(axis, axis2[0]) * obb.halfSizes.x)
                     + std::abs(glm::dot(axis, axis2[1]) * obb.halfSizes.y)
                     + std::abs(glm::dot(axis, axis2[2]) * obb.halfSizes.z);
            float distance = std::abs(glm::dot(axis, D));
            float overlap = (rA + rB) - distance;

            if (overlap < 0.0f) return glm::vec3(0.0f); // 分離してる

            if (overlap < minOverlap)
            {
                minOverlap = overlap;
                smallestAxis = axis * (glm::dot(axis, D) < 0.0f ? -1.0f : 1.0f); // 押し出し方向を逆転
            }
        }

        axis = axis2[i];
        if (glm::dot(axis, axis) > EPSILON)
        {
            axis = glm::normalize(axis);
            float rA = std::abs(glm::dot(axis, axes[0]) * halfSizes.x)
                     + std::abs(glm::dot(axis, axes[1]) * halfSizes.y)
                     + std::abs(glm::dot(axis, axes[2]) * halfSizes.z);
            float rB = std::abs(glm::dot(axis, axis2[0]) * obb.halfSizes.x)
                     + std::abs(glm::dot(axis, axis2[1]) * obb.halfSizes.y)
                     + std::abs(glm::dot(axis, axis2[2]) * obb.halfSizes.z);
            float distance = std::abs(glm::dot(axis, D));
            float overlap = (rA + rB) - distance;

            if (overlap < 0.0f) return glm::vec3(0.0f);

            if (overlap < minOverlap)
            {
                minOverlap = overlap;
                smallestAxis = axis * (glm::dot(axis, D) < 0.0f ? -1.0f : 1.0f);
            }
        }
    }

    // 交差軸も調べる（合計15軸）
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            glm::vec3 axis = glm::cross(axis1[i], axis2[j]);
            if (glm::dot(axis, axis) < EPSILON) continue; // 平行 or ゼロ

            axis = glm::normalize(axis);
            float rA = std::abs(glm::dot(axis, axes[0]) * halfSizes.x)
                     + std::abs(glm::dot(axis, axes[1]) * halfSizes.y)
                     + std::abs(glm::dot(axis, axes[2]) * halfSizes.z);
            float rB = std::abs(glm::dot(axis, axis2[0]) * obb.halfSizes.x)
                     + std::abs(glm::dot(axis, axis2[1]) * obb.halfSizes.y)
                     + std::abs(glm::dot(axis, axis2[2]) * obb.halfSizes.z);
            float distance = std::abs(glm::dot(axis, D));
            float overlap = (rA + rB) - distance;

            if (overlap < 0.0f) return glm::vec3(0.0f);

            if (overlap < minOverlap)
            {
                minOverlap = overlap;
                smallestAxis = axis * (glm::dot(axis, D) < 0.0f ? -1.0f : 1.0f);
            }
        }
    }

    // 押し出し方向・量を返す
    return smallestAxis * minOverlap;
}

bool OBB::testAxis(const glm::vec3& axis, const OBB& a, const OBB& b, const glm::vec3& D) const
{
    // a, b それぞれの半径を axis 上に投影
    float rA = std::abs(glm::dot(axis, a.axes[0]) * a.halfSizes.x) +
               std::abs(glm::dot(axis, a.axes[1]) * a.halfSizes.y) +
               std::abs(glm::dot(axis, a.axes[2]) * a.halfSizes.z);

    float rB = std::abs(glm::dot(axis, b.axes[0]) * b.halfSizes.x) +
               std::abs(glm::dot(axis, b.axes[1]) * b.halfSizes.y) +
               std::abs(glm::dot(axis, b.axes[2]) * b.halfSizes.z);

    float distance = std::abs(glm::dot(axis, D));

    return distance <= (rA + rB);
}




bool OBB::intersectRay(const glm::vec3& origin, const glm::vec3& dir, float& outDistance)
{
    // OBB内にローカル変換
    glm::vec3 p = origin - center;
    glm::vec3 d = dir;

    float tMin = -FLT_MAX;
    float tMax = FLT_MAX;

    for (int i = 0; i < 3; i++)
    {
        glm::vec3 axis = axes[i];
        float e = glm::dot(axis, p);
        float f = glm::dot(axis, d);

        if (fabs(f) > 1e-6)
        {
            float t1 = (e + halfSizes[i]) / -f;
            float t2 = (e - halfSizes[i]) / -f;
            if (t1 > t2) std::swap(t1, t2);
            tMin = std::max(tMin, t1);
            tMax = std::min(tMax, t2);
            if (tMin > tMax) return false;
        }
        else
        {
            if (-e - halfSizes[i] > 0 || -e + halfSizes[i] < 0)
                return false;
        }
    }

    outDistance = tMin;
    return true;
}