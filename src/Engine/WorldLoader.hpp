#ifndef WorldLoader_hpp
#define WorldLoader_hpp

#include <vector>
#include "../Objects/DrawableObject.hpp"

class WorldLoader
{
public:

    static void createWorld(const class Engine* engine, class World* world);
    
    static bool isTooClose(DrawableObject* newStructure, DrawableObject* existingStructure);

    static float getRadius(DrawableObject* structure);

    static std::vector<DrawableObject> createdStructures;
        
private:
    
    static int getRandomInt(int min, int max);
    
    static void createBuildings(class World* world);
    
    static void createResources(class World* world);
    
    static void createScenery(class World* world);
    
    static void createStructureOrigin(class World* world, DrawableObject* structure);

};

#endif /* WorldLoader_hpp */
