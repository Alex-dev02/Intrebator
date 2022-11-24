#include "../../include/Entities/Match.hpp"

Match::Match(std::uint32_t id, std::string date)
	: m_id(id), m_date(date)
{}

const std::uint32_t& Match::GetId() const{
	return m_id;
}

const std::string& Match::GetDate() const{
	return m_date;
}

void Match::SetId(std::uint32_t id){
	m_id = id;
}

void Match::SetDate(std::string date){
	m_date = date;
}
