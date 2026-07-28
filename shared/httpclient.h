#pragma once

#include <string>
#include <map>
#include <cstdio>

// avoid pulling <curl/curl.h> into every file that includes this header
typedef void CURL;
struct curl_slist;

namespace myapp {

struct HttpResponse {
    long status;
    std::string body;
};

using Headers = std::map<std::string, std::string>;

class HttpClient {
public:
    HttpClient();
    ~HttpClient();

    HttpClient(const HttpClient&) = delete;
    HttpClient& operator=(const HttpClient&) = delete;

    HttpResponse get(const std::string& url, const Headers& headers = {});
    HttpResponse post(const std::string& url, const std::string& body,
                       const std::string& contentType = "application/json",
                       const Headers& headers = {});

    void downloadToFile(const std::string& url, const std::string& outPath,
                         const Headers& headers = {});

    void setDefaultHeader(const std::string& key, const std::string& value);
    void removeDefaultHeader(const std::string& key);

    static std::string encodeURIComponent(const std::string& s);

private:
    void* curl_; // actually CURL*, void* here so curl.h doesn't leak into the header
    Headers defaultHeaders_;

    curl_slist* buildHeaderList(const Headers& perCallHeaders) const;

    static size_t writeCallback(char* ptr, size_t size, size_t nmemb, void* userdata);
    static size_t writeFileCallback(char* ptr, size_t size, size_t nmemb, void* userdata);
};

} // namespace myapp
