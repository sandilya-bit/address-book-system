/* ============================================================
   PROJECT      : ADDRESS BOOK SYSTEM
   LANGUAGE     : C++
    CONCEPTS     : Classes, Encapsulation, Abstraction, Inheritance,
                        Polymorphism, Arrays, String Handling, Loops
    DESCRIPTION  : A menu-driven program to store and manage
                        contacts through an object-oriented class model.
   ============================================================ */

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <memory>
#include <cctype>
#include <utility>

using namespace std;

void printLine(char ch, int length);

const int MAX_CONTACTS = 100;

class Contact
{
private:
    string name;
    string phone;
    string email;
    string address;

public:
    Contact(const string& contactName, const string& contactPhone,
            const string& contactEmail, const string& contactAddress)
        : name(contactName), phone(contactPhone), email(contactEmail),
          address(contactAddress) {}

    virtual ~Contact() {}

    const string& getName() const { return name; }
    const string& getPhone() const { return phone; }
    const string& getEmail() const { return email; }
    const string& getAddress() const { return address; }

protected:
    void displayCommonDetails() const;

public:
    virtual void displayDetails() const = 0;
};

class PersonalContact : public Contact
{
public:
    PersonalContact(const string& name, const string& phone,
                    const string& email, const string& address)
        : Contact(name, phone, email, address) {}

    void displayDetails() const override;
};

class BusinessContact : public Contact
{
private:
    string company;

public:
    BusinessContact(const string& name, const string& phone,
                    const string& email, const string& address,
                    const string& companyName)
        : Contact(name, phone, email, address), company(companyName) {}

    void displayDetails() const override;
};

class AddressBook
{
private:
    unique_ptr<Contact> contacts[MAX_CONTACTS];
    int contactCount;

    int searchContact(const string& name) const;

public:
    AddressBook() : contactCount(0) {}
    void addContact();
    void searchContactUI() const;
    void deleteContact();
    void displayContacts() const;
};

void showMenu();
bool isValidPhone(string phone);
bool isValidEmail(string email);
string toLowerCase(string text);

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
        text[i] = static_cast<char>(tolower(static_cast<unsigned char>(text[i])));
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
        if (!isdigit(static_cast<unsigned char>(phone[i])))
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
void AddressBook::addContact()
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

    string name;
    string phone;
    string email;
    string address;
    string contactType;
    string company;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Contact Type (1. Personal, 2. Business) : ";
    getline(cin, contactType);
    while (contactType != "1" && contactType != "2")
    {
        cout << "Choose 1 for Personal or 2 for Business : ";
        getline(cin, contactType);
    }

    // ---- Input Name ----
    cout << "Enter Name    : ";
    getline(cin, name);
    while (name.empty())
    {
        cout << "Name cannot be empty. Enter Name again : ";
        getline(cin, name);
    }

    // ---- Input Phone Number (validated using string handling) ----
    cout << "Enter Phone   : ";
    getline(cin, phone);
    while (!isValidPhone(phone))
    {
        cout << "Invalid Phone! Enter digits only (7-15 digits) : ";
        getline(cin, phone);
    }

    // ---- Input Email (validated using string handling) ----
    cout << "Enter Email   : ";
    getline(cin, email);
    while (!isValidEmail(email))
    {
        cout << "Invalid Email! It must contain '@' and '.' : ";
        getline(cin, email);
    }

    // ---- Input Address ----
    cout << "Enter Address : ";
    getline(cin, address);

    if (contactType == "2")
    {
        cout << "Enter Company : ";
        getline(cin, company);
        contacts[contactCount].reset(
            new BusinessContact(name, phone, email, address, company));
    }
    else
    {
        contacts[contactCount].reset(new PersonalContact(name, phone, email, address));
    }
    contactCount++;

    cout << endl << ">> Contact Added Successfully" << endl;
}

/* ============================================================
   SEARCHING LOGIC (core function)
   1. Accept contact name (done by the calling function)
   2. Traverse contact records one by one
   3. Compare names (case-insensitive)
   4. If match found  -> return the index of the contact
   5. Else            -> return -1 (not found)
   ============================================================ */
int AddressBook::searchContact(const string& name) const
{
    for (int index = 0; index < contactCount; index++)
    {
        if (toLowerCase(contacts[index]->getName()) == toLowerCase(name))
            return index;
    }
    return -1;
}

void PersonalContact::displayDetails() const
{
    printLine('.', 40);
    cout << "  Type    : Personal" << endl;
    displayCommonDetails();
    printLine('.', 40);
}

void BusinessContact::displayDetails() const
{
    printLine('.', 40);
    cout << "  Type    : Business" << endl;
    cout << "  Company : " << company << endl;
    displayCommonDetails();
    printLine('.', 40);
}

void Contact::displayCommonDetails() const
{
    cout << "  Name    : " << getName() << endl;
    cout << "  Phone   : " << getPhone() << endl;
    cout << "  Email   : " << getEmail() << endl;
    cout << "  Address : " << getAddress() << endl;
}

/* ============================================================
   MODULE 2 : SEARCH CONTACT (User Interface)
   Search By : Name
   Output    : Contact Details Found  OR  Contact Not Found
   ============================================================ */
void AddressBook::searchContactUI() const
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
        if (cin.eof()) return;
        cout << "Name cannot be empty. Enter Name again : ";
        getline(cin, name);
    }

    int index = searchContact(name);

    if (index != -1)
    {
        cout << endl << ">> Contact Details Found" << endl;
        contacts[index]->displayDetails();
    }
    else
    {
        cout << endl << ">> Contact Not Found" << endl;
    }
}

/* ============================================================
   MODULE 3 : DELETE CONTACT
   Input  : Contact Name
   Output : Contact Deleted Successfully  OR  Contact Not Found
   Working: Find the contact, then shift all contacts after it
            one position to the left (array deletion technique).
   ============================================================ */
void AddressBook::deleteContact()
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
        if (cin.eof()) return;
        cout << "Name cannot be empty. Enter Name again : ";
        getline(cin, name);
    }

    int index = searchContact(name);

    if (index == -1)
    {
        cout << endl << ">> Contact Not Found" << endl;
        return;
    }

    cout << endl << "Contact to be deleted :" << endl;
    contacts[index]->displayDetails();

    for (int current = index; current < contactCount - 1; current++)
    {
        contacts[current] = move(contacts[current + 1]);
    }
    contacts[contactCount - 1].reset();
    contactCount--;

    cout << ">> Contact Deleted Successfully" << endl;
}

/* ============================================================
   MODULE 4 : DISPLAY CONTACTS
   Output : List of all stored contacts in a tabular format
   ============================================================ */
void AddressBook::displayContacts() const
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

    for (int index = 0; index < contactCount; index++)
    {
        cout << "Contact #" << (index + 1) << endl;
        contacts[index]->displayDetails();
    }
}

/* ------------------------------------------------------------
   MENU FORMAT (strictly matches specification)
   =========================
   ADDRESS BOOK SYSTEM
   =========================

   1. Add Contact
   2. Search Contact
   3. Delete Contact
   4. Display Contacts
   5. Exit

   Enter Choice:
   ------------------------------------------------------------ */
void showMenu()
{
    cout << endl;
    cout << "=========================" << endl;
    cout << "ADDRESS BOOK SYSTEM" << endl;
    cout << "=========================" << endl;
    cout << endl;
    cout << "1. Add Contact" << endl;
    cout << "2. Search Contact" << endl;
    cout << "3. Delete Contact" << endl;
    cout << "4. Display Contacts" << endl;
    cout << "5. Exit" << endl;
    cout << endl;
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
   7. End Program
   ============================================================ */
int main()
{
    int choice;
    AddressBook addressBook;

    cout << endl << "Welcome to the Address Book System!" << endl;

    do
    {
        showMenu();             // Step 2 : Display Menu
        cin >> choice;          // Step 3 : Accept User Choice

        // If the user types a non-number or EOF is reached
        if (!cin)
        {
            if (cin.eof()) break;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = 0;
        }

        switch (choice)         // Step 4 : Perform Selected Operation
        {
            case 1: addressBook.addContact();      break;
            case 2: addressBook.searchContactUI(); break;
            case 3: addressBook.deleteContact();   break;
            case 4: addressBook.displayContacts(); break;
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
