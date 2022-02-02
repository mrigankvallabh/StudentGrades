#ifndef RECORDS_H
#define RECORDS_H
#include <fstream>
#include <string>
#include <vector>

class Student {
 private:
   int id;
   std::string name;

 public:
   Student(int the_id, std::string the_name);
   int get_id();
   std::string get_name();
};

class Course {
 private:
   int id;
   std::string name;
   unsigned char credits;

 public:
   Course(int the_id, std::string the_name, unsigned char the_credits);
   int get_id();
   std::string get_name();
   unsigned char get_credits();
};

class Grade {
 private:
   int student_id;
   int course_id;
   char grade;

 public:
   Grade(int sid, int cid, char the_grade);
   int get_student_id();
   int get_course_id();
   char get_grade();
};

class StudentRecords {
 private:
   std::vector<Student> students;
   std::vector<Course> courses;
   std::vector<Grade> grades;

   float get_gp(char);

 public:
   void add_student(int, std::string);
   void add_course(int, std::string, unsigned char);
   void add_grades(int, int, char);

   std::string get_student_name(int);
   std::string get_course_name(int);
   unsigned char get_course_credits(int);
   float get_gpa(int);
   void printReport(int, std::ostream&);
   void fileFullReport(std::ofstream&);
};
#endif //* RECORDS_H */