#include <cstring>
#include <iostream>
#include "student.h"
using namespace std;
 ///////////////////////////Constructor///////////////////////////
   CStudent:: CStudent(): student_name{},
              student_ID(0),
              student_email_username{},
              student_major{},
              student_grades{},
              student_score(0.0),
              student_email_password{}
    {

    }
    ///////////////////////////Setter functions///////////////////////////
    void CStudent::setStudentName( char* name) {
        strncpy(student_name, name, 49);
        student_name[49] = '\0'; // Ensure null-termination
    }

    void CStudent::setStudentID(int ID) {
        student_ID = ID;
    }

    void CStudent::setStudentEmailUsername(const char* username) {
        strncpy(student_email_username, username, 9);
        student_email_username[9] = '\0'; // Ensure null-termination
    }

    void CStudent::setStudentMajor(const char* major) {
        strncpy(student_major, major, 9);
        student_major[9] = '\0'; // Ensure null-termination
    }

    void CStudent::setStudentGrades(const float* grades) {
        memcpy(student_grades, grades, sizeof(float) * 5);
    }

    void CStudent::setStudentScore(float score) {
        student_score = score;
    }

    void CStudent::setStudentEmailPassword(const char* password) {
        strncpy(student_email_password, password, 9);
        student_email_password[9] = '\0'; // Ensure null-termination
    }

    ///////////////////////////Getter functions///////////////////////////
    const char* CStudent::getStudentName() const {
        return student_name;
    }

    int CStudent::getStudentID() const {
        return student_ID;
    }

    const char* CStudent::getStudentEmailUsername() const {
        return student_email_username;
    }

    const char* CStudent::getStudentMajor() const {
        return student_major;
    }

    const float* CStudent::getStudentGrades() const {
        return student_grades;
    }

    float CStudent::getStudentScore() const {
        return student_score;
    }

    const char* CStudent::getStudentEmailPassword() const {
        return student_email_password;
    }

    ///////////////////////////Registration functions///////////////////////////
    
    void CStudent::registerStudent(char *nameOfStudent,
    char *emailUserOfStudent,
    char* emailPassOfStudent,
    int *idOfStudent ,
    char *majorOfStudent,
    float* gradesOfStudent, 
    float scoreOfStudent ,
    int *fullySubmitted


    ) {
        

        ImGui::Text("Student name");
        ImGui::InputText("##studentName", nameOfStudent, 49);

        ImGui::Text("Student ID");
        ImGui::InputInt("##studentID", idOfStudent, sizeof(idOfStudent));
        
        ImGui::Text("Student major");
        ImGui::InputText("##studentMajor", majorOfStudent, 9);

        ImGui::Text("Student email username");
        ImGui::InputText("##studentUserName", emailUserOfStudent, 9);

        ImGui::Text("Student email password");
        ImGui::InputText("##studentpassword", emailPassOfStudent, 9);

        ImGui::Text("Student grades");
        ImGui::InputFloat("##studentGrade1", &gradesOfStudent[0], 1);
        ImGui::InputFloat("##studentGrade2", &gradesOfStudent[1], 1);
        ImGui::InputFloat("##studentGrade3", &gradesOfStudent[2], 1);
        ImGui::InputFloat ("##studentGrade4", &gradesOfStudent[3], 1);
        ImGui::InputFloat("##studentGrade5", &gradesOfStudent[4], 1);

        if (ImGui::Button("Submit"))
        {
            if(strlen(nameOfStudent)>0 && strlen(majorOfStudent)> 0,idOfStudent>0 && strlen(emailUserOfStudent)> 0 && strlen(emailPassOfStudent)> 0)
            {
               *fullySubmitted = 1;
               
               CStudent::setStudentID(*idOfStudent);
               CStudent::setStudentName(nameOfStudent);
               CStudent::setStudentEmailPassword(emailPassOfStudent);
               CStudent::setStudentEmailUsername(emailUserOfStudent);
               CStudent::setStudentGrades(gradesOfStudent);
               CStudent::setStudentMajor(majorOfStudent);
               CStudent::calculateGPA();

            }
            else
            {
               *fullySubmitted = 0;
            }
        }
        if(*fullySubmitted==0)
        {
            ImGui::Text("pleaase fill in all required info");
        }
        else
        {

        }

        }
    

    ///////////////////////////Calculate GPA///////////////////////////
    void CStudent::calculateGPA() {
        float sum = 0.0;
        for (int i = 0; i < 5; i++) {
            sum += student_grades[i];
        }
        student_score = sum / 100.0;
    }

    ///////////////////////////Print student's data ///////////////////////////
    void CStudent::getStudentInfo()  {
        cout << "Student Name: " << student_name << endl;
        cout << "Student ID: " << student_ID<< endl;
        cout << "Student major: " << student_major<< endl;
        cout << "Student Email Username: " << student_email_username << endl;
        cout << "Student Email Password: " << student_email_password << endl;
        cout << "Student GPA: " << student_score << endl;
    }

/////////////////////////////////////////////////////////////


///////////////////////////Constructor///////////////////////////
CCourse::CCourse():
    course_name{},course_code{}, course_cost{}
{
}
    ///////////////////////////Setter functions///////////////////////////
    void CCourse::setCourseName(const char* name)
    {
        strncpy(course_name, name, sizeof(course_name) - 1);
        course_name[sizeof(course_name) - 1] = '\0';  // Null-terminate the string
    }

    void CCourse::setCourseCode(const char* code)
    {
        strncpy(course_code, code, sizeof(course_code) - 1);
        course_code[sizeof(course_code) - 1] = '\0';  // Null-terminate the string
    }

    void CCourse::setCourseCost( float cost)
    {
        course_cost=cost;
    }

    ///////////////////////////Getter functions///////////////////////////
    const char* CCourse::getCourseName() const
    {
        return course_name;
    }

    const char* CCourse::getCourseCode() const
    {
        return course_code;
    }

    float CCourse::getCourseCost() const
    {
 
        return course_cost;
    }


    ///////////////////////////Adding Courses function///////////////////////////
    void CCourse::registerCourses()
    {
        char *nameOfCourse=(char *) malloc(sizeof(course_name));
        char *codeOfCourse=(char *) malloc(sizeof(course_code));
        float costOfCourse;
        cout<<"\nEnter name of course: ";
        cin>>nameOfCourse;
        cout<<"\nEnter code of course: ";
        cin>>codeOfCourse;
        cout<<"\nEnter cost of course: ";
        cin>>costOfCourse;
        setCourseName(nameOfCourse);
        setCourseCode(codeOfCourse);
        setCourseCost(costOfCourse);


        
    }
    ///////////////////////////Get Course information function///////////////////
    void CCourse::getCourseInfo() const
    {
        cout << "Course Name: " << getCourseName() << endl;
        cout << "Course Code: " << getCourseCode() << endl;
        cout << "Course Costs: "<< getCourseCost() << " ";
        
        cout << endl;
    }

    ///////////////////////////Constructor///////////////////////////
     CPG_Student:: CPG_Student(): pg_student_job_title{}{}
    
    ///////////////////////////Setter function///////////////////////////
    void CPG_Student::setPGStudentJobTitle(const char*jobTitle){

    strncpy(pg_student_job_title, jobTitle, 20);
    pg_student_job_title[20] = '\0'; // Ensure null-termination
    }
    const char *CPG_Student::getPGStudentJobTitle()const{
        return pg_student_job_title;
    }
    void CPG_Student::registerStudent(char* nameOfStudent,
        char* emailUserOfStudent,
        char* emailPassOfStudent,
        int *idOfStudent,
        char* majorOfStudent,
        float* gradesOfStudent,
        float scoreOfStudent,
        int *fullySubmitted

    ) {
        CStudent::registerStudent(nameOfStudent,
            emailUserOfStudent,
            emailPassOfStudent,
            idOfStudent,
            majorOfStudent,
            gradesOfStudent,
            scoreOfStudent,
            fullySubmitted

            );
        cout<<"Enter student job title: ";
        char *gSjobTitle=(char *) malloc(sizeof(pg_student_job_title));
        cin>> gSjobTitle;
        setPGStudentJobTitle(gSjobTitle);
    }
    void CPG_Student::getStudentInfo() {
        CStudent::getStudentInfo();
        cout << "Student job title: " << pg_student_job_title << endl;
    }