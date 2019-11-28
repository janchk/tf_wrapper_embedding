//
// Created by jakhremchik on 08.11.2019.
//

#include "common_ops.h"

std::string common_ops::extract_class(const std::string &filepath) {
   std::string spilt_delim = "/"; //TODO another delimiter for windows
   std::string token;
   std::string train_identifier = "series/";
   std::string test_identifier = "queries/";
   std::string classname_delim = "__";
   size_t pos_end;

   if (!filepath.empty()) {
       size_t pos_begin = filepath.find(test_identifier);
       if (std::string::npos == pos_begin) { // if not test directory
           pos_begin = filepath.find(train_identifier) + train_identifier.size(); // find train directory identifier
           token = filepath.substr(pos_begin, std::string::npos);
           pos_end = token.find(spilt_delim);

           token = token.substr(0, pos_end);

           pos_end = token.find(classname_delim);
           if (std::string::npos != pos_end) {
               token = token.substr(0, pos_end);
           }


       } else { //we assume that we are in test directory
           pos_begin = filepath.find(test_identifier) + test_identifier.size();
           token = filepath.substr(pos_begin, std::string::npos);
           pos_end = token.find(spilt_delim);

           token = token.substr(0, pos_end);

           pos_end = token.find(classname_delim);
           if (std::string::npos != pos_end) {
               token = token.substr(0, pos_end);
           }
       }
   }
   else
       throw std::invalid_argument("Path is empty!");



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

void common_ops::check_end_slash(std::string &path) {
    if (path[path.size() - 1] == '/')
        path.pop_back();
}

std::string common_ops::extract_class(const std::string &path_to_img, std::string &series_path, std::string &queries_path) {
    size_t class_pos = 0;
    check_end_slash(series_path);
    check_end_slash(queries_path);
    size_t in_queries_pos = path_to_img.find(queries_path);
    size_t in_imgs_pos = path_to_img.find(series_path);

    if (in_queries_pos == std::string::npos)
        class_pos = in_imgs_pos + series_path.size() + 1;
    else
        class_pos = in_queries_pos + queries_path.size() + 1;

    std::string relative_img_path = path_to_img.substr(class_pos, std::string::npos);
    std::string classname = split(relative_img_path, "/")[0];
    classname = split(classname, "__")[0];
    return classname;
}
