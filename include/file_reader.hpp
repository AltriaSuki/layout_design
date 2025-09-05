#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include "placedata.hpp"
#include "myplace.hpp"

class FileReader{
    public:
        /**
         * @brief Construct a new File Reader object
         * 
         * @param filepath 需要读取的文件夹
         * @return none
         * 
         */
        FileReader(const std::string& filepath){
            std::filesystem::path path(filepath);
            std::string dir_name = path.filename().string();
            std::filesystem::path aux_path = path / (dir_name + ".aux");
            std::filesystem::path nets_path = path / (dir_name + ".nets");
            std::filesystem::path nodes_path = path / (dir_name + ".nodes");
            std::filesystem::path pl_path = path / (dir_name + ".pl");
            std::filesystem::path scl_path = path / (dir_name + ".scl");
            std::filesystem::path wts_path = path / (dir_name + ".wts");



        }

    private:
    void read_aux(std::filesystem::path aux_path);
    void read_nets(std::filesystem::path nets_path);
    void read_nodes(std::filesystem::path nodes_path);
    void read_pl(std::filesystem::path pl_path);
    void read_scl(std::filesystem::path scl_path);
    void read_wts(std::filesystem::path wts_path);

    PlaceData* pdata;
    MyPlacer* myplace;

    

    
};