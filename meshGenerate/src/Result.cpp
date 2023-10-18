#include <iostream>
#include <fstream>
#include <assert.h>

#include "Result.h"

void Result::Read_Value(std::fstream &file, std::string name) {
    char buffer[1024] = "";
    file >> buffer;

    m_Data[name] = std::vector<float>(m_Size);
    for (size_t i = 0; i < m_Size; i++)
    {
        float value= 0;
        file >> buffer;
        //file >> value;
        m_Data[name][i] = atof(buffer);
    }

}

void Result::Load(std::string fileDir)
{
    std::fstream file;
    file.open(fileDir, std::ios::in);
    if (file.is_open() == 0)
    {
        std::cout << "FileName : [" << fileDir << "]is not open!" << std::endl;
		assert(0);
    }

    char buffer[1024] = "";
    while (file >> buffer)
    {
        std::string name(buffer);
        if(name == "vonmises")
        {
            Read_Value(file, name);
        }
    }
    file.close();
}

std::vector<float> Result::Get_Data(std::string name)
{
    return m_Data[name];
}

