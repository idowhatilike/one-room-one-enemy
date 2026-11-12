# CMake generated Testfile for 
# Source directory: C:/Users/Trieu/one-room-one-enemy
# Build directory: C:/Users/Trieu/one-room-one-enemy/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test("player_test" "C:/Users/Trieu/one-room-one-enemy/build/player_test.exe")
set_tests_properties("player_test" PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Trieu/one-room-one-enemy/CMakeLists.txt;71;add_test;C:/Users/Trieu/one-room-one-enemy/CMakeLists.txt;0;")
add_test("weapon_mastery_test" "C:/Users/Trieu/one-room-one-enemy/build/weapon_mastery_test.exe")
set_tests_properties("weapon_mastery_test" PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Trieu/one-room-one-enemy/CMakeLists.txt;71;add_test;C:/Users/Trieu/one-room-one-enemy/CMakeLists.txt;0;")
subdirs("_deps/raylib-build")
