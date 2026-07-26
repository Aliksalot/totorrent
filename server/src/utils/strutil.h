#pragma once

#include<string>
#include<string_view>
#include<vector>
#include<cctype>
#include<sstream>
#include<iomanip>
#include <curl/curl.h>

inline std::vector<std::string_view> split(
    std::string_view str, char delim) {
  std::vector<std::string_view> out;
  size_t start = 0;
  while(start <= str.size()) {
    size_t pos = str.find(delim, start);
      if(pos == std::string_view::npos) {
        out.push_back(str.substr(start));
        break;
      }
      out.push_back(str.substr(start, pos - start));
      start = pos + 1;
  }
  return out;
}

inline std::string_view trim(std::string_view s) {
  auto isSpace = [](unsigned char c) { return std::isspace(c); };

  size_t start = 0;
  while (start < s.size() && isSpace(s[start])) ++start;

  size_t end = s.size();
  while (end > start && isSpace(s[end - 1])) --end;

  return s.substr(start, end - start);
}

/// Designed to precisely match JS's encodeURIComponent
inline std::string encodeSafeUri(const std::string& s) {
  std::ostringstream out;
  out << std::hex << std::uppercase;

  for (unsigned char c : s) {
    if (std::isalnum(c) ||
      c == '-' || c == '_' || c == '.' || c == '~' ||
      c == '!' || c == '*' || c == '\'' || c == '(' || c == ')') {
      out << c;
    } else {
      out << '%' << std::setw(2) << std::setfill('0') << static_cast<int>(c);
    }
  }

  return out.str();
}

