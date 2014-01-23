#include "JoystickController.hpp"

JoystickController::JoystickController(AnnEngine* engine)
{
    m_engine = engine;
    
    setWalkAxis();
    setStraffAxis();
    setRotateAxis();
    
    setDeadzone();

    reverse[WALK] = true;
    reverse[STRAFF] = false;
    reverse[ROTATE] = true;

    if(m_engine->getOISJoyStick())
        MAX = m_engine->getOISJoyStick()->MAX_AXIS;
}

void JoystickController::setWalkAxis(int axisID)
{
    axesID[WALK] = axisID;
}
void JoystickController::setStraffAxis(int axisID)
{
    axesID[STRAFF] = axisID;
}
void JoystickController::setRotateAxis(int axisID)
{
    axesID[ROTATE] = axisID;
}

void JoystickController::setReverseWalk(bool state)
{
    reverse[WALK] = state;
}

void JoystickController::setReverseStraff(bool state)
{
    reverse[STRAFF] = state;
}

void JoystickController::setReverseRotate(bool state)
{
    reverse[ROTATE] = state;
}

void JoystickController::update()
{
    if(!m_engine->getOISJoyStick()) return; //if no joystick, cut here
    updateJoystickValues();
    updateVirtualBodyValues();
    debug();
}



float JoystickController::getAxisValue(int axisID)
{
    return trimToFitDeadzone(static_cast<float>(m_engine->
            getOISJoyStick()->getJoyStickState().mAxes[
            axesID[axisID]
            ].abs)/static_cast<float>(MAX));
}

void JoystickController::updateJoystickValues()
{
    walk = getAxisValue(WALK);
    straff = getAxisValue(STRAFF);
    rotate = getAxisValue(ROTATE);

    if(reverse[WALK]) walk *= -1;
    if(reverse[STRAFF]) straff *= -1;
    if(reverse[ROTATE]) rotate *= -1;

}

void JoystickController::updateVirtualBodyValues()
{
    bodyParams* virtualBody = m_engine->getBodyParams();

    float forward = virtualBody->walkSpeed * walk;
    float side = virtualBody->walkSpeed * straff;
    float turn = virtualBody->turnSpeed * rotate;

    float Yvel = virtualBody->Body->getLinearVelocity().y();
    
    float yaw = virtualBody->Orientation.getYaw().valueRadians() + turn*m_engine->getTime()*1000;
    float pitch = virtualBody->Orientation.getPitch().valueRadians();
    float roll = virtualBody->Orientation.getRoll().valueRadians();

    virtualBody->Orientation = Ogre::Euler(yaw,pitch,roll);
    m_engine->setPhysicBodyLinearSpeed(virtualBody->Orientation.toQuaternion()*Ogre::Vector3(side,Yvel,-forward));


}

void JoystickController::debug(void)
{
    cerr << "WALK : " << walk << endl;
    cerr << "STRAFF : " << straff << endl;
    cerr << "ROTATE : " << rotate << endl;

}

void JoystickController::setDeadzone(float threshold)
{
    deadzone = threshold;
}

float JoystickController::trimToFitDeadzone(float value)
{
    if(abs(value) > deadzone) return value;
    return 0.0f;
}

float JoystickController::abs(float value)
{
    if(value < 0) return -value;
    return value;
}
