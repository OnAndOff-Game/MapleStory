#pragma once
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

using namespace rapidxml;

class Node
{
public:
	Node();
	Node(const Node& n);
	Node(rapidxml::xml_node<char>* n);
	Node(const char* fileName);
	~Node();

	std::string GetValueString();
	int GetValueInt();
	float GetValueFloat();
	Gdiplus::Point GetValuePoint();
	const char* GetName();
	bool IsNull();

	void ChildList();

	void Release();

	Node begin() const;
	Node end() const;

	Node& operator*() { return *this; }
	void operator=(const Node& o);
	bool operator==(Node const& o) const;
	bool operator!=(Node const& o) const;
	Node& operator++(int);
	Node operator[](const char* name);
	Node operator[](int index);
	Node operator[](Node* o);

	operator bool() const { return node ? true : false; }

private:
	rapidxml::xml_node<>* node;
	rapidxml::xml_document<>* xmlDoc;
	rapidxml::file<>* xmlFile;
};