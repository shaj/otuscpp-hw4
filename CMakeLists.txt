cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION "1")
if($ENV{TRAVIS_BUILD_NUMBER})
  set(PATCH_VERSION $ENV{TRAVIS_BUILD_NUMBER})
endif()

project(print_ip VERSION 0.0.${PATCH_VERSION})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(print_ip main.cpp)

add_executable(test_printer test_printer.cpp)


set_target_properties(print_ip test_printer PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_DEFINITIONS BOOST_LOG_DYN_LINK
  COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)

target_link_libraries(print_ip
  ${Boost_LIBRARIES}
)

set_target_properties(test_printer PROPERTIES
  COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
  INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)


target_link_libraries(test_printer
  ${Boost_UNIT_TEST_LIBRARIES}
  ${Boost_LIBRARIES}
)


configure_file("${PROJECT_SOURCE_DIR}/version.h.in" "${PROJECT_BINARY_DIR}/version.h")
target_include_directories(print_ip PUBLIC "${PROJECT_BINARY_DIR}")


install(TARGETS print_ip RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT kolobrod2002@yandex.ru)

include (CPack)

enable_testing()

add_test(test_printer test_printer)
