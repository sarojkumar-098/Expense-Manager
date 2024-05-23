#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Structure to represent each expense
typedef struct ExpenseNode {
    char date[20];
    char payee[50];
    float amount;
    struct ExpenseNode *next;
} ExpenseNode;

// Structure to represent a queue of expenses
typedef struct {
    ExpenseNode *front;
    ExpenseNode *rear;
} ExpenseQueue;

// Structure to represent each category node in the tree
typedef struct TreeNode {
    char category[50];
    ExpenseQueue queue;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// Function to create a new node in the tree
struct TreeNode* createNode(char category[]) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    strcpy(newNode->category, category);
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->queue.front = NULL;
    newNode->queue.rear = NULL;
    return newNode;
}

int isQueueEmpty(ExpenseQueue *queue) {
    return queue->front == NULL;
}

// Function to add an expense structure, date, payee, amount you want to add
void enqueue(ExpenseQueue *queue, char date[], char payee[], float amount) {
    ExpenseNode newNode = (ExpenseNode)malloc(sizeof(ExpenseNode));
    // if (newNode == NULL) {
    //     return;
    // }
    strcpy(newNode->date, date);
    strcpy(newNode->payee, payee);
    newNode->amount = amount;
    newNode->next = NULL;
    if (isQueueEmpty(queue)) {
        queue->front = newNode;
    } else {
        queue->rear->next = newNode;
    }
    queue->rear = newNode;
}

// Function to display expenses for each category, prints category and then its all transactions(pre-order traversal)
void displayExpenses(TreeNode* root) {
    if (root != NULL) {
        // printf("Category: %s\n", root->category);
        if (!isQueueEmpty(&(root->queue))) {
            ExpenseNode *firstTransaction = root->queue.front;
            struct ExpenseNode * current = firstTransaction;
            printf("Category: %s\n", root->category);
            while(current != NULL){
                printf("Date: %s | Payee: %s | Amount: %.2f\n", firstTransaction->date, firstTransaction->payee, firstTransaction->amount);
                current = current->next;
            }
            printf("\nPrintng Expenses Successful!\n");
        } 
        displayExpenses(root->left);
        displayExpenses(root->right);
    }
}

// Function to print all expenses of a particular category, takes category as a input and print all transaction of that category
void printCategoryExpenses(TreeNode* root, char category[]) {
    if (root != NULL) {
        if (strcmp(category, root->category) == 0) {
            // printf("Category: %s\n", root->category);
            if (isQueueEmpty(&(root->queue))) {
                return;
            }
            else {
                printf("All Expenses:\n");
                ExpenseNode *current = root->queue.front;
                while (current != NULL) {
                printf("Date: %s | Payee: %s | Amount: %.2f\n", current->date, current->payee, current->amount);
                current = current->next;
                }
            }
            printf("\nPrinting Category Successful!\n");
            return;
        }
        printCategoryExpenses(root->left, category);
        printCategoryExpenses(root->right, category);
    }
}


void addExpense(TreeNode ** root, char date[20], char payee[50], float amount, char category[50]) {
    if (*root == NULL) {
        *root = createNode(category);
    } else {
        if (strcmp(category, (*root)->category) == 0) {
            enqueue(&((*root)->queue), date, payee, amount);
        } else if (strcmp(category, (*root)->category) < 0) {
            addExpense(&((*root)->left), date, payee, amount, category);
        } else {
            addExpense(&((*root)->right), date, payee, amount, category);
        }
    }
}


// Function to add expense, takes the file and then edit categories queue using enqueue function
void expense_filename(TreeNode* root, char filename[], float *current_expenses) {
    
    FILE* file = fopen(filename, "r");

    /* The file expense contains: (for our case)
        24-03-2024 PNB 12000 Bills
        04-04-2024 Prince 1200 Others 
    */

    char line[100]; // Assuming each line won't exceed 100 characters
    char *token; // Used to break the strings into single words separated by commas, spaces

    if (file == NULL) {
        printf("File doesn't exist.\n");
        return;
    }
    while (fgets(line, sizeof(line), file) != NULL) {
    char date[20], payee[50], category[20];
    float amount;
    
    token = strtok(line, " ");
    if (token != NULL) {
        strcpy(date, token);
        token = strtok(NULL, " "); // Here we take NULL to continue in the same line, next line will be initiates by fgets
        if (token != NULL) {
            strcpy(payee, token);
            token = strtok(NULL, " ");
            if (token != NULL) {
                amount = atof(token);
                token = strtok(NULL, " ");
                *current_expenses += amount;
                if (token != NULL) {
                    strcpy(category, token);
                    // printf("Date: %s | Payee: %s | Amount: %.2f | Category: %s\n", date, payee, amount, category);
                    addExpense(&(root), date, payee, amount, category);
                }
            }
        }
    }
}

    fclose(file);
}

// Function to search transactions based on payee name, date, or amount
void searchTransactions(TreeNode* root, char key[], char option[]) {
    if (root != NULL) {
        searchTransactions(root->left, key, option);
        if (!isQueueEmpty(&(root->queue))) {
            ExpenseNode *current = root->queue.front;
            while (current != NULL) {
                if ((strcmp(option, "payee") == 0 && strcmp(current->payee, key) == 0) ||
                    (strcmp(option, "date") == 0 && strcmp(current->date, key) == 0) ||
                    (strcmp(option, "amount") == 0 && current->amount == atof(key))) { // atof converts strings to float 
                    // printf("\nCategory: %s\n", root->category);
                    printf("\nDate: %s | Payee: %s | Amount: %.2f\n", current->date, current->payee, current->amount);
                    printf("\nSearch Successful!\n"); // Moved inside the condition
                }
                current = current->next;
            }
        }
        searchTransactions(root->right, key, option);
    } 
}


int main() {
    TreeNode* root = NULL;
    clock_t start, end;
    double time_taken = 0.0f;

    // Defining some default categoies to the tree
    // New categories id any given by user will be added based upon its lexicographic order
    if (root == NULL) {
        root = createNode("ALL");
        root->left = createNode("Bills");
        root->right = createNode("Others");
        root->left->left = createNode("Housing");
        root->left->right = createNode("Maintenance");
        root->right->left = createNode("Food");
        root->right->right = createNode("Transportation");
        root->right->left->left = createNode("Family");
        root->right->left->right = createNode("Friends");
    }

    float current_income = 0;
    float current_expenses = 0;

 
    // Basic UI and choosing of which function to perform
    printf("    What do you want to do? Choose from the following:\n");
    printf("    1. Add Income\n");
    printf("    2. Add Expense\n");
    printf("    3. View all category's transactions\n");
    printf("    4. View Category's all transactions\n");
    printf("    5. Search all transactions\n");
    printf("    6. Money left\n");
    printf("    7. Exit\n");

    char choosen_option[50];
    scanf("%s",  choosen_option);
    start = clock();
    while(strcmp(choosen_option, "7") != 0){
        
        if(strcmp(choosen_option,"1") == 0){
            float to_add_income = 0;
            printf("Add the amount you want to add:\n");
            scanf("%f", &to_add_income);
            current_income += to_add_income;
        }
        else if(strcmp(choosen_option,"2") == 0){
            char filename[50];
            printf("Enter the expense filename:\n");
            scanf("%s", filename);
            expense_filename(root, filename, &current_expenses);
        }
        else if(strcmp(choosen_option,"3") == 0){
            displayExpenses(root);
        }
        else if(strcmp(choosen_option,"4") == 0){
            char categoryToPrint[50];
            printf("\nEnter category to print all expenses: ");
            scanf("%s", categoryToPrint);
            printCategoryExpenses(root, categoryToPrint);
        }
        else if(strcmp(choosen_option, "5") == 0){
            char key[50], option[10];
            printf("Enter search option (payee/date/amount): \n");
            scanf("%s", option);
            printf("Enter search key: \n");
            scanf("%s", key);
            searchTransactions(root, key, option);
        }
        else if(strcmp(choosen_option, "6") == 0){
            printf("%.2f", current_income - current_expenses);
        }
        printf("\n    What do you want to do? Choose from the following:\n");
        printf("    1. Add Income\n");
        printf("    2. Add Expense\n");
        printf("    3. View all category's transactions\n");
        printf("    4. View Category's all transaction\n");
        printf("    5. Search all transactions\n");
        printf("    6. Money left\n");
        printf("    7. Exit\n");
        scanf("%s", choosen_option);
        
    }
    end = clock();
    time_taken += ((double) (end-start)) / CLOCKS_PER_SEC;
    printf("\nTime Taken: %f", time_taken);
    return 0;
}