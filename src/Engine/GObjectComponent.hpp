#ifndef GObjectComponent_hpp
#define GObjectComponent_hpp

class GObjectComponent
{
public:
    
    GObjectComponent(class GObject* owner);
    
    virtual ~GObjectComponent();
    
protected:
    
    class GObject* const owner;
};

#endif /* GObjectComponent_hpp */
