#ifndef OBJECT_H
#define OBJECT_H

#include <string>

class Object {
public:
    virtual void Init(int x, int y, int w, int h, int textureID,
                      void (*callback)() = 0) = 0;
    virtual void Clean() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
protected:
    Object() {}
    virtual ~Object() {}
};

#endif
