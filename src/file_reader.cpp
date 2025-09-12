#include "file_reader.hpp"
#pragma message("Compiling file_reader.cpp")

void FileReader::read_nets(const std::filesystem::path &nets_path) {
  std::ifstream infile(nets_path);
  if (!infile.is_open()) {
    throw std::runtime_error("Could not open file: " +
                             nets_path.filename().string());
  }
  std::string line;
  while (std::getline(infile, line)) {
    std::istringstream iss(line);
    std::string token;
    if (line.find("NumPins") != std::string::npos) {

    } else if (line.find("NumNets") != std::string::npos) {
      iss >> token;
      iss >> token;
      iss >> token;
      pdata->netCount = std::stoi(token);
    } else if (line.find("NetDegree") != std::string::npos) {
      iss >> token;
      iss >> token;
      iss >> token;
      unsigned int num_pins = std::stoi(token);
      string net_name;
      iss >> net_name;
      auto net = std::make_shared<Net>(net_name);
      for (unsigned int i = 0; i < num_pins; i++) {
        std::getline(infile, line);
        std::istringstream pin_iss(line);
        string pin_name, module_name;
        pin_iss >> module_name;
        pin_iss >> pin_name;
        pin_iss >> token; // skip :
        float x_offset, y_offset;
        pin_iss >> token;
        x_offset = std::stof(token);
        pin_iss >> token;
        y_offset = std::stof(token);
        auto mod = pdata->getModuleByName(module_name);
        if (mod == nullptr) {
          // throw std::runtime_error("Module " + module_name + " not found in
          // moduleMap");
        } else {
        }
        auto pin = std::make_shared<Pin>();
        if (pin_name == "I") {
          pin->idx = 0;
        } else if (pin_name == "O") {
          pin->idx = 1;
        } else if (pin_name == "B") {
          pin->idx = 2;
        }
        pin->module = mod;
        pin->offset = POS_2D(x_offset, y_offset);
        pin->net = net;
        // mod->modulePins.push_back(pin);
        // mod->nets.push_back(net);leave it undone until other files have been
        // read
        net->netPins.push_back(pin);
        pdata->Pins.push_back(pin);
      }
      pdata->Nets.push_back(net);
    }
  }
}