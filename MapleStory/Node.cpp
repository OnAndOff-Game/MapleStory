#include "pch.h"
#include "Node.h"

using namespace rapidxml;

Node::Node()
{
}

Node::Node(const Node& n) : node(n.node)
{
}

Node::Node(xml_node<char>* n) : node(n)
{
}

Node::Node(const char* fileName)
{
	xmlFile = new rapidxml::file<char>(fileName);
	xmlDoc = new rapidxml::xml_document<char>();
	xmlDoc->parse<0>(xmlFile->data());
	node = xmlDoc->first_node();

	// Release();
}

Node::~Node()
{
}

std::string Node::GetValueString()
{
	return node->first_attribute()->next_attribute()->value();
}

int Node::GetValueInt()
{
	return atoi(node->first_attribute()->next_attribute()->value());
}

float Node::GetValueFloat()
{
	return atof(node->first_attribute()->next_attribute()->value());
}

Gdiplus::Point Node::GetValuePoint()
{
	Gdiplus::Point pt;
	pt.X = GetValueInt();
	pt.Y = atoi(node->first_attribute()->next_attribute()->next_attribute()->value());
	return pt;
}

const char* Node::GetName()
{
	return node->first_attribute()->value();
}

bool Node::IsNull()
{
	if (node == nullptr)
		return true;
	else
		return false;
}

void Node::ChildList()
{
	for (auto n = node->first_node(); n; n = n->next_sibling())
	{
		std::cout << n->first_attribute()->value() << std::endl;
	}
}

void Node::Release()
{
	if (xmlDoc != nullptr)
		delete xmlDoc;

	if (xmlFile != nullptr)
		delete xmlFile;	
}


Node Node::begin() const
{
	return (node->first_node());
}

Node Node::end() const
{
	return (node->last_node());
}

void Node::operator=(const Node& o)
{
	node = o.node;
}

bool Node::operator==(Node const& o) const
{
	return node == o.node;
}

bool Node::operator!=(Node const& o) const
{
	return node != o.node;
}

Node& Node::operator++(int)
{
	node = node->next_sibling();
	return *this;
}

Node Node::operator[](const char* name)
{
	for (xml_node<char>* n = node->first_node(); n; n = n->next_sibling())
	{
		if (!strcmp(n->first_attribute()->value(), name))
		{
			return { n };
		}
	}
	return Node((xml_node<char>*)nullptr);
}

Node Node::operator[](int index)
{
	char buffer[20];
	_itoa_s(index, buffer, 10);
	return this->operator[](buffer);
}

Node Node::operator[](Node* o)
{
	return operator[](o->GetValueString().c_str());
}