#ifndef GAMEOBJ_HPP
#define GAMEOBJ_HPP

class GameObj {
public:
    Vector2 pos;

    virtual float ZOrder() = 0;
    virtual void Update(float) = 0;
    virtual void Draw() = 0;
    virtual ~GameObj() { }
};

#endif
