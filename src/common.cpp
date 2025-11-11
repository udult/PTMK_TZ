// common.cpp - common funcs source code

#include <ctime>
#include <exception>
#include "../include/common.hpp"

pqxx::result exec_sql_request(std::string_view request)
{
	pqxx::connection cx(connection_request);

	if (!cx.is_open())
		throw std::runtime_error("cannot connect to postgres db");

	pqxx::work wx(cx);

	pqxx::result result = wx.exec(request);
	wx.commit();

	return result;
}

void current_date(int &year, int &month, int &day)
{
	time_t now  = time(NULL);
	tm *nowtime = localtime(&now);
	
	day   = nowtime->tm_mday + 0;
	month = nowtime->tm_mon  + 1;
	year  = nowtime->tm_year + 1900;
}

/**/