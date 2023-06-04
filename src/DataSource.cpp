#include "DataSource.h"

DataSource::DataSource(const char* path)
{
    //ctor
    this->path = (char*)path;
}

DataSource::~DataSource()
{
    //dtor
}

/*unsigned long long GetFileSize(const char* path) {
    HANDLE fileHandle = CreateFile(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (fileHandle == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to open the file." << std::endl;
        return 0;
    }

    LARGE_INTEGER fileSize;
    if (GetFileSizeEx(fileHandle, &fileSize) == 0) {
        std::cerr << "Failed to get file size." << std::endl;
        CloseHandle(fileHandle);
        return 0;
    }

    CloseHandle(fileHandle);
    return static_cast<unsigned long long>(fileSize.QuadPart);
}*/

double* DataSource::GetData(ull& num_samples){

std::ifstream f_in(this->path, std::ifstream::binary);
    std::filebuf* f_in_pbuf = f_in.rdbuf();
    size_t sbuff_size = f_in_pbuf->pubseekoff(0, f_in.end, f_in.in);
    f_in_pbuf->pubseekpos(0, f_in.in);

    //f_in.seekg(0, f_in.end);
    //size_t sbuff_size = f_in.tellg();
    //f_in.seekg(0, f_in.beg);

    //ull sbuff_size = GetFileSize(this->path);

    //std::cout << (sbuff_size>>3) << std::endl;

    double* buffer = new double[sbuff_size>>0x3];
    f_in_pbuf->sgetn(reinterpret_cast<char*>(buffer), sbuff_size);
    f_in.close();
    num_samples = (sbuff_size>>4);
    return buffer;
}
