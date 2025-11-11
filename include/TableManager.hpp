/*
 * TableManager.hpp
 *
 * Provides:
 * - Package transmit into database
 * - All users scenarios
 */

#ifndef TABLE_MANAGER_HPP
#define TABLE_MANAGER_HPP

#include <string>
#include <vector>

#include "../include/Employee.hpp"

class TableManager
{
private:
	void package_transmit(const std::vector<Employee>&);

	std::string generate_birthdate();

public:
	/* mode 1 */
	void create_employees_db();

	/* mode 2 */
	void insert_employee(const std::string&, const std::string&, const std::string&);

	/* mode 3 */
	void show_employees();

	/* mode 4 */
	void insert_1M_employees();

	void insert_100_F_male();

	/* mode 5 */
	void show_F_male();
};

#endif /* TABLE_MANAGER_HPP */