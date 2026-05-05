# 📒 Address Book Management System (C)

![C](https://img.shields.io/badge/Language-C-blue.svg)
![Platform](https://img.shields.io/badge/Platform-Console-lightgrey)
![Status](https://img.shields.io/badge/Status-Completed-brightgreen)
[![License](https://img.shields.io/badge/License-MIT-green)](LICENSE)

---

## 📌 Overview
The Address Book Management System is a console-based application developed in C to manage contact details efficiently. It supports creating, searching, editing, deleting, and listing contacts with strong input validation and persistent storage using file handling.

---

## 🚀 Features
- ➕ Add new contacts
- 🔍 Search contacts (by Name / Phone / Email)
- ✏️ Edit existing contacts
- ❌ Delete contacts
- 📋 Display all contacts in table format
- 💾 Save contacts to file (contacts.txt)
- 📂 Load contacts automatically on startup
- 🔐 Strong input validation:
   - Name → only alphabets & spaces
   - Phone → 10 digits, starts with 6–9
   - Email →
      - must contain @
      - must end with .com
      - no uppercase letters
      - domain only alphabets
- 🚫 Duplicate prevention (Phone & Email)
- 🔁 Retry system (3 attempts for invalid input)

---

## 🛠️ Tech Stack
- **Language:** C  
- **Concepts Used:**
  - Structures
  - Arrays
  - Functions
  - Strings
  - File Handling
  - Recursion & Iteration
  - Input Validation

---

## 📂 Project Structure
```
├── main.c        → Menu-driven interface (entry point)
├── contact.c     → Core logic (create, search, edit, delete)
├── contact.h     → Structure definitions & function declarations
├── file.c        → File handling (save & load contacts)
├── file.h        → File function declarations
├── contacts.txt  → Stored contact data (auto-created)
```

---

## ⚙️ How It Works
1. Loads existing contacts from file at startup.
2. Displays a menu-driven interface.
3. Validates all user inputs:
   - Name → alphabets & spaces only  
   - Phone → 10 digits, starts with 6–9, unique  
   - Email → valid format, unique, ends with `.com`  
4. Stores data using structures and arrays.
5. Saves all contacts to file before exiting.

---

## 🔐 Validation Highlights
- Maximum 3 retry attempts for invalid inputs
- Email validation:
  - Must contain `@`
  - Must end with `.com`
  - Domain contains only alphabets
- Prevents duplicate entries
- Safe input handling to avoid crashes

---

## 📸 Sample Output

## 🧠 Key Learnings
- Modular programming using multiple files
- Debugging segmentation faults and logical errors
- Real-world input validation techniques
- File handling (`fopen`, `fprintf`, `fscanf`)
- Efficient data management using structures

---

## 📈 Future Enhancements
- Support for multiple domains (`.org`, `.net`)
- Sorting contacts (Name / Phone)
- Partial search (substring match)
- Develop a GUI version using Qt framework (C/C++) for better user interaction
- Export contacts to CSV / Excel

---

## 🙌 Author
**Hariharan R**  
🎓 2025 Graduate | Electronics and Communication Engineering  
🔧 Aspiring Embedded Systems Engineer  
💻 Strong in C Programming, Problem Solving & Input Validation Logic  
⚙️ Interested in Embedded Systems, Microcontrollers & Low-Level Development  

---

## 🌟 Support
If you like this project:

⭐ Star this repository  
🍴 Fork and improve it   
📢 Share with others   

---

## 📬 Contact
- GitHub: https://github.com/hariharanr8  
- LinkedIn: https://www.linkedin.com/in/hariharanrbe/  

---

## 🏷️ Tags
`C Programming` `File Handling` `Data Structures` `Console Application` `Projects`
