//
// Created by candas on 1/21/24.
//

#include "CurlCookies.h"

CurlCookies::CurlCookies()
{
    cookies = json::object();
}

CurlCookies::~CurlCookies()
{
    cookies.clear();
}

void CurlCookies::setCookie(const std::string& key, const std::string& value)
{
    cookies[key] = value;
}

json CurlCookies::getCookies()
{
    return cookies;
}
