#ifndef HELPS_H
#define HELPS_H

#include <string>
#include<vector>

std::string md5_func(const char*);

int split_string(const std::string& str, std::vector<std::string>& ret_, std::string sep);

#endif