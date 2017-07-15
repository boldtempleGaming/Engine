#include "File.h"

#ifdef USE_PHYSFS

File::File(){
}

File::~File(){
}

File::File(const std::string& file, bool trunc){
    Open(file, trunc);
}

bool File::Open(const std::string& file, bool trunc){
    _s_file = file;

    if(!OpenReadStream(true)){
        //Try open in write dir
        return OpenWriteStream(trunc);
    }

    return true;
}

void File::Close(){
    //Close write stream
    if(_out_file != nullptr){
        _out_file.reset();
    }

    //Close read stream
    if(_in_file != nullptr){
        _in_file.reset();
    }
}

bool File::Read(std::vector<char> &data) const{
    size_t size = GetSize();

    if(size == 0){
        return false;
    }

    data.resize(size);

    return Read(&data[0], size);
}

bool File::Read(char* data, size_t length) const{
    bool success = false;

    if(OpenReadStream()){
        if(*_in_file){
            _in_file->read(data, length);

            if(!*_in_file){
                std::cerr << " >> !ERROR! << Couldn't read file: " <<  _s_file << std::endl;
            }else{
                success = true;
            }

            _in_file.reset();
        }else{
             std::cerr << " >> !ERROR! << Couldn't open file: " <<  _s_file << std::endl;
        }
    }

    _can_read = false;

    return success;
}

bool File::Write(const std::vector<char>& data, bool append, bool create_ifn_exists){
    if(OpenWriteStream(append)){
        return Write(&data[0], data.size());
    }
    return false;
}

bool File::Write(const char* data, size_t length, bool append, bool create_ifn_exists){
    bool success = false;

    if(OpenWriteStream(append)){
        if(*_out_file){
            _out_file->write(data, length);
            success = true;
            _out_file.reset();
        }else{
            std::cerr << " >> !ERROR! << Couldn't write to file: " <<  _s_file << std::endl;
        }
    }

    _can_write = false;
    return success;
}

bool File::IsOpen() const{
    return PhysFS::exists(_s_file);
}

size_t File::GetSize() const{
//PHYSFS_sint64 PHYSFS_fileLength 	( 	PHYSFS_File *  	handle 	 )
//Note that if the file size can't be determined (since the archive is "streamed" or whatnot)
//than this will report (-1).
//Also note that if another process/thread is writing to this file at the same time,
//then the information this function supplies could be incorrect before you get it.
//Use with caution, or better yet, don't use at all.

    OpenReadStream();

    if(_in_file != nullptr){
        return _in_file->length();
    }
    else if(_out_file != nullptr){
        return _out_file->length();
    }else{
        return 0;
    }
}

bool File::OpenReadStream(bool silent) const{
    if(_can_read){
        return true;
    }

    //Close write stream
    if(_out_file != nullptr){
        _out_file.reset();
    }

    if(_in_file == nullptr){
        try{
            _in_file.reset(new PhysFS::ifstream(_s_file));
            _can_read = true;
        }
        catch(const std::logic_error& ex){
            if(!silent) {
                std::cerr << " >> !ERROR! << " << ex.what() << std::endl;
            }
            return false;
        }
    }

    return true;
}

bool File::OpenWriteStream(bool append, bool silent) const{
    if(_can_write){
        return true;
    }

    //Close read stream
    if(_in_file != nullptr){
        _in_file.reset();
    }

    if(_out_file == nullptr){
        try{
            //Trunc write dir path
            std::string write_dir = PhysFS::getWriteDir();
            std::string path;

            std::cout << write_dir << std::endl;

            if(_s_file.find(write_dir) != -1){
                path = _s_file.substr(write_dir.size(),  std::string::npos);
            }else{
                path = _s_file;
            }

            if(append){
                _out_file.reset(new PhysFS::ofstream(path, PhysFS::APPEND));
            }else{
                _out_file.reset(new PhysFS::ofstream(path));
            }

            _can_write = true;
        }
        catch(std::logic_error ex){
            if(!silent) {
                std::cerr << " >> !ERROR! << " << ex.what() << std::endl;
            }

            _can_write = false;
            return false;
        }
    }

    return true;
}

#else

File::File(){
    _s_file = "";
}

File::File(const std::string& file, bool trunc){
    Open(file, trunc);
}

File::~File(){
    Close();
}

bool File::Open(const std::string& file, bool trunc){
    _s_file = file;

    Close();

    if(trunc){
        _file.open(_s_file,  std::fstream::in
                   | std::fstream::out
                   | std::fstream::binary
                   | std::fstream::trunc);
    }else{
        _file.open(_s_file,  std::fstream::in
                   | std::fstream::out
                   | std::fstream::binary);
    }

    return IsOpen();
}

void File::Close(){
    if(_file.is_open()){
        _file.close();
    }
}

bool File::Read(std::vector<char> &data) const{
    size_t file_length = GetSize();

    data.reserve(file_length);
    data.resize(file_length);

    return Read(&data[0], file_length);
}

bool File::Read(char* data, size_t length) const{
    if(IsOpen() && _file.good()){
        _file.read(data, length);
        _file.seekg(0, std::ios::beg);
        return !_file.fail();
    }

    return false;
}

bool File::Write(const std::vector<char>& data, bool append, bool create_ifn_exists){
    return Write(&data[0], data.size(), append, create_ifn_exists);
}

bool File::Write(const char* data, size_t length, bool append, bool create_ifn_exists){

    //try to create file
    if((!IsOpen() || !_file.good()) && create_ifn_exists){
        Open(_s_file, true);
    }

    if(IsOpen() && _file.good()){
        if(append){
            _file.seekp(0, std::ios::end);
        }

        _file.write(data, length);
        _file.flush();

        _file.seekp(0, std::ios::beg);

        return !_file.fail();
    }

    return false;
}

bool File::IsOpen() const{
    return _file.is_open();
}

size_t File::GetSize() const{
    std::ifstream in(_s_file, std::ios::binary | std::ios::ate);
    return (in.good() ? static_cast<size_t>(in.tellg()) : 0);
}

#endif
