project(EuropeByRailsTests)

add_subdirectory(../../googletest googletest)
include_directories(../../googletest/googletest/include)

add_executable(EuropeByRailsTests
        ../src/city.h
        ../src/priority_queue.h
        ../src/rail_system.h
        ../src/rail_system.cpp
        ../src/service.h
        priority_queue_student_tests.cpp
        rail_system_student_tests.cpp
        priority_queue_Stas_tests.cpp
        rail_system_Stas_tests.cpp
)

target_link_libraries(EuropeByRailsTests gtest gtest_main)
