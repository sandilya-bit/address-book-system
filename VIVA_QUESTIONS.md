# VIVA QUESTIONS & ANSWERS — Address Book System (C++)

*Prepared for first-year / second-year B.Tech / BCA / B.Sc (CS) practical examination.*

---

## Section A : Basics of the Project

**Q1. What is your project about?**
**A:** It is a menu-driven **Address Book System** developed in C++. It stores contact details (Name, Phone, Email, Address) using structures and performs Add, Search, Delete and Display operations through a menu that repeats until the user chooses Exit.

**Q2. Why did you choose C++ for this project?**
**A:** C++ supports structures and arrays for organized data storage, provides a rich string library, compiles to fast native code, and is the language prescribed for our course. Its procedural style is ideal for demonstrating structures, functions and menu-driven programming.

**Q3. Which data structure did you use and why?**
**A:** An **array of structures** (`Contact contacts[100]`). Structures group all fields of one contact together; the array stores many contacts in contiguous memory. It is simple, needs no pointers or dynamic memory, and directly supports linear traversal — which matches the course requirements.

**Q4. What is the maximum number of contacts your system can store?**
**A:** 100, defined by the constant `MAX_CONTACTS`. It can be increased by changing one line, or replaced with dynamic memory for unlimited capacity.

**Q5. Is your data saved permanently? What happens when the program closes?**
**A:** No. Data is stored in **RAM**, so it is lost when the program ends. Permanent saving using files (`fstream`) is listed as a future enhancement.

---

## Section B : Structures

**Q6. What is a structure in C++?**
**A:** A structure is a **user-defined data type** that groups variables of different data types under a single name. Each variable inside it is called a **member** (or field).

**Q7. Show the structure you used.**
**A:**
```cpp
struct Contact
{
    string name;
    string phone;
    string email;
    string address;
};
```

**Q8. What is the difference between a structure and an array?**
**A:** An array stores **many values of the same type**; a structure stores **related values of different types** as one unit. In my project, one `Contact` structure holds four different strings, and the array `contacts[]` holds up to 100 such structures.

**Q9. What is the difference between a structure and a class in C++?**
**A:** The only default difference is **access**: structure members are `public` by default, class members are `private` by default. Structures are traditionally used for plain data records (like my contact record); classes are used for object-oriented design with encapsulation and member functions.

**Q10. How do you access the members of a structure?**
**A:** Using the **dot operator**: `contacts[i].name`, `contacts[i].phone`, etc. If accessing through a pointer, the arrow operator is used: `ptr->name`.

**Q11. What is a nested structure? Did you use one?**
**A:** A structure declared inside another structure. I did not need one; if required, `Address` (house, city, pincode) could be a separate structure nested inside `Contact`.

**Q12. What is the size of a structure in memory?**
**A:** At least the **sum of the sizes of its members** (plus possible padding bytes for alignment). My `Contact` has four `std::string` members, so its size is 4 × sizeof(std::string).

---

## Section C : Functions & Program Flow

**Q13. List the main functions of your program.**
**A:** `addContact()`, `searchContact()` (returns the index), `searchContactUI()` (interface), `deleteContact()`, `displayContacts()`, `showMenu()`, plus helpers `toLowerCase()`, `isValidPhone()`, `isValidEmail()`, `printContact()` and `printLine()`. `main()` drives the menu loop.

**Q14. Why did you divide the program into functions?**
**A:** For **modularity**: each module is independent, the code becomes readable, debugging is easier, and logic can be reused — for example `searchContact()` is used by both the Search and the Delete modules.

**Q15. Why is the menu written inside a do-while loop?**
**A:** Because the menu must be shown **at least once** and then repeated after every operation until the user enters 5. A do-while is an **exit-controlled** loop that guarantees at least one iteration — exactly this behaviour. (`while (choice != 5);`)

**Q16. Why did you use switch instead of if-else for the menu?**
**A:** `switch` is cleaner and more readable for multi-way branching on a single integer variable (the choice), and it directly maps one case to one module.

**Q17. Why does `searchContact()` return an `int`?**
**A:** It returns the **index** of the found contact (so the caller can display or delete it), or `-1` as a sentinel value meaning "not found".

**Q18. What are global variables in your program and why did you use them?**
**A:** `contacts` (the array) and `contactCount`. They are shared by all modules, so passing them as parameters to every function would be repetitive. In bigger projects, they would be wrapped in a class or passed explicitly.

---

## Section D : String Handling

**Q19. Why is the phone number stored as a string and not an int?**
**A:** Phone numbers can be **longer than the int range**, may **start with 0** (which an int would drop), may contain a leading `+` in some formats, and are validated character-by-character. String storage handles all of this naturally.

**Q20. Why did you use `getline()` instead of `cin >>`?**
**A:** `cin >>` stops reading at the first **space**, so "Rahul Sharma" would be cut to "Rahul". `getline(cin, str)` reads the **entire line including spaces**, which is essential for names and addresses.

**Q21. What is the purpose of `cin.ignore()` in your code?**
**A:** After `cin >> choice`, the **newline character** remains in the input buffer. The next `getline()` would read that empty line and skip input. `cin.ignore(numeric_limits<streamsize>::max(), '\n')` clears the buffer up to and including the newline before every `getline()`.

**Q22. How did you validate the phone number?**
**A:** Character-by-character using `isdigit()` in a loop: every character must be a digit, and the length must be 7–15. Otherwise the user is asked again.

**Q23. How does your case-insensitive search work?**
**A:** A helper function `toLowerCase()` converts both the stored name and the input name to lower case using `tolower()` in a loop, then the comparison is done. So "PRIYA", "priya" and "Priya" all match.

**Q24. Which string functions of C++ did you use?**
**A:** `.length()`, indexing with `[]`, `tolower()`/`isdigit()` from `<cctype>`, and comparison with `==`. (Other useful ones are `substr()`, `find()`, `append()`, `c_str()`.)

**Q25. What is the difference between `string` and `char` array?**
**A:** `std::string` is a class that manages memory automatically, grows dynamically, and supports operators like `==` and `+`. A `char` array is fixed-size, requires functions like `strcmp()` and `strcpy()`, and risks buffer overflow. I used `std::string` for safety and simplicity.

---

## Section E : Searching & Deleting

**Q26. Explain your searching logic.**
**A:** **Linear search**: accept the name → traverse from index 0 to `contactCount-1` → compare names case-insensitively → return the index if a match is found → return -1 if the loop ends without a match.

**Q27. What is the time complexity of your search?**
**A:** O(n) — worst case checks all n contacts. A sorted array would allow O(log n) binary search; a hash table would give O(1) average.

**Q28. How does deletion work in an array?**
**A:** After locating the index, every element **after** it is shifted one position to the left (`contacts[i] = contacts[i+1]`), overwriting the deleted record, and `contactCount` is decremented. The last slot is then free.

**Q29. What is the time complexity of deletion?**
**A:** O(n) — searching is O(n) and shifting up to n-1 elements is O(n).

**Q30. Why do you show the record before deleting it?**
**A:** As a confirmation step — the user sees exactly which contact is about to be removed, preventing accidental deletion of a wrong record.

---

## Section F : General C++ Concepts

**Q31. What is the difference between `=` and `==`?**
**A:** `=` is **assignment** (stores a value); `==` is **comparison** (checks equality). In my code `contacts[i].name == name` compares; `contactCount++` style updates assign.

**Q32. What is `const int MAX_CONTACTS = 100;`?**
**A:** A **named constant** — its value cannot change during execution. Using it instead of a raw number (a "magic number") makes the code clearer and the capacity easy to change.

**Q33. What does `using namespace std;` do?**
**A:** It brings the entire standard library namespace into scope, so I can write `cout`, `cin`, `string` instead of `std::cout`, `std::cin`, `std::string`.

**Q34. What is the difference between `++i` and `i++`?**
**A:** Both increase `i` by 1, but `++i` (pre-increment) returns the new value while `i++` (post-increment) returns the old value. In my loops they behave identically.

**Q35. What are the three types of loops in C++? Which did you use?**
**A:** `for`, `while`, `do-while`. I used `for` for traversals and validation loops, and `do-while` for the main menu and input re-prompting.

**Q36. What is function overloading? Did you use it?**
**A:** Defining multiple functions with the same name but different parameter lists. No — I used descriptive distinct names (`searchContact` and `searchContactUI`) to keep the beginner-level code simple.

**Q37. What is `return 0;` at the end of main()?**
**A:** It returns the **exit status** to the operating system: 0 conventionally means successful termination.

**Q38. What is compilation? Which compiler did you use?**
**A:** Compilation translates human-readable C++ source code into machine code. I used **g++ (GCC/MinGW)** with `g++ -std=c++17 -Wall -Wextra address_book.cpp -o address_book`.

**Q39. What is the difference between syntax error and logical error?**
**A:** A **syntax error** violates language grammar and is caught by the compiler (e.g., missing semicolon). A **logical error** compiles but produces wrong behaviour (e.g., wrong loop bound) and must be found by testing.

**Q40. What are the limitations of your project?**
**A:** Data is not saved permanently (no file storage), capacity is fixed at 100, search is only by name (exact, not partial), no edit/update operation, and it is console-based. All of these are covered in the Enhancements section.

**Q41. What would you improve in the next version?**
**A:** Add `fstream`-based file storage so contacts persist, alphabetical sorting, duplicate detection, edit option, search by phone/email, and finally a GUI.

**Q42. If two contacts have the same name, what happens?**
**A:** Search and delete operate on the **first matching** record. Detecting and handling duplicates is a planned enhancement.

---

## Section G : One-Line Rapid-Fire

| Question | Answer |
|---|---|
| Primary data structure? | Array of structures (`struct Contact`) |
| Search technique? | Linear search (case-insensitive) |
| Search returns? | Index of contact, or -1 if not found |
| Menu loop type? | do-while (exit-controlled) |
| Input method for names? | `getline()` (reads spaces) |
| Buffer-clearing function? | `cin.ignore()` |
| Phone validation? | `isdigit()` on every character, length 7–15 |
| Deletion technique? | Left-shift of subsequent elements |
| Capacity? | `MAX_CONTACTS` = 100 |
| Data persistent? | No — RAM only; files are a future enhancement |
| Compiler used? | g++ (MinGW-w64 GCC) |
| Paradigm? | Procedural, menu-driven |
