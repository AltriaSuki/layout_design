#include "file_reader.hpp"

void FileReader::read_nets(std::filesystem::path nets_path){
    std::ifstream infile(nets_path);
    if(!infile.is_open()){
        throw std::runtime_error("Could not open file: " + nets_path.filename().string());
    }
    std::string line;
    while(std::getline(infile,line)){
        std::istringstream iss(line);
        std::string token;
        if(line.find("NumPins") != std::string::npos){

        }else if(line.find("NumNets")!= std::string::npos){
            iss >> token;
            pdata->netCount = std::stoi(token);
            pdata->Nets.resize(pdata->netCount);
        }else if(line.find("NetDegree")!= std::string::npos){

        }
    }

}