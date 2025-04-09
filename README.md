# 🧑‍💼 Employee Management System (Terminal-based)

A lightweight, **C-based Employee Management System** with an intuitive **terminal UI powered by ncurses**.  
This project allows users to manage employee data through a menu-driven interface, supporting features like:

- ➕ Add New Employee  
- ✏️ Update Existing Employee  
- ❌ Delete Employee Records  
- 📄 View and Search Employee Info  
- 📊 Sort Employees and View Statistics  
- 📁 Export Data to CSV  

Data is persistently stored in files, making it simple yet effective for small-scale record management without the need for a database.

---

## 🧰 Built With

- **C Programming Language (C17 Standard)**
- **ncurses** – for terminal UI and interactivity
- **File I/O** – to store employee records persistently

---

## 📦 How to Compile & Run

### ✅ Requirements

- GCC Compiler
- ncurses library

### ⚙️ Compilation

```bash
gcc main.c employee.c fileops.c stats.c utils.c ui.c -o ems -lncurses
./ems
```
---
## License
This project is created by Govarthanahri N for educational purposes.
Feel free to fork and modify it for your own use!

**⭐ If you found this useful, consider giving the project a star!**

