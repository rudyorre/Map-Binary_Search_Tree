// updated 9:47pm 3-12-2020
#ifndef MAP_CPP
#define MAP_CPP
#include "Map.h"
#include <iostream>
#include <iomanip>
using namespace std;

Map::Map()
{
	root = nullptr;
}

Map::Map(const Map& rhs)
{
	for (int i = 0; i < rhs.size(); i++)
	{
		KeyType key;
		ValueType value;

		rhs.get(i, key, value);

		insert(key, value);
	}
}

Map::~Map()
{
	while (!empty())
	{
		KeyType key;
		ValueType value;

		get(0, key, value);
		erase(key);
	}
}

const Map& Map::operator=(const Map& rhs)
{
	bool isSame = true;

	if (rhs.size() == size())
	{
		for (int i = 0; i < size(); i++)
		{
			KeyType key, rKey;
			ValueType value, rValue;

			get(i, key, value);
			rhs.get(i, rKey, rValue);

			if (key != rKey || value != rValue)
			{
				isSame = false;
				break;
			}
		}
		if (isSame)
		{
			return *this;
		}
	}

	while (!empty())
	{
		KeyType key;
		ValueType value;

		get(0, key, value);
		erase(key);
	}

	for (int i = 0; i < rhs.size(); i++)
	{
		KeyType key;
		ValueType value;

		rhs.get(i, key, value);

		insert(key, value);
	}

	return rhs;
}

bool Map::empty() const
{
	if (root == nullptr)
	{
		return true;
	}
	return false;
}

int Map::size() const
{
	return size(root);
}

bool Map::insert(const KeyType& key, const ValueType& value)
{
	Node* newNode = new Node;
	newNode->key = key;
	newNode->value = value;
	newNode->right = nullptr;
	newNode->left = nullptr;

	if (root == nullptr)
	{
		root = newNode;
		return true;
	}
	else if (!contains(key))
	{
		Node* current = root;
		Node* prev = root;
		int left;

		while (current != nullptr)
		{
			if (key < current->key)
			{
				prev = current;
				current = current->left;
				left = 1;
			}
			else if (key >= current->key)
			{
				prev = current;
				current = current->right;
				left = 0;
			}
		}

		if (left == 1)
		{
			prev->left = newNode;
		}
		else
		{
			prev->right = newNode;
		}
		return true;
	}

	delete newNode;
	return false;
}

bool Map::update(const KeyType& key, const ValueType& value)
{
	if (root != nullptr)
	{
		Node* current = root;

		while (current != nullptr)
		{
			if (key < current->key)
			{
				current = current->left;
			}
			else if (key > current->key)
			{
				current = current->right;
			}
			else if (key == current->key)
			{
				if (value == current->value)
				{
					return false;
				}
				current->value = value;
				return true;
			}
		}
	}
	return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
	if (contains(key))
	{
		update(key, value);
	}
	else
	{
		insert(key, value);
	}
	return true;
}

bool Map::erase(const KeyType& key)
{
	Node* garbage = nullptr;
	Node* parent = nullptr;

	if (root != nullptr)
	{
		Node* current = root;
		Node* prev = root;

		while (current != nullptr)
		{
			if (key < current->key)
			{
				prev = current;
				current = current->left;
			}
			else if (key > current->key)
			{
				prev = current;
				current = current->right;
			}
			else if (key == current->key)
			{
				parent = prev;
				garbage = current;
				break;
			}
		}
	}

	if (garbage == nullptr)
	{
		return false;
	}

	if (garbage->numChildren() == 0) // if it is a leaf
	{
		if (garbage != root)
		{
			if (parent->left == garbage)
			{
				parent->left = nullptr;
			}
			else
			{
				parent->right = nullptr;
			}
		}
		else // if tree only has root, set it to nullptr
		{
			root = nullptr;
		}
		delete garbage;
	}
	else if (garbage->numChildren() == 1)
	{
		Node* child = nullptr;

		if (garbage->left != nullptr)
		{
			child = garbage->left;
		}
		else
		{
			child = garbage->right;
		}

		if (garbage != root)
		{
			if (garbage == parent->left)
			{
				parent->left = child;
			}
			else
			{
				parent->right = child;
			}
		}
		else
		{
			root = child;
		}
		delete garbage;
	}
	else // two children
	{
		Node* min = nullptr;
		minimum(garbage, min);

		KeyType minKey = min->key;
		ValueType minValue = min->value;

		erase(min->key);

		garbage->key = minKey;
		garbage->value = minValue;
	}
	return true;
}

bool Map::contains(const KeyType& key) const
{
	if (root != nullptr)
	{
		Node* current = root;

		while (current != nullptr)
		{
			if (key < current->key)
			{
				current = current->left;
			}
			else if (key > current->key)
			{
				current = current->right;
			}
			else if (key == current->key)
			{
				return true;
			}
		}
	}
	return false;
}

bool Map::get(const KeyType& key, ValueType& value) const
{
	if (root != nullptr)
	{
		Node* current = root;

		while (current != nullptr)
		{
			if (key < current->key)
			{
				current = current->left;
			}
			else if (key > current->key)
			{
				current = current->right;
			}
			else if (key == current->key)
			{
				value = current->value;
				return true;
			}
		}
	}
	return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
	static int count = 0;
	i++;
	Node* current = nullptr;
	get(root, i, count, current);
	count = 0;

	if (current != nullptr)
	{
		key = current->key;
		value = current->value;
		return true;
	}

	return false;
}

void Map::swap(Map& other)
{ 
	Node* temp = root;
	root = other.root;
	other.root = temp;
}

// private member functions

int Map::size(Node* current) const
{
	if (current == nullptr)
	{
		return 0;
	}
	return size(current->left) + 1 + size(current->right);
}

void Map::get(Node* node, int i, int& count, Node*& current) const
{
	
	if (node == nullptr)
	{
		return;
	}

	if (count <= i)
	{
		get(node->left, i, count, current);
		count++;

		if (count == i)
		{
			current = node;
		}

		get(node->right, i, count, current);
	}
}

void Map::minimum(Node* current, Node*& min)
{
	current = current->left;
	while (current->right != nullptr)
	{
		current = current->right;
	}
	min = current;
}

// public non-member functions

bool combine(const Map& m1, const Map& m2, Map& result)
{
	bool ret = true;
	result = m1;

	for (int i = 0; i < m2.size(); i++)
	{
		KeyType key;
		ValueType value;
		m2.get(i, key, value);

		if (!result.contains(key))
		{
			result.insert(key, value);
		}
		else
		{
			ValueType resultValue;
			result.get(key, resultValue);

			if (resultValue != value)
			{
				ret = false;
				result.erase(key);
			}
		}
	}

	return ret;
}

void subtract(const Map& m1, const Map& m2, Map& result)
{
	result = m1;

	for (int i = 0; i < m2.size(); i++)
	{
		KeyType key;
		ValueType value;
		m2.get(i, key, value);

		if (result.contains(key))
		{
			result.erase(key);
		}
	}
}

void print(const Map& m)
{
	cout << endl << left << setw(10) << "Key:" << left << setw(10) << "Value:" << endl << endl;

	for (int i = 0; i < m.size(); i++)
	{
		KeyType key;
		ValueType value;
		m.get(i, key, value);
		cout << left << fixed << setprecision(2) << setw(10) << key;
		cout << left << fixed << setprecision(2) << setw(10) << value << endl;
	}
}

#endif /*MAP_CPP*/