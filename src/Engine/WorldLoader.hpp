#ifndef WorldLoader_hpp
#define WorldLoader_hpp

class WorldLoader
{
public:

    static void createWorld(const class Engine* engine, class World* world);
        
private:
    static int getRandomInt(int min, int max);
    static void createBuildings(class World* world);
    static void createResources(class World* world);
    static void createScenery(class World* world);
    static int getStructureOrigin();
};

#endif /* WorldLoader_hpp */
