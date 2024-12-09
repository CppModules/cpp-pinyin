#include "cpp-pinyin/Pinyin.h"


#include <cpp-pinyin/G2pglobal.h>

#include <memory>
#include <vector>
#include <unordered_set>

namespace Pinyin {

class G2pGlobal {
public:
  std::filesystem::path path = std::filesystem::current_path() / "res" / "dict";
};

auto m_global = std::make_unique<G2pGlobal>();

std::filesystem::path dictionaryPath() {
  if (!m_global) {
    m_global = std::make_unique<G2pGlobal>();
  }
  return m_global->path;
}

void setDictionaryPath(const std::string &dir) {
  m_global->path = dir;
}

bool isLetter(char32_t c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool isHanzi(char32_t c) {
  return c >= 0x4e00 && c <= 0x9fa5;
}

bool isKana(char32_t c) {
  return (c >= 0x3040 && c <= 0x309F) || (c >= 0x30A0 && c <= 0x30FF);
}

bool isDigit(char32_t c) {
  return c >= '0' && c <= '9';
}

bool isSpace(char32_t c) {
  return c == ' ';
}

bool isSpecialKana(char32_t c) {
  static const std::unordered_set<char32_t> specialKana = {
    U'ャ', U'ュ', U'ョ', U'ゃ', U'ゅ', U'ょ',
    U'ァ', U'ィ', U'ゥ', U'ェ', U'ォ', U'ぁ', U'ぃ', U'ぅ', U'ぇ', U'ぉ'
  };
  return specialKana.find(c) != specialKana.end();
}

std::string getInitials(const std::string &pinyin, bool strict) {
  auto startsWith = [](const std::string &str, std::string_view prefix) {
    // 检查前缀的长度是否大于源字符串的长度
    if (prefix.length() > str.length()) {
      return false;
    }
    // 使用substr进行比较
    return str.substr(0, prefix.length()) == prefix;
  };
  std::vector<std::string_view> *p;
  if (strict) {
    static std::vector<std::string_view> _INITIALS = {"b", "p", "m", "f", "d", "t", "n", "l", "g", "k", "h", "j", "q",
                                                      "x", "zh", "ch", "sh", "r", "z", "c", "s",};
    p = &_INITIALS;
  } else {
    static std::vector<std::string_view> _INITIALS_NOT_STRICT = {"b", "p", "m", "f", "d", "t", "n", "l", "g", "k", "h",
                                                                 "j", "q",
                                                                 "x", "zh", "ch", "sh", "r", "z", "c", "s", "y", "w"};
    p = &_INITIALS_NOT_STRICT;
  }
  for (auto &i: *p) {
    if (startsWith(pinyin,i)) {
      return i.data();
    }
  }
  return "";
}

}

