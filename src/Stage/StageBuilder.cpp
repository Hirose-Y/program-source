#include "Stage/StageBuilder.h"

#include <iostream>
#include <vector>
#include <utility>
#include <memory>
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>

#include "GLHeaders.h"

#include "Shader.h"
#include "World/World.h"
#include "Behavior/Behavior.h"

#include "Object/Object.h"
#include "Object/ObjectInfo.h"
#include "Object/Object_Cube.h"
#include "Object/Object_Floor.h"
#include "Object/Object_Pyramid.h"

using json = nlohmann::json;

StageBuilder::StageBuilder(Shader* shader_, World* world_)
:shader(shader_), world(world_)
{
    IDCounter["sticks"] = 0;
	IDCounter["Floor"] = 0;
	IDCounter["Pyramid"] = 0;
}

StageBuilder::~StageBuilder()
{

}

void StageBuilder::LoadFloors(const std::string& path, std::vector<std::unique_ptr<Floor>>& floors)
{
    auto objects = GenerateObjects(path, "floors");

    for(auto& [info, behavior] : objects)
    {
        auto floor = std::make_unique<Floor>(shader, world, info, std::move(behavior));
        
        floors.push_back(std::move(floor));
    }
}

void StageBuilder::LoadSticks(const std::string& path, std::vector<std::unique_ptr<Cube>>& cubes)
{
    auto objects = GenerateObjects(path, "sticks");

    for(auto& [info, behavior] : objects)
    {
        auto cube = std::make_unique<Cube>(shader, world, info, std::move(behavior));
        
        cubes.push_back(std::move(cube));
    }
}

void StageBuilder::LoadPyramids(const std::string& path, std::vector<std::unique_ptr<Pyramid>>& pyramids)
{
    auto objects = GenerateObjects(path, "pyramids");

    for(auto& [info, behavior] : objects)
    {
        auto pyramid = std::make_unique<Pyramid>(shader, world, info, std::move(behavior));
        
        pyramids.push_back(std::move(pyramid));
    }
}

//------------------------------------------------//
// 各オブジェクトを外部のjsonファイルから読み込む関数 //
//------------------------------------------------//
std::vector<std::pair<ObjectInfo, std::unique_ptr<Behavior>>> 
StageBuilder::GenerateObjects(const std::string& filepath, const std::string& objctType)
{
    std::vector<std::pair<ObjectInfo, std::unique_ptr<Behavior>>> result;

    // アサ―トで失敗条件を検出
    assert(!filepath.empty() && "Error: Filepath is empty!");
    assert((objctType == "floors" || objctType == "sticks" || objctType == "pyramids") &&
           "Error: Invalid object type!");

    if (filepath.empty() || 
       (objctType != "floors" && objctType != "sticks" && objctType != "pyramids")) {
        std::cout << "Failed object type!!" << std::endl;
        return {};
    }

    // jsonファイルを読み込む
    std::ifstream inFile(filepath);
    json j;
    inFile >> j;

    // jsonファイルの "sticks" という配列の各要素stickData 
    for (const auto& objctData : j[objctType]) {
        ObjectInfo info;
        info.id = NextId(objctType);

        // 初期位置
        info.transform.position = glm::vec3( objctData["position"][0], objctData["position"][1], objctData["position"][2] );
        // 初期角度
        info.transform.rotation = glm::vec3( objctData["rotation"][0], objctData["rotation"][1], objctData["rotation"][2]);
        // 初期スケール
        info.transform.scale = glm::vec3( objctData["scale"][0], objctData["scale"][1], objctData["scale"][2] );
        // 初期カラー
        info.color = glm::vec3( objctData["color"][0], objctData["color"][1], objctData["color"][2] );
       
        // ビヘイビアを生成
        std::unique_ptr<Behavior> behavior;

        const auto& beh = objctData["behavior"];
        std::string type = beh["type"];

        if (type == "Rotate") {
            glm::vec3 axis(beh["axis"][0], beh["axis"][1], beh["axis"][2]);
            float speed = beh["speed"];
            behavior = std::make_unique<RotateBehavior>(axis, speed);
        } else if (type == "translate") {
            glm::vec3 direction(beh["trans"][0], beh["trans"][1], beh["trans"][2]);
            float val = beh["val"];
            behavior = std::make_unique<TranslateBehavior>(direction, val);
        } else if (type == "Round") {
            glm::vec3 axis(beh["axis"][0], beh["axis"][1], beh["axis"][2]);
            float val = beh["val"];
            behavior = std::make_unique<RoundBehavior>(axis, val);
        } else if (type == "Scale") {
            glm::vec3 targetScale(beh["scale"][0], beh["scale"][1], beh["scale"][2]);
            float val = beh["val"];
            behavior = std::make_unique<ScaledBehavior>(targetScale, val);
        } else if (type == "Composite") {
            auto composite = std::make_unique<CompositeBehavior>();

            for (const auto& sub : beh["behaviors"]) {
                std::string subType = sub["type"];

                if (subType == "Rotate") {
                    glm::vec3 axis(sub["axis"][0], sub["axis"][1], sub["axis"][2]);
                    float speed = sub["speed"];
                    composite->addBehavior(std::make_unique<RotateBehavior>(axis, speed));
                } else if (subType == "translate") {
                    glm::vec3 direction(sub["trans"][0], sub["trans"][1], sub["trans"][2]);
                    float val = sub["val"];
                    composite->addBehavior(std::make_unique<TranslateBehavior>(direction, val));
                } else if (subType == "Round") {
                    glm::vec3 axis(sub["axis"][0], sub["axis"][1], sub["axis"][2]);
                    float val = sub["val"];
                    composite->addBehavior(std::make_unique<RoundBehavior>(axis, val));
                } else if (subType == "Scale") {
                    glm::vec3 targetScale(sub["scale"][0], sub["scale"][1], sub["scale"][2]);
                    float val = sub["val"];
                    composite->addBehavior(std::make_unique<ScaledBehavior>(targetScale, val));
                }
            }
            behavior = std::move(composite);
        }
        result.emplace_back(std::move(info), std::move(behavior));
    }
    return result;
}