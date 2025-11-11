/*
 * main.cpp
 * EmployeeTableManager programm
 * Programm works in different modes (1, 2, 3, 4, 5)
 * 
 * -std=c++17
 * -lpqxx
 */

#include <string>
#include <iostream>
#include <exception>
#include "../include/TableManager.hpp"

void show_usage();

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "No mode is specified" << std::endl;
		show_usage();
		return 1;
	}

	std::string argv1(argv[1]);
	
	if (argv1 != "1" && argv1 != "2" && argv1 != "3" && argv1 != "4" && argv1 != "5")
	{
		std::cerr << "No such mode" << std::endl;
		show_usage();
		return 1;
	}

	TableManager manager;

	try
	{
		int mode = std::stoi(argv1);

		if (mode != 2 && argc > 2)
		{
			std::cerr << "too many arguments for " << argv1 << " mode" << std::endl;
			show_usage();
			return 1;
		}

		else if (mode == 2 && argc > 5)
		{
			std::cerr << "too many arguments for " << argv1 << " mode" << std::endl;
			show_usage();
			return 1;
		}

		else if (mode == 2 && argc < 5)
		{
			std::cerr << "too few arguments for " << argv1 << " mode" << std::endl;
			show_usage();
			return 1;
		}

		else { }

		switch (mode)
		{
			case 1: 
				manager.create_employees_db();
				break;

			case 2:
				manager.insert_employee(argv[2], argv[3], argv[4]);
				break;
			
			case 3:
				manager.show_employees(); 
				break;
			
			case 4: 
				manager.insert_1M_employees();
				manager.insert_100_F_male();
				break;

			case 5:
				manager.show_F_male();
				break;
		}
	}

	catch (const std::exception &exc)
	{
		std::cerr << exc.what() << std::endl;
		return 1;
	}

	return 0;
}

void show_usage()
{
	std::cout << "Usage: ./EmployeesTableManager <mode> [options]\n\n"
		 << "Modes:\n" 
		 << "  1  -  create employees table\n"
		 << "  2  -  insert new employee | <fullname>, <birthdate> as YYYY-MM-DD, <gender> as male/female\n"
		 << "  3  -  show all employees unique fullname + birthdate\n"
		 << "  4  -  insert 1,000,000 employees + 100 male employees fullname starts with 'F'\n"
		 << "  5  -  show all male employees fullname starts with 'F'\n\n";
}

/* _EOF_ */