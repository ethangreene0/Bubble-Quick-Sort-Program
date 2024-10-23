#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function declarations
void generate_random_numbers(int arr[], int start, int end, int max_value);
void print_array(int arr[], int size, const char *label);
void copy_array(const int source[], int dest[], int size);
void quick_sort(int arr[], int low, int high);
int partition(int arr[], int low, int high);
void bubble_sort(int arr[], int size);
void handle_sorting(int **numbers, int m, int choice);
void re_generate_random(int **numbers, int n, int m);
void prompt_and_sort(int **numbers, int n, int m);
void clear_input_buffer();

int main() {
    int n, m;

    srand(time(NULL)); // Seed for random number generation

    // User prompt for n and m
    printf("Enter the number of inputs (n): ");
    scanf("%d", &n);

    // Ensure n is even
    while (n % 2 != 0) {
        printf("Enter the number of inputs (n): ");
        scanf("%d", &n);
    }

    printf("Enter the array length (m): ");
    scanf("%d", &m);

    // Ensure m is even and m >= n
    while (m % 2 != 0 || n > m) {
        printf("Enter the array length (m): ");
        scanf("%d", &m);
    }
    int **numbers = (int **)malloc(2 * sizeof(int *));
    for (int i = 0; i < 2; i++) {
        numbers[i] = (int *)malloc(m * sizeof(int));
    }

    printf("Enter n elements: ");
    int user_input_count = 0; // Keep track of user input count

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &numbers[0][i]) != 1) {
            printf("Invalid input detected. Exiting input loop.\n");
            clear_input_buffer();
            break;  // Exit the loop on invalid input
        }
        printf("%d", numbers[0][i]);
        user_input_count++; // Increment valid input count

    }
    printf("%d", user_input_count);


    if (user_input_count < n){
        generate_random_numbers(numbers[0],user_input_count,m,10000);
    }
    // Fill remaining positions with random numbers if n < m
    if (n < m) {
        generate_random_numbers(numbers[0], n, m, 10000);
    }

    // Display the number of user-entered and randomly generated numbers
    printf("\nYou entered %d number(s), ", user_input_count);
    printf("%d randomly generated numbers will be generated\n", m - user_input_count);

    // Start the sorting and interaction process
    prompt_and_sort(numbers, n, m);

    // Free dynamically allocated memory
    for (int i = 0; i < 2; i++) {
        free(numbers[i]);
    }
    free(numbers);

    return 0;
}

// Function to generate random numbers
void generate_random_numbers(int arr[], const int start, const int end, const int max_value) {
    for (int i = start; i < end; i++) {
        arr[i] = rand() % (max_value + 1);
    }
}

// Function to print the array
void print_array(int arr[], const int size, const char *label) {
    printf("%s:\n", label);
    for (int i = 0; i < size; i++) {
        printf("%6d ", arr[i]);
        if ((i + 1) % 10 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

// Function to copy array
void copy_array(const int source[], int dest[], const int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = source[i];
    }
}

// Quick sort function
void quick_sort(int arr[], const int low, const int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

// Partition function for quicksort
int partition(int arr[], const int low, const int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

// Bubble sort function
void bubble_sort(int arr[], const int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to handle sorting based on user input
void handle_sorting(int **numbers, int m, int choice) {
    copy_array(numbers[0], numbers[1], m); // Copy to second row before sorting

    time_t time1, time2;
    time(&time1); // Record start time

    if (choice == 0) {
        quick_sort(numbers[1], 0, m - 1);
    } else if (choice == 1) {
        bubble_sort(numbers[1], m);
    }

    time(&time2); // Record end time

    // Calculate and print the sorting time
    print_array(numbers[1], m, "Sorted Array");
    printf("Sorting took %lld seconds.\n", time2 - time1);
}

// Function to regenerate random numbers and sort
void re_generate_random(int **numbers, int n, int m) {
    generate_random_numbers(numbers[0], n, m, 10000);
    print_array(numbers[0], m, "Original Array with new random numbers");
    prompt_and_sort(numbers, n, m);
}

// Function to handle user prompts and sorting
void prompt_and_sort(int **numbers, int n, int m) {
    int choice;
    char command;

    // Ask user to choose sorting algorithm
    printf("::Choose a sorting algorithm::\n|| (0)Quick sort | (1)Bubble sort ||\n");
    scanf("%d", &choice);

    // Handle the sorting
    handle_sorting(numbers, m, choice);

    // Ask for further commands
    while (1) {
        printf("\nEnter a command from the following list \n(R) Re-generate random numbers and chose a different sorting algorithm\n(N) Enter another value for n and m, and enter new n numbers\n(S)Use  a different sorting algorithm\n(Q) Quit\n ");
        scanf(" %c", &command);

        if (command == 'R' || command == 'r') {
            re_generate_random(numbers, n, m);
        } else if (command == 'N' || command == 'n') {
            main(); // Re-run the program for new n and m
        } else if (command == 'S' || command == 's') {
            printf("Enter 0 for Quick Sort or 1 for Bubble Sort: ");
            scanf("%d", &choice);
            handle_sorting(numbers, m, choice);
        } else if (command == 'Q' || command == 'q') {
            break; // Quit
        } else {
            printf("Invalid command. Try again.\n");
        }
    }
}
void clear_input_buffer() {
    while (getchar() != '\n'); // Clear the buffer until newline
}