#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;

uniform vec3 lightDir;      // 平行光の方向
uniform vec3 lightColor;    // 平行光の色

uniform vec3 pointLightPos;   // 点光源の位置
uniform vec3 pointLightColor; // 点光源の色

uniform vec3 viewPos;       // カメラ位置
uniform vec3 objectColor;   // オブジェクトの色

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // ===== 平行光 (Directional Light) =====
    vec3 dirLightDir = normalize(-lightDir);
    float diffDir = max(dot(norm, dirLightDir), 0.0);
    vec3 reflectDirDir = reflect(-dirLightDir, norm);
    float specDir = pow(max(dot(viewDir, reflectDirDir), 0.0), 32);
    vec3 ambientDir = 0.4 * lightColor;
    vec3 diffuseDir = diffDir * lightColor;
    vec3 specularDir = specDir * lightColor;

    // ===== 点光源 (Point Light) =====
    vec3 lightVec = pointLightPos - FragPos;
    float distance = length(lightVec);
    vec3 pointLightDir = normalize(lightVec);

    float diffPoint = max(dot(norm, pointLightDir), 0.0);
    vec3 reflectDirPoint = reflect(-pointLightDir, norm);
    float specPoint = pow(max(dot(viewDir, reflectDirPoint), 0.0), 32);

    // 距離減衰 (Attenuation)
    float attenuation = 1.0 / (1.0 + 0.09 * distance + 0.032 * (distance * distance));

    vec3 ambientPoint = 0.8 * pointLightColor;
    vec3 diffusePoint = diffPoint * pointLightColor;
    vec3 specularPoint = specPoint * pointLightColor;

    ambientPoint *= attenuation;
    diffusePoint *= attenuation;
    specularPoint *= attenuation;

    // ===== 合成 =====
    vec3 result = (ambientDir + diffuseDir + specularDir +
                   ambientPoint + diffusePoint + specularPoint) * objectColor;

    FragColor = vec4(result, 1.0);
}
