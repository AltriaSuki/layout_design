#ifndef FILEREADER_HPP
#define FILEREADER_HPP
#include "myplace.hpp"
#include "placedata.hpp"
#include <charconv>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <thread>

#define NUM_LINES 100000

class FileReader {
public:
  /**
   * @brief Construct a new File Reader object
   *
   * @param filepath 需要读取的文件夹
   * @return none
   *
   */
  FileReader(const std::string &filepath) {
    std::filesystem::path path(filepath);
    std::string dir_name = path.filename().string();
    std::filesystem::path aux_path = path / (dir_name + ".aux");
    std::filesystem::path nets_path = path / (dir_name + ".nets");
    std::filesystem::path nodes_path = path / (dir_name + ".nodes");
    std::filesystem::path pl_path = path / (dir_name + ".pl");
    std::filesystem::path scl_path = path / (dir_name + ".scl");
    std::filesystem::path wts_path = path / (dir_name + ".wts");
    pdata = make_shared<PlaceData>();
    std::vector<std::thread> threads;
    
    // read_aux(aux_path);
    read_pl(pl_path);
    read_nets(nets_path);
    // read_nodes(nodes_path);
    
    // read_scl(scl_path);
    // read_wts(wts_path);
    myplace = make_shared<MyPlacer>(pdata.get());
  }

  void print() {
    std::cout<<pdata->pinCount<<" "<<pdata->Pins.size();
    std::cout << pdata->max_net_degree;
  }

private:
  void read_aux(const std::filesystem::path &aux_path);
  void read_nets(const std::filesystem::path &nets_path);
  void read_nodes(const std::filesystem::path &nodes_path);
  void read_pl(const std::filesystem::path &pl_path);
  void read_scl(const std::filesystem::path &scl_path);
  void read_wts(const std::filesystem::path &wts_path);

  void process_net(const std::string &sv);

  std::vector<std::string> splist_by_space(std::string &line);

  // PlaceData* pdata;
  // MyPlacer* myplace;

  shared_ptr<PlaceData> pdata;
  shared_ptr<MyPlacer> myplace;
};

struct Orientation {
  static constexpr float N = 0;
  static constexpr float E = 90;
  static constexpr float S = 180;
  static constexpr float W = 270;
  // to be confirmed
  static constexpr float FS = 0;
};

#endif