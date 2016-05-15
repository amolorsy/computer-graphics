#include <string>

#include "glm-0.9.7.4/glm/glm.hpp"

static inline void ltrim(std::string &str) {
  str.erase(str.begin(), find_if(str.begin(), str.end(), not1(std::ptr_fun<int, int>(isspace))));
}

static inline void rtrim(std::string &str) {
  str.erase(find_if(str.rbegin(), str.rend(), not1(std::ptr_fun<int, int>(isspace))).base(), str.end());
}

static inline void trim(std::string &str) {
  ltrim(str);
  rtrim(str);
}

static inline void removeComment(std::string &str) {
  int found = str.find('#');
  if (found != std::string::npos) str.erase(found, str.length() - 1);
}
