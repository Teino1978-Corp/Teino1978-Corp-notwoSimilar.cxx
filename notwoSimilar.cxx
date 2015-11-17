#pragma once

#include <algorithm>
#include <cstring>
#include <unordered_map>
#include <string>
#include <utility>
#include <vector>

using ull = unsigned long long;
using charCount = std::pair<char,ull>;

template <template <class, class...> typename A, typename B, typename C>
static inline bool exists(const A<B,C>& map, const B& key) {
  try {
    map.at(key);
    return true;
  } catch (...) {
    return false;
  }
}

template <template <class, class...> typename A, typename B, typename C>
static inline bool nExists(const A<B,C>& map, const B& key) {
  return !exists<A,B,C>(map, key);
}

template <template <class, class...> typename A, typename B, typename C>
static inline decltype(auto) defArg(A<B,C>& map, const B& key, const C& def) {
  if (exists<A,B,C>(map, key)) {
    return map[key];
  } else {
    return def;
  }
}

static inline bool constrained(const std::string& str, ull maxChar) {
  auto sumOfRest = str.size() - maxChar;
  return sumOfRest + 1 < maxChar;
}

static bool shuffle(std::string& string) {
  std::unordered_map<char,ull> hash;

  for (auto& ch : string) {
    if (nExists<std::unordered_map,char,ull>(hash, ch)) {
      hash[ch] = 0ull;
    }

    ++hash[ch];
  }

  std::vector<std::pair<char,ull>> sorted{hash.cbegin(), hash.cend()};

  std::sort(sorted.begin(), sorted.end(), [] (auto pairA, auto pairB) {
    return pairA.second < pairB.second;
  });

  if (constrained(string, sorted.back().second)) {
    return false;
  }

  auto& maxPair = sorted.back();
  sorted.pop_back();
  std::string newStr;

  while (sorted.size() != 0) {
    if (newStr.back() != maxPair.first) {
      newStr.append(1, maxPair.first);
      --maxPair.second;

      if (maxPair.second == 0) {
        maxPair = sorted.back();
        sorted.pop_back();
      }
    }

    if (newStr.back() != sorted.back().first) {
      newStr.append(1, sorted.back().first);
      --sorted.back().second;

      if (sorted.back().second == 0) {
        sorted.pop_back();
      }
    }
  }

  string = newStr;

  return true;
}