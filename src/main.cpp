#include <Annwvyn.h>
#include "JoystickController.hpp"
using namespace Annwvyn;

int main(void)
{
    AnnEngine* GameEngine = new AnnEngine;
    
   // GameEngine->getBodyParams()->eyeHeight = 1.65f;

    GameEngine->loadZip("media/OgreOculus.zip");
    GameEngine->loadDir("media/3Dobjects");
    GameEngine->loadDir("media");
    GameEngine->loadDir("media/male");
    GameEngine->initRessources();
    
/*  AnnGameObject* Desk = GameEngine->createGameObject("Desk.mesh");
    Desk->setPos(-0.5,-1.3,9.5);
    
    AnnLightObject* DeskLight = GameEngine->addLight();
    DeskLight->setPosition(-1,1,9);
*/

    AnnLightObject* l = GameEngine->addLight();
    
    l->setType(Ogre::Light::LT_DIRECTIONAL);
    l->setDirection(-.75,-1,-0.25);

    l->setPosition(0,1,0);
    
    GameEngine->initPlayerPhysics();

    GameEngine->oculusInit();
    
//    GameEngine->setDebugPhysicState(true);

    AnnMap(GameEngine, "media/classroom.map");
    
/*    AnnGameObject* npc = GameEngine->createGameObject("basichBody.mesh");
    npc->node()->setScale(0.1,0.1,0.1);

    npc->setPos(0,1,1);
    
    npc->setAnimation("Walk");
    npc->playAnimation(true);
    npc->loopAnimation(true);

    npc->setUpBullet(80,boxShape);*/
    
    JoystickController joystickController(GameEngine);
    joystickController.setRotateAxis(3);
    joystickController.setReverseRotate(false);
    while(!GameEngine->requestStop())
    {
        joystickController.update();
/*        std::cerr << "Player height : " << GameEngine->getBodyParams()->eyeHeight << std::endl;
        std::cerr << "node height : " << GameEngine->getBodyParams()->Position.y << std::endl;
        std::cerr << "camera height : "  << GameEngine->getCamera()->getPosition().y << std::endl;*/
        
        GameEngine->refresh();
    }
    
    delete GameEngine;
    return EXIT_SUCCESS;
}
