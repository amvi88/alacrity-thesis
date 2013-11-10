#ifndef IOUTILS_H
#define IOUTILS_H


#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdexcept>
#include <string.h>
#include <errno.h>

using namespace std;

class IOUtils
{
    public:
        static bool DirectoryExists(string path);
        static bool FileExists(string filepath);
        static bool FileExistsAndNotEmpty(string filepath);
        static void ValidateFileStatus(string filename);
    protected:
    private:
};

#endif // IOUTILS_H
