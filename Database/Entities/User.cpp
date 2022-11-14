#include "User.h"

User::User(unsigned int id, const std::string& name)
	: id(id),
	name(name)
{}

std::string User::GetName() const {
	return name;
}

unsigned int User::GetId() const {
	return id;
}

void User::SetName(const std::string& name) {
	this->name = name;
}

void User::SetId(unsigned int id) {
	this->id = id;
}
