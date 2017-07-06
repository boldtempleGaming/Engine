#include "TextFile.h"

TextFile::TextFile(){}
TextFile::TextFile(const std::string &file, bool trunc): File(file, trunc){}

std::string TextFile::Read(){
    std::string data;
    size_t size = File::GetSize();

    data.resize(size);
    File::Read(&data[0], size);

    return data;
}

bool TextFile::Write(const std::string &data, bool append)
{
    return File::Write(data.c_str(), data.length(), append);
}
