#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class Course {
public:
	string name;
	string grade;
	int credits;

	Course(string name, string grade, int credits) {
		this->name = name;
		this->grade = grade;
		this->credits = credits;
	}
};

class Student {
private:
	vector<Course> courses;
	int totalCredits;
	double totalGradePoints;

	double gradeToPoints(string grade) {
		unordered_map<string, double> gradeMap = {
			{ "A", 4.0 }, { "A-", 3.7 }, { "B+", 3.3 }, { "B", 3.0 }, { "B-", 2.7 },
			{ "C+", 2.3 }, { "C", 2.0 }, { "C-", 1.7 }, { "D+", 1.3 }, { "D", 1.0 },
			{ "F", 0.0 }
		};
		return gradeMap[grade];
	}

public:
	Student() {
		totalCredits = 0;
		totalGradePoints = 0.0;
	}

	void addCourse(string name, string grade, int credits) {
		double gradePoints = gradeToPoints(grade);
		courses.push_back(Course(name, grade, credits));
		totalCredits += credits;
		totalGradePoints += gradePoints * credits;
	}

	double calculateGPA() {
		if (totalCredits == 0) return 0.0;
		return totalGradePoints / totalCredits;
	}

	void displayCourses() {
		cout << "Course Details:\n";
		for (auto &course : courses) {
			cout << "Name: " << course.name
				<< ", Grade: " << course.grade
				<< ", Credits: " << course.credits << endl;
		}
	}

	double calculateCGPA() {
		return calculateGPA();
	}
};

int main() {
	Student student;
	int numberOfCourses;

	cout << "Enter the number of courses: ";
	while (!(cin >> numberOfCourses) || numberOfCourses <= 0) {
		cout << "Invalid input. Please enter a positive integer for the number of courses: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	for (int i = 0; i < numberOfCourses; ++i) {
		string name;
		string grade;
		int credits;

		cout << "Enter course " << i + 1 << " name: ";
		cin >> ws; // consume any leading whitespace
		getline(cin, name);

		cout << "Enter course " << i + 1 << " grade (A, A-, B+, B, B-, C+, C, C-, D+, D, F): ";
		cin >> grade;
		while (grade != "A" && grade != "A-" && grade != "B+" && grade != "B" && grade != "B-" &&
			grade != "C+" && grade != "C" && grade != "C-" && grade != "D+" && grade != "D" &&
			grade != "F") {
			cout << "Invalid grade. Please enter a valid grade (A, A-, B+, B, B-, C+, C, C-, D+, D, F): ";
			cin >> grade;
		}

		cout << "Enter course " << i + 1 << " credits: ";
		while (!(cin >> credits) || credits <= 0) {
			cout << "Invalid input. Please enter a positive integer for credits: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		student.addCourse(name, grade, credits);
	}

	student.displayCourses();

	double cgpa = student.calculateCGPA();
	cout << "CGPA: " << cgpa << endl;

	system("pause");
	return 0;
}
