#include <fstream>
#include <iostream>
#include <vector>

#include "records.hpp"

using namespace std;

void initialize();
void initialize(ifstream&);

StudentRecords stuRec;
ifstream ifile;
ofstream ofile;
int main()
{
   initialize(ifile);
   stuRec.fileFullReport(ofile);
   int student_id;

   cout << "Enter the student id: ";
   cin >> student_id;

   if (stuRec.get_student_name(student_id) != "") {
      stuRec.printReport(student_id, cout);
   }
   else {
      cout << "Student id: " << student_id
           << " not found or student grades not available" << endl;
   }

   return 0;
}

void initialize()
{
   vector<Student> students = {
       Student(1, "Hilda Jones"),
       Student(2, "Barry White"),
       Student(3, "Husain Akter"),
   };

   vector<Course> courses = {
       Course(101, "Algebra 101", 5),
       Course(201, "Physics 101", 4),
       Course(301, "English", 3),
       Course(401, "Chemistry 101", 4),
   };

   vector<Grade> grades = {
       Grade(1, 101, 'B'), Grade(1, 201, 'A'), Grade(1, 301, 'C'),
       Grade(2, 101, 'A'), Grade(2, 201, 'A'), Grade(2, 401, 'B'),
   };

   for (auto& s : students) {
      stuRec.add_student(s.get_id(), s.get_name());
   }

   for (auto& c : courses) {
      stuRec.add_course(c.get_id(), c.get_name(), c.get_credits());
   }

   for (auto& g : grades) {
      stuRec.add_grades(g.get_student_id(), g.get_course_id(), g.get_grade());
   }
}

void initialize(ifstream& ifile)
{
   string str, name;
   int sid, cid;
   unsigned char credits;
   char grade;
   int count = 0;
   ifile.open("students.txt");
   if (ifile.fail()) {
      cerr << "ERROR: Unable to open file" << endl;
   }
   else {
      while (!ifile.eof()) {
         getline(ifile, str);
         sid = stoi(str);
         getline(ifile, name);
         stuRec.add_student(sid, name);
         count++;
      }

      ifile.close();
      cout << "Found " << count << "students" << endl;
   }

   count = 0;
   ifile.open("courses.txt");
   if (ifile.fail()) {
      cerr << "ERROR: Unable to open file" << endl;
   }
   else {
      while (!ifile.eof()) {
         getline(ifile, str);
         cid = stoi(str);
         getline(ifile, name);
         getline(ifile, str);
         credits = stoi(str);
         stuRec.add_course(cid, name, credits);
         count++;
      }

      ifile.close();
      cout << "Found " << count << "courses" << endl;
   }

   count = 0;
   ifile.open("grades.txt");
   if (ifile.fail()) {
      cerr << "ERROR: Unable to open file" << endl;
   }
   else {
      while (!ifile.eof()) {
         getline(ifile, str);
         sid = stoi(str);
         getline(ifile, str);
         cid = stoi(str);
         getline(ifile, str);
         grade = str[0];
         stuRec.add_grades(sid, cid, grade);
         count++;
      }

      ifile.close();
      cout << "Found " << count << "grades" << endl;
   }
}