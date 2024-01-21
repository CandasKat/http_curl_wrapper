//
// Created by candas on 1/21/24.
//

#include "CurlSession.h"

CurlSession::CurlSession()
{
    curl = curl_easy_init();
    if (!curl)
    {
        throw CurlException("Failed to initialize curl: " + std::string(curl_easy_strerror(curl_easy_getinfo(curl, CURLINFO_OS_ERRNO, NULL))));
    }
}

CurlSession::~CurlSession()
{
    curl_easy_cleanup(curl);
}

void CurlSession::setSessionId(const std::string& newSessionId)
{
    if (newSessionId.empty()) {
        throw std::invalid_argument("Session ID cannot be empty");
    }
    this->sessionId = newSessionId;
    cookies.setCookie("SessionId", sessionId);
}

std::string CurlSession::getSessionId()
{
    return sessionId;
}

CURL *CurlSession::getCurl()
{
    return curl;
}
