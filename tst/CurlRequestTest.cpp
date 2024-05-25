//
// Created by candas on 1/19/24.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../src/CurlRequest.h"
#include <gmock/gmock-actions.h>


// an interface class for mock CurlRequest
class CurlRequestInterface {
public:
    virtual ~CurlRequestInterface() = default;
    virtual std::string getUrl() const = 0;
    virtual std::string getBody() const = 0;
    virtual void setUrl(const std::string& newUrl) = 0;
    virtual void setHeader(const std::string& newHeader) = 0;
    virtual void setBody(const std::string& newBody) = 0;
    virtual void setBody(const std::string& newBody, size_t size) = 0;
    virtual void setTimeout(int newTimeout) = 0;
    virtual void setCookies(const CurlCookies& cookies) = 0;
    virtual std::unique_ptr<CurlResponse> sendGet() = 0;
    virtual std::unique_ptr<CurlResponse> sendPost(const std::string& body) = 0;
    virtual std::unique_ptr<CurlResponse> sendPut(const std::string& body) = 0;
    virtual std::unique_ptr<CurlResponse> sendDelete() = 0;
    virtual std::unique_ptr<CurlResponse> sendHead() = 0;
    virtual std::unique_ptr<CurlResponse> sendOptions() = 0;
    virtual bool isSessionIdValid() const = 0;
};


// a mock class implementing CurlRequestInterface
class MockCurlRequest : public CurlRequestInterface {
public:
    MOCK_METHOD(std::string, getUrl, (), (const, override));
    MOCK_METHOD(std::string, getBody, (), (const, override));
    MOCK_METHOD(void, setUrl, (const std::string& newUrl), (override));
    MOCK_METHOD(void, setHeader, (const std::string& newHeader), (override));
    MOCK_METHOD(void, setBody, (const std::string& newBody), (override));
    MOCK_METHOD(void, setBody, (const std::string& newBody, size_t size), (override));
    MOCK_METHOD(void, setTimeout, (int newTimeout), (override));
    MOCK_METHOD(void, setCookies, (const CurlCookies& cookies), (override));
    MOCK_METHOD(std::unique_ptr<CurlResponse>, sendGet, (), (override));
    MOCK_METHOD(std::unique_ptr<CurlResponse>, sendPost, (const std::string& body), (override));
    MOCK_METHOD(std::unique_ptr<CurlResponse>, sendPut, (const std::string& body), (override));
    MOCK_METHOD(std::unique_ptr<CurlResponse>, sendDelete, (), (override));
    MOCK_METHOD(std::unique_ptr<CurlResponse>, sendHead, (), (override));
    MOCK_METHOD(std::unique_ptr<CurlResponse>, sendOptions, (), (override));
    MOCK_METHOD(bool, isSessionIdValid, (), (const, override));
};


//fixture class
class FixtureForCurlRequest : public ::testing::Test {
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
TEST_F(FixtureForCurlRequest, SendGet) {
    CurlRequest request(session, "https://httpbin.org/get", "", cookies, 10);
    const std::string header = "accept: application/json";
    request.setHeader(header);
    std::unique_ptr<CurlResponse> response = request.sendGet();
    ASSERT_EQ(response->getStatus(), 200);
}


// fixture 
TEST_F(FixtureForCurlRequest, sendHead)
{
    CurlRequest request(session, "https://httpbin.org/get", "", cookies, 10);
    const std::string header = "accept: application/json";
    request.setHeader(header);
    std::unique_ptr<CurlResponse> response = request.sendHead();
    ASSERT_EQ(response->getStatus(), 200);
    json headersObj = response->getHeaders();
    ASSERT_TRUE(request.isSessionIdValid());
}

// TEST with mock

TEST(MockCurlRequest, sendOptions) {
    MockCurlRequest mockCurlRequest;
    auto mockResponse = std::make_unique<CurlResponse>(200, "headers", "body");
    auto responsePtr = mockResponse.get();

    auto lambda = [responsePtr]() mutable -> std::unique_ptr<CurlResponse> {
        return std::make_unique<CurlResponse>(*responsePtr);
        };

    EXPECT_CALL(mockCurlRequest, sendOptions()).WillOnce(testing::Invoke(lambda));

    std::unique_ptr<CurlResponse> response = mockCurlRequest.sendOptions();
    ASSERT_EQ(response->getStatus(), 200);
    ASSERT_EQ(response->getBody(), "body");
    ASSERT_EQ(response->getHeadersString(), "headers");
    ASSERT_NE(response->getBody(), "NO body");
    ASSERT_NE(response->getHeadersString(), "NO headers");
}


TEST(IntegrationTest, sendPost)
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

TEST(IntegrationTest, sendPut)
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

TEST(IntegrationTest, sendDelete)
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

TEST(IntegrationTest, sendPatch)
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

TEST(IntegrationTest, setUrl)
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

TEST(IntegrationTest, setBody)
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

TEST(IntegrationTest, setTimeout)
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

