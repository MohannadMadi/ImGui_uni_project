#include <cstring>
#include <iostream>

#ifndef STUDENT_H
#define STUDENT_H

class CStudent {
private:
    char student_name[50];
    int student_ID;
    char student_email_username[10];
    char student_major[10];
    float student_grades[5];
    float student_score=0;
    char student_email_password[10];

public:
    ///////////////////////////Constructor///////////////////////////
    CStudent();
    ///////////////////////////Setter functions///////////////////////////
    void setStudentName(char* ) ;

    void setStudentID(int ) ;
    void setStudentEmailUsername(const char* ) ;

    void setStudentMajor(const char* ) ;

    void setStudentGrades(const float*);

    void setStudentScore(float ) ;

    void setStudentEmailPassword(const char*);

    ///////////////////////////Getter functions///////////////////////////
    const char* getStudentName() const ;

    int getStudentID() const ;

    const char* getStudentEmailUsername() const ;

    const char* getStudentMajor() const ;

    const float* getStudentGrades() const;

    float getStudentScore() const ;

    const char* getStudentEmailPassword() const ;

    ///////////////////////////Registration functions///////////////////////////
    virtual void registerStudent(char* nameOfStudent,
        char* emailUserOfStudent,
        char* emailPassOfStudent,
        int *idOfStudent,
        char* majorOfStudent,
        float* gradesOfStudent,
        float scoreOfStudent,
        int *fullySubmitted
        ,int* current_Student_index
        
        ) ;

    ///////////////////////////Calculate GPA///////////////////////////
    void calculateGPA() ;

    ///////////////////////////Print student's data ///////////////////////////
    virtual void getStudentInfo()  ;

};

class CCourse
{
private:
    char course_name[20];
    char course_code[5];
    float course_cost;

public:
    ///////////////////////////Constructor///////////////////////////
    CCourse();  
    ///////////////////////////Setter functions///////////////////////////
    void setCourseName(const char*);
    void setCourseCode(const char*);
    void setCourseCost( float );

    ///////////////////////////Getter functions///////////////////////////
    const char* getCourseName() const;

    const char* getCourseCode() const;

    float getCourseCost( ) const;


    ///////////////////////////Adding Courses function///////////////////////////
    void registerCourses();
    ///////////////////////////Get Course information function///////////////////
    void getCourseInfo() const;
 
};
class CPG_Student : public CStudent {
private:
    char pg_student_job_title[20];

public:
    ///////////////////////////Constructor///////////////////////////
    CPG_Student();
    
    ///////////////////////////Setter function///////////////////////////
    void setPGStudentJobTitle(const char*);

    ///////////////////////////Getter function///////////////////////////
    const char* getPGStudentJobTitle() const;
    ///////////////////////////Registration functions///////////////////////////
    void registerStudent(char* nameOfStudent,
        char* emailUserOfStudent,
        char* emailPassOfStudent,
        int *idOfStudent,
        char* majorOfStudent,
        float* gradesOfStudent,
        float scoreOfStudent,
        int *fullySubmitted
       , int* current_Student_index
        
    )override ;
    ///////////////////////////Print student's data ///////////////////////////
    void getStudentInfo() override;

};

#endif  // STUDENT_H
