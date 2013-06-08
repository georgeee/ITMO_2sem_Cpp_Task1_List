/* 
 * File:   main.cpp
 * Author: georgeee
 *
 * Created on 7 Апрель 2013 г., 15:16
 */

#include <cstdlib>
#include <iostream>
#include "../list.hpp"

#define BOOST_TEST_MODULE ListTesting
#define BOOST_TEST_DYN_LINK
#define BOOST_MAIN


#include <boost/test/unit_test.hpp>

using namespace std;

BOOST_AUTO_TEST_CASE(push_pop_test) {
    List<int> list;
    BOOST_CHECK_THROW(list.pop_back(), List<int>::ListException);
    for (int i = 10; i < 20; i++) list.push_back(i);
    for (int i = 9; i >= 0; i--) list.push_front(i);
    for (int i = 0; i < 10; i++) {
        BOOST_CHECK_EQUAL(list.front(), i);
        BOOST_CHECK_EQUAL(list.pop_front(), i);
    }
    for (int i = 19; i >= 10; i--) {
        BOOST_CHECK_EQUAL(list.back(), i);
        BOOST_CHECK_EQUAL(list.pop_back(), i);
    }
    BOOST_CHECK(list.is_empty());
}

BOOST_AUTO_TEST_CASE(test_iterators) {
    List<int> list;
    for (int i = 0; i < 5; i++)
        list.push_back(i);

    int k = 0;
    for (List<int>::Iterator it = list.begin(); it != list.end(); it++, k++) {
        BOOST_CHECK_EQUAL(k, *it);
    }

    List<int>::Iterator it = list.begin();
    const List<int>::Iterator & it2 = (const List<int>::Iterator &) (it++);
    BOOST_CHECK_EQUAL(*it, 1);
    BOOST_CHECK_EQUAL(*it2, 0);
    BOOST_CHECK_EQUAL(*(++it), 2);
    List<int>::Iterator it3 = ++it++;
    BOOST_CHECK_EQUAL(*it3, 3);
    BOOST_CHECK_EQUAL(*it, 3);
    it3 = --it--;
    BOOST_CHECK_EQUAL(*it3, 2);
    BOOST_CHECK_EQUAL(*it, 2);
}

BOOST_AUTO_TEST_CASE(test_constructors) {
    List<int> list1;
    for (int i = 0; i < 5; i++)
        list1.push_back(i);
    List<int> list2 = list1;
    for (int i = 0; i < 3; i++) BOOST_CHECK_EQUAL(list2.pop_front(), i);
    List<int> list3 = list1;
    for (int i = 0; i < 4; i++) BOOST_CHECK_EQUAL(list3.pop_front(), i);
    list3 = list2;
    for (int i = 3; i < 5; i++) BOOST_CHECK_EQUAL(list3.pop_front(), i);
    for (int i = 3; i < 5; i++) BOOST_CHECK_EQUAL(list2.pop_front(), i);
}

BOOST_AUTO_TEST_CASE(insert_erase_test) {
    List<int> list;
    for (int i = 0; i < 20; i++) {
        list.push_back(i);
    }
    List<int>::Iterator it = --list.end();
    for (int i = 20; i < 30; i++) {
        list.push_back(i);
    }
    for (int i = 20; i < 30; i++) {
        list.push_back(i);
    }
    for (int i = 50; i < 80; i++) {
        list.push_back(i);
    }
    BOOST_CHECK_EQUAL(*++it, 20);
    for (int i = 20; i < 30; i++) BOOST_CHECK_EQUAL(*it++, i);
    for (int i = 20; i < 30; i++){
        BOOST_CHECK_EQUAL(*it, i);
        it = list.erase(it);
    }
    BOOST_CHECK_EQUAL(*--it,29);
    for(int i=30; i<50; i++) it = list.insert(it, i);
    BOOST_CHECK_EQUAL(*it,49);
    BOOST_CHECK_EQUAL(*++it,50);
    it = list.begin();
    for(int i=0; i<80; i++){
        BOOST_CHECK_EQUAL(i, *it++);
    }
    BOOST_CHECK(it==list.end());
}
