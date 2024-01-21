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
    if (key.empty() || value.empty()) {
        throw std::invalid_argument("Key and value cannot be empty");
    }
    cookies[key] = value;
}

json CurlCookies::getCookies()
{
    return cookies;
}
