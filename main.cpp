#include <iostream>
#include <limits>

int getNum(std::string prompt);

/**********************************************************************
 * Month represents a given month in a year with its name and the number of
 * days it has. Isn't aware of leap days on it's own but has the ability to
 * leap one day.
 ***********************************************************************/
class Month {
public:
  Month();
  Month(int);

  static int getMonth();
  static int getMonth(char *a);

  void leap(bool);

  std::string name();
  int days();

private:
  static std::string monthNames[];
  static int daysArr[];

  std::string monthName;
  int numDays;
};

/**********************************************************************
 * Calendar has the capability to display a calendar for a given month in a
 * given year.
 ***********************************************************************/
class Calendar {
public:
  Calendar();
  Calendar(int, int);

  static int getYear();
  static int getYear(char *a);

  void display();

private:
  static int daysBeforeArr[];

  int year;
  Month month;
  int offset;

  bool isLeapYear();
  int daysBefore(int);
  int computeOffset(int, int);
};

/**********************************************************************
 * Main uses the Calendar and Month classes' static input functions to ask the
 * user to input a month number and a year. It then creates a Calendar object
 * and displays its visual representation to stdout.
 ***********************************************************************/
int main(int argc, char *argv[]) {
  Calendar cal;
  if (argc == 3) {
    cal = Calendar(Calendar::getYear(argv[2]), Month::getMonth(argv[1]));
  } else {
    cal = Calendar(Calendar::getYear(), Month::getMonth());
  }

  cal.display();

  return 0;
}

/**********************************************************************
 * Takes a string input to prompt to the user, requests a
 * numerical input, and then returns the value if valid.
 ***********************************************************************/
int getNum(std::string prompt) {
  int number;

  while (true) {
    std::cout << prompt;

    if (std::cin >> number) {
      return number;
    } else {
      std::cout << "Please enter a valid number.\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
}

int Month::daysArr[]{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
std::string Month::monthNames[]{
    "January", "February", "March",     "April",   "May",      "June",
    "July",    "August",   "September", "October", "November", "December"};

/**********************************************************************
 * Month default constructor
 ***********************************************************************/
Month::Month() {}

/**********************************************************************
 * Month constructor: takes a month number and creates a month object with the
 * appropriate name and number of days. Leap day not taken into account yet.
 ***********************************************************************/
Month::Month(int monthNum) {
  if (monthNum > 0 && monthNum < 13) {
    this->monthName = Month::monthNames[monthNum - 1];
    this->numDays = Month::daysArr[monthNum - 1];
  }
}

/**********************************************************************
 * Month name getter
 ***********************************************************************/
std::string Month::name() { return this->monthName; }

/**********************************************************************
 * Month days getter
 ***********************************************************************/
int Month::days() { return this->numDays; }

/**********************************************************************
 * Use getNum to ask a user for a number and ensure that it is
 * between 1 and 12.
 ***********************************************************************/
int Month::getMonth() {
  while (true) {
    int month = getNum("Enter a month number: ");

    if (month > 0 && month <= 12)
      return month;
    else
      std::cout << "Month must be between 1 and 12.\n";
  }
}

int Month::getMonth(char *a) {
  int month = std::atoi(a);

  if (month > 0 && month <= 12)
    return month;
  else
    std::cout << "Month must be between 1 and 12.\n";
  exit(1);
}

/**********************************************************************
 * Increment the number of days in a month by 1. Used when a month
 * is a part of a leap year.
 ***********************************************************************/
void Month::leap(bool isLeapYear) {
  if (isLeapYear && this->monthName == "February")
    this->numDays++;
}

/**********************************************************************
 * Calendar default constructor
 ***********************************************************************/
Calendar::Calendar() {}

/**********************************************************************
 * Calendar constructor: Takes in arbitrary year and month number inputs and
 * sets its internal fields accordingly. A leap day is appended if the given
 * year is a leap year. The offset is calculated using the year and the
 * daysBefore.
 ***********************************************************************/
Calendar::Calendar(int yearNum, int monthNum)
    : year(yearNum), month(Month(monthNum)) {
  this->month.leap(this->isLeapYear());

  this->offset =
      Calendar::computeOffset(this->year, this->daysBefore(monthNum));
}

/**********************************************************************
 * Uses getNum to ask the user for a number and ensure the value is 1753 or
 * later.
 ***********************************************************************/
int Calendar::getYear() {
  while (true) {
    int year = getNum("Enter year: ");

    if (year >= 1753)
      return year;
    else
      std::cout << "Year must be 1753 or later.\n";
  }
}

int Calendar::getYear(char *a) {
  int year = std::atoi(a);

  if (year >= 1753)
    return year;
  else
    std::cout << "Year must be 1753 or later.\n";
  exit(1);
}

/**********************************************************************
 * Determines whether or not the year field is a leap year or not
 ***********************************************************************/
bool Calendar::isLeapYear() {
  return this->year % 400 == 0 || this->year % 4 == 0 && this->year % 100 != 0;
}

int Calendar::daysBeforeArr[]{0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};

/**********************************************************************
 * Returns the number of days that have passed before a given month and adds
 * a leap day if necessary.
 ***********************************************************************/
int Calendar::daysBefore(int monthNum) {
  int numDays = 0;

  if (monthNum > 0 and monthNum < 13) {
    numDays = Calendar::daysBeforeArr[monthNum - 1];

    if (monthNum > 2 && this->isLeapYear()) {
      numDays++;
    }
  }

  return numDays;
}

/**********************************************************************
 * Takes the sum of all the days and leap days from 1753 to year to determine
 * the offset of the calendar for printing. Essentially what day of the month
 * is the 1st.
 ***********************************************************************/
int Calendar::computeOffset(int year, int monthDays) {
  int numYears = year - 1753;

  int numDays =
      numYears + monthDays + numYears / 4 - numYears / 100 + numYears / 400;

  return 6 - numDays % 7;
}

/**********************************************************************
 * Displays a purty calendar to the user.
 ***********************************************************************/
void Calendar::display() {
  std::cout << std::endl
            << "\t" << this->month.name() << " " << this->year << std::endl
            << "  Su  Mo  Tu  We  Th  Fr  Sa\n  ";

  for (int x = 0; x < (7 - this->offset) % 7; ++x) {
    std::cout << "    ";
  }

  for (int x = 0; x < this->month.days(); ++x) {
    if (x && !((x - this->offset) % 7)) {
      std::cout << "\n  ";
    }
    if (x < 9) {
      std::cout << " ";
    }
    std::cout << x + 1;
    if ((x + 1 - this->offset) % 7 && x + 1 != this->month.days()) {
      std::cout << "  ";
    }
  }
  std::cout << std::endl;
}
