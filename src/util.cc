#include "util.h"

#include <folly/dynamic.h>
#include <folly/json.h>

#include <iostream>

namespace mongo {

namespace {
void flattenJson(const folly::dynamic &obj, std::string prefix,
                 folly::dynamic *out) {
  if (!obj.isObject()) {
    throw std::invalid_argument("input must be an object");
  }

  // Go through each key, value pair. If value is a map, recurse and append the
  // key to the accumulated prefix. If value is primitive type, we don't need to
  // recurse and can append to the output.
  for (auto &kv : obj.items()) {
    auto &key = kv.first;
    if (!key.isString()) {
      // Key must be string. Otherwise this is malformed JSON.
      throw std::invalid_argument("key must be string");
    }

    switch (kv.second.type()) {
    case folly::dynamic::Type::BOOL:
      FOLLY_FALLTHROUGH;
    case folly::dynamic::Type::DOUBLE:
      FOLLY_FALLTHROUGH;
    case folly::dynamic::INT64:
      FOLLY_FALLTHROUGH;
    case folly::dynamic::STRING:
      (*out)[prefix + key.asString()] = kv.second;
      break;
    case folly::dynamic::OBJECT:
      flattenJson(kv.second,
                  folly::to<std::string>(prefix, key.asString(), '.'), out);
      break;
    case folly::dynamic::ARRAY:
      // This is guaranteed to not happen
      FOLLY_FALLTHROUGH;
    case folly::dynamic::NULLT:
      throw std::invalid_argument("Unexpected type");
    }
  }
}
} // namespace

std::string flattenJson(std::string input) {
  try {
    folly::dynamic json = folly::parseJson(input);
    folly::dynamic out = folly::dynamic::object;
    flattenJson(json, "", &out);
    return folly::toJson(out);
  } catch (const folly::json::parse_error &e) {
    // Catch the parse error and return as invalid_argument to make it
    // consistent.
    throw std::invalid_argument(e.what());
  }

  // Shouldn't reach here
  folly::assume_unreachable();
}
} // namespace mongo
