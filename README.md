# 🎮 C++ Cybersecurity Training Game

An interactive **terminal-based cybersecurity simulation game** developed in **native C++** to teach foundational offensive and defensive security concepts through progressive hands-on challenges.

The game recreates a command-line style learning environment featuring scoring systems, simulated security labs, networking exercises, and authentication challenges — all implemented using core procedural C++ without external frameworks.

---

# 📌 Project Overview

This project was designed as an educational cybersecurity training simulator capable of:

* Teaching Linux command-line fundamentals
* Demonstrating password auditing concepts
* Simulating network packet analysis workflows
* Recreating authentication and privilege escalation scenarios
* Tracking user progression through multi-level gameplay

The entire system operates inside a custom terminal interface enhanced using ANSI styling and real-time interaction logic.

---

# ⚙️ Core Technical Features

# 🖥️ 1. Interactive Terminal Engine

### ✔ ANSI-Based Console Interface

Implements:

* Colored terminal rendering
* Dynamic text formatting
* Interactive command prompts
* Real-time console feedback

### ✔ Game State Management

Custom operational loops manage:

* User progression
* Level transitions
* Score compilation
* Attempt tracking
* Failure conditions

---

# 🧠 2. Real-Time Input Validation System

### ✔ Secure Command Parsing

Processes and validates:

* Linux-style commands
* Simulated authentication inputs
* Packet analysis responses
* Interactive challenge solutions

### ✔ Sandboxed Stage Logic

Each level executes independently with:

* Dedicated validation handlers
* Context-aware challenge processing
* Dynamic gameplay progression

---

# 🕹️ Game Levels & Implementations

# 🐧 Level 1 — Linux CLI Mastery Challenge

Introduces essential Linux command-line operations through guided tutorials and interactive challenges.

### Topics Covered:

* File navigation
* File management
* Permission handling
* System monitoring
* Basic networking utilities

### Commands Simulated:

```bash id="6gtd1x"
chmod
ps aux
ping
ls
cd
mkdir
rm
```

### Features:

* Command verification engine
* Real-time scoring system
* Multi-question challenge mode
* Terminal simulation workflow

---

# 🔓 Level 2 — Brute-Force Password Analytics

Simulates authentication systems and password auditing workflows.

### Core Concepts:

* Credential strength analysis
* Brute-force attack logic
* Password complexity evaluation
* Iterative authentication loops

### Technical Implementations:

* Recursive attempt tracking
* Validation heuristics
* Login simulation states
* Failure & retry management

---

# 🌐 Level 3 — Interactive Network Forensics Simulator

Implements a lightweight networking simulation environment using structured packet modeling.

### `NetworkPacket` Structure Includes:

* Source IP Address
* Destination IP Address
* Port Numbers
* Protocol Flags (TCP/UDP)
* Packet Checksums
* Data Payload Streams

### Technical Features:

* Simulated packet parsing
* Bitwise XOR validation
* Logical checksum verification
* Packet integrity analysis

---

# 🔐 Level 4 — Simulated Web Security Authentication

Recreates simplified web authentication and access control scenarios.

### Simulated Concepts:

* Login validation
* Authentication bypass logic
* Privilege escalation workflows
* Access verification models

### Features:

* Mock application states
* Dynamic credential checks
* Conditional access control
* Security rule evaluation

---

# 🏗️ System Architecture

```text
main.cpp
│
├── linux_challenge.cpp
├── password_analytics.cpp
├── network_forensics.cpp
├── web_auth_simulator.cpp
├── scoring_engine.cpp
└── utility_modules.cpp
```

The modular architecture improves:

* Maintainability
* Expandability
* Code readability
* Feature isolation

---

# 💻 Tech Stack & Dependencies

| Category              | Technology                         |
| --------------------- | ---------------------------------- |
| **Language**          | Native C++                         |
| **Programming Style** | Procedural & Modular               |
| **Terminal Engine**   | ANSI Escape Styling                |
| **Platform**          | Cross-Platform Console Application |

---

# 📚 Libraries Utilized

```cpp id="kw14lh"
<iostream>
<vector>
<chrono>
<thread>
<random>
<algorithm>
<string>
```

---

# 🚀 How to Run

## 1️⃣ Clone the Repository

```bash id="m90k7d"
git clone <repository-link>
```

---

## 2️⃣ Compile the Project

Using **G++**:

```bash id="e7dwg2"
g++ main.cpp -o cyber_game
```

Using **Clang**:

```bash id="mxnqg1"
clang++ main.cpp -o cyber_game
```

---

## 3️⃣ Run the Game

### Linux / macOS

```bash id="2yj0m4"
./cyber_game
```

### Windows

```bash id="c4kg88"
cyber_game.exe
```

---

# 📊 Key Concepts Demonstrated

* Linux Command-Line Operations
* Authentication Systems
* Password Security Concepts
* Network Packet Structures
* Bitwise Operations
* Input Validation
* Terminal UI Engineering
* Interactive Simulation Design
* Game State Management
* Cybersecurity Training Logic

---

# 🎯 Project Goals

* Teach cybersecurity concepts interactively
* Simulate real-world security workflows
* Strengthen C++ programming fundamentals
* Explore low-level terminal application development
* Build educational cybersecurity tooling

---

# 🔒 Cybersecurity Concepts Covered

* Linux Fundamentals
* Password Auditing
* Brute-Force Simulation
* Network Packet Analysis
* Authentication Logic
* Access Control
* Security Validation
* Privilege Escalation Concepts

---

# 👨‍💻 Project Domain

* Cybersecurity Education
* C++ Systems Programming
* Terminal Application Development
* Interactive Simulations
* Defensive & Offensive Security Training
* CLI Game Development


