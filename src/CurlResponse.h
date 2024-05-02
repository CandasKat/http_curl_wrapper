//
// Created by candas on 1/19/24.
//

#ifndef HTTP_CURL_WRAPPER_CURLRESPONSE_H
#define HTTP_CURL_WRAPPER_CURLRESPONSE_H

#include "cstdio"
#include <string>
#include "../lib/json-develop/single_include/nlohmann/json.hpp"
using json = nlohmann::json;

class CurlResponse {
public:
    CurlResponse(int status, const std::string& headers, std::string body);
    ~CurlResponse() = default;
    [[nodiscard]] int getStatus() const;
    json getHeaders();
    const std::string &getHeadersString();
    const std::string &getBody();
    static std::string setHeadersToParse(const std::string& headersToParse);

    private:
    int status;
    std::string headersToParse;
    std::string body;
    std::string headers;
};


#endif //HTTP_CURL_WRAPPER_CURLRESPONSE_H
