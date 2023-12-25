#include "rapidxml/rapidxml.hpp"
#include "rge.hpp"

using namespace rapidxml;

#define STR_EQUAL(A, B) (strcmp(A, B) == 0)

static bool read_attribute_int(xml_node<>* node, const char* name, int* value) {
	if(node == nullptr)
		return false;

	xml_attribute<>* attribute = node->first_attribute(name);
	if(attribute == nullptr)
		return false;

	try {
		*value = std::stoi(attribute->value());
		return true;
	} catch(std::exception e) {
		return false;
	}
}

static bool read_attribute_float(xml_node<>* node, const char* name, float* value) {
	if(node == nullptr)
		return false;

	xml_attribute<>* attribute = node->first_attribute(name);
	if(attribute == nullptr)
		return false;

	try {
		*value = std::stof(attribute->value());
		return true;
	} catch(std::exception e) {
		return false;
	}
}

static bool read_attribute_str(xml_node<>* node, const char* name, char** str) {
	if(node == nullptr)
		return false;

	xml_attribute<>* attribute = node->first_attribute(name);
	if(attribute == nullptr)
		return false;

	*str = attribute->value();
	return true;
}

static bool read_attribute_bool(xml_node<>* node, const char* name, bool* value) {
	if(node == nullptr)
		return false;

	xml_attribute<>* attribute = node->first_attribute(name);
	if(attribute == nullptr)
		return false;

	if(
		STR_EQUAL(attribute->value(), "true") ||
		STR_EQUAL(attribute->value(), "TRUE") ||
		STR_EQUAL(attribute->value(), "True") ||
		STR_EQUAL(attribute->value(), "1")
	) {
		*value = true;
		return true;
	} else if(
		STR_EQUAL(attribute->value(), "false") ||
		STR_EQUAL(attribute->value(), "FALSE") ||
		STR_EQUAL(attribute->value(), "False") ||
		STR_EQUAL(attribute->value(), "0")
	) {
		*value = false;
		return true;
	} else {
		return false;
	}
}