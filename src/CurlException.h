//
// Created by candas on 1/20/24.
//

#ifndef HTTP_CURL_WRAPPER_CURLEXCEPTION_H
#define HTTP_CURL_WRAPPER_CURLEXCEPTION_H


#include <string>

class CurlException : public std::exception {
public:
    explicit CurlException(const std::string& message);
    [[nodiscard]] const std::string& getMessage() const noexcept;

private:
    std::string message;
};


#endif //HTTP_CURL_WRAPPER_CURLEXCEPTION_H
