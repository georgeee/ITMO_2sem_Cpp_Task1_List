#!/bin/bash
g++ list.hpp tests/boost.cpp -Wall -olist_boost_tests -static -lboost_unit_test_framework && ./list_boost_tests 
g++ list.hpp tests/valgrind.cpp -Wall -olist_valgrind_test && valgrind  ./list_valgrind_test