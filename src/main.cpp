#include <Annwvyn.h>
#include "JoystickController.hpp"
using namespace Annwvyn;

int main(void)
{
    AnnEngine* GameEngine = new AnnEngine("PPD Balade Virtuelle");
    
   // GameEngine->getBodyParams()->eyeHeight = 1.65f;

    GameEngine->loadZip("media/OgreOculus.zip");
    GameEngine->loadDir("media/3Dobjects");
    GameEngine->loadDir("media");
    GameEngine->loadDir("media/male");
    GameEngine->initRessources();
    

    AnnLightObject* l = GameEngine->addLight();
    
    l->setType(Ogre::Light::LT_DIRECTIONAL);
    l->setDirection(-.75,-1,-0.25);

    l->setPosition(0,1,0);
    
    GameEngine->initPlayerPhysics();

    GameEngine->oculusInit();
    

    AnnMap(GameEngine, "media/classroom.map");
    
    
    //configure joystick
    JoystickController joystickController(GameEngine);
    joystickController.setRotateAxis(3);
    joystickController.setReverseRotate(false);
    
    while(!GameEngine->requestStop())
    {
        //update joystick
        joystickController.update();
        
        //update view
        GameEngine->refresh();
    }
    
    delete GameEngine;
    return EXIT_SUCCESS;
}
