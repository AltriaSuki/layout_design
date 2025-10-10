#ifndef PLACEDATA_H
#define PLACEDATA_H
#include "objects.hpp"
#include <unordered_map>
#include <map>
class PlaceData {
public:
  int moduleCount;
  int MacroCount;
  int netCount;
  int pinCount;

  int numRows;
  size_t max_net_degree{0};
  std::map<int, int> pin_num;

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


  //task 4
  //计算空白面积 = 布局行 SiteRow 区域面积- （标准单元面积 + 宏块面积）
  double empty_area;
  //计算总填充面积 = 空白面积* targetDensity - （标准单元面积 + 宏块面积* targetDensity）
  double total_area;

  //targetDensity 为设定的目标密度
  double target_density;
  //（2）设定填充节点高 = 常规高度，其中常规高度是读取*.scl 文件中读取。
  double setting_height;
  //（3）计算填充节点宽 = 填充节点面积/填充节点高
  double setting_width;
  //（4）计算填充节点的个数 = 总填充面积 / 填充节点面积
  double padding_num;
  //计算填充节点面积：将所有节点按面积从大到小排序，去掉前后 5%，将
  // 剩下的 90%的节点面积求平均，得到填充节点面积。
  double calculate_padding_area();
  //计算节点面积 = 标准单元面积 + 宏块面积
  double node_area;
};
#endif