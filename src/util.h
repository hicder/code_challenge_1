#pragma once

#include <string>

namespace mongo {

/**
 * Flatten the JSON string.
 *
 * @param input JSON string input.
 * @return flattened JSON string.
 * @throws std::invalid_argument If the input is malformed in some way.
 */
std::string flattenJson(std::string input);

} // namespace mongo
