#ifndef GObjectComponent_hpp
#define GObjectComponent_hpp

class GameObjectComponent
{
public:
    
    GameObjectComponent(class GameObject* owner);
    
    virtual ~GameObjectComponent();
    
protected:
    
    class GameObject* const owner;
};

#endif /* GObjectComponent_hpp */
