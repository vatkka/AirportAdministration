#include <iostream>
#include <fstream>
#include <string>

using namespace std;

enum FlightType { Departure, Arrival };
enum errorCode {fail, rangeError, success};

struct TimeRec {
    int hour; // 0 to 23
    int min; // 0 to 59
    int sec; // 0 to 59
};

TimeRec CurrentTime;

void enterCurrentTime();

struct FlightRec {
    string FlightNO;
    string Destination;
    TimeRec Time;
    FlightType Ftype;
    bool Delay;
    TimeRec ExpectedTime; // if the flight is delayed
};

template <class FlightRec>
struct Node {
    FlightRec entry;
    Node<FlightRec>* next;
    Node();
    Node(FlightRec item, Node<FlightRec>* n = NULL);
};

template <class FlightRec>
class List {
public:
    List();
    void clear();
    bool empty() const;
    int size() const;
    Node<FlightRec>* setPosition(int) const;
    //void traverse(void(*visit)(FlightRec&));
    ~List();
    // functions to perform the operations listed above
    void readFlightsFromFile();
    void writeFlightsToFile();
    errorCode addNewFlight();
    errorCode deleteFlight();
    errorCode modifyFlightTime();
    void enterDelay();
    void displayAllFlights();
    void displayDepartures();
    void displayArrivals();
    void sortFlightsByFlightNO();
    void sortFlightsByTime();
private:
    Node<FlightRec> *head;
    int count;
};

void menuTxt() {
    cout << "\nPlease select an option:";
    cout << "\n1. Renter Current Time";
    cout << "\n2. Add New Flight";
    cout << "\n3. Delete Flight";
    cout << "\n4. Modify Flight Time";
    cout << "\n5. Enter Delay for a Flight";
    cout << "\n6. Display All Flights";
    cout << "\n7. Display Departures";
    cout << "\n8. Display Arrivals";
    cout << "\n0. Exit Program";
}

int main() {
    List<FlightRec> flights;

    // Allow the user to enter the current time
    enterCurrentTime();
    int choice;

    do { 
        menuTxt();
        cin >> choice;
        switch (choice) {
            case 1: 
                enterCurrentTime();
                break;
            case 2:
                flights.addNewFlight(); 
                break;
            case 3:
                flights.deleteFlight();
                break;
            case 4:
                flights.modifyFlightTime();
                break;
            case 5:
                flights.enterDelay();
                break;
            case 6: 
                flights.displayAllFlights();
                break;
            case 7: 
                flights.displayDepartures();
                break;
            case 8:
                flights.displayArrivals();
                break;
            case 0: 
                return 0;
            default:
                cout << "Incorrect input, try again.";
                break;
        }
    } while (true);
    return 0;
}

template <class T>
Node<T>::Node() {
    next = NULL;
}

template <class T>
Node<T>::Node(T item, Node<T>* n) {
    entry = item;
    next = n;
}

void enterCurrentTime()
{
    int x;
    cout << "\nEnter current time";
    do {
        cout << "\nHours(0-23): ";
        cin >> x;
        if (x < 0 || x>23) {
            cout << "\nIncorrect input, try again";
        }
    } while (x < 0 || x>23);

    CurrentTime.hour = x;
    do {
        cout << "\nMinutes(0-59): ";
        cin >> x;
        if (x < 0 || x>59) {
            cout << "\nIncorrect input, try again";
        }
    } while (x < 0 || x>59);
    CurrentTime.min = x;

    do {
        cout << "\nSeconds(0-59): ";
        cin >> x;
        if (x < 0 || x>59) {
            cout << "\nIncorrect input, try again";
        }
    } while (x < 0 || x>59);
    CurrentTime.sec = x;

}

template<class FlightRec>
List<FlightRec>::List()
{
    head = NULL;
    count == 0;
}

template<class FlightRec>
void List<FlightRec>::clear()
{
    Node<FlightRec>* temp;

    while (head != NULL) {
        temp = head;
        head = head->next;
        delete temp;
    }
}

template<class FlightRec>
bool List<FlightRec>::empty() const
{
    return count == 0;
}

template<class FlightRec>
int List<FlightRec>::size() const
{
    return count;
}

template<class T>
Node<T>* List<T>::setPosition(int position) const
{
    Node<FlightRec>* q = head;
    for (int i = 0; i < position; i++)
        q = q->next;
    return q;
}



template<class FlightRec>
List<FlightRec>::~List()
{
    Node<FlightRec>* temp;

    while (head != NULL) {
        temp = head;
        head = head->next;
        delete temp;
    }
}

template<class FlightRec>
errorCode List<FlightRec>::addNewFlight()
{
    int x;
    string str;
    Node<FlightRec> *newNode,* current = nullptr;
    current = head;
    newNode = new Node<FlightRec>;
    newNode->next = current;
    cout << "\nEnterter FlightNO: ";
    cin >> newNode->entry.FlightNO;
    cout << "\nEnterter Destination: ";
    cin >> newNode->entry.Destination;
    cout << "\nEnterter Time: ";
    cin >> newNode->entry.Time.hour;
    do {
        cout << "\nHours(0-23): ";
        cin >> x;
        if (x < 0 || x>23) {
            cout << "\nIncorrect input, try again";
        }
    } while (x < 0 || x>23);
    newNode->entry.Time.hour = x;
    do {
        cout << "\nMinutes(0-59): ";
        cin >> x;
        if (x < 0 || x>59) {
            cout << "\nIncorrect input, try again";
        }
    } while (x < 0 || x>59);
    newNode->entry.Time.min = x;
    cout << "\nEnterter Ftype: ";
    cin >> str;
    if (str == "Departure") {
        newNode->entry.Ftype = Departure;

    }
    else { newNode->entry.Ftype = Arrival; }
    cout << "\nEnterter Delay: ";
    cin >> newNode->entry.Delay;
    if (newNode->entry.Delay == true) {
        cout << "\nEnterter ExpectedTime: ";
        do {
            cout << "\nHours(0-23): ";
            cin >> x;
            if (x < 0 || x>23) {
                cout << "\nIncorrect input, try again";
            }
        } while (x < 0 || x>23);
        newNode->entry.ExpectedTime.hour = x;
        do {
            cout << "\nMinutes(0-59): ";
            cin >> x;
            if (x < 0 || x>59) {
                cout << "\nIncorrect input, try again";
            }
        } while (x < 0 || x>59);
        newNode->entry.ExpectedTime.min = x;
    }
    head = newNode;
    count++;
    return success;
}

template<class FlightRec>
errorCode List<FlightRec>::deleteFlight()
{
    string str;
    cout << "\nEnter Flight number: ";
    cin >> str;
    Node<FlightRec>* current = head;
    for (int i = 0; i < count; i++) {
        if (current->entry.FlightNO==str){
            Node<FlightRec>* previous = nullptr;
            if (i == 0) current = head;
            else {
                previous = setPosition(i - 1);
                current = previous->next;
            }
            if (i == 0) head = head->next;
            else previous->next = current->next;
            delete  current;
            count--;
            return success;

        }
        current = current->next;
    }
}

template<class FlightRec>
errorCode List<FlightRec>::modifyFlightTime()
{
    string str;
    cout << "\nEnter Flight number: ";
    cin >> str;
    Node<FlightRec>* current = head;
    for (int i = 0; i < count; i++) {
        if (current->entry.FlightNO == str) {
            cout << "\nEnter new data";
            int x;
            do {
                cout << "\nHours(0-23): ";
                cin >> x;
                if (x < 0 || x>23) {
                    cout << "\nIncorrect input, try again";
                }
            } while (x < 0 || x>23);
            current->entry.Time.hour = x;
            do {
                cout << "\nMinutes(0-59): ";
                cin >> x;
                if (x < 0 || x>59) {
                    cout << "\nIncorrect input, try again";
                }
            } while (x < 0 || x>59);
            current->entry.Time.min = x;
            return success;
           
        }
        current = current->next;
    }
}

template<class FlightRec>
void List<FlightRec>::enterDelay()
{
    int x;
    string str;
    cout << "\nEnter Flight number: ";
    cin >> str;
    Node<FlightRec>* current = head;
    for (int i = 0; i < count; i++) {
        if (current->entry.FlightNO == str) {
            cout << "\nEnterter Delay: ";
            cin >> current->entry.Delay;
            if (current->entry.Delay == true) {
                cout << "\nEnterter ExpectedTime: ";
                do {
                    cout << "\nHours(0-23): ";
                    cin >> x;
                    if (x < 0 || x>23) {
                        cout << "\nIncorrect input, try again";
                    }
                } while (x < 0 || x>23);
                current->entry.ExpectedTime.hour = x;
                do {
                    cout << "\nMinutes(0-59): ";
                    cin >> x;
                    if (x < 0 || x>59) {
                        cout << "\nIncorrect input, try again";
                    }
                } while (x < 0 || x>59);
                current->entry.ExpectedTime.min = x;
            }
        }
        current = current->next;
    }
}

template<class FlightRec>
void List<FlightRec>::displayAllFlights()
{
    Node<FlightRec>* current = head;
    for (int i = 0; i < count; i++) {
        cout << "\n" << current->entry.FlightNO << " " << current->entry.Destination << " " << current->entry.Time.hour<<":"<< current->entry.Time.min;
        cout << " " << current->entry.Ftype << " " << current->entry.Delay << " " << current->entry.ExpectedTime.hour<<":" << current->entry.ExpectedTime.min;
        current = current->next;
    }
}

template<class FlightRec>
void List<FlightRec>::displayDepartures()
{
    Node<FlightRec>* current = head;
    for (int i = 0; i < count; i++) {
        if (current->entry.Ftype == Departure) {
            cout << "\n" << current->entry.FlightNO << " " << current->entry.Destination << " " << current->entry.Time.hour << ":" << current->entry.Time.min;
            cout << " " << current->entry.Ftype << " " << current->entry.Delay << " " << current->entry.ExpectedTime.hour << ":" << current->entry.ExpectedTime.min;
        }
        current = current->next;
    }
}

template<class FlightRec>
void List<FlightRec>::displayArrivals()
{      
    Node<FlightRec>* current = head;
    for (int i = 0; i < count; i++) {
        if (current->entry.Ftype != Departure) {
            cout << "\n" << current->entry.FlightNO << " " << current->entry.Destination << " " << current->entry.Time.hour << ":" << current->entry.Time.min;
            cout << " " << current->entry.Ftype << " " << current->entry.Delay << " " << current->entry.ExpectedTime.hour << ":" << current->entry.ExpectedTime.min;
        }
    }
            current = current->next;
   
   
}



