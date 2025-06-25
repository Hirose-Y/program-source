#include "Scene/GameScene.h"
#include "Scene/GameSceneController.h"
#include "Core/AppContext.h"

GameScene::GameScene(GameSceneController* controller_)
:controller(controller_)
{

}

void GameScene::requestSceneChange(SceneType type)
{
    controller->ChangeScene(type);
}

AppContext* GameScene::Context()
{ 
    return controller->GetContext();
}