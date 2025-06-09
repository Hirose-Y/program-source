#ifndef SCENE_CHANGE_ACTIONS_H
#define SCENE_CHANGE_ACTIONS_H

#include <string>
#include "Scene/SceneType.h"

class SceneChangeActions
{
public:
    // シーン切替
    virtual bool ShouldChangeSceneTo(SceneType& outType) = 0;
};

#endif /* SCENE_CHANGE_ACTIONS_H */