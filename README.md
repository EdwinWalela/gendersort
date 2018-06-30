# Student Shuffle Algorithim

Year 1 Semester 1 C++ project. (Gender Sorting algorithm)
## Problem Statement
The current Computer Science freshmen are in three groups, A, B and C respectively. The gender
ratios in these groups are as shown below.

| ICS Group     | Male   | Female |
| ------------- |:------:|:------:|
| ICS A         | 19     |   11   |
| ICS B         | 16     |   12   |
| ICS C         | 36     |   19   |
| **Totals**    | 71     |   42   |

Assuming the Faculty has decided to merge the three groups into two, balancing the gender ratios
as shown below.
Develop a perfect shuffle algorithm (coded) that will give the output in the table below. 


| ICS Group     | Male   | Female |
| ------------- |:------:|:------:|
| ICS A         | 36     |   21   |
| ICS B         | 35     |   21   |
| **Totals**    | 71     |   42   |

### Prerequisites 
1. Objects and Classes
2. STL library (vectors)

## Test it out
1. clone repository
2. locate ` Release ` folder 
3. run ` studentSystem.exe `

# Project Oveview
## Objects
### Students
#### Attributes
  1. surname
  2. Name
  3. Admission number
  4. Gender
#### Methods
  1.Create

## Shuffle Algorithim

### Vectors
1. ` student list `
2. ` A_students ` 
3. ` B_students `

### Workflow
1. First, files are read from file (one at a time) and stored into a vector ` student list `

2. ` student list ` is split into two separate vectors ` boys ` and ` girls `

3. push ` boy ( n ) ` from ` boys ` to ` A_students ` and ` boy ( n + 1 ) ` from ` boys ` to ` B_students `

4. push ` girl ( n ) ` from ` girls ` to ` A_students ` and ` girl ( n + 1 ) ` from ` girls ` to ` B_students `

5. print ` A_students ` vector to ` B_list.csv ` 

6. print ` B_students ` vector to ` A_list.csv `

### Code samples

```
// split student list to boys and girls

for (unsigned int i = 0; i < student_list.size(); i++){
   if (student_list.at(i).gender == "M"){
      boys.push_back(student_list.at(i));
   } else {
      girls.push_back(student_list)
   }
}
```

```
//push female(n) to A female (n+1) to B

div = girls.size() % 2;  
for (unsigned int i = 0; i<girls.size()-1; i+=2) {
 A_students.push_back(girls.at(i));
 B_students.push_back(girls.at(i + 1));
 
 if (div > 0 && i == girls.size() - 3) {
  A_students.push_back(girls.at(i + 2));
 }
}
```
```
// printing B students to listA

std::ofstream outFileA;

outFileA.open("listA.csv");
 for (unsigned int i = 0; i < listB.size(); i++) {
  outFileA <<listB.at(i).numbr<<","
           <<listB.at(i).surname<<" "
           <<listB.at(i).name<<","
           <<listB.at(i).gender
           <<std::endl;
 }
outFileA.close();
```

