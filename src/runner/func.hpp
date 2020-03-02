#pragma once

#include <string>
#include <sys/stat.h>

long get_filesize(const std::string & file) {
    struct stat stat_buf;
    int rc = stat(file.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}