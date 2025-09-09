#ifndef OBJECTS_H
#define OBJECTS_H
#include "common.hpp"

class Module;
class SiteRow;
class Pin;
class Net;
class PlaceData;

class Module
{
public:
    Module()
    {
        Init();
    }
    int idx;
    string name;
    float width;
    float height;
    float area;
    float orientation;
    bool isMacro;
    bool isFixed;
    bool isFiller;
    vector<Pin *> modulePins;
    vector<Net *> nets;
    void Init()
    {
        idx = -1;
        center.SetZero();
        width = 0;
        height = 0;
        area = 0;
        orientation = 0;
        isMacro = false;
        isFiller = false;
        isFixed = false;
     }
    POS_2D center; 
    
 
};
class SiteRow 
{
public:
    SiteRow()
    {
        bottom = 0;
        height = 0;
        step = 0;
        start.SetZero();
        end.SetZero();
    }

    double bottom;             
    double height;             
    double step;                
    POS_2D start;               
    POS_2D end;                 
};
/**
 * @brief id:0 respresents I;1 respresents O
 */
class Pin
{
public:

    Pin()
    {
        init();
    }
    
    void init()
    {
        idx = -1;
        module = NULL;
        net = NULL;
        offset.SetZero();

    }
    int idx;
    Module *module;
    Net *net;
    POS_2D offset;
};

class Net
{
public:

    Net(string& _name):name(_name)
    {
        init();
    }
    string name;
    vector<Pin *> netPins;

    void init()
    {
        netPins.clear();
    }
};

#endif