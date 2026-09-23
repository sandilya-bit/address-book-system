# 📖 Address Book System — C++ Mini Project

A menu-driven **Address Book System** in C++ using **Structures** — built as a college mini-project (first-year / second-year academic requirement).

- 🔗 **Live GitHub Repository:** [https://github.com/sandilya-bit/address-book-system](https://github.com/sandilya-bit/address-book-system)
- 🌐 **Live Web Prototype (GitHub Pages):** [https://sandilya-bit.github.io/address-book-system/](https://sandilya-bit.github.io/address-book-system/)
- 💻 **Standalone Binary:** `address_book.exe` (Statically linked, zero DLL dependencies, runs on any Windows PC)

## Features (Menu)

```
=========================
ADDRESS BOOK SYSTEM
=========================

1. Add Contact
2. Search Contact
3. Delete Contact
4. Display Contacts
5. Exit

Enter Choice:
```

| Module | Input | Output |
|---|---|---|
| 1. Add Contact | Name, Phone, Email, Address | `Contact Added Successfully` (with phone/email validation) |
| 2. Search Contact | Name | `Contact Details Found` or `Contact Not Found` (case-insensitive) |
| 3. Delete Contact | Name | `Contact Deleted Successfully` or `Contact Not Found` |
| 4. Display Contacts | — | List all stored contacts with total count |
| 5. Exit | — | Goodbye message, program ends |

## Project Files

| File | Description |
|---|---|
| `address_book.cpp` | Complete C++ source code (structures + functions + arrays + string handling) |
| `address_book.exe` | Pre-built Windows executable (64-bit, built with GCC 16.2) |
| `PROJECT_REPORT.md` | Full report: objective, problem statement, data structure design, searching logic, modules, algorithm, flowchart, sample outputs, advantages, enhancements, conclusion |
| `VIVA_QUESTIONS.md` | 42 viva questions with answers + rapid-fire table |
| `README.md` | This file — how to compile and run |

## How to Compile & Run

### Windows (MinGW / Code::Blocks / Dev-C++ / WinLibs)
```bash
g++ -std=c++17 -Wall -Wextra -o address_book address_book.cpp
address_book.exe
```
*(Or open `address_book.cpp` in Code::Blocks / Dev-C++ and press Build & Run. No pre-built exe? Use the command above.)*

### Linux / macOS
```bash
g++ -std=c++17 -Wall -Wextra -o address_book address_book.cpp
./address_book
```

### Online (no installation)
Paste `address_book.cpp` into any online C++ compiler (Programiz / OnlineGDB / Compiler Explorer) and click Run. The code uses only the standard library.

**Requirements:** any C++ compiler (C++98 or later works; the code deliberately avoids C++11-only features).

## Concepts Demonstrated

- **Structures** — `struct Contact { name; phone; email; address; }` as the core record
- **Arrays** — `Contact contacts[100]` holds the whole address book
- **Functions** — one function per module, with reusable search logic
- **String Handling** — `getline`, `tolower`, `isdigit`, length/indexing, validation loops
- **Loops** — `do-while` menu, `for` traversals, validation re-prompt loops
- **Conditionals** — `switch` menu dispatch, `if/else` for found/not-found and empty-book cases

## Sample Session

```
Enter Choice: 1
Enter Name    : Rahul Sharma
Enter Phone   : 9876543210
Enter Email   : rahul@gmail.com
Enter Address : 21 MG Road, Bengaluru

>> Contact Added Successfully!

Enter Choice: 2
Enter Name to Search : rahul

>> Contact Found!
  Name    : Rahul Sharma
  Phone   : 9876543210
  ...
```

Full tested outputs (add / search / delete / display / validation / invalid choice) are in `PROJECT_REPORT.md` → Section 9.

## Notes

- Data lives in RAM only — contacts are not saved after closing (file storage is a listed future enhancement).
- Search and delete match names **case-insensitively** and act on the **first** matching record.
- Phone numbers must be 7–15 digits; email must contain `@` and `.`.
