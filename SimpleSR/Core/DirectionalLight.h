#ifndef DirectionalLight_h__
#define DirectionalLight_h__

#include <Vector3.h>
#include <Color.h>

class DirectionalLight
{
public:
    Vector3 Direction;
    float Intensity;
    Color Col;
};

#endif // DirectionalLight_h__
