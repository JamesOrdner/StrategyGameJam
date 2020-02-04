#ifndef InputTypes_hpp
#define InputTypes_hpp

#include <functional>

/// InputEvent enumerates all possible user inputs
enum class InputEvent
{
    Camera_X,
    Camera_Y
};

typedef std::function<void(float)> InputCallback;

#endif /* InputTypes_hpp */
