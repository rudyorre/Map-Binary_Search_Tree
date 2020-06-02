#include <iostream>
#include<string>
#include<cassert>
#include "Map.h"
using namespace std;

void test()
{
	Map m;
	assert(m.insert("Please", 123)); // testing insert()
	assert(m.insert("give", 456));
	assert(m.insert("me", 789));
	assert(m.insert("an A", 0));
	assert(m.size() == 4); // making sure the size is correct
	assert(!m.empty()); // should be not empty
	while (!m.empty()) { 
		KeyType key; ValueType value;
		assert(m.get(0, key, value)); // getting the first in-order element
		assert(m.erase(key));} // erasing the first element (4 times)
	assert(m.empty());
	assert(m.size() == 0);
	assert(!m.erase("Rudy"));
	assert(m.insert("Rudy",1.0));
	assert(!m.update("Rudy", 1.0)); // updating same key and value
	assert(m.update("Rudy", 1.1)); // different value
	assert(m.erase("Rudy"));
	assert(m.insert("Rudy", 1.0));
	assert(!m.insert("Rudy", 3.0)); // can't insert same key
	assert(m.update("Rudy", 5.0));
	assert(!m.empty());
	assert(m.size() == 1);
	assert(m.contains("Rudy"));
	string names[] = { "Alex", "Branden", "Cody", "Dylan"};
	for (int i = 0; i < 4; i++){ assert(m.insert(names[i], i)); } // adding 4 elements
	assert(m.size() == 5);
	Map n;
	for (int i = 3; i >= 0; i--) { assert(n.insert(names[i], i)); } // adding 4 elements, in reverse
	for (int i = 0; i < 4; i++) {
		KeyType key; ValueType value;
		assert(m.get(0, key, value)); 
		assert(m.erase(key));} // erasing all the elements
	for (int i = 0; i < 4; i++) { assert(m.insert(names[i], i)); }
	Map o;
	assert(combine(m, n, o)); // test combine()
	for (int i = 0; i < 4; i++) {
		KeyType key; ValueType value;
		assert(n.get(i, key, value));
		assert(n.update(key, 3.14159)); // update all to pi
		assert(!n.update(key, 3.14159));} // false bc can't update with same value
	assert(!combine(m, n, o));
	assert(n.insert("Rudy", 3.14159));
	assert(!n.insert("Rudy", 3.14159));
	if (true){ // using this as a scope to be deleted
		KeyType key = "Alex"; ValueType value;
		assert(n.get(key, value));
		assert(value == 3.14159);} // checking if right value was inserted earlier
	while (!m.empty()){ // clearing m
		KeyType key;
		ValueType value;
		assert(m.get(0, key, value));
		assert(m.erase(key));}
	while (!n.empty()){ // clearing n
		KeyType key;
		ValueType value;
		assert(n.get(0, key, value));
		assert(n.erase(key));}
	while (!o.empty()){ // clearing o
		KeyType key;
		ValueType value;
		assert(o.get(0, key, value));
		assert(o.erase(key));}
	assert(!m.size() && !n.size() && !o.size()); // all sizes should be 0
	m = n;
	o.swap(n); // testing swap
	m.swap(m);
	assert(!m.size() && !n.size() && !o.size()); // all sizes should still be 0
	std::cout << "All tests passed :)" << std::endl;
}

int main()
{
	test();
}