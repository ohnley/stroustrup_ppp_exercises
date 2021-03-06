#include "../std_lib_facilities.h"

// the parts used to define a class are called members, and a class has 0 or more memebers
class X {

    // the public stuff is the interface, accessed by users
    public:
        int m; // data member
        int mf(int v) {int old = m; int m = v; return old;} // function member, don't need to refer back to the objects name to access items if in a member func

    // the private stuff is the implementation 
    // class members are private by default
};

// For something that is just a data container, we can use a struct -- a class where the members are public by default
struct Z {
    int age;
    double score;
    string name;
};

// enums aka enumerations are simple, user defined type, specifying a set of values as symbolic constants
enum class Month { // the class keyword says that the enumerator are in the scope of the enumeration, so you need to do Month::jan to refer to jan
    jan, // if we don't init the first one, it starts at 0
    feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec // if we do not specify value, it will add one from the previous value
};

enum class Day{
    monday, tuesday, wednesday, thursday, friday, saturday, sunday
};

// But doesn't provide any error checking for leap years, valid numbers etc
struct Date {
    int year, month, day;
    Date(int year, int month, int day);
    // start to provide error checking with functions in the struct
    // undefined here, but would properly add the date/
    // hwoever, we are still in a struct so users could still just do whatever they want to 
    // the member data -- NO GOOD -- we need to use private in a class to prevent this

    void add_day(int n);
};

class DateClass {

    static const int min = 1; // static means only create ONE min int for ALL instances of this class, to save space, could have used constexpr instead of const
    public:
        DateClass(int yy, Month mm, int dd);
        // DateClass() : y{2001}, m{Month::jan}, d{1} {} // this is the default constructor 
        // DateClass() : y{default_date().year()}, 
        //               m{default_date().month()},
        //               d{default_date().day()} {}
        void add_day(int n) {} // if you define the function in the class body, the compiler will try to generate code
                               // at each point of call rather than jumping around, this can boost performance for 
                               // functions that are used a lot, but don't do much

        Month month() const {return m;} // use of the const keyword will allow const verison of this function to work
        int year() const {return y;}
        int day() const {return d;}
        void add_year(int n) {} // all uses of the class will need to be recompuled when you change the body of the class,
                                // but the if the function body is outside of the class declaration, you don't need to recomp
                                // this can provide large benefits in big programs -- so inline code thats short and simple
    private:
        int y,d;
        Month m;
        bool is_valid(); // is this date valid

};

// declaring a constructor outside of the class
DateClass::DateClass(int yy, Month mm, int dd) : y{yy}, m{mm}, d{dd} {
    if (!is_valid()) throw exception{};
}

bool DateClass::is_valid(){
    if ((int)m < 1 || (int)m > 12) return false;
    return true;
}


// // If we don't want to put the default values into the constructor code, can do this to create one instance of the default date that is constant
// const DateClass& default_date(){
//     static const DateClass dd {2001, Month::jan, 1};
//     return dd;
// }

void f(int x, int y){
    try{
        DateClass dxy = DateClass{2005, Month(x), y};
        // cout << dxy << '\n';
        dxy.add_day(2);
    } catch (exception e){
        error(e.what());
    }
}




// since enums don't have constructors, we can make a simple function like so to check that the creation is valid
// and return an enum Month if it passes a simple check
Month int_to_month(int x){
    if (x < int(Month::jan) || x < int(Month::dec)) error ("bad month");
    return Month(x);
}

// we can also do operator overloading like so to provide notation for a user defined type
Month operator++(Month &m){
    m = (m==Month::dec) ? Month::jan : Month(int(m)+1);
    return m;
}

// 0-11 for each month
vector<string> month_tbl = {"January","Feb","March","April","May","June","July","August","September","October","November","December"};

// an overloaded operator must have at least one user defined type as an operand
ostream& operator<<(ostream& os, Month m){
    return os << month_tbl[int(m)];
}
int main(){

    X var;
    var.m = 7;
    int x = var.mf(9);

    // now we can use the enum like so
    Month m = Month::feb;
    // Month m2 = feb; // error as not in scope

    // m = 7; // can't assign an int to a month;
    // int n = m; // can't assign a month to an int
    Month mm = Month(54); // unchecked conversion
    // Month mmm = Month{43}; // checked conversion that fails
    // Month n = Month{2}; // checked conversion that also fails

    // what should a good interface do?
    // keep interfaces complete and minimal
    // provide constrcutors and explicitly support/prohibit copying
    // use types to enhance argument checking
    // free resources in the destructor 

    // the default of copying object is that all the members are copied
    DateClass holiday = DateClass{1978, Month(3), 5};
    DateClass d2 = holiday;
    

    cout << Month::jun;
    return 0;
}