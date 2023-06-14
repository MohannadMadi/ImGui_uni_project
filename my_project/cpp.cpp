// this project was created by:
// Mohannad Madi: 221001139
// Mahmoud Ahmed: 221001868
// Abdallah kamal eldin hassan: 221001710
// Mohamed Awes: 221000931
// Mousa Ashraf: 221000995

#include<iostream>
#include<cstring>
#include<cstdlib>
#include "student.cpp"

using namespace std;

int main(){
int n_students=0,n_courses=0,n_CPG_students=0;

// Storing number of loops
cout<<"number of students: ";
cin>>n_students;
cout<<"\nnumber of grad students: ";
cin>>n_CPG_students;
cout<<"\nnumber of courses: ";
cin>>n_courses;
cout<<"\n(Register students)\n";
//allocating memory
 CStudent* students = new CStudent[n_students];
 CCourse* courses = new CCourse[n_courses];
 CPG_Student* gradStudents = new CPG_Student[n_CPG_students];

// Inputting student info
for (int i = 0; i < n_students; i++)
{
    cout<< "Register student"<<i+1<<":\n";
    students[i].registerStudent();
    students[i].calculateGPA();
}

// Inputting postgrad student info

cout<<"\n(Register post grad students)\n";

for (int i = 0; i < n_CPG_students; i++)
{
    cout<< "Register post grad student"<<i+1<<":\n";
    gradStudents[i].registerStudent();
    gradStudents[i].calculateGPA();
}

// Inputting courses info

cout<<"\n(Register courses)\n";
for (int i = 0; i < n_courses; i++)
{
    cout<< "Register course"<<i+1<<":";
    courses[i].registerCourses();
}

// outputting student info

for (int i = 0; i < n_students; i++)
{
    cout<< "student"<<i+1<<" info:\n";
    
    students[i].getStudentInfo();
}
// outputting postgrad student info

for (int i = 0; i < n_CPG_students; i++)
{
    cout<< "post grad student"<<i+1<<" info:\n";
    
    gradStudents[i].getStudentInfo();
}
// outputting courses info

for (int i = 0; i < n_courses; i++)
{
    cout<< "Course"<<i+1<<" info:";
    courses[i].getCourseInfo();
}
// deallocate memory
    delete[] students; 
    delete[] courses;
    delete[] gradStudents;
    return 0;
}