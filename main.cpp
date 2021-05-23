#include <iostream>
#include <string>

int getNum(std::string prompt);

/**********************************************************************
 * Month represents a given month in a year with its name and the number of
 * days it has. Isn't aware of leap days on it's own but has the ability to
 * leap one day.
 ***********************************************************************/
class Month
{
   public:
      Month();
      Month(int);
      
      static int getMonth();

      void leap(bool);

      std::string name();
      int days();

   private:
      std::string monthName;
      int numDays;
};

/**********************************************************************
 * Calendar has the capability to display a calendar for a given month in a
 * given year.
 ***********************************************************************/
class Calendar
{
   public:
      Calendar();
      Calendar(int, int);
      
      static int getYear();
      
      void display();

   private:
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
int main()
{
   Calendar cal = Calendar(Calendar::getYear(), Month::getMonth());

   cal.display();

   return 0;
}

/**********************************************************************
 * Takes a string input to prompt to the user, requests a
 * numerical input, and then returns the value if valid.
 ***********************************************************************/
int getNum(std::string prompt)
{
   int number;

   while (true)
   {
      std::cout << prompt;

      if (std::cin >> number)
      {
         return number;
      }
      else
      {
         std::cout << "Please enter a valid number.\n";
         std::cin.clear();
         while (std::cin.get() != '\n');
      }
   }
}

/**********************************************************************
 * Month default constructor
 ***********************************************************************/
Month::Month()
{
}

/**********************************************************************
 * Month constructor: takes a month number and creates a month object with the
 * appropriate name and number of days. Leap day not taken into account yet.
 ***********************************************************************/
Month::Month(int monthNum)
{
   switch (monthNum)
   {
      case 1:
         this->monthName = "January";
         this->numDays = 31;
         break;
      case 2:
         this->monthName = "February";
         this->numDays = 28;
         break;
      case 3:
         this->monthName = "March";
         this->numDays = 31;
         break;
      case 4:
         this->monthName = "April";
         this->numDays = 30;
         break;
      case 5:
         this->monthName = "May";
         this->numDays = 31;
         break;
      case 6:
         this->monthName = "June";
         this->numDays = 30;
         break;
      case 7:
         this->monthName = "July";
         this->numDays = 31;
         break;
      case 8:
         this->monthName = "August";
         this->numDays = 31;
         break;
      case 9:
         this->monthName = "September";
         this->numDays = 30;
         break;
      case 10:
         this->monthName = "October";
         this->numDays = 31;
         break;
      case 11:
         this->monthName = "November";
         this->numDays = 30;
         break;
      case 12:
         this->monthName = "December";
         this->numDays = 31;
         break;
   }
}

/**********************************************************************
 * Month name getter
 ***********************************************************************/
std::string Month::name()
{
   return this->monthName;
}

/**********************************************************************
 * Month days getter
 ***********************************************************************/
int Month::days()
{
   return this->numDays;
}

/**********************************************************************
 * Use getNum to ask a user for a number and ensure that it is
 * between 1 and 12.
 ***********************************************************************/
int Month::getMonth()
{
   while (true)
   {
      int month = getNum("Enter a month number: ");
      
      if (month > 0 && month <= 12)
         return month;
      else
         std::cout << "Month must be between 1 and 12.\n";
   }
}

/**********************************************************************
 * Increment the number of days in a month by 1. Used when a month
 * is a part of a leap year.
 ***********************************************************************/
void Month::leap(bool isLeapYear)
{
   if (isLeapYear && this->monthName == "February")
      this->numDays++;
}

/**********************************************************************
 * Calendar default constructor
 ***********************************************************************/
Calendar::Calendar()
{
}

/**********************************************************************
 * Calendar constructor: Takes in arbitrary year and month number inputs and
 * sets its internal fields accordingly. A leap day is appended if the given
 * year is a leap year. The offset is calculated using the year and the
 * daysBefore.
 ***********************************************************************/
Calendar::Calendar(int yearNum, int monthNum)
: year(yearNum), month(Month(monthNum))
{
   this->month.leap(this->isLeapYear());
   
   this->offset = Calendar::computeOffset(this->year,
         this->daysBefore(monthNum));
}

/**********************************************************************
 * Uses getNum to ask the user for a number and ensure the value is 1753 or
 * later.
 ***********************************************************************/
int Calendar::getYear()
{
   while (true)
   {
      int year = getNum("Enter year: ");
      
      if (year >= 1753)
         return year;
      else
         std::cout << "Year must be 1753 or later.\n";
   }
}

/**********************************************************************
 * Determines whether or not the year field is a leap year or not
 ***********************************************************************/
bool Calendar::isLeapYear()
{
   return this->year % 400 == 0 ||
      this->year % 4 == 0 && this->year % 100 != 0;
}

/**********************************************************************
 * Returns the number of days that have passed before a given month and adds
 * a leap day if necessary.
 ***********************************************************************/
int Calendar::daysBefore(int monthNum)
{
   int numDays = 0;

   switch (monthNum)
   {
      case 2:
         return 31;
      case 3:
         return 59;
      case 4:
         return 90;
      case 5:
         return 120;
      case 6:
         return 151;
      case 7:
         return 181;
      case 8:
         return 212;
      case 9:
         return 243;
      case 10:
         return 273;
      case 11:
         return 304;
      case 12:
         return 334;
   }
   
   if (monthNum > 2 && this->isLeapYear())
   {
      numDays++;
   }
   return numDays;
}

/**********************************************************************
 * Takes the sum of all the days and leap days from 1753 to year to determine
 * the offset of the calendar for printing. Essentially what day of the month
 * is the 1st.
 ***********************************************************************/
int Calendar::computeOffset(int year, int monthDays)
{
   int numYears = year - 1753;

   int numDays = numYears * 365 + monthDays + numYears / 4 - numYears / 100
      + numYears / 400;
     
   return numDays % 7 + 1;
}

/**********************************************************************
 * Displays a purty calendar to the user.
 ***********************************************************************/
void Calendar::display()
{
   std::cout << std::endl << this->month.name()
             << ", " << this->year << std::endl
             << "  Su  Mo  Tu  We  Th  Fr  Sa\n  ";
  
   for (int x = 0; x < this->offset % 7; ++x)
   {
      std::cout << "    ";
   }
   
   int invOffset = 7 - this->offset;
   for (int x = 0; x < this->month.days(); ++x)
   {
      if (x && !((x - invOffset) % 7))
      {
         std::cout << "\n  ";
      }
      if (x < 9)
      {
         std::cout << " ";
      }
      std::cout << x + 1;
      if ((x + 1 - invOffset) % 7 && x + 1 != this->month.days())
      {
         std::cout << "  ";
      }
   }
   std::cout << std::endl;
}
