#ifndef CAMERA_VARIABLE_H
#define CAMERA_VARIABLE_H

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct CameraTransform {
    glm::vec3 position;   // カメラの位置
    glm::vec3 direction; // カメラの向き (正面方向)
    glm::vec3 up;         // カメラの上方向
};

struct CameraProjection {
    float fov;         // 視野角 (Field of View)
    float aspectRatio; // アスペクト比 (幅 / 高さ)
    float nearPlane;   // 近クリップ面
    float farPlane;    // 遠クリップ面
};

#endif /* CAMERA_VARIABLE_H */