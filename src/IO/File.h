#ifndef FILE_H
#define FILE_H

#include <cstddef>
#include <cstring>
#include <vector>

//#define USE_PHYSFS

#include <iostream>

#ifdef USE_PHYSFS
#include <memory>
#include <physfs.hpp>
#else
#include <fstream>
#endif

class File
{
public:
    File();
    File(const std::string& file, bool trunc = false);
    ~File();

    bool Open(const std::string& file, bool trunc = false);
    void Close();

    bool Read(std::vector<char>& data) const;
    bool Read(char* data, size_t length) const;

    bool Write(const std::vector<char>& data, bool append = false, bool create_ifn_exists = false);
    bool Write(const char* data, size_t length, bool append = false, bool create_ifn_exists = false);

    bool IsOpen() const;
    size_t GetSize() const;

private:
    std::string _s_file;

#ifdef USE_PHYSFS
    mutable std::unique_ptr<PhysFS::ifstream> _in_file;
    mutable std::unique_ptr<PhysFS::ofstream> _out_file;

    mutable bool _can_read = false;
    mutable bool _can_write = false;

    bool OpenWriteStream(bool append, bool silent = false) const;
    bool OpenReadStream(bool silent = false) const;
#else
    mutable std::fstream _file;
#endif
};

#endif // FILE_H
