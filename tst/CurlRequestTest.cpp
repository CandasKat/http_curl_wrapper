//
// Created by candas on 1/19/24.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../src/CurlRequest.h"



//fixture class
class CurlRequestTest : public ::testing::Test {
protected:
    CurlSession session;
    CurlCookies cookies;

    void SetUp() override {
        cookies.setCookie("freeform", "value1");
        session.setSessionId("1234567890");
    }

    void TearDown() override {
        // Code here will be called immediately after each test
        // (right before the destructor).
    }
};

// Unit tests

// Test for CurlSession::setSessionId
TEST(UnitTest, testSetSessionId) {
    CurlSession session;
    session.setSessionId("1234567890");
    ASSERT_EQ(session.getSessionId(), "1234567890");
}

// Test for CurlRequest::getUrl
TEST(UnitTest, testGetUrl) {
    CurlSession session;
    CurlCookies cookies;
    CurlRequest request(session, "https://httpbin.org/get", "", cookies, 10);
    ASSERT_EQ(request.getUrl(), "https://httpbin.org/get");
}

// Test for CurlCookies::setCookie
TEST(UnitTest, testSetCookie) {
    CurlCookies cookies;
    cookies.setCookie("freeform", "value1");
    ASSERT_EQ(cookies.getCookies()["freeform"], "value1");
}


// Integration tests

// fixture test
TEST_F(CurlRequestTest, SendGet) {
    CurlRequest request(session, "https://httpbin.org/get", "", cookies, 10);
    const std::string header = "accept: application/json";
    request.setHeader(header);
    std::unique_ptr<CurlResponse> response = request.sendGet();
    ASSERT_EQ(response->getStatus(), 200);
}


// fixture 
TEST_F(CurlRequestTest, sendHead)
{
    CurlRequest request(session, "https://httpbin.org/get", "", cookies, 10);
    const std::string header = "accept: application/json";
    request.setHeader(header);
    std::unique_ptr<CurlResponse> response = request.sendHead();
    ASSERT_EQ(response->getStatus(), 200);
    json headersObj = response->getHeaders();
    printf("body:\n%s\n", response->getBody().c_str());
    printf("headers:\n%s\n", headersObj.dump().c_str());
    ASSERT_TRUE(request.isSessionIdValid());
}

TEST(RequestTest, sendOptions)
{
    CurlSession session;
    CurlCookies cookies;
    cookies.setCookie("freeform", "value1");
    session.setSessionId("1234567890");
    CurlRequest request(session, "https://httpbin.org/get", "", cookies, 10);
    const std::string header = "accept: application/json";
    request.setHeader(header);
    std::unique_ptr<CurlResponse> response = request.sendOptions();
    ASSERT_EQ(response->getStatus(), 200);
}

TEST(RequestTest, sendPost)
{
    CurlSession session;
    CurlCookies cookies;
    cookies.setCookie("freeform", "value1");
    session.setSessionId("1234567890");
    CurlRequest request(session, "https://httpbin.org/post", "", cookies, 10);
    const std::string header = "accept: application/json";
    request.setHeader(header);
    std::unique_ptr<CurlResponse> response = request.sendPost("hello world");
    ASSERT_EQ(response->getStatus(), 200);
}

TEST(RequestTest, sendPut)
{
    CurlSession session;
    CurlCookies cookies;
    cookies.setCookie("freeform", "value1");
    session.setSessionId("1234567890");
    CurlRequest request(session, "https://httpbin.org/put", "", cookies, 10);
    const std::string header = "accept: application/json";
    request.setHeader(header);
    std::unique_ptr<CurlResponse> response = request.sendPut("hello world");
    ASSERT_EQ(response->getStatus(), 200);
}

TEST(RequestTest, sendDelete)
{
    CurlSession session;
    CurlCookies cookies;
    cookies.setCookie("freeform", "value1");
    session.setSessionId("1234567890");
    CurlRequest request(session, "https://httpbin.org/delete", "", cookies, 10);
    const std::string header = "accept: application/json";
    request.setHeader(header);
    std::unique_ptr<CurlResponse> response = request.sendDelete();
    ASSERT_EQ(response->getStatus(), 200);
}

TEST(RequestTest, sendPatch)
{
    CurlSession session;
    CurlCookies cookies;
    cookies.setCookie("freeform", "value1");
    session.setSessionId("1234567890");
    CurlRequest request(session, "https://httpbin.org/patch", "", cookies, 10);
    const std::string header = "accept: application/json";
    request.setHeader(header);
    std::unique_ptr<CurlResponse> response = request.sendPatch("hello world");
    ASSERT_EQ(response->getStatus(), 200);
}

TEST(RequestTest, setUrl)
{
    CurlSession session;
    CurlCookies cookies;
    session.setSessionId("1234567890");
    CurlRequest request(session, "https://httpbin.org/get", "", cookies, 10);
    request.setUrl("https://httpbin.org/post");
    request.setBody("hello world");
    request.setHeader("accept: application/json");
    std::unique_ptr<CurlResponse> response = request.sendPost("hello world");
    ASSERT_EQ(request.getUrl(), "https://httpbin.org/post");
}

TEST(RequestTest, setBody)
{
    CurlSession session;
    CurlCookies cookies;
    session.setSessionId("1234567890");
    CurlRequest request(session, "https://httpbin.org/post", "", cookies, 10);
    request.setBody("hello world", 11);
    request.setHeader("accept: application/json");
    std::unique_ptr<CurlResponse> response = request.sendPost("hello world");
    ASSERT_EQ(request.getBody(), "hello world");
}

TEST(RequestTest, setTimeout)
{
    CurlSession session;
    CurlCookies cookies;
    session.setSessionId("1234567890");
    CurlRequest request(session, "https://httpbin.org/post", "", cookies, 10);
    request.setTimeout(20);
    request.setHeader("accept: application/json");
    std::unique_ptr<CurlResponse> response = request.sendPost("hello world");
    ASSERT_EQ(request.getUrl(), "https://httpbin.org/post");
}

// 2 tests fixture et un 1 test utilisant mock
