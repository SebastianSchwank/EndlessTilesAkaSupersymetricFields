#include "pointlight.h"

PointLight::PointLight(){

}

PointLight::PointLight(float x, float y,
                       float emission, unsigned int color){
    FloatBits UintRgba;

    UintRgba.i_ = (unsigned int) (x*4294967295.0);
    mData.append(UintRgba.i_);
    UintRgba.i_ = (unsigned int) (y*4294967295.0);
    mData.append(UintRgba.i_);

    UintRgba.i_ = (unsigned int) (emission*4294967295.0);
    mData.append(UintRgba.i_);

    mData.append(color);

    velX = 0.0;
    velY = 0.0;
}

unsigned int PointLight::getAttributeAsPixel(int i){
    return mData[i];
}

float PointLight::getPosX(){
    return mData[0]/4294967295.0;
}

float PointLight::getPosY(){
    return mData[1]/4294967295.0;
}

float PointLight::getCharge(){
    return 1.0f - mData[2]/2147483647.5;
}

void PointLight::setPos(float x, float y){
    FloatBits UintRgba;

    UintRgba.i_ = (unsigned int) (x*4294967295.0);
    mData[0] = UintRgba.i_;
    UintRgba.i_ = (unsigned int) (y*4294967295.0);
    mData[1] = UintRgba.i_;
}

int PointLight::getSize(){
    //Size of one line-object in "uints"
    return 4;
}
