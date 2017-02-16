#include "TextFile.h"

TextFile::TextFile(){}
TextFile::TextFile(std::string file): File(file){}

std::string TextFile::Read(){
    std::string data;
    size_t size = File::GetSize();

    data.resize(size);
    File::Read(&data[0], size);

    return data;
}
