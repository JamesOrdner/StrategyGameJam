#ifndef WorldLoader_hpp
#define WorldLoader_hpp

#include <vector>
#include "../Objects/DrawableObject.hpp"

class WorldLoader
{
public:

    static void createWorld(const class Engine* engine, class World* world);
    
    static bool isTooClose(DrawableObject* newStructure, DrawableObject* existingStructure, int minDistance);

    static float getRadius(DrawableObject* structure);

    static std::vector<DrawableObject*> createdStructures;

    static const int minDistanceBetweenStructures = 18000;

    static const int minDistanceFromStructures = 1000;
        
private:
    
    static int getRandomInt(int min, int max);
    
    static void createStructures(class World* world);
    
    static void createScenery(class World* world);
    
    static void createStructureOrigin(class World* world, DrawableObject* structure, int minDistance);

};

#endif /* WorldLoader_hpp */
