# Expense-Manager
Optimizing Expense Management: Leveraging Binary Search Trees for Efficient Categorization


Expense Tracker

Overview
The Expense Tracker is a C program that allows users to manage their personal finances by tracking income and expenses. It organizes expenses into categories and provides functionalities to view, add, and search for transactions.

Features
Add Income: Allows the user to add income to their total balance.
Add Expense: Allows the user to add expenses from a file. Expenses are categorized and stored accordingly.
View All Transactions: Displays all transactions in all categories.
View Category Transactions: Displays all transactions in a specified category.
Search Transactions: Allows the user to search for transactions by payee, date, or amount.
Money Left: Displays the balance after subtracting expenses from income.

Data Structures
ExpenseNode: Represents an individual expense.
ExpenseQueue: Represents a queue of expenses for a particular category.
TreeNode: Represents a category node in a binary search tree.
Files

main.c: Contains the source code for the program.
expenses.txt: Example file containing expenses.

Menu Options:

Add Income: Enter the amount to add to your income.
Add Expense: Enter the filename containing expense data.
View All Transactions: Displays all transactions across all categories.
View Category Transactions: Enter the category name to view transactions.
Search Transactions: Search transactions by payee, date, or amount.
Money Left: Displays the remaining balance.
Exit: Exit the program.

Code Explanation
createNode: Creates a new category node.
isQueueEmpty: Checks if an expense queue is empty.
enqueue: Adds a new expense to a category queue.
displayExpenses: Displays all expenses for all categories (pre-order traversal).
printCategoryExpenses: Displays all expenses for a specified category.
addExpense: Adds an expense to the appropriate category in the tree.
expense_filename: Reads expenses from a file and adds them to the tree.
searchTransactions: Searches for transactions based on payee, date, or amount.
