#pragma once

#include <string>

namespace mongo {

/**
 * Flatten a JSON.
 *
 * @param input Input string, must be JSON
 * @return A flattened JSON string.
 */
std::string flattenJson(std::string input);

} // namespace mongo
