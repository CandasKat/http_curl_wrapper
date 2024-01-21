//
// Created by candas on 1/21/24.
//

#ifndef HTTP_CURL_WRAPPER_CURLCOOKIES_H
#define HTTP_CURL_WRAPPER_CURLCOOKIES_H


#include <string>
#include <map>
#include "../lib/json-develop/single_include/nlohmann/json.hpp"
using json = nlohmann::json;

class CurlCookies {
public:
    CurlCookies();
    ~CurlCookies();
    void setCookie(const std::string& key, const std::string& value);
    json getCookies();

private:
    json cookies;
};


#endif //HTTP_CURL_WRAPPER_CURLCOOKIES_H
