//
// Created by candas on 1/21/24.
//

#include "CurlSession.h"

CurlSession::CurlSession()
{
    curl = curl_easy_init();
    if (!curl)
    {
        throw CurlException("Failed to initialize curl");
    }
}

CurlSession::~CurlSession()
{
    curl_easy_cleanup(curl);
}

void CurlSession::setSessionId(const std::string& newSessionId)
{
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
