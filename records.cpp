#include "records.hpp"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

//* Student class
Student::Student(int the_id, string the_name)
{
   id = the_id;
   name = the_name;
}

int Student::get_id() { return id; }

string Student::get_name() { return name; }

//* Course class
Course::Course(int the_id, string the_name, unsigned char the_credits)
{
   id = the_id;
   name = the_name;
   credits = the_credits;
}

int Course::get_id() { return id; }

string Course::get_name() { return name; }

unsigned char Course::get_credits() { return credits; }

//* Grade class
Grade::Grade(int sid, int cid, char the_grade)
{
   student_id = sid;
   course_id = cid;
   grade = the_grade;
}

int Grade::get_student_id() { return student_id; }

int Grade::get_course_id() { return course_id; }

char Grade::get_grade() { return grade; }

//* StudentRecords class
void StudentRecords::add_student(int sid, string sname)
{
   students.push_back(Student(sid, sname));
}

void StudentRecords::add_course(int cid, string cname, unsigned char c)
{
   courses.push_back(Course(cid, cname, c));
}

void StudentRecords::add_grades(int sid, int cid, char g)
{
   grades.push_back(Grade(sid, cid, g));
}

float StudentRecords::get_gp(char l)
{
   switch (l) {
   case 'A':
      return 4.0f;
   case 'B':
      return 3.0f;
   case 'C':
      return 2.0f;
   case 'D':
      return 1.0f;
   default:
      return 0.0f;
   }
}

string StudentRecords::get_student_name(int sid)
{
   for (auto& s : students) {
      if (s.get_id() == sid)
         return s.get_name();
   }
   return "";
}

string StudentRecords::get_course_name(int cid)
{
   for (auto& c : courses) {
      if (c.get_id() == cid)
         return c.get_name();
   }
   return "";
}

unsigned char StudentRecords::get_course_credits(int cid)
{
   for (auto& c : courses) {
      if (c.get_id() == cid)
         return c.get_credits();
   }

   return 0;
}

float StudentRecords::get_gpa(int sid)
{
   float tgp = 0.0f, tc = 0.0f;

   for (auto& g : grades) {
      if (g.get_student_id() == sid) {
         float cc = get_course_credits(g.get_course_id());
         tgp += get_gp(g.get_grade()) * cc;
         tc += cc;
      }
   }

   return tc == 0 ? 0 : tgp / tc;
}

void StudentRecords::printReport(int sid, ostream& stream)
{
   stream << "Report Card" << endl;
   stream << "Student Name: " << get_student_name(sid) << endl;
   float tgp = 0.0f, tc = 0.0f;

   for (auto& g : grades) {
      if (g.get_student_id() == sid) {
         stream << get_course_name(g.get_course_id()) << " : " << g.get_grade()
                << endl;
         float cc = get_course_credits(g.get_course_id());
         tgp += get_gp(g.get_grade()) * cc;
         tc += cc;
      }
   }
   stream << "GPA: " << (tc == 0 ? 0 : tgp / tc) << endl;
}

void StudentRecords::fileFullReport(ofstream& ofile)
{
   int sid;
   ofile.open("report.txt");
   if (ofile.fail()) {
      cerr << "ERROR!: Failed to open file";
      return;
   }
   for (auto& s : students) {
      ofile << "===================BEGIN REPORT===================" << endl;
      sid = s.get_id();
      printReport(sid, ofile);
      ofile << "=====================END REPORT===================" << endl;
   }
   ofile.close();
}