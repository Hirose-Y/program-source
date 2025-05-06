#include "Scene/GameScene.h"
#include "Scene/GameSceneController.h"

GameScene::GameScene(GameSceneController* controller_)
:controller(controller_)
{

}

void GameScene::requestSceneChange(SceneType type)
{
    controller->ChangeScene(type);
}