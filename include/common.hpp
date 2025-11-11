// common.h - some common funcs to use in Employee and TableManager class impls

#ifndef COMMON_HPP
#define COMMON_HPP

#include <string>
#include <pqxx/pqxx>

const std::string connection_request = "dbname=postgres user=postgres password= host=localhost port=5432";

pqxx::result exec_sql_request(std::string_view);

void current_date(int&, int&, int&);

#endif /* COMMON_HPP */