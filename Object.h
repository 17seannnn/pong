#ifndef OBJECT_H
#define OBJECT_H

#include <string>

class Object {
public:
    virtual void Init(int x, int y, int w, int h, std::string textureID,
                      int callbackID = 0, int animSpeed = 0) = 0;
    virtual void Clean() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
protected:
    Object() {}
    virtual ~Object() {}
};

#endif
