//
// Created by jakhremchik on 08.11.2019.
//

#include "common_ops.h"

std::string common_ops::extract_class(const std::string &filepath) {
   std::string slash_delim = "/"; //TODO another delimiter for windows
   std::string underscore_delim = "__";
   size_t pos_end = filepath.find(underscore_delim);
   if (pos_end == std::string::npos) {
	   underscore_delim = "/";
	   pose_end = filepath.rfind(underscore_delim);
   }

   std::string token = filepath.substr(0, pos_end);

   size_t pos_begin = token.rfind(slash_delim);

   token = token.substr(pos_begin + 1, std::string::npos);
   return token;
}


