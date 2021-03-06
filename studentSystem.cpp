
#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <vector>
#include <time.h>


// OBJECTS
class Student {
public:
	std::string surname;
	std::string name;
	std::string numbr;
	std::string gender;

	void create(std::string numb, std::string sname = "N/A", std::string lname = "N/A", std::string  sex = "N/A") {
		surname = sname;
		name = lname;
		numbr = numb;
		gender = sex;
	}

};

class Data_File {
public:
	//create read stream
	std::ifstream inputStream;
	std::string dir;
	std::string file_item;
	int counter = 0;
	std::vector<Student>file_dat;
	
	//Methods
	void promtDirectory() {	// open file requested by user
		system("cls");
		std::cout << "\n\n\n\t\t\t\t\t\t\t\t    enter file name:  ";
		std::cin >> dir;
		inputStream.open(dir); 

		while (inputStream.fail()) { // if directory doesnt exists
			system("cls");
			std::cerr << "\a\n\n\t\t\t\t\t\t\t unable to open file,try adding(.csv): ";
			getline(std::cin, dir);
			inputStream.open(dir);
		}
	}
	
	std::vector<Student> fetchData() {
		while (!inputStream.eof()) {
			Student stud_obj;
			std::string fname,sname,numb,gender;
			getline(inputStream, numb, ',');
			if (numb == "") {
				break;
			}
			getline(inputStream, sname, ',');
			getline(inputStream, fname, ',');
			getline(inputStream, gender, '\n');
			stud_obj.create(numb, sname, fname, gender);
			//push new student to vector
			file_dat.push_back(stud_obj);
		}
		inputStream.close();// close file when done
		
		return file_dat; // return a vector of student objects
	}
	void clear(){
		file_dat.clear();
	}
};

//FUNCTIONS
void printSortedData(std::vector<Student> listA, std::vector<Student> listB) {
	int Amcounter = 0; int Afcounter = 0;
	int Bmcounter = 0; int Bfcounter = 0;
	for (unsigned int i = 0; i < listA.size(); i++) {
		if (listA.at(i).gender == "F") {
			//std::cout << listA.at(i).name<<"\n";
			Afcounter++;
		}
		else {
			//std::cout << listA.at(i).name << "\n";
			Amcounter++;
		}
	}
	for (unsigned int i = 0; i < listB.size(); i++) {
		if (listB.at(i).gender == "F") {
			Bfcounter++;
		}
		else {
			Bmcounter++;
		}
	}
	system("cls");
	std::cout << "\n\n\t\t\t\t\t\t\t\t\tSort algorithm complete...\n\n";
	std::cout << "\t\t\t\t\t\t\t\t -------------- GROUP A ---------------\n\n";
	std::cout << "\t\t\t\t\t\t\t\t |  girls:  [ " << Afcounter << " ]  |  boys :  [ " << Amcounter <<" ] |\n"<<std::endl;
	std::cout << "\t\t\t\t\t\t\t\t --------------------------------------\n\n";
	std::cout << "\t\t\t\t\t\t\t\t -------------- GROUP B ---------------\n\n";
	std::cout << "\t\t\t\t\t\t\t\t |  girls:  [ " << Bfcounter << " ]  |  boys :  [ " << Bmcounter <<" ] |\n" << std::endl;
	std::cout << "\t\t\t\t\t\t\t\t --------------------------------------\n\n";
	std::cout << "\t\t\t\t\t\t\t\t\t Total Students : " << Afcounter + Bfcounter+ Amcounter + Bmcounter <<"\n\a"<<std::endl;
}

void fetch_data(std::vector<Student> &student_list, Data_File &File) {
	File.promtDirectory(); // prompt user to enter file directory

	//store data extracted from file to vector
	student_list = File.fetchData();
}

void sort_students(std::vector<Student> &student_list, std::vector<Student> &A_students, std::vector<Student> &B_students) {
	std::vector<Student>boys, girls;

	//populate male & female vectors
	for (unsigned int i = 0; i < student_list.size(); i++) {
		if (student_list.at(i).gender == "M") {
			boys.push_back(student_list.at(i));
		}
		else {
			girls.push_back(student_list.at(i));
		}
	}

	int div = girls.size() % 2;
	//push female(n) to A female (n+1) to B
	for (unsigned int i = 0; i<girls.size()-1; i+=2) {
		A_students.push_back(girls.at(i));
		B_students.push_back(girls.at(i + 1));
		if (div > 0 && i == girls.size() - 3) {
			A_students.push_back(girls.at(i + 2));
		}
	}
	div = boys.size() % 2;
	//push male(n) to A, male (n+1) to B
	for (unsigned int i = 0; i<boys.size() - 1; i += 2) {
		A_students.push_back(boys.at(i));
		B_students.push_back(boys.at(i + 1));
		if (div > 0 && i == boys.size() - 3) {
			A_students.push_back(boys.at(i + 2));
		}
	}
}

void print_result(std::vector<Student>& listA, std::vector<Student>& listB) {
	std::ofstream outFileA;
	std::ofstream outFileB;

	outFileA.open("listA.csv");
	for (unsigned int i = 0; i < listB.size(); i++) {
		outFileA <<listB.at(i).numbr<<","<<listB.at(i).surname<<" "<<listB.at(i).name<<","<<listB.at(i).gender<<std::endl;
	}
	outFileA.close();

	outFileB.open("listB.csv");
	for (unsigned int i = 0; i < listA.size(); i++) {
		outFileB << listA.at(i).numbr << "," << listA.at(i).surname << " " << listA.at(i).name << "," << listA.at(i).gender << std::endl;
	}
	outFileB.close();
	
	std::cout << "\n\n\t\t\t\t\t\t\t\t-------------------- REPORT -------------------\n";
	std::cout << "\n\n\t\t\t\t\t\t\t\t new files created, listA.csv and listB.csv :) \n";
	std::cout << "\n\n\t\t\t\t\t\t\t\t-----------------------------------------------\n";
	system("pause");

}

void clear(std::vector<Student> &student_list,std::vector<Student>&A_students, std::vector<Student>&B_students, Data_File &File) {
	student_list.clear();
	File.clear();
	A_students.erase(A_students.begin(), A_students.begin() + A_students.size());
	B_students.erase(B_students.begin(), B_students.begin() + B_students.size());
}

void main_menu(std::vector<Student> &student_list, Data_File &File, std::vector<Student>A_students, std::vector<Student>B_students) {
	system("cls");
	int choice;
	std::cout
		<< "\n\t\t\t\t\t\t\t\t----------------------------------------\n"
		<< "\n\t\t\t\t\t\t\t\t---------- STUDENT SORT SYSTEM ---------\n"
		<< "\n\t\t\t\t\t\t\t\t----------------------------------------\n"
		<< "\n\t\t\t\t\t\t\t\t------------- CURRENT STATUS -----------\n"
		<< "\n\t\t\t\t\t\t\t\t\t   Students in A  : " << A_students.size() << "\n"
		<< "\t\t\t\t\t\t\t\t\t   Students in B  : " << B_students.size() << "\n"
		<< "\t\t\t\t\t\t\t\t\t   Total Students : " << student_list.size() << "\n"
		<< "\t\t\t\t\t\t\t\t\t ----------------------\n"
		<< "\n\t\t\t\t\t\t\t\t Select an option from the menu below\n"
		<< "\n\t\t\t\t\t\t\t\t  1. Fetch data from file\n"
		<< "\n\t\t\t\t\t\t\t\t  2. Sort students\n"
		<< "\n\t\t\t\t\t\t\t\t  3. Print Sorted Students\n"
		<< "\n\t\t\t\t\t\t\t\t  4. Clear data\n"
		<< "\n\t\t\t\t\t\t\t\t  5. Exit\n"
		<< "\n\t\t\t\t\t\t\t\t"
		<< "\n\t\t\t\t\t\t\t\tInput choice --> ";
	std::cin >> choice;
	if (choice == 1) {
		system("cls");
		int numb;
		std::cout << "\n\t\t\t\t\t\t\t***---Ensure files are in same directory as the program---***"
				  <<"\n\n\n\t\t\t\t\t\t\t\t    Input of files to be retrieved: ";
		std::cin >> numb;
		for (int i = 0; i < numb; i++) {
			fetch_data(student_list, File); // fetch data from file and store it in a vector
			std::cout << "\n\t\t\t\t\t\t\t\t\t students retrived " << student_list.size() << std::endl;
			system("pause");
		}
		main_menu(student_list, File, A_students, B_students);
	}
	else if (choice == 2) {
		if (A_students.size() > 0 || B_students.size() > 0) {
			std::cout << "\a\n\t\t\t\t\t\t\t\t Data has already been sorted!\n";
		} else if (student_list.size() > 0) {
			sort_students(student_list, A_students, B_students);
			printSortedData(A_students, B_students);
		} else {
			std::cout << "\a\n\t\t\t\t\t\t\t\t\t   No data found!\n";
		}
		
		system("pause");
		main_menu(student_list, File, A_students, B_students);
	}
	else if (choice == 3) {
		if (A_students.size()==0) {
			std::cout << "\a\n\t\t\t\t\t\t\t\t\t   No data found!\n";
			system("pause");
			main_menu(student_list, File, A_students, B_students);

		}
		else {
			print_result(A_students, B_students);
			main_menu(student_list, File, A_students, B_students);
		}
	}
	else if(choice == 5) {
		std::string ans;
		std::cout << "\n\n\t\t\t\t\t\t\t\t You are about to exit the program, continue? (y/n)_: ";
		std::cin >> ans;
		if (ans == "y") {
			exit(0);
		}
		else {
			main_menu(student_list, File, A_students, B_students);
		}
		
	}
	else if (choice == 4) {
		std::string ans;
		std::cout << "\n\n\t\t\t\t\t\t\t You are about to clear all data in the program, continue? (y/n)_: ";
		std::cin >> ans;
		if (ans == "y") {
			clear(student_list, A_students, B_students,File);
			main_menu(student_list, File, A_students, B_students);
		}
		else {
			main_menu(student_list, File, A_students, B_students);
		}
	}
	else {
		main_menu(student_list, File, A_students, B_students);
	}
};

int main()
{
	
	Data_File File; // declare File Object to handle file operations

	std::vector<Student>student_list, A_students, B_students;; // declare vector of student objects

	 // main program control
	main_menu(student_list, File, A_students, B_students); 

	system("pause");
    return 0;
}
