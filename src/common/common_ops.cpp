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
	   pos_end = filepath.rfind(underscore_delim);
   }

   std::string token = filepath.substr(0, pos_end);

   size_t pos_begin = token.rfind(slash_delim);

   token = token.substr(pos_begin + 1, std::string::npos);
   return token;
}

std::vector<std::string> common_ops::split(const std::string &text, const std::string &delim) {
    std::vector<std::string> results;
    for (auto p = cbegin(text); p != cend(text); ) {
        const auto n = search(p, cend(text), cbegin(delim), cend(delim));
        results.emplace_back(p, n);
        p = n;
        if (cend(text) != n) // we found delim, skip over it.
            p += delim.length();
    }
    return results;
}

std::string common_ops::extract_class_depth_based(const std::string &filepath) {
    std::vector<std::string> tokens = split(filepath, "/");
    std::string classname = tokens[tokens.size() - 3];
    return split(classname, "__")[0];
}
