#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "libs/nanodbc/nanodbc.h"

//std::string sName;
std::string db;
std::string user;
std::string pwd;
std::string jecnaServer = "193.85.203.188";
std::string query;
std::vector<std::string> tables;
std::vector<std::string> at;
std::string tName;
bool loggedIn = false;
bool testing = true;

void loginExitCode() {
	if (db == "0000" || user == "0000" || pwd == "0000") {
		exit(0);
	}
}
void connectToDB() {
	if (!loggedIn) {
		std::cout << "Enter the database name: ";
		std::cin >> db;
		loginExitCode();
		std::cout << "Enter the username: ";
		std::cin >> user;
		loginExitCode();
		std::cout << "Enter the password: ";
		std::cin >> pwd;
		loginExitCode();
	}
}

/*void createTemplateTables() {
	query.clear();
	query = "CREATE TABLE Members(id_mem INTEGER PRIMARY KEY, fname_mem NVARCHAR(50) NOT NULL);";
}*/
void getTableNames() {
	query.clear();
	query = "SELECT TABLE_NAME, TABLE_SCHEMA, TABLE_TYPE FROM INFORMATION_SCHEMA.TABLES;";
}
void ownQuery() {
	query.clear();
	std::string input;
	std::cout << "Own Query:" << std::endl;
	std::cin >> input;
	query = input;
	std::cout << query;
}
void txtToDB(std::string filePath) {
	query.clear();
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
	std::cout << "Done, but make sure to check using allT" << std::endl;
	file.close();
}
void csvT(std::string filePath) {
	query.clear();
	std::ifstream file(filePath);
	if (!file.is_open()) {
		std::cerr << "NAH" << std::endl;
		return;
	}
	std::string line;
	std::vector<std::vector<std::string>> data;
	while (std::getline(file, line)) {
		std::stringstream ss(line);
		std::string attribute;
		std::vector<std::string> lineData;
		while (std::getline(ss, attribute, ',')) {
			if (attribute == "autoI") {
				attribute = "IDENTITY(1,1)";
			}
			lineData.push_back(attribute + " ");
		}
		data.push_back(lineData);
	}
	file.close();
	std::cout << "CSV Data:" << std::endl;
	for (const auto& lineData : data) {
		for (const auto& attr : lineData) {
			std::cout << attr << " ";
		}
		std::cout << std::endl;
	}
	std::string tableName;
	std::cout << "Enter the table name: ";
	std::cin >> tableName;
	query = "CREATE TABLE " + tableName + "(";
	for (int j = 0; j < data.size(); j++) {
		for (int i = 0; i < data[0].size(); i++) {
			query += data[0][i];
			//std::cout << " ";
		}
	}
	query += ");";
	std::cout << query;
}
void userCsvInsert() {
	query.clear();
	std::string filePath;
	std::string choice;
	std::cout << "[1] for inserting into Members\n[2] for inserting into Trainers\n~";
	std::cin >> choice;
	if (choice == "1") {
		filePath = "csv/members.csv";
		query = "insert into Members(FirstName, LastName, Email, PhoneNumber, DateOfBirth, MembershipID, JoinDate) values(";
		std::ifstream file(filePath);
		if (!file.is_open()) {
			std::cerr << "NAH" << std::endl;
			return;
		}
		std::string line;
		std::vector<std::vector<std::string>> data;
		while (std::getline(file, line)) {
			std::stringstream ss(line);
			std::string attribute;
			std::vector<std::string> lineData;
			while (std::getline(ss, attribute, ',')) {
				lineData.push_back(attribute);
			}
			data.push_back(lineData);
		}
		for (int i = 0; i < data.size(); i++) {
			for (int j = 0; j < data[0].size() - 1; j++) {
				data[i][j] += ", ";

			}
		}
		file.close();
		for (int j = 0; j < data.size(); j++) {
			for (int i = 0; i < data[0].size(); i++) {
				query += data[j][i];
			}
			query += ")";
			if (j != data.size() - 1) {
				query += ", (";
			}
		}
		query += ";";
		std::cout << query;
	}
	else if (choice == "2") {
	}
	else {
		std::cout << "invalid choice";
	}
}
void csvInsert(std::string filePath) {
	getTableNames();
	query.clear();
	query = "INSERT INTO " + tName + "(";
	for (int i = 1; i < at.size(); i++) {
		query += at[i];
		if (i != at.size() - 1) {
			query += ", ";
		}
		else {
			query += ") VALUES (";
		}
	}
	std::cout << query;
	//query.clear();
	std::ifstream file(filePath);
	if (!file.is_open()) {
		std::cerr << "NAH" << std::endl;
		return;
	}
	std::string line;
	std::vector<std::vector<std::string>> data;
	while (std::getline(file, line)) {
		std::stringstream ss(line);
		std::string attribute;
		std::vector<std::string> lineData;
		while (std::getline(ss, attribute, ',')) {
			lineData.push_back(attribute);
		}
		data.push_back(lineData);
	}
	for (int i = 0; i < data.size(); i++) {
		for (int j = 0; j < data[0].size() - 1; j++) {
			data[i][j] += ", ";

		}
	}
	file.close();
	/*std::cout << "CSV Data:" << std::endl;
	for (const auto& lineData : data) {
		for (const auto& attr : lineData) {
			std::cout << attr << " ";
		}
		std::cout << std::endl;
	}*/
	for (int j = 0; j < data.size(); j++) {
		for (int i = 0; i < data[0].size(); i++) {
			query += data[j][i];
			//std::cout << " ";
		}
		query += ")";
		if (j != data.size() - 1) {
			query += ", (";
		}
	}
	query += ";";
	std::cout << query;
}
void attrAlign() {
	std::cout << "If this ends up being empty or seems like it has not been updated, run allT and then try again" << std::endl;
	std::vector<std::string> a;
	query.clear();
	std::cout << "Enter the table name: ";
	std::cin >> tName;
	query = "SELECT * FROM sys.columns WHERE object_id = OBJECT_ID('dbo." + tName + "')";
}
void userAttr() {
	query.clear();
	query = "SELECT * FROM sys.columns WHERE object_id = OBJECT_ID('dbo.Members')";
}
void insertData(nanodbc::result r) {
	at.push_back(r.get<std::string>(1));
	std::cout << r.get<std::string>(1) << std::endl;
}
int main()
{
	std::cout << query << std::endl;
	std::string c;
	while (1) {
		connectToDB();
		while (c != "exit") {
			try {
				nanodbc::connection conn(NANODBC_TEXT("Driver={ODBC Driver 17 for SQL Server}; Server=" + jecnaServer + "; Database=" + db + "; UID=" + user + "; PWD=" + pwd));
				if (conn.connected() == 1) {
					std::cout << "\nconnected\n";
					loggedIn = true;
				}
				else { std::cout << "\nerror\n"; return 0; }
				while (1) {
					std::cout << "\n[" << user << "@" << "dscpp" << "]$ ";
					std::cin >> c;
					if (c == "allT" && !testing) {
						getTableNames();
						tables.clear();
						nanodbc::result res = nanodbc::execute(conn, NANODBC_TEXT(query));
						while (res.next()) {
							std::cout << res.get<std::string>(0) << " "
								<< res.get<std::string>(1) << " "
								<< res.get<std::string>(2) << std::endl;
							tables.push_back(res.get<std::string>(0));
						}
						break;
					}
					else if (c == "ownQ" && !testing) {
						ownQuery();
						nanodbc::result res = nanodbc::execute(conn, NANODBC_TEXT(query));
						while (res.next()) {
							std::cout << res.get<std::string>(0) << " "
								<< res.get<std::string>(1) << " "
								<< res.get<std::string>(2) << std::endl;
						}
						break;
					}
					else if (c == "txtQ" && !testing) {
						std::string fp;
						std::cout << "Enter the file path: ";
						std::cin >> fp;
						txtToDB(fp);
						nanodbc::result res = nanodbc::execute(conn, NANODBC_TEXT(query));
						while (res.next()) {
							std::cout << res.get<std::string>(0) << " "
								<< res.get<std::string>(1) << " "
								<< res.get<std::string>(2) << std::endl;
						}
						break;
					}
					else if (c == "template" && !testing) {
						std::string choice;
						std::cout << "1 for template tables, 2 for template data: ";
						std::cin >> choice;
						if (choice == "1") {
							txtToDB("txt/template.txt");
						}
						else if (choice == "2") {
							txtToDB("txt/inserts.txt");
						}
						else {
							std::cout << "invalid choice";
							break;
						}
						nanodbc::result res = nanodbc::execute(conn, NANODBC_TEXT(query));
						while (res.next()) {
							std::cout << res.get<std::string>(0) << " "
								<< res.get<std::string>(1) << " "
								<< res.get<std::string>(2) << std::endl;
						}
						break;
					}
					else if (c == "attr" && !testing) {
						attrAlign();
						nanodbc::result res = nanodbc::execute(conn, NANODBC_TEXT(query));
						while (res.next()) {
							std::cout << res.get<std::string>(0) << " "
								<< res.get<std::string>(1) << " "
								<< res.get<std::string>(2) << std::endl;
							insertData(res);
						}
						break;
					}
					else if (c == "csvI" && !testing) {
						at.clear();
						attrAlign();
						nanodbc::result res = nanodbc::execute(conn, NANODBC_TEXT(query));
						while (res.next()) {
							std::cout << res.get<std::string>(0) << " "
								<< res.get<std::string>(1) << " "
								<< res.get<std::string>(2) << std::endl;
							insertData(res);
						}
						std::string fp;
						std::cout << "Enter the file path: ";
						std::cin >> fp;
						csvInsert(fp);
						nanodbc::result res2 = nanodbc::execute(conn, NANODBC_TEXT(query));
						while (res2.next()) {
							std::cout << res2.get<std::string>(0) << " "
								<< res2.get<std::string>(1) << " "
								<< res2.get<std::string>(2) << std::endl;
						}
					}
					else if (c == "delete" && !testing) {
						getTableNames();
						nanodbc::result res = nanodbc::execute(conn, NANODBC_TEXT(query));
						while (res.next()) {
							std::cout << res.get<std::string>(0) << " "
								<< res.get<std::string>(1) << " "
								<< res.get<std::string>(2) << std::endl;
						}
						attrAlign();
						res = nanodbc::execute(conn, NANODBC_TEXT(query));
						while (res.next()) {
							std::cout << res.get<std::string>(1) << std::endl;
							at.push_back(res.get<std::string>(1));
						}
						std::cout << std::endl<< tName << std::endl;
                        query.clear();
                        query = "select * from [dbo].[" + tName + "];";
                        res = nanodbc::execute(conn, NANODBC_TEXT(query));
						auto columns = res.columns();
                        while (res.next()) {
							for (int i = 0; i < columns; ++i) {
								std::cout << res.get<std::string>(i, "NULL") << "\t";
							}
							std::cout << std::endl;
                        }
						std::string id;
						std::cout << "Enter the id of the row you want to delete: ";
						std::cin >> id;
						query.clear();
						query = "DELETE FROM " + tName + " WHERE " + at[0] + " = " + id + ";";
						nanodbc::result res2 = nanodbc::execute(conn, NANODBC_TEXT(query));
					}
					else if (c == "selectAll") {
						getTableNames();
						tables.clear();
						nanodbc::result res = nanodbc::execute(conn, NANODBC_TEXT(query));
						while (res.next()) {
							std::cout << res.get<std::string>(0) << " "
								<< res.get<std::string>(1) << " "
								<< res.get<std::string>(2) << std::endl;
							tables.push_back(res.get<std::string>(0));
						}
						for (int i = 0; i < tables.size(); i++) {
							query.clear();
							query = "select * from [dbo].[" + tables[i] + "];";
							nanodbc::result res = nanodbc::execute(conn, NANODBC_TEXT(query));
							auto columns = res.columns();
							std::cout << tables[i] << std::endl;
							while (res.next()) {
								for (int i = 0; i < columns; ++i) {
									std::cout << res.get<std::string>(i, "NULL") << "\t";
								}
								std::cout << std::endl;
							}
							std::cout << std::endl;
						}
					}
					else if (c == "dropT" && !testing) {
						query.clear();
						std::string name;
						std::cout << "Enter the table name: ";
						std::cin >> name;
						query = "DROP TABLE " + name + ";";
						nanodbc::result res = nanodbc::execute(conn, NANODBC_TEXT(query));
					}
					else if (c == "new") {
						std::vector<std::string> input;
						userAttr();
						nanodbc::result res = nanodbc::execute(conn, NANODBC_TEXT(query));
						while (res.next()) {
							insertData(res);
						}
						for (int i = 1; i < at.size(); i++) {
							std::string in;
							std::cout << "your " << at[i] << ": ";
							std::cin >> in;
							input.push_back(in);
						}
						query.clear();
						query = "INSERT INTO " + tName + "(";
						for (int i = 1; i < at.size(); i++) {
							query += at[i];
							if (i != at.size() - 1) {
								query += ", ";
							}
							else {
								query += ") VALUES (";
							}
						}
						query += "'" + input[0] + "'" + "'" + input[1] + "'" + "'" + input[2] + "'" + input[3] + "'" + input[4] + "'" + input[5] +
							"'" + input[6] + "');";

					}
					else if (c == "csvIns") {
						userCsvInsert();
						nanodbc::result res = nanodbc::execute(conn, NANODBC_TEXT(query));
					}
					else if (c == "help") {
						std::cout << "allT - lists all tables and updates the tables vector\nownQ - write a query in the command line [does not work in testing mode]\ntxtQ - allows you to run a sql query in a txt file\ntemplate - creates a database for testing [reccomended for testers]\nattr - lists all attributes in a chosen table\ncsvI - allows csv input\ndelete - deletes a chosen row in a chosen table\nselectAll - selects everything in every table and writes it out in an organised matter\ndropT - drops the chosen tablen\n"
							<< "However, you are in testing/user mode, you're commands consist of:\n" << std::endl;
						break;
					}
					else if (c == "exit") {
						return 0;
					}
					else {
						std::cout << "invalid command";
						break;
					}
				}
			}
			catch (const nanodbc::database_error& e) {
				std::cerr << "Database error: " << e.what() << "\n";
				std::cerr << "SQL State: " << e.state() << "\n";
				std::cerr << "Native Error Code: " << e.native() << "\n";
				break;
			}
			catch (const std::exception& e) {
				std::cerr << "Standard exception: " << e.what() << "\n";
				break;
			}
			catch (...) {
				std::cerr << "Unknown error occurred\n";
				break;
			}
		}
	}
	//use later for a clean writout for table names
	//for (int i = 0; i < tables.size(); i++) {
		//std::cout << tables[i] << std::endl;
	//}
}

