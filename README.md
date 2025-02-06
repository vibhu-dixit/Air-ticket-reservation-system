# Air Ticket Reservation System

A console-based C++ application for managing flight reservations, cancellations, and passenger records with a text-based UI.

## Features

- **Reservation**: Book tickets (Economic/Executive class).
- **Cancellation**: Cancel tickets using ticket numbers.
- **Flight Enquiry**: View flights, routes, and fares.
- **Passenger Records**: Display passenger details.
- **Delete Records**: Remove all passengers for a flight.
- **List Passengers**: View passengers for a selected flight.

## Prerequisites

- **Compiler**: Turbo C++ or Borland C++ (uses legacy headers like `conio.h`, `dos.h`).
- **OS**: Compatible with DOS-based systems or emulators (e.g., DOSBox).

## Installation & Usage

1. **Compile**: Open `airticket.cpp` in Turbo C++ and build the executable.
2. **Run**: Execute the `.exe` file and follow menu prompts.
3. **Data Files**:
   - `TICKET.DAT`: Stores flight details.
   - `PASS.DAT`: Stores passenger records.

## Code Structure

### Classes

1. **`DRAW`**: Handles UI elements (boxes, lines) using `gotoxy` and `cout`.
2. **`TICKET`**: Manages flight data (e.g., `ADDITION()`, `ENQUIRY()`).
3. **`PASSENGER`**: Manages passenger data (e.g., `ADD_RECORD()`, `DELETE_TICKET()`).
4. **`RESERVE`**: Core functionality (e.g., `RESERVATION()`, `CANCELLATION()`).

## Example Usage

1. **Reserve a Ticket**: Select `1`, choose a flight, and enter passenger details.
2. **Cancel a Ticket**: Select `2` and enter the ticket number.
3. **View Flight List**: Select `4`.

---

# Concepts and Learning

## **1. Object-Oriented Programming (OOP)**  
- **Classes & Objects**: Structured data using classes like `DRAW`, `TICKET`, and `PASSENGER`.  
- **Inheritance**: Derived `RESERVE` from `TICKET` and `PASSENGER` for code reuse.  
- **Encapsulation**: Used `private` and `protected` to secure sensitive data.  
- **Data Abstraction**: Exposed essential functions like `ADD_RECORD()` while hiding implementation details.  

## **2. File Handling**  
- **Binary File Operations**: Stored data in `.DAT` files using `fstream`.  
- **Data Persistence**: Retained data between program runs.  
- **Record Management**: Added, deleted, and searched records (e.g., `DELETE_TICKET()`).  

## **3. User Interface (UI) Design**  
- **Text-Based UI**: Used `conio.h` functions like `gotoxy()` and `clrscr()` for UI design.  
- **Input Validation**: Ensured valid inputs (e.g., age range, flight number).  
- **Interactive Menus**: Created nested menus for user interaction.  

## **4. Problem-Solving Skills**  
- **Modular Programming**: Split code into smaller functions for easier debugging.  
- **Error Handling**: Added checks for edge cases (e.g., seat availability).  
- **Data Linking**: Connected flight and passenger records using ticket numbers.  

## **5. Real-World Application**  
- **Project Planning**: Mapped features (reservation, cancellation) to code structures.  
- **Debugging**: Fixed issues like incorrect file paths and infinite loops.  
- **Documentation**: Wrote comments and a README for clarity.  

---

## Limitations

- **Legacy Code**: Uses outdated headers (`iostream.h`, `conio.h`) and non-standard `void main()`.
- **Hardcoded Flights**: Default flights cannot be modified without recompiling.
- **UI Constraints**: Text-based interface with limited navigation.

---

This project strengthened my understanding of **C++ programming** and aligned with the **CBSE syllabus** (OOP, File Handling, Arrays & Strings). It was a great learning experience! 🚀  
