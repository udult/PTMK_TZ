/*
 * Employee.hpp
 *
 * Provides: 
 * - Employee class prot
 * - Method of saving into db
 * - Calculate age method
 * - Data access methods
 */

#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP

#include <string>

class Employee
{
private:
	std::string fullname;
	std::string birthdate;
	std::string gender;

public:
	Employee(const std::string&, const std::string&, const std::string&);

	void save_into_db() const;

	int calculate_age() const;

	const std::string& get_fullname() const;
	
	const std::string& get_birthdate() const;
	
	const std::string& get_gender() const;
};

#endif /* EMPLOYEE_HPP */