//
// Created by candas on 1/19/24.
//

#ifndef HTTP_CURL_WRAPPER_CURLREQUEST_H
#define HTTP_CURL_WRAPPER_CURLREQUEST_H


#include <cstdio>
#include <curl/curl.h>
#include <string>
#include "CurlResponse.h"
#include "CurlException.h"
#include "CurlCookies.h"

class CurlRequest {
public:
    CurlRequest(std::string url, std::string header, const CurlCookies& cookies, std::string body, int timeout);
    ~CurlRequest();
    void setUrl(std::string newUrl);
    void setHeader(std::string newHeader);
    void setBody(std::string newBody);
    void setBody(std::string newBody, size_t size);
    void setTimeout(int newTimeout);
    void setCookies(const CurlCookies& cookies);

    std::unique_ptr<CurlResponse> sendGet();
    std::unique_ptr<CurlResponse> sendPost();
    std::unique_ptr<CurlResponse> sendPut();
    std::unique_ptr<CurlResponse> sendDelete();
    std::unique_ptr<CurlResponse> sendHead();
    std::unique_ptr<CurlResponse> sendOptions();
    std::unique_ptr<CurlResponse> sendPatch();

private:
    CURL *curl;
    std::string url;
    std::string method;
    std::string header;
    std::string body;
    CurlCookies cookies;
    int timeout;
    static size_t WriteCallBack(void *contents, size_t size, size_t nmemb, void *userp);

};


#endif //HTTP_CURL_WRAPPER_CURLREQUEST_H
