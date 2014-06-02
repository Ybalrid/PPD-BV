#include <Annwvyn.h>
#include "JoystickController.hpp"
using namespace Annwvyn;

int main(void)
{
    AnnEngine* GameEngine = new AnnEngine("PPD Balade Virtuelle");
    
    //Confort adjustement : reduce Body turn speed
    GameEngine->getBodyParams()->turnSpeed *=0.7f; 
    GameEngine->getBodyParams()->Position = Ogre::Vector3(-15.5, 0, -0.5);


    GameEngine->loadZip("media/OgreOculus.zip");
    GameEngine->loadDir("media/3Dobjects");
    GameEngine->loadDir("media");
    GameEngine->loadDir("media/vesale");
    GameEngine->initRessources();
    
    
    //compensate some lighting problem :
    AnnLightObject* l = GameEngine->addLight();
    l->setType(Ogre::Light::LT_DIRECTIONAL);
    l->setDirection( 0.5,-1,-0.25);
    l->setPosition(0,1,0);
    l->setPowerScale(0.2f);
    GameEngine->setAmbiantLight(Ogre::ColourValue(0.1f,0.1f,0.1f)); 
    GameEngine->initPlayerPhysics();
    GameEngine->oculusInit();
    

    //load vesale !!!!
    AnnMap(GameEngine, "media/vesale/vesale.map");
    AnnMap B(GameEngine, "media/vesale/fourniture.map");    
    AnnGameObject* debugDesk =  B.getContent()[0];
    


    //configure joystick
    JoystickController joystickController(GameEngine);
    joystickController.setRotateAxis(3);
    joystickController.setReverseRotate(false);
    
//    GameEngine->setDebugPhysicState(true);
    
    while(!GameEngine->requestStop())
    {
        //update joystick
        joystickController.update();
        
        //update view
        GameEngine->refresh();

        std::cerr << GameEngine->getBodyParams()->Position << std::endl;
        std::cerr << "DESK :" << debugDesk->pos() << std::endl;
    }
    
    delete GameEngine;
    return EXIT_SUCCESS;
}
