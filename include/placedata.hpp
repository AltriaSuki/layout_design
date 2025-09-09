#ifndef PLACEDATA_H
#define PLACEDATA_H
#include "objects.hpp"

class PlaceData
{
public:
    int moduleCount; 
    int MacroCount;
    int netCount;
    int pinCount;

    vector<Module *> Nodes; 
    vector<Module *> Terminals;
    vector<Pin *> Pins;
    vector<Net *> Nets;
    vector<SiteRow> SiteRows;

    map<string, Module *> moduleMap; 
    Module* getModuleByName(const string &name){
        if(moduleMap.find(name) != moduleMap.end()){
            return moduleMap[name];
        }
        return nullptr;
    }
};
#endif