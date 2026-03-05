# Low Level Command Parser 

A modular command-line terminal written in C that supports:

✔ File operations  - readfile, writefile, appendfile, copyfile, mergefile, filewords

✔ Directory operations -Create directory, Remove directory, List directory contents, Change directory, Show current directory path, Create file in current directory, Delete file in current directory

✔ Text processing  - countwords, reversetext, uppercase, lowercase, copytext

✔ Search utilities  - multi-word search, suffix/prefix search, compare files, compare files, longest/shortest line search

✔ Math calculations  - arithmetic, factorial, median, mode, sort, statistics

✔ System utilities  - date, time, about, clear screen, banner, uptime 

✔ Custom command registration  

---

Replication of a windows terminal with lesser features as OS calls are not used, but offers better UI/UX. 

Includes 50+ commands. 

Uses a virtual filesystem to perform directory operations.

Instructions to compile and run:
1. Go to the correct directory
2. Ensure that all files are saved
3. Type "mingw32-make" to compile from the makefile
4. type ".\terminal.exe" to run the program
5. Rest of the instructions appear as you run the program
