
#ifndef ROAD_H
#define ROAD_H

#include <string>
#include <vector>
#include <irrlicht.h>

class RoadType;

typedef irr::core::vector3d<double> vector3dd;
typedef irr::core::vector2d<double> vector2dd;
struct RoadPoint
{
    vector3dd               p;
    int                     radius;
    irr::video::SColor      color;
};

class Road
{
public:
    typedef std::vector<RoadPoint> roadPointVector_t;

public:
    Road(const std::string& roadFilename, bool& ret, bool global, bool read = false);
    Road(const std::string& roadFilename,
         const std::string& roadName,
         const std::string& roadDataFilename,
         RoadType*          roadType,
         bool               global);
    ~Road();

    bool isLoaded(); // inline
    const std::string& getName(); // inline

    void editorRender(bool editorRoad = false);
    const roadPointVector_t& getRoadPointVector() const; // inline
    RoadType* getRoadType(); // inline

private:
    bool readHeader();
    bool writeHeader();
    bool readData();
    bool writeData();

    // only called by the editor: pos is the current camera pos, so not the absolute position
    void addRoadFarPoint(const irr::core::vector3df& pos);
    void addRoadFarPointBegin(const irr::core::vector3df& pos);
    void removeRoadPoint();
    void removeRoadPointBegin();
    
private:
    // only called by the addFarPoint
    void addRoadPoint(const vector3dd& pos);
    void addRoadPointBegin(const vector3dd& pos);

private:
    std::string             roadFilename;
    std::string             roadName;
    std::string             roadDataFilename;

    RoadType*               roadType;
    bool                    loaded;
    bool                    global;

    roadPointVector_t       roadPointVector;


    friend class RoadManager;
    friend class MenuPageEditor;
    friend class MenuPageEditorRoad;
    friend class MenuPageEditorRace;
    friend class MenuPageEditorDay;
    friend class MenuPageEditorStage;
};

inline bool Road::isLoaded()
{
    return loaded;
}

inline const std::string& Road::getName()
{
    return roadName;
}

inline const Road::roadPointVector_t& Road::getRoadPointVector() const
{
    return roadPointVector;
}

inline RoadType* Road::getRoadType()
{
    return roadType;
}

#endif // ROAD_H
