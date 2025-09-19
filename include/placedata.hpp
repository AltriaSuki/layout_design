#ifndef PLACEDATA_H
#define PLACEDATA_H
#include "objects.hpp"
#include <unordered_map>
class PlaceData {
public:
  int moduleCount;
  int MacroCount;
  int netCount;
  int pinCount;

  size_t max_net_degree{0};

  // vector<Module *> Nodes;
  // vector<Module *> Terminals;
  // vector<Pin *> Pins;
  // vector<Net *> Nets;
  vector<shared_ptr<Module>> Nodes;
  vector<shared_ptr<Module>> Terminals;
  vector<shared_ptr<Pin>> Pins;
  vector<shared_ptr<Net>> Nets;
  vector<SiteRow> SiteRows;

  unordered_map<string, shared_ptr<Module>> moduleMap;
  shared_ptr<Module> getModuleByName(const string &name) {
    if (moduleMap.find(name) != moduleMap.end()) {
      return moduleMap[name];
    }
    return nullptr;
  }
};
#endif