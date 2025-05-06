#ifndef STAGEBUILDER_H
#define STAGEBUILDER_H

#include <utility>
#include <memory>
#include <vector>
#include <unordered_map>

class Shader;
class World;
class ObjectInfo;
class Floor;
class Cube;
class Pyramid;
class Behavior;

class StageBuilder
{
public:
    StageBuilder(Shader* shader_, World* world_);
    ~StageBuilder();

    void LoadFloors(const std::string& path, std::vector<std::unique_ptr<Floor>>& floors);
    void LoadSticks(const std::string& path, std::vector<std::unique_ptr<Cube>>& cubes);
    void LoadPyramids(const std::string& path, std::vector<std::unique_ptr<Pyramid>>& pyramids);
private:
    std::vector<std::pair<ObjectInfo, std::unique_ptr<Behavior>>>
    GenerateObjects(const std::string& filepath, const std::string& objctType);

    World* world;
    Shader* shader;

    //IDカウンター
    std::unordered_map<std::string, int> IDCounter; 
    // カウンタを増やして新規idの発行
    int NextId(const std::string& type) { return IDCounter[type]++; }
};

#endif /* STAGEBUILDER_H */