// TableManager class source code

#include <ctime>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <exception>
#include "../include/common.hpp"
#include "../include/TableManager.hpp"

void TableManager::package_transmit(const std::vector<Employee>& employees)
{
	if (employees.empty())
		throw std::runtime_error("package to send is empty");

	size_t req_size = 60;

	for (const Employee& employee : employees)
	{
		req_size += 11;
		req_size += employee.get_fullname().size();
		req_size += employee.get_birthdate().size();
		req_size += employee.get_gender().size();
	}
		
	std::string request;
		
	request.reserve(req_size + 1);

	request += "INSERT INTO employees(fullname,birthdate,gender) VALUES";
		
	for (const Employee& employee : employees)
	{
		request += "('";
		request += employee.get_fullname();
		request += "','";
		request += employee.get_birthdate(); 
		request += "','";
		request += employee.get_gender();
		request += "'),";
	}

	request.pop_back();

	exec_sql_request(request);

	std::cout << employees.size() << " employee package has been transmited" << std::endl;
}

std::string TableManager::generate_birthdate()
{
	int day   = rand() % 28 + 1;
	int month = rand() % 12 + 1;
	int year  = rand() % 30 + 1970;

	return std::to_string(year) + '-' + std::to_string(month) + '-' + std::to_string(day);	
}

void TableManager::create_employees_db()
{
	std::string request = "CREATE TABLE employees (id SERIAL PRIMARY KEY, fullname VARCHAR(50), birthdate DATE, gender VARCHAR(6))";

	exec_sql_request(request);

	std::cout << "table has been created successfully" << std::endl;
}

void TableManager::insert_employee(const std::string& fullname, const std::string& birthdate, const std::string& gender)
{
	Employee employee(fullname, birthdate, gender);

	employee.save_into_db();
}

void TableManager::show_employees()
{
	std::string request = "SELECT DISTINCT ON (fullname, birthdate) * FROM employees ORDER BY fullname";

	pqxx::result result = exec_sql_request(request);
		
	if (result.empty())
		throw std::runtime_error("request results is empty");

	for (const pqxx::row &row : result)
	{
		Employee employee(row[1].c_str(), row[2].c_str(), row[3].c_str());

		std::cout << std::left << std::setw(50) << employee.get_fullname() << employee.get_birthdate() << '\t'
			 << std::left << std::setw(10) <<  employee.get_gender()  << employee.calculate_age() << std::endl;
	}
}

void TableManager::insert_1M_employees()
{
	std::ifstream file("../data/dataset.txt");

	if (!file.is_open())
		throw std::runtime_error("cannot open dataset file");

	size_t vec_size = 1000000;

	std::vector<Employee> employees;
		
	employees.reserve(vec_size + 1);

	std::string line;

	srand(time(NULL));

	for (int i = 0; i < vec_size && getline(file, line); i++)
	{
		size_t delpos = line.find(',');
		
		if (delpos == std::string::npos)
			throw std::runtime_error("insert_1M_employees(): aborted: no delpos on iter " + std::to_string(i));

		employees.emplace_back(line.substr(0, delpos), generate_birthdate(), line.substr(delpos + 1));
			
		line.clear();
	}

	file.close();

	package_transmit(employees);
}

void TableManager::insert_100_F_male()
{
	std::ifstream file("../data/dataset.txt");

	if (!file.is_open())
		throw std::runtime_error("cannot open dataset file");

	srand(time(NULL));
	
	std::string line;
	std::vector<Employee> employees;

	int count = 0;

	while (count < 100 && getline(file, line))
	{
		if (line[0] != 'F' && line[0] != 'f')
		{
			line.clear();
			continue;
		}

		size_t delpos = line.find(',');

		if (delpos == std::string::npos)
			throw std::runtime_error("insert_100_F_male(): aborted: no delpos");

		if (line.substr(delpos + 1) != "male")
		{
			line.clear();
			continue;
		}
			
		employees.emplace_back(line.substr(0, delpos), generate_birthdate(), line.substr(delpos + 1));
			
		line.clear();
		
		count++;
	}

	file.close();

	package_transmit(employees);
}

void TableManager::show_F_male()
{
	std::string request = "SELECT * FROM employees WHERE fullname LIKE 'F%' AND gender='male'";

	pqxx::result result = exec_sql_request(request);

	if (result.empty())
		throw std::runtime_error("request results is empty");

	for (const pqxx::row &row : result)
		std::cout << std::left << std::setw(40) << row[1].c_str() << row[2].c_str() << '\t' << std::left << std::setw(10) << row[3].c_str() << std::endl;
	
	request = "EXPLAIN ANALYZE " + request;

	result = exec_sql_request(request);

	std::cout << "\n==================== QUERY PLAN ====================\n" << std::endl;

	for (const pqxx::row &row : result)
		std::cout << row[0].c_str() << std::endl;
}

/* _EOF_ */