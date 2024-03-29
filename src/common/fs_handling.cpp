//
// Created by jakhremchik
//

#include "fs_handling.h"
#include <utility>



std::vector<cv::Mat> read_batch(const std::string &imgs_path, int batch_size) {
    std::vector<cv::Mat> batch;
    cv::Mat batch_image;
    batch.push_back(batch_image);

}

cv::Mat fs_img::read_img(const std::string &im_filename, cv::Size &size ) {
    cv::Mat img;
    img = cv::imread(im_filename, cv::IMREAD_COLOR);
    cv::cvtColor(img, img, cv::COLOR_BGR2RGB);

//    tf_aux::fastResizeIfPossible(img, const_cast<cv::Mat *>(&img), size);
    return img;
}

bool path_is_img(std::string &path){
    auto  extension = path.substr(path.find_last_of('.') + 1);
    return extension == "jpg" || extension == "JPG";
}

std::vector<std::string> fs_img::list_imgs(const std::string &dir_path) {
    std::vector<std::string> vector_of_data;
    for (const auto &entry : fs::recursive_directory_iterator(dir_path)) {
        if (fs::is_regular_file(entry) && path_is_img((std::string &) entry.path()))
            vector_of_data.emplace_back(entry.path());
    }
    return vector_of_data;
}

bool DataHandling::open_datafile() {
   imgs_datafile.open(config.datafile_path, std::ios::in | std::ios::app);
   return true;
}

bool DataHandling::open_error_datafile() {
   errors_datafile.open("errors.txt", std::ios::in | std::ios::app); //TODO!!
   return true;
}

bool DataHandling::open_config() {
    config_datafile.open(config_path, std::ios::in | std::ios::app);
    return true;
}

bool DataHandling::load_config() {

    using namespace rapidjson;
    Document doc;
    std::string line;

    open_config();

    if (this->config_datafile.is_open()) {
        std::getline(config_datafile, line);
        doc.Parse(line.c_str());
        if (doc.IsObject()){
            rapidjson::Value &input_size = doc["input_size"];
            rapidjson::Value &datafile_path = doc["datafile_path"];
            rapidjson::Value &img_path = doc["imgs_path"];
            rapidjson::Value &input_node = doc["input_node"];
            rapidjson::Value &output_node = doc["output_node"];
            rapidjson::Value &pb_path = doc["pb_path"];


            config.input_node = input_node.GetString();
            config.output_node = output_node.GetString();
            config.datafile_path = datafile_path.GetString();
            config.imgs_path = img_path.GetString();
            config.pb_path = pb_path.GetString();
            config.input_size.height = input_size.GetArray()[0].GetInt();
            config.input_size.width = input_size.GetArray()[1].GetInt();
            if (doc.HasMember("top_n")) {
               rapidjson::Value &top_n = doc["top_n"];
               config.top_n = top_n.GetInt();
            } else {
               config.top_n = 5;
               std::cerr << "TopN not defined, Using TopN = 5" << std::endl;
            }
            return true;
        } else
            return false;

    } else {
        return false;
    }

//    return true;
}

bool DataHandling::load_database() {
    using namespace rapidjson;
    std::string line;
    Document doc;

    if(!data_vec_base.empty())
        data_vec_base.clear();

    if (imgs_datafile.is_open()) {
        while (std::getline(imgs_datafile, line)) {
            data_vec_entry base_entry;
            doc.Parse(line.c_str());

            rapidjson::Value &img_name = doc["name"];
            rapidjson::Value &img_embedding = doc["embedding"];

            base_entry.filepath = img_name.GetString();
            for (const auto &value : img_embedding.GetArray()) {
                base_entry.embedding.emplace_back(value.GetFloat());
            }
            data_vec_base.emplace_back(base_entry);

        }

    } else {
        open_datafile();
        load_database();
    }
    imgs_datafile.close();
    return true;
}

// Adding images one by one. No batch using.
bool DataHandling::add_json_entry(data_vec_entry new_data) {
    using namespace rapidjson;
    StringBuffer strbuf;
    Writer<StringBuffer> writer(strbuf);

    Document line; // rapidjson doc as line in file
    line.SetObject();
    Value embedding(kArrayType); // for embedding
    Value name(kStringType); // for img path
    Document::AllocatorType& allocator = line.GetAllocator();
    if (imgs_datafile.is_open()) {
        for (const auto &value : new_data.embedding) {
            embedding.PushBack(value, allocator);
        }
        name.SetString(new_data.filepath.c_str(), allocator);

        line.AddMember("name", name, allocator);
        line.AddMember("embedding", embedding, allocator);

        line.Accept(writer);
//        std::cout << "json entry " << strbuf.GetString() << std::endl;
        imgs_datafile << strbuf.GetString() << std::endl;
        imgs_datafile.close();

    }
    else {
        open_datafile();
        add_json_entry(std::move(new_data));

    }
}

bool DataHandling::add_error_entry(const std::string& act_class_in,
                                   const std::string& act_path_in, const std::string& expected_class_in) {
     using namespace rapidjson;
    StringBuffer strbuf;
    Writer<StringBuffer> writer(strbuf);

    Document line; // rapidjson doc as line in file
    line.SetObject();
    // Value embedding(kArrayType); // for embedding
    Value act_class(kStringType); // for img path
    Value act_path(kStringType); // for img path
    Value expected_class(kStringType); // for img path
    Document::AllocatorType& allocator = line.GetAllocator();
    if (!this->errors_datafile.is_open()) {
        this->open_error_datafile();
    }
        // for (const auto &value : new_data.embedding) {
            // embedding.PushBack(value, allocator);
            // }
        act_class.SetString(act_class_in.c_str(), allocator);
        act_path.SetString(act_path_in.c_str(), allocator);
        expected_class.SetString(expected_class_in.c_str(), allocator);

        line.AddMember("actual_path", act_path, allocator);
        line.AddMember("actual_class", act_class, allocator);
        line.AddMember("expected_class", expected_class, allocator);

        line.Accept(writer);
        // std::cout << "json entry " << strbuf.GetString() << std::endl;
        this->errors_datafile << strbuf.GetString() << std::endl;
        this->errors_datafile.close();

}