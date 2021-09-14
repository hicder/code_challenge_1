#include <gtest/gtest.h>

#include <folly/dynamic.h>
#include <folly/json.h>

#include "../util.h"

namespace mongo {
namespace test {
using namespace folly;

void runTest(std::string input, dynamic expectedDynamic) {
  auto flattenedStr = flattenJson(input);
  dynamic flattenedDynamic = folly::parseJson(flattenedStr);
  ASSERT_TRUE(flattenedDynamic == expectedDynamic);
}

TEST(FlattenJson, Basic) {
  std::string json = R"(
{
    "name": "ABC",
    "location": {
        "city": "Tahoe",
        "state": "CA"
    },
    "bio": {
        "age": 32,
        "married": false,
        "height": 6.5
    }
}
)";
  dynamic expectedDynamic =
      dynamic::object("name", "ABC")("location.city", "Tahoe")(
          "location.state", "CA")("bio.age", 32)("bio.married",
                                                 false)("bio.height", 6.5);
  runTest(std::move(json), std::move(expectedDynamic));
}

TEST(FlattenJson, EmptyJSON) {
  std::string json = "{}";
  dynamic expectedDynamic = dynamic::object;
  runTest(std::move(json), std::move(expectedDynamic));
}

TEST(FlattenJson, InvalidJson) {
  std::string json = R"(
{
    "name": "ABC",
    "location": {
        "city": "Tahoe",
        "state": "CA"
    },
    "bio": {
        "age": 32,
        "married": false
        "height": 6.5
    }
}
)";

  EXPECT_THROW(flattenJson(std::move(json)), std::invalid_argument);
}

} // namespace test
} // namespace mongo

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
