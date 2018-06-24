
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
		std::cout << "enter file name:\n ";
		std::cin >> dir;
		inputStream.open(dir); 

		while (inputStream.fail()) { // if directory doesnt exists
			system("cls");
			std::cerr << "\aunable to open file,try adding(.csv):\n";
			getline(std::cin, dir);
			inputStream.open(dir);
		}
	}
	
	std::vector<Student> fetchData() {
		while (!inputStream.eof()) {
			Student stud_obj;
			std::string fname,sname,numb,gender;
			getline(inputStream, numb, ',');
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

};

//FUNCTIONS

void printSortedData(std::vector<Student> listA, std::vector<Student> listB) {
	int Amcounter = 0; int Afcounter = 0;
	int Bmcounter = 0; int Bfcounter = 0;
	for (int i = 0; i < listA.size(); i++) {
		if (listA.at(i).gender == "F") {
			//std::cout << listA.at(i).name<<"\n";
			Afcounter++;
		}
		else {
			//std::cout << listA.at(i).name << "\n";
			Amcounter++;
		}
	}
	for (int i = 0; i < listB.size(); i++) {
		if (listB.at(i).gender == "F") {
			Bfcounter++;
		}
		else {
			Bmcounter++;
		}
	}
	std::cout << "\n\nSort algorithm complete...\nResult:\n\n";
	std::cout << " ------- GROUP A -------\n";
	std::cout << "  | girls:  [ " << Afcounter << " ] |\n  | boys :  [ " << Amcounter <<" ] |\n"<<std::endl;
	std::cout << " -----------------------\n\n";
	std::cout << " ------- GROUP B -------\n";
	std::cout << "  | girls:  [ " << Bfcounter << " ] |\n  | boys :  [ " << Bmcounter <<" ] |\n" << std::endl;
	std::cout << " -----------------------\n\n";
	std::cout << "  Total Students : " << Afcounter + Bfcounter+ Amcounter + Bmcounter <<"\n\a"<<std::endl;
}

void fetch_data(std::vector<Student> &student_list, Data_File &File) {
	File.promtDirectory(); // prompt user to enter file directory

	//store data extracted from file to vector
	student_list = File.fetchData();
}

void sort_students(std::vector<Student> &student_list, std::vector<Student> &A_students, std::vector<Student> &B_students) {
	std::vector<Student>boys, girls;

	//populate male & female vectors
	for (int i = 0; i < student_list.size(); i++) {
		if (student_list.at(i).gender == "M") {
			boys.push_back(student_list.at(i));
		}
		else {
			girls.push_back(student_list.at(i));
		}
	}
	int div = boys.size() % 2;
	//push male(n) to A, male (n+1) to B
	for(int i = 0; i<boys.size()-2;i+=2){
		A_students.push_back(boys.at(i));
		B_students.push_back(boys.at(i+1));
		if (div > 0 && i == boys.size()-3) {
			A_students.push_back(boys.at(i+2));
		}
	}
	 div = girls.size() % 2;
	//push female(n) to A female (n+1) to B
	for (int i = 0; i<girls.size()-1; i+=2) {
		A_students.push_back(girls.at(i));
		B_students.push_back(girls.at(i + 1));
		if (div > 0 && i == girls.size() - 3) {
			A_students.push_back(girls.at(i + 2));
		}
	}
}

void main_menu(std::vector<Student> &student_list, Data_File &File, std::vector<Student>A_students, std::vector<Student>B_students) {
	system("cls");
	int choice;
	std::cout << "\n----Student Managment System----\n"
		<< "select an option from the menu below\n"
		<< "\n1. Fetch data from file\n2. Sort students\n\nInput choice: ";
	std::cin >> choice;
	if (choice == 1) {
		fetch_data(student_list, File); // fetch data from file and store it in a vector
		std::cout << "students retrived " << student_list.size() << std::endl;
		system("pause");
		main_menu(student_list, File, A_students, B_students);
	}
	else if (choice == 2) {
		if (student_list.size() > 0) {
		
			sort_students(student_list, A_students, B_students);
			printSortedData(A_students, B_students);
		}else{
		std::cout << "\a\nNo data found!\n";
		}
		system("pause");
		main_menu(student_list, File, A_students, B_students);
	}
};

int main()
{
	srand(time(NULL));
	Data_File File; // declare File Object to handle file operations

	std::vector<Student>student_list, A_students, B_students;; // declare vector of student objects

	main_menu(student_list, File, A_students, B_students); // main program control

	system("pause");
    return 0;
}

