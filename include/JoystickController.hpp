#include <Annwvyn.h>

using namespace std;
using namespace OIS;
using namespace Annwvyn;

class JoystickController
{
    private: //datatypes 
    enum {
        WALK,
        STRAFF,
        ROTATE
    };

    public:
        JoystickController(AnnEngine* engine);

        void setWalkAxis(int axisID = 1);
        void setStraffAxis(int axisID = 0);
        void setRotateAxis(int axisID = 2);
        
        void setReverseWalk(bool state = true);
        void setReverseStraff(bool state = false);
        void setReverseRotate(bool state = true);

        void setDeadzone(float threshold = 0.15);

        void update();
    private:
        //private methods :
        void updateJoystickValues();
        void updateVirtualBodyValues(); 
        float getAxisValue(int axisID);
        float trimToFitDeadzone(float value);
        void debug(void);
        //private atributes :
        AnnEngine* m_engine;
        float walk;
        float straff;
        float rotate;
    
        float deadzone;

        int axesID[3];
        
        bool reverse[3];

        int MAX;

        float abs(float value);
};

