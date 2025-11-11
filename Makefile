# PTMK_TZ Makefile
CXX      =  g++
CXXFLAGS = -std=c++17 -c
LDFLAGS  = -lpqxx

SOURCES  = ./src/common.cpp ./src/Employee.cpp ./src/main.cpp ./src/TableManager.cpp

all: compile link
	
compile:
	@mkdir -p bin
	for source in $(SOURCES); do \
		object=bin/$$(basename $$source .cpp).o; \
		$(CXX) $(CXXFLAGS) $$source -o $$object; \
	done

link:
	$(CXX) $(LDFLAGS) ./bin/*.o -o ./bin/EmployeesTableManager $(LDFLAGS)

# install 
install:
	sudo apt install -y postgresql
	sudo apt install -y libpqxx-dev

# delete build directory
clean: 
	@rm -rf ./bin

#