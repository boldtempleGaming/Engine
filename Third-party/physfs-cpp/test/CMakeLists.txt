add_executable(physfs_test physfs_test.cpp)
target_link_libraries(physfs_test physfs++ cppunit)
add_test(physfs_test physfs_test)
