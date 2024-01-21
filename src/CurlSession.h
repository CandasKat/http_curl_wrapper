//
// Created by candas on 1/21/24.
//

#ifndef HTTP_CURL_WRAPPER_CURLSESSION_H
#define HTTP_CURL_WRAPPER_CURLSESSION_H

#include <cstdio>
#include <curl/curl.h>
#include <string>
#include "CurlResponse.h"
#include "CurlException.h"
#include "CurlCookies.h"

class CurlSession {
public:
    CurlSession();
    ~CurlSession();

    void setSessionId(const std::string& sessionId);
    std::string getSessionId();
    CURL *getCurl();

private:
    CURL *curl;
    CurlCookies cookies;
    std::string sessionId;

};


#endif //HTTP_CURL_WRAPPER_CURLSESSION_H
