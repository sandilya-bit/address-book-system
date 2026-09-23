/* ============================================================
   PROJECT      : ADDRESS BOOK SYSTEM
   LANGUAGE     : C++
   CONCEPTS     : Structures, Functions, Arrays, String Handling,
                  Loops, Conditional Statements, Menu Driven Programming
   DESCRIPTION  : A menu-driven program to store and manage
                  contact information using an array of structures.
   ============================================================ */

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

/* ------------------------------------------------------------
   MAXIMUM CAPACITY OF THE ADDRESS BOOK (fixed size array)
   ------------------------------------------------------------ */
const int MAX_CONTACTS = 100;

/* ------------------------------------------------------------
   DATA STRUCTURE DESIGN
   Each contact is stored in one structure variable.
   The address book is an array of such structures.
   ------------------------------------------------------------ */
struct Contact
{
    string name;      // Contact's full name
    string phone;     // Contact's phone number
    string email;     // Contact's email address
    string address;   // Contact's postal address
};

/* Global array of structures acting as the address book */
Contact contacts[MAX_CONTACTS];
int contactCount = 0;      // Number of contacts currently stored

/* ------------------------------------------------------------
   FUNCTION DECLARATIONS (PROTOTYPES)
   ------------------------------------------------------------ */
void showMenu();
void addContact();
int  searchContact(string name);
void searchContactUI();
void deleteContact();
void displayContacts();
bool isValidPhone(string phone);
bool isValidEmail(string email);
string toLowerCase(string text);
void printLine(char ch, int length);

/* ------------------------------------------------------------
   UTILITY : Print a horizontal line (for neat output)
   ------------------------------------------------------------ */
void printLine(char ch, int length)
{
    for (int i = 0; i < length; i++)
        cout << ch;
    cout << endl;
}

/* ------------------------------------------------------------
   STRING HANDLING : Convert a string to lower case so that
   search / delete can match names ignoring capitalisation.
   Example : "JOHN" and "john" are treated as the same name.
   ------------------------------------------------------------ */
string toLowerCase(string text)
{
    for (int i = 0; i < (int)text.length(); i++)
        text[i] = tolower(text[i]);
    return text;
}

/* ------------------------------------------------------------
   STRING HANDLING : Validate a phone number.
   A valid phone number contains only digits (7 to 15 digits).
   ------------------------------------------------------------ */
bool isValidPhone(string phone)
{
    if (phone.length() < 7 || phone.length() > 15)
        return false;

    for (int i = 0; i < (int)phone.length(); i++)
    {
        if (!isdigit(phone[i]))
            return false;      // Any non-digit makes it invalid
    }
    return true;
}

/* ------------------------------------------------------------
   STRING HANDLING : Basic email validation.
   A simple check : email must contain '@' and '.'
   ------------------------------------------------------------ */
bool isValidEmail(string email)
{
    bool hasAt = false, hasDot = false;

    for (int i = 0; i < (int)email.length(); i++)
    {
        if (email[i] == '@') hasAt = true;
        if (email[i] == '.') hasDot = true;
    }
    return (hasAt && hasDot);
}

/* ============================================================
   MODULE 1 : ADD CONTACT
   Input  : Name, Phone Number, Email, Address
   Output : "Contact Added Successfully"
   ============================================================ */
void addContact()
{
    printLine('-', 40);
    cout << "              ADD CONTACT" << endl;
    printLine('-', 40);

    // Check if the address book is full
    if (contactCount >= MAX_CONTACTS)
    {
        cout << "Address Book is Full! Cannot add more contacts." << endl;
        return;
    }

    Contact newContact;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // ---- Input Name ----
    cout << "Enter Name    : ";
    getline(cin, newContact.name);
    while (newContact.name.empty())
    {
        cout << "Name cannot be empty. Enter Name again : ";
        getline(cin, newContact.name);
    }

    // ---- Input Phone Number (validated using string handling) ----
    cout << "Enter Phone   : ";
    getline(cin, newContact.phone);
    while (!isValidPhone(newContact.phone))
    {
        cout << "Invalid Phone! Enter digits only (7-15 digits) : ";
        getline(cin, newContact.phone);
    }

    // ---- Input Email (validated using string handling) ----
    cout << "Enter Email   : ";
    getline(cin, newContact.email);
    while (!isValidEmail(newContact.email))
    {
        cout << "Invalid Email! It must contain '@' and '.' : ";
        getline(cin, newContact.email);
    }

    // ---- Input Address ----
    cout << "Enter Address : ";
    getline(cin, newContact.address);

    // ---- Store the structure into the array ----
    contacts[contactCount] = newContact;
    contactCount++;

    cout << endl << ">> Contact Added Successfully!" << endl;
}

/* ============================================================
   SEARCHING LOGIC (core function)
   1. Accept contact name (done by the calling function)
   2. Traverse contact records one by one
   3. Compare names (case-insensitive)
   4. If match found  -> return the index of the contact
   5. Else            -> return -1 (not found)
   ============================================================ */
int searchContact(string name)
{
    for (int i = 0; i < contactCount; i++)
    {
        if (toLowerCase(contacts[i].name) == toLowerCase(name))
            return i;           // Match found at index i
    }
    return -1;                  // No match found
}

/* ------------------------------------------------------------
   Display one contact in a readable format
   ------------------------------------------------------------ */
void printContact(Contact c)
{
    printLine('.', 40);
    cout << "  Name    : " << c.name << endl;
    cout << "  Phone   : " << c.phone << endl;
    cout << "  Email   : " << c.email << endl;
    cout << "  Address : " << c.address << endl;
    printLine('.', 40);
}

/* ============================================================
   MODULE 2 : SEARCH CONTACT (User Interface)
   Search By : Name
   Output    : Contact details  OR  "Contact Not Found"
   ============================================================ */
void searchContactUI()
{
    printLine('-', 40);
    cout << "             SEARCH CONTACT" << endl;
    printLine('-', 40);

    if (contactCount == 0)
    {
        cout << "Address Book is Empty! Nothing to search." << endl;
        return;
    }

    string name;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter Name to Search : ";
    getline(cin, name);
    while (name.empty())
    {
        cout << "Name cannot be empty. Enter Name again : ";
        getline(cin, name);
    }

    int index = searchContact(name);   // Traverse + Compare happens here

    if (index != -1)
    {
        cout << endl << ">> Contact Found!" << endl;
        printContact(contacts[index]);
    }
    else
    {
        cout << endl << ">> Contact Not Found!" << endl;
    }
}

/* ============================================================
   MODULE 3 : DELETE CONTACT
   Input  : Contact Name
   Output : "Contact Deleted Successfully" OR "Contact Not Found"
   Working: Find the contact, then shift all contacts after it
            one position to the left (array deletion technique).
   ============================================================ */
void deleteContact()
{
    printLine('-', 40);
    cout << "             DELETE CONTACT" << endl;
    printLine('-', 40);

    if (contactCount == 0)
    {
        cout << "Address Book is Empty! Nothing to delete." << endl;
        return;
    }

    string name;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter Name to Delete : ";
    getline(cin, name);
    while (name.empty())
    {
        cout << "Name cannot be empty. Enter Name again : ";
        getline(cin, name);
    }

    int index = searchContact(name);   // Reuse the searching logic

    if (index == -1)
    {
        cout << endl << ">> Contact Not Found!" << endl;
        return;
    }

    cout << endl << "Contact to be deleted :" << endl;
    printContact(contacts[index]);

    // Shift every contact after 'index' one place to the left
    for (int i = index; i < contactCount - 1; i++)
    {
        contacts[i] = contacts[i + 1];
    }
    contactCount--;                     // One contact removed

    cout << ">> Contact Deleted Successfully!" << endl;
}

/* ============================================================
   MODULE 4 : DISPLAY CONTACTS
   Output : List of all stored contacts in a tabular format
   ============================================================ */
void displayContacts()
{
    printLine('-', 40);
    cout << "            ALL CONTACTS" << endl;
    printLine('-', 40);

    if (contactCount == 0)
    {
        cout << "No Contacts Stored Yet!" << endl;
        return;
    }

    cout << "Total Contacts : " << contactCount << endl << endl;

    for (int i = 0; i < contactCount; i++)
    {
        cout << "Contact #" << (i + 1) << endl;
        printContact(contacts[i]);
    }
}

/* ------------------------------------------------------------
   MENU FORMAT (as per requirement)
   ------------------------------------------------------------ */
void showMenu()
{
    printLine('=', 40);
    cout << "        ADDRESS BOOK SYSTEM" << endl;
    printLine('=', 40);
    cout << "1. Add Contact" << endl;
    cout << "2. Search Contact" << endl;
    cout << "3. Delete Contact" << endl;
    cout << "4. Display Contacts" << endl;
    cout << "5. Exit" << endl;
    printLine('=', 40);
    cout << "Enter Choice: ";
}

/* ============================================================
   MAIN FUNCTION : Menu Driven System (Algorithm Driver)
   1. Start Program
   2. Display Menu
   3. Accept User Choice
   4. Perform Selected Operation
   5. Return To Menu
   6. Exit When User Chooses Exit
   ============================================================ */
int main()
{
    int choice;

    cout << endl << "Welcome to the Address Book System!" << endl;

    do
    {
        showMenu();             // Step 2 : Display Menu
        cin >> choice;          // Step 3 : Accept User Choice

        // If the user types a non-number, treat it as an invalid choice
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = 0;
        }

        switch (choice)         // Step 4 : Perform Selected Operation
        {
            case 1: addContact();      break;
            case 2: searchContactUI(); break;
            case 3: deleteContact();   break;
            case 4: displayContacts(); break;
            case 5: cout << endl
                         << "Thank you for using Address Book System. Goodbye!"
                         << endl;
                    break;
            default: cout << endl
                          << "Invalid Choice! Please enter 1 to 5."
                          << endl;
        }
    } while (choice != 5);      // Step 5 : Return To Menu (loop)

    return 0;                   // Step 7 : End Program
}
