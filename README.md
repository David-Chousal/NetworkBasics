
# NetworkBasics

This repository contains three C programs demonstrating basic networking concepts: file transfer with threads, network persistence, and switching scenarios.

## Contents

- `FilesThreads.c` – Multi-threaded file copy utility
- `NPersistence.c` – Calculates timing for non-persistent and persistent HTTP connections
- `Switching.c` – Simulates circuit and packet switching scenarios

---

## 1. FilesThreads.c

**Description:**  
Copies multiple files in parallel using threads. Each thread copies one file from a source to a destination.

**How it works:**  
- Takes the number of file copies to perform, followed by pairs of source and destination filenames.
- Spawns a thread for each file copy operation.

**Usage:**
```bash
gcc -o FilesThreads FilesThreads.c -lpthread
./FilesThreads <n> <src1> <dst1> ... <srcN> <dstN>
```
- `<n>`: Number of file copy operations (threads)
- `<srcX>`: Source filename
- `<dstX>`: Destination filename

**Example:**
```bash
./FilesThreads 2 file1.txt copy1.txt file2.txt copy2.txt
```

---

## 2. NPersistence.c

**Description:**  
Calculates and prints the total time required for HTTP object transfers using persistent and non-persistent connections, based on fixed RTT and DNS values.

**How it works:**  
- No arguments required.
- Prints timing calculations for single and multiple object transfers.

**Usage:**
```bash
gcc -o NPersistence NPersistence.c
./NPersistence
```

---

## 3. Switching.c

**Description:**  
Simulates circuit switching and packet switching scenarios, calculating the number of users supported and various probabilities related to user activity.

**How it works:**  
- Requires four arguments: link bandwidth, user bandwidth, average number of packet switching users, and total number of packet switching users.
- Prints results for both circuit and packet switching scenarios.

**Usage:**
```bash
gcc -o Switching Switching.c -lm
./Switching <linkBandwidth> <userBandwidth> <tPSusers> <nPSusers>
```
- `<linkBandwidth>`: Total link bandwidth (e.g., 200)
- `<userBandwidth>`: Bandwidth per user (e.g., 20)
- `<tPSusers>`: Average number of packet switching users (e.g., 5)
- `<nPSusers>`: Total number of packet switching users (e.g., 10)

**Example:**
```bash
./Switching 200 20 5 10
```

---

## Compilation Notes

- Use `-lpthread` for `FilesThreads.c` and `-lm` for `Switching.c` when compiling.
- All programs are standard C and should compile with `gcc` on Linux.

---

## Author

David Chousal

---
