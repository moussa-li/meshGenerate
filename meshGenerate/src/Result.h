#pragma once

#include <unordered_map>
#include <vector>

class Result
{
    std::unordered_map<std::string,std::vector<float>> m_Data;

    size_t m_Size;

private:
    void Read_Value(std::fstream &file, std::string name);
    

public:
    Result(int size) 
        :m_Size(size)
    {}

    void Load(std::string fileDir);
    std::vector<float> Get_Data(std::string name);
};
