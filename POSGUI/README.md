\# POS System – Qt GUI



A graphical Point of Sale application built with Qt 6 (C++).



\## Features

\- Add and manage stock items

\- Create discount codes (percentage-based)

\- Shopping cart: add / remove items, apply discount

\- Checkout with detailed receipt

\- Real-time stock updates



\## Requirements

\- Qt 6.11 or later (Widgets module)

\- C++17 compiler (MinGW / MSVC)



\## How to Build \& Run

1\. Open `POSGUI.pro` in Qt Creator.

2\. Configure with the Desktop Qt 6.x kit.

3\. Click the green run button (or press Ctrl+R).



Alternatively, from the command line:

```bash

qmake POSGUI.pro

make        # or mingw32-make on Windows

./POSGUI    # executable name

