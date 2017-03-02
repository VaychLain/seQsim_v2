#include <string>
#include <stdio.h>
#include <string.h>
#include <openssl/md5.h>
#include "helps.h"

std::string md5_func(const char* str) {
	std::string ret_str("");
	char buf[40] = {0};
	MD5_CTX md5_ctx;
	unsigned char md5_data[16];
	
	if(str == NULL)
		return ret_str;
		
	MD5_Init(&md5_ctx);
	MD5_Update(&md5_ctx, str, strlen(str));
	MD5_Final(md5_data, &md5_ctx);
	
	for (int i=0; i < 16; i++) {
		sprintf(buf + i*2, "%02x", md5_data[i]);
	}
	buf[32] = 0;
	
	ret_str = std::string(buf);
	return ret_str;
}

int split_string(const std::string& str, std::vector<std::string>& ret_, std::string sep = ",")
{
    if (str.empty())
    {
        return 0;
    }

    std::string tmp;
    std::string::size_type pos_begin = str.find_first_not_of(sep);
    std::string::size_type comma_pos = 0;

    while (pos_begin != std::string::npos)
    {
        comma_pos = str.find(sep, pos_begin);
        if (comma_pos != std::string::npos)
        {
            tmp = str.substr(pos_begin, comma_pos - pos_begin);
            pos_begin = comma_pos + sep.length();
        }
        else
        {
            tmp = str.substr(pos_begin);
            pos_begin = comma_pos;
        }

        if (!tmp.empty())
        {
            ret_.push_back(tmp);
            tmp.clear();
        }
    }
    return 0;
}