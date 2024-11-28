# Library Management System

## Overview

This Library Management System is a desktop application built using **Qt** and **SQL Server** that allows librarians and managers to manage books, staff, and supplies efficiently. It provides features such as adding new books, assigning genres, managing staff, and tracking book supplies.

This project was developed as part of a college course in Computer Engineering.

## Features

- **Book Management**:  
  - Add, update, and search for books by name, author, publisher, or language.
  - Manage book genres using combo boxes for multiple categories.
  
- **Staff Management**:  
  - Add new staff members with details like name, email, phone, salary, and start date.
  - Automatically assign a branch based on librarian or manager.

- **Supply Tracking**:  
  - Record new book batches and track their supply history.
  - Insert supply details automatically into the `Supplies` table.

- **SQL Integration**:  
  - Uses custom SQL queries to interact with tables such as `Books`, `Authors`, `Categories`, and `Supplies`.
  - Dynamic data retrieval using user input.

## Prerequisites

- **Qt Framework**
- **Visual Studio IDE** (or any C++ IDE supporting Qt)
- **SQL Database** (e.g., SQLite, MySQL, or SQL Server)
- **C++ Compiler** (GCC, MSVC, etc.)

## SQL Functions Used

- **Get Branch ID by Librarian ID**:  
  A custom SQL function to retrieve the branch ID from the `Branches` table based on a `LibrarianID`.
  ```sql
  CREATE FUNCTION GetBranchIdByLibrarianId (@librarianId INT) RETURNS INT AS
  BEGIN
      DECLARE @BranchId INT;
      SELECT @BranchId = BranchID FROM Branches WHERE ManagerID = @librarianId;
      RETURN @BranchId;
  END;
  ```

## Example Queries

1. **Search for a Book by Name:**
   ```cpp
   SELECT BookName, CopyID, Edition, CONCAT(a.FirstName, ' ', a.LastName) AS AuthorFullName 
   FROM Books b 
   JOIN Authors a ON b.AuthorID = a.AuthorID 
   WHERE BookName = :searchedBookName;
   ```

2. **Insert New Book Batch:**
   ```cpp
   INSERT INTO Books (BookName, AuthorID, Edition, PublisherID, PagesNo, Languagee) 
   VALUES (:BookName, :AuthorID, :Edition, :PublisherID, :PagesNo, :Languagee);
   ```

## Issues and Debugging

- **Error inserting data into `Supplies` table**:  
  Ensure `CopyID` is correctly retrieved using `lastInsertId()`.
  
- **Ambiguous `CopyID` error**:  
  Ensure table aliases (`b.CopyID`, `c.CopyID`) are used correctly in queries.

## Contributions

Contributions are welcome! Feel free to submit issues, feature requests, or pull requests to improve the project.

## Author

- **Ahmed Salah** - [GitHub Profile](https://github.com/AhmedSalahz03)
