#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <fstream>
#include <iostream> //debug
//#include <windows.h> // big file size :(((

typedef unsigned long long ull;

class DataSource
{
    public:
        DataSource(const char* path);
        virtual ~DataSource();
        double* GetData(ull& num_samples);

    protected:

    private:
        char* path;
};

#endif // DATASOURCE_H
