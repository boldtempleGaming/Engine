#ifndef TEXTFILE_H
#define TEXTFILE_H

#include "IO/File.h"

class TextFile : public File
{
public:
    TextFile();
    TextFile(const std::string& file, bool trunc = false);

    std::string Read();
    bool Write(const std::string& data, bool append = false);
};

#endif // TEXTFILE_H
