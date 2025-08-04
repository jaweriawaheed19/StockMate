# StockMate📦🧾  
*C++ Warehouse Inventory and Order Management System*

StockMate is a console-based inventory and order management system developed in C++. It is designed to manage perishable and electronic goods with robust order processing, stock tracking, returns, and low-stock alerts. This project showcases Object-Oriented Programming (OOP) principles like abstraction, inheritance, and polymorphism, alongside file handling and CSV report generation.

## Features

- ✅ *Add & manage products* (Perishable & Electronic)
- 📊 *Display inventory* with clean tabular output
- 🛒 *Order placement* with real-time stock update
- 🔁 *Returns/refunds* with customer order tracking
- ⚠ *Low stock warning* when items fall below threshold
- 📤 *CSV report export* of current inventory (Stock_Report.csv)
- 💾 *Dynamic memory management* and OOP architecture

## Object-Oriented Design

- Product → Abstract base class
- Perishable → Derived class for food items (includes batch, expiry)
- Electronic → Derived class for tech products (includes brand, warranty)
- Order → Class representing customer orders
- Warehouse → Aggregates inventory and handles system logic

## Technologies Used

- *Language*: C++
- *IDE*: Visual Studio
- *Files*: .cpp, .sln, .vcxproj, .csv

## Functionalities

*🗂 Product Management*
- Add, update, delete, and search items
- Support for multiple product categories
- Track brand, expiry date, warranty, and location

*📦 Order Processing*
- Place and manage customer orders
- Check item availability and quantity
- Process returns and refunds

*📊 Inventory Monitoring*
- View complete stock details
- Detect and flag low-stock items
- Filter/search items case-insensitively

*🧾 Report Generation*
- Export inventory as a well-structured CSV file
- Colored headers and formatted columns
- Includes low-stock indicators for quick review

## Learning Outcomes

- Applied core OOP principles: encapsulation, inheritance, abstraction, polymorphism
- Practiced file handling and CSV generation in C++
- Implemented modular design using classes and vectors
- Gained experience with inventory/order logic and string processing
- Learned to manage projects in Visual Studio (.sln, .cpp files)

## Author

*Jaweria Waheed Satti*

- Student – BS Computer Science, Bahria University  
- [LinkedIn](https://www.linkedin.com/in/jaweriasatti)  
- [Email](mailto:jaweriasatti19@gmail.com)

##  License

This project is released under the MIT License.
