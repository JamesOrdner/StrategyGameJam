#ifndef GObjectComponent_hpp
#define GObjectComponent_hpp

class GameObjectComponent
{
public:
    
    GameObjectComponent(class GameObject* owner);
    
    virtual ~GameObjectComponent();
    
    class GameObject* const owner;
};

#endif /* GObjectComponent_hpp */
