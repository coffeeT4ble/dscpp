#include <iostream>
#include <fstream>
#include "libs/nanodbc/nanodbc.h"

//std::string sName;
std::string db;
std::string user;
std::string pwd;
std::string jecnaServer = "193.85.203.188";
std::string query;

void connectToDB() {
	std::cout << "Enter the database name: ";
	std::cin >> db;
	std::cout << "Enter the username: ";
	std::cin >> user;
	std::cout << "Enter the password: ";
	std::cin >> pwd;
}

void createTemplateTables() {
	query.clear();
	query = "CREATE TABLE Members(id_mem INTEGER PRIMARY KEY, fname_mem NVARCHAR(50) NOT NULL);";
}
void getTableNames() {
	query.clear();
	query = "SELECT TABLE_NAME, TABLE_SCHEMA, TABLE_TYPE FROM INFORMATION_SCHEMA.TABLES;";
}
void ownQuery() {
	query.clear();
	std::cout << "Own Query:" << std::endl;
	std::cin >> query;
}
void txtToDB() {
	query.clear();
	std::string filePath = "txt/query.txt.txt";
	std::ifstream file(filePath);
	if (!file.is_open()) {
		std::cerr << "NAH" << std::endl;
		return;
	}
	std::string line;
	while (std::getline(file, line)) {
		std::cout << line << std::endl;
		query += line;
	}
	file.close();
}

int main()
{//ignore the testing code
	//std::cout << "Enter the server name: ";
	//std::cin >> sName;
	/*std::cout << "Enter the database name: ";
	std::cin >> db;
	std::cout << "Enter the username: ";
	std::cin >> user;
	std::cout << "Enter the password: ";
	std::cin >> pwd;


	/*nanodbc::result res = execute(conn, NANODBC_TEXT("SELECT * FROM dbo.employees"));
	while (res.next()) {
		std::cout << res.get<int>(0) << std::endl;
	}
	return 0;*/

	//connectToDB();

	/*try {
		nanodbc::connection conn(NANODBC_TEXT("Driver={ODBC Driver 17 for SQL Server}; Server=" + jecnaServer + "; Database=" + db + "; UID=" + user + "; PWD=" + pwd));
		if (conn.connected() == 1) {
			std::cout << "connected\n";
		}
		else { std::cout << "error"; }
	}
	catch (const nanodbc::database_error& e) {
		std::cout << "invalid something... figure it out";
	}*/
	std::cout << query << std::endl;
	connectToDB();
	try {
		nanodbc::connection conn(NANODBC_TEXT("Driver={ODBC Driver 17 for SQL Server}; Server=" + jecnaServer + "; Database=" + db + "; UID=" + user + "; PWD=" + pwd));
		if (conn.connected() == 1) {
			std::cout << "connected\n";
		}
		else { std::cout << "error"; }
		std::string c;
		std::cin >> c;
		if (c == "allT") {
			getTableNames();
			nanodbc::result res = nanodbc::execute(conn, NANODBC_TEXT(query));
			while (res.next()) {
				std::cout << res.get<std::string>(0) << " "
					<< res.get<std::string>(1) << " "
					<< res.get<std::string>(2) << std::endl;
			}
		}
		else if (c == "createT") {
			createTemplateTables();
			nanodbc::result res = nanodbc::execute(conn, NANODBC_TEXT(query));
			while (res.next()) {
				std::cout << res.get<std::string>(0) << " "
					<< res.get<std::string>(1) << " "
					<< res.get<std::string>(2) << std::endl;
			}
		}
		else if (c == "ownQ") {
			ownQuery();
			nanodbc::result res = nanodbc::execute(conn, NANODBC_TEXT(query));
			while (res.next()) {
				std::cout << res.get<std::string>(0) << " "
					<< res.get<std::string>(1) << " "
					<< res.get<std::string>(2) << std::endl;
			}
		}
		else if (c == "txtQ") {
			txtToDB();
			nanodbc::result res = nanodbc::execute(conn, NANODBC_TEXT(query));
			while (res.next()) {
				std::cout << res.get<std::string>(0) << " "
					<< res.get<std::string>(1) << " "
					<< res.get<std::string>(2) << std::endl;
			}
		}
		else if (c == "exit") {
			return 0;
		}
		else {
			std::cout << "invalid command";
		}
	}
	catch (const nanodbc::database_error& e) {
		std::cerr << "Database error: " << e.what() << "\n";
		std::cerr << "SQL State: " << e.state() << "\n";
		std::cerr << "Native Error Code: " << e.native() << "\n";
	}
	catch (const std::exception& e) {
		std::cerr << "Standard exception: " << e.what() << "\n";
	}
	catch (...) {
		std::cerr << "Unknown error occurred\n";
	}
}

