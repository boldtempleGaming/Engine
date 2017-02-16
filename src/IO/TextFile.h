#ifndef TEXTFILE_H
#define TEXTFILE_H

#include <IO/File.h>

class TextFile : public File
{
public:
    TextFile();
    TextFile(std::string file);

    std::string Read();
    bool Write(const std::string& data);
};

#endif // TEXTFILE_H
