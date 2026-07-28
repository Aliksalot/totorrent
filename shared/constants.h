#pragma once

namespace totorrent {
  constexpr const char* UNKNOWN_FIELD_VALUE = "(Unknown)";
  constexpr const char* PBAPI_INFO = "https://apibay.org/t.php";
  constexpr const char* PBAPI_SEARCH = "https://apibay.org/q.php";

  constexpr int16_t BASE_PORT = 8080;
  constexpr const char* BASE_URL = "http://127.0.0.1:8080/";

  using json = nlohmann::json;
}
