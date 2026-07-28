#include "httpclient.h"

#include <curl/curl.h>
#include <cstdio>
#include <stdexcept>

namespace totorrent {

HttpClient::HttpClient() : curl_(curl_easy_init()) {
    if (!curl_) throw std::runtime_error("Failed to initialize curl");
}

HttpClient::~HttpClient() {
    if (curl_) curl_easy_cleanup(static_cast<CURL*>(curl_));
}

// -------- default header management --------

void HttpClient::setDefaultHeader(const std::string& key, const std::string& value) {
    defaultHeaders_[key] = value;
}

void HttpClient::removeDefaultHeader(const std::string& key) {
    defaultHeaders_.erase(key);
}

// -------- header list building --------
// Merges defaultHeaders_ with any per-call headers (per-call wins on conflict),
// and hands back a curl_slist* the caller is responsible for freeing via
// curl_slist_free_all() once the request is done.
curl_slist* HttpClient::buildHeaderList(const Headers& perCallHeaders) const {
    Headers merged = defaultHeaders_;
    for (const auto& [key, value] : perCallHeaders) {
        merged[key] = value; // per-call overrides default of the same key
    }

    curl_slist* list = nullptr;
    for (const auto& [key, value] : merged) {
        std::string line = key + ": " + value;
        list = curl_slist_append(list, line.c_str());
    }
    return list;
}

// -------- write callbacks --------

size_t HttpClient::writeCallback(char* ptr, size_t size, size_t nmemb, void* userdata) {
    auto* out = static_cast<std::string*>(userdata);
    size_t totalSize = size * nmemb;
    out->append(ptr, totalSize);
    return totalSize;
}

size_t HttpClient::writeFileCallback(char* ptr, size_t size, size_t nmemb, void* userdata) {
    auto* out = static_cast<std::FILE*>(userdata);
    return std::fwrite(ptr, size, nmemb, out);
}

// -------- GET --------

HttpResponse HttpClient::get(const std::string& url, const Headers& headers) {
    CURL* curl = static_cast<CURL*>(curl_);

    std::string body;
    curl_slist* headerList = buildHeaderList(headers);

    curl_easy_reset(curl); // clear any options left over from a previous call
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerList);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &body);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    CURLcode res = curl_easy_perform(curl);

    long status = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status);

    curl_slist_free_all(headerList);

    if (res != CURLE_OK) {
        throw std::runtime_error(curl_easy_strerror(res));
    }

    return HttpResponse{status, std::move(body)};
}

// -------- POST --------

HttpResponse HttpClient::post(const std::string& url, const std::string& requestBody,
                               const std::string& contentType, const Headers& headers) {
    CURL* curl = static_cast<CURL*>(curl_);

    std::string responseBody;

    // merge Content-Type into the per-call headers so it goes through the
    // same merge/override logic as everything else
    Headers allHeaders = headers;
    allHeaders["Content-Type"] = contentType;
    curl_slist* headerList = buildHeaderList(allHeaders);

    curl_easy_reset(curl);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, requestBody.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, static_cast<long>(requestBody.size()));
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerList);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseBody);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    CURLcode res = curl_easy_perform(curl);

    long status = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status);

    curl_slist_free_all(headerList);

    if (res != CURLE_OK) {
        throw std::runtime_error(curl_easy_strerror(res));
    }

    return HttpResponse{status, std::move(responseBody)};
}

// -------- download to file (streamed, not buffered in memory) --------

void HttpClient::downloadToFile(const std::string& url, const std::string& outPath,
                                 const Headers& headers) {
    CURL* curl = static_cast<CURL*>(curl_);

    std::FILE* file = std::fopen(outPath.c_str(), "wb");
    if (!file) {
        throw std::runtime_error("Failed to open output file: " + outPath);
    }

    curl_slist* headerList = buildHeaderList(headers);

    curl_easy_reset(curl);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerList);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFileCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    CURLcode res = curl_easy_perform(curl);

    long status = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status);

    curl_slist_free_all(headerList);
    std::fclose(file);

    if (res != CURLE_OK) {
        // best-effort cleanup of a partial/corrupt download
        std::remove(outPath.c_str());
        throw std::runtime_error(curl_easy_strerror(res));
    }

    if (status < 200 || status >= 300) {
        std::remove(outPath.c_str());
        throw std::runtime_error("Download failed with HTTP status " + std::to_string(status));
    }
}

// -------- encodeURIComponent (matches JS semantics, not curl_easy_escape) --------

std::string HttpClient::encodeURIComponent(const std::string& s) {
    static const char* hex = "0123456789ABCDEF";
    std::string out;
    out.reserve(s.size() * 3);

    for (unsigned char c : s) {
        bool unreserved =
            std::isalnum(c) ||
            c == '-' || c == '_' || c == '.' || c == '~' ||
            c == '!' || c == '*' || c == '\'' || c == '(' || c == ')';

        if (unreserved) {
            out += static_cast<char>(c);
        } else {
            out += '%';
            out += hex[(c >> 4) & 0xF];
            out += hex[c & 0xF];
        }
    }
    return out;
}

} // namespace myapp
