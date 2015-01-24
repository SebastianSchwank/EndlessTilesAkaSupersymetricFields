#ifndef SCENE_H
#define SCENE_H

#pragma once

#include <QVector>
#include <QImage>

#include "lineobject.h"
#include "pointlight.h"


class Scene
{
public:
    Scene();
    void addObject(LineObject newObject);
    void addObject(PointLight newObject);
    QImage getSceneImageLines();
    QImage getSceneImageParticles();

    unsigned int getClickedLight(float x, float y, float r);
    void moveLight(float x, float y, unsigned int i);

    QVector<PointLight> mSceneP;
    QVector<LineObject> mSceneL;

private:
    QImage *SceneImage;
};

#endif // SCENE_H
