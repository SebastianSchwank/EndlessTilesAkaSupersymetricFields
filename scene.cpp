#include "scene.h"

Scene::Scene()
{
}

void Scene::addObject(LineObject newObject){
    mSceneL.append(newObject);
}

void Scene::addObject(PointLight newObject){
    mSceneP.append(newObject);
}

unsigned int Scene::getClickedLight(float x, float y, float r){
    unsigned int j = 0;
    for(int i = 0; i < mSceneP.size(); i++){
        float d = sqrt((x-mSceneP[i].getPosX())*(x-mSceneP[i].getPosX())+(y-mSceneP[i].getPosY())*(y-mSceneP[i].getPosY()));
        if(d < r) j = i;
    }
    return j;
}

void Scene::moveLight(float x, float y,unsigned int i){
    mSceneP[i].setPos(x,y);
}

QImage Scene::getSceneImageLines(){
    //Probably a memory leak here !
    SceneImage = new QImage(mSceneL.size(),LineObject::getSize(),QImage::Format_ARGB32);

    //Set the Scene
    for(int j = 0; j < mSceneL.size(); j++){
        for(int i = 0; i < LineObject::getSize(); i++)
            SceneImage->setPixel(j,i,mSceneL[j].getAttributeAsPixel(i));
    }

    return *SceneImage;
}

QImage Scene::getSceneImageParticles(){
    //Probably a memory leak here !
    SceneImage = new QImage(mSceneP.size(),PointLight::getSize(),QImage::Format_ARGB32);

    //Set the Scene
    for(int j = 0; j < mSceneP.size(); j++){
        for(int i = 0; i < PointLight::getSize(); i++)
            SceneImage->setPixel(j,i,mSceneP[j].getAttributeAsPixel(i));
    }

    return *SceneImage;
}
