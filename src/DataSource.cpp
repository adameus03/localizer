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

double* DataSource::GetData(ull& num_samples){
    std::ifstream f_in(this->path, std::ifstream::binary);
    std::filebuf* f_in_pbuf = f_in.rdbuf();
    size_t sbuff_size = f_in_pbuf->pubseekoff(0, f_in.end, f_in.in);
    f_in_pbuf->pubseekpos(0, f_in.in);
    double* buffer = new double[sbuff_size>>0x3];
    f_in_pbuf->sgetn(reinterpret_cast<char*>(buffer), sbuff_size);
    f_in.close();
    return buffer;
}
