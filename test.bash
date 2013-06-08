#!/bin/bash
g++ list.hpp tests/boost.cpp -std=c++0x -Wall -olist_boost_tests -lboost_unit_test_framework && ./list_boost_tests  && valgrind ./list_boost_tests
g++ list.hpp tests/valgrind.cpp -std=c++0x -Wall -olist_valgrind_test && valgrind  ./list_valgrind_test
