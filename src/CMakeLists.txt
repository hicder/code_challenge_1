add_library(util util.cc)
target_link_libraries(util folly glog pthread double-conversion fmt -ldl)

add_executable(flat_json flat_json.cc)
target_link_libraries(flat_json util)

add_subdirectory(test)
