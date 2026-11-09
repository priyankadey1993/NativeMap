# NativeMap
A lightweight desktop application built from scratch using **Native C++ (Win32 API)** and **Windows GDI** to render interactive 2D maps, city nodes, roads, and shortest path highlights without relying on heavy external frameworks like Qt or web engines.

# Features
* **Zero Dependencies:** Runs natively on Windows using standard Windows Desktop Application templates.
* **Custom GDI Rendering:** Uses Win32 GDI pens and brushes to draw map nodes (cities), road networks (edges), and custom highlighted paths.
* **Lightweight & Fast:** Built directly on top of the Win32 message loop (`WM_PAINT`, `wWinMain`).

## Tech Stack
* **Language:** C++
* **Platform:** Windows (Visual Studio)
* **Graphics:** Win32 GDI (Graphics Device Interface)

## How to Run
1. Clone the repository or download the source code.
2. Open the project solution (`.sln`) in **Visual Studio**.
3. Build and run the project (Press **F5**).
