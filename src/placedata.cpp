#include "placedata.hpp"
#include <algorithm>
#include <cstddef>
#include <random>
#include <string>
#include<vector>
double PlaceData::calculate_padding_area() {
  // 计算填充节点面积
  std::vector<double> areas;
  for (const auto &module : Nodes) {
    areas.push_back(module->area);
  }
  // 从大到小排序
  std::sort(areas.begin(), areas.end(), std::greater<double>());
  size_t total_modules = areas.size();
  if(total_modules < 20){
    double sum_area = 0.0;
    for(const auto &area: areas){
        sum_area += area;
    }
    return sum_area / total_modules;
  }
  size_t off_num = static_cast<size_t>(total_modules * 0.05);
  size_t start_index = off_num;
  size_t end_index = total_modules - off_num;
  double sum_area = 0.0;
  for (size_t i = start_index; i < end_index; ++i) {
    sum_area += areas[i];
  }

  return sum_area / (end_index - start_index);
}

void PlaceData::calculate_padding_parameters() {
  // （2）设定填充节点高 = 常规高度，其中常规高度是读取*.scl 文件中读取。
  // （3）计算填充节点宽 = 填充节点面积/填充节点高
  // （4）计算填充节点的个数 = 总填充面积 / 填充节点面积

  double padding_area = calculate_padding_area();

  setting_width = padding_area / setting_height;
  padding_num = static_cast<size_t>(total_area / padding_area);
}

void PlaceData::create_padding_nodes() {
    padding_nodes.reserve(padding_num);
    double padding_area = calculate_padding_area();
    const auto& random_gen = gen();
    for(size_t i = 0; i < padding_num;++i){
        auto pad_node = std::make_unique<Module>();
        pad_node->idx = i;// 填充节点索引,与原有节点区分开
        pad_node->name = "padding_node_" + std::to_string(i);
        pad_node->width = setting_width;
        pad_node->height = setting_height;
        pad_node->area = padding_area;
        pad_node->isFiller = true;
        // 设定随机位置，假设布局区域为 (0,0) 到
        pad_node->center = random_position(random_gen);
        padding_nodes.push_back(std::move(pad_node));
    }
}

POS_2D PlaceData::random_position(const std::mt19937 &gen) {
    size_t row_num = SiteRows.size();
    std::uniform_int_distribution<> row_dist(0, row_num - 1);
    size_t row_index = row_dist(gen);
    const auto &row = SiteRows[row_index];
    //module 中的 center是中心点
    double left_x = row.start.x;
    double right_x = row.end.x;
    double bottom_y = row.bottom;
    double top_y = row.bottom + row.height;
    //生成随机的边缘坐标
    //通过加宽度和高度的一般,来生成中心点坐标
    std::uniform_real_distribution<> x_dist(left_x, right_x - setting_width);
    std::uniform_real_distribution<> y_dist(bottom_y, top_y - setting_height);
    double rand_x = x_dist(gen) + setting_width / 2.0;
    double rand_y = y_dist(gen) + setting_height / 2.0;
    //这样做就不用std::move了,因为返回值优化
    return {rand_x, rand_y};
}