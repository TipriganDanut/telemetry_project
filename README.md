
This project is a C++ telemetry simulation system that I am currently developing in my free time to strengthen my skills in high‑level software engineering.
Currently it simulates certain vehicle telemetry data, distributes it through an Observer pattern, persists it using SQLite, and visualizes it in charts through a Qt‑based GUI.
The goal of this project is to practice building a clean, scalable, production‑style architecture — the kind used in automotive and industrial embedded systems.

**Key Features:**

• Modular CMake architecture with separate Simulation, Persistence, and GUI modules

• Observer pattern for clean decoupling between simulation, logging, and UI

• Real‑time simulation loop running in a dedicated thread

• SQLite persistence layer using a repository pattern

• Qt GUI for displaying live telemetry

• Clean separation of concerns across all components

• Professional Git workflow with structured commits and repository hygiene

**Skills Practiced:**

• C++ & Software Architecture (C++17, OOP design patterns, Multithreading)


• Build Systems & Tooling (CMake, MSVC & Qt Creator toolchain)


• Persistence & Data Handling (SQLite, decoupled persistence observer)


• GUI Development (Qt Widgets, Signals/slots, Real‑time UI updates)


• Professional Engineering Workflow


• Debugging compiler and linker issues

**Architecture Overview:**
The project is split into three main modules and each module is isolated and communicates through well‑defined interfaces:


• **SimulationLib**  
  Generates telemetry data, manages the simulation loop, and notifies observers.


• **PersistenceLib**  
  Implements a repository and an observer that logs telemetry to SQLite.


• **VehicleTelemetryGUI**  
  Qt application that displays live telemetry data.

This project represents my commitment to continuous learning and my interest in automotive software and high‑level C++ development.  
This project is developed independently. I am using AI tools (Microsoft Copilot) as a technical sounding board for debugging, architectural decisions, and workflow improvements.

