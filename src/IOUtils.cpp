#include "IOUtils.hxx"

bool IOUtils::DirectoryExists(string path){
    struct stat dirStatus;
    return (stat(path.c_str(), &dirStatus) == 0) && (dirStatus.st_mode & S_IFDIR);

};
bool IOUtils::FileExists(string filepath){
    struct stat fileStatus;
    return (stat(filepath.c_str(), &fileStatus) == 0) && ( fileStatus.st_mode & S_IFREG );
};

bool IOUtils::FileExistsAndNotEmpty(string filepath){
    struct stat fileStatus;
    return (stat(filepath.c_str(), &fileStatus) == 0) && ( fileStatus.st_mode & S_IFREG ) && (fileStatus.st_size > 0);
};


void IOUtils::ValidateFileStatus(string filename){
    struct stat fileStatus;
    errno = 0;
    if(stat(filename.c_str(), &fileStatus) == -1) // ==0 ok; ==-1 error
    {
        if( errno == ENOENT )      // errno declared by include file errno.h
            throw ( std::runtime_error("Path file_name does not exist, or path is an empty string.") );
        else if( errno == ENOTDIR )
            throw ( std::runtime_error("A component of the path is not a directory."));
        else if( errno == ELOOP )
            throw ( std::runtime_error("Too many symbolic links encountered while traversing the path."));
        else if( errno == EACCES )
            throw ( std::runtime_error("Permission denied."));
        else if( errno == ENAMETOOLONG )
            throw ( std::runtime_error("File can not be read\n"));
    }
}
