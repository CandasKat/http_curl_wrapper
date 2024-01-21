//
// Created by candas on 1/20/24.
//

#include "CurlException.h"

CurlException::CurlException(const std::string& message)
{
    this->message = message;
}

const std::string& CurlException::getMessage() const noexcept
{
    return message;
}