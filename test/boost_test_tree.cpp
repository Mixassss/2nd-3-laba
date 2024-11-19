#define BOOST_TEST_MODULE TreeTest
#include <boost/test/included/unit_test.hpp>
#include "../include/tree.h"

BOOST_AUTO_TEST_CASE(TestInsertTree) {
    CompleteBinaryTree Tree;
    Tree.insert(5);
    Tree.insert(2);
    Tree.insert(9);

    BOOST_CHECK(Tree.search(5));
    BOOST_CHECK(Tree.search(2));
    BOOST_CHECK(Tree.search(9));
    BOOST_CHECK(!Tree.search(7));
}

BOOST_AUTO_TEST_CASE(TestCompleteTree) {
    CompleteBinaryTree Tree1;
    Tree1.insert(10);
    Tree1.insert(5);
    Tree1.insert(15);
    BOOST_CHECK(Tree1.isComplete());
    
    CompleteBinaryTree Tree2;
    Tree2.insert(10);
    Tree2.insert(5);
    Tree2.insert(15);
    Tree2.insert(3);  
    Tree2.insert(7);   
    BOOST_CHECK(Tree2.isComplete());
    
    CompleteBinaryTree Tree3;
    Tree3.insert(10);
    Tree3.insert(5);
    Tree3.insert(15);
    Tree3.insert(3);
    Tree3.insert(6); 
    Tree3.insert(12); 
    Tree3.insert(18); 
    BOOST_CHECK(Tree3.isComplete());
}

BOOST_AUTO_TEST_CASE(TestToString) {
    CompleteBinaryTree Tree;
    Tree.insert(5);
    Tree.insert(2);
    Tree.insert(9);
    BOOST_CHECK_EQUAL(Tree.toString(), "5 2 9 "); // Проверка выводимой строки
}

BOOST_AUTO_TEST_CASE(test_count_nodes) {
    CompleteBinaryTree tree;
    tree.insert(5);
    tree.insert(2);
    tree.insert(9);
    
    BOOST_CHECK_EQUAL(tree.getSize(), 3);
}

BOOST_AUTO_TEST_CASE(TestPrintFunction) {
    CompleteBinaryTree tree;
    tree.insert(5);
    tree.insert(2);
    tree.insert(9);
    tree.print(); // Проверяем, что функция print() работает без ошибок
}