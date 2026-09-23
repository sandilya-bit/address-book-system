# 📖 Address Book System — C++ Mini Project

A menu-driven **Address Book System** in C++ using **Structures** — built as a college mini-project (first-year / second-year level).

**🌐 Live Web Prototype:** https://sandilya-bit.github.io/address-book-system/

## Features

```
=========================
ADDRESS BOOK SYSTEM
=========================
1. Add Contact
2. Search Contact
3. Delete Contact
4. Display Contacts
5. Exit
=========================
Enter Choice:
```

| Module | Output |
|---|---|
| 1. Add Contact | Contact Added Successfully (with phone/email validation) |
| 2. Search Contact | Contact details / Contact Not Found (case-insensitive) |
| 3. Delete Contact | Contact Deleted Successfully / Contact Not Found |
| 4. Display Contacts | All stored contacts with total count |
| 5. Exit | Goodbye message, program ends |

## Concepts Demonstrated

- **Structures** — `struct Contact { name; phone; email; address; }`
- **Arrays** — `Contact contacts[100]` (array of structures)
- **Functions** — one function per module; search logic reused by Search & Delete
- **String Handling** — `getline`, `tolower`, `isdigit`, validation loops
- **Menu-Driven Programming** — do-while loop + switch

## How to Compile & Run

```bash
g++ -std=c++17 -Wall -Wextra -o address_book address_book.cpp
./address_book        # (Windows: address_book.exe)
```

Or download **`address_book.exe`** — a standalone build that runs on any Windows PC with no installation.

## Files

| File | Description |
|---|---|
| `index.html` | 🌐 Web GUI prototype (served by GitHub Pages) |
| `address_book.cpp` | Complete C++ source code |
| `address_book.exe` | Standalone Windows executable |
| `PROJECT_REPORT.pdf` | Full formatted project report |
| `PROJECT_REPORT.md` | Report source (markdown) |
| `VIVA_QUESTIONS.md` | 42 viva questions with answers |

---
*Developed by Sandilya — Department of Computer Science & Engineering*
