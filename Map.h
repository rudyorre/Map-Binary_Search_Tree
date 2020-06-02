// updated 9:47pm 3-12-2020
#ifndef MAP_H
#define MAP_H
#include <string>

using KeyType = std::string;
using ValueType = double;

class Map
{
private:
	struct Node
	{
		KeyType key;
		ValueType value;
		Node* left;
		Node* right;

		int numChildren()
		{
			if (left == nullptr && right == nullptr)
			{
				return 0;
			}
			else if (left == nullptr || right == nullptr)
			{
				return 1;
			}
			else
			{
				return 2;
			}
		}
	};

	Node* root;

public:
	Map();              // Create an empty map (i.e., one with no key/value pairs)

	Map(const Map& rhs);

	~Map();

	const Map& operator=(const Map& rhs);

	bool empty() const; // Return true if the map is empty, otherwise false.

	int size() const;   // Return the number of key/value pairs in the map.

	bool insert(const KeyType& key, const ValueType& value);
	// If key is not equal to any key currently in the map, and if the
	// key/value pair can be added to the map, then do so and return true.
	// Otherwise, make no change to the map and return false (indicating
	// that either the key is already in the map).

	bool update(const KeyType& key, const ValueType& value);
	// If key is equal to a key currently in the map, then make that key no
	// longer map to the value it currently maps to, but instead map to
	// the value of the second parameter; return true in this case.
	// Otherwise, make no change to the map and return false.

	bool insertOrUpdate(const KeyType& key, const ValueType& value);
	// If key is equal to a key currently in the map, then make that key no
	// longer map to the value it currently maps to, but instead map to
	// the value of the second parameter; return true in this case.
	// If key is not equal to any key currently in the map then add it and 
	// return true. In fact this function always returns true.

	bool erase(const KeyType& key);
	// If key is equal to a key currently in the map, remove the key/value
	// pair with that key from the map and return true.  Otherwise, make
	// no change to the map and return false.

	bool contains(const KeyType& key) const;
	// Return true if key is equal to a key currently in the map, otherwise
	// false.

	bool get(const KeyType& key, ValueType& value) const;
	// If key is equal to a key currently in the map, set value to the
	// value in the map that that key maps to, and return true.  Otherwise,
	// make no change to the value parameter of this function and return
	// false.

	bool get(int i, KeyType& key, ValueType& value) const;
	// If 0 <= i < size(), copy into the key and value parameters the
	// key and value of one of the key/value pairs in the map and return
	// true.  Otherwise, leave the key and value parameters unchanged and
	// return false.  (See below for details about this function.)

	void swap(Map& other);
	// Exchange the contents of this map with the other one.

private:

	int size(Node* current) const;

	void get(Node* node, int n, int& count, Node*& current) const;

	void minimum(Node* current, Node*& min);
};

bool combine(const Map& m1, const Map& m2, Map& result);
// When this function returns, result must consist of pairs determined by these rules:
// -If a key appears in exactly one of m1 and m2, then result must contain a pair
//  consisting of that key and its corresponding value.
// -If a key appears in both m1 and m2, with the same corresponding value in both,
//  then result must contain a pair with that key and value.
// returns false if there is a key in both maps that have different values

void subtract(const Map& m1, const Map& m2, Map& result);

void print(const Map& m);

#endif /*MAP_H*/