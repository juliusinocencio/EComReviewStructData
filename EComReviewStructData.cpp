/* Name: Julius Inocencio
* Date: 21 Jul 2024
 * Section: COP3363-0002
 * Assignment: Module 11: Womens Clothing E-Commerce Reviews Data using Structures Program
 * Due Date:  July 21 by 11:59pm
 * About this project: This program will allow the user to input either (a) displays data from file showing reviews with age, rating, item, and comment / (b) displaying the maximum, minimum, and average rating for each item / (c) quit the program
 * Assumptions: If the user inputs correctly (a,b,c), they will have the option to see info from the text document. If they enter anything else, a prompt will tell them that they entered an invalid option.
 * All work below was performed by Julius Inocencio */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct Review
{
    string item;
    int age;
    int rating;
    string comments;
};

// Function prototypes
void readDataFromFile(vector<Review>& reviews);
void displayMenu();
void processOptionA(const vector<Review>& reviews);
void processOptionB(const vector<Review>& reviews);
void processOptionC();

int main()
{
    // Create a vector to store the reviews
    vector<Review> reviews;

    // Read data from the file and store it in the vector
    readDataFromFile(reviews);

    // Display the menu options
    displayMenu();

    // Get the user's selection
    char option;
    cin >> option;

    // Convert the option to lowercase
    option = tolower(option);

    // Process the user's selection
    if (option == 'a')
    {
        // Display data
        processOptionA(reviews);
    } else if (option == 'b')
    {
        // Find the Maximum, Minimum, and Average Rating by Item
        processOptionB(reviews);
    } else if (option == 'c')
    {
        // Quit
        processOptionC();
    } else
        // Display an error message if the user enters an invalid option
        cout << "Invalid option entered" << endl;

    return 0;
}

// Function to read data from file and store it in the vector
void readDataFromFile(vector<Review>& reviews)
{
    // Open the input file
    ifstream infile;
    string filename = "EComReviews.txt";
    infile.open(filename);

    // Check if the file was opened successfully
    if (!infile)
    {
        cout << "Error opening file! Please make sure file is in the correct directory." << endl;
        exit(0);
    }

    string line;

    // Read the file line by line
    while (getline(infile, line))
    {
        // Extract data from the line
        string tempItem, tempAge, tempRating;
        int tabCount = 0;

        for (int j = 0; j < line.length(); j++)
        {
            // Check if the current character is a tab
            if (line[j] == '\t')
            {
                tabCount++;
            } else if (tabCount == 0)
            {
                // If we haven't reached the first tab yet, add the character to the item name
                tempItem += line[j];
            } else if (tabCount == 1)
            {
                // If we've reached the first tab, add the character to the age
                tempAge += line[j];
            } else if (tabCount == 2)
            {
                // If we've reached the second tab, add the character to the rating
                tempRating += line[j];
            }
        }

        // Convert age and rating to integers
        Review review;
        review.item = tempItem;
        review.age = stoi(tempAge);
        review.rating = stoi(tempRating);

        // Read the comment on the next line
        getline(infile, line);
        review.comments = line;

        // Add the review to the vector
        reviews.push_back(review);
    }

    // Close the input file
    infile.close();
}

// Function to display menu options to the user
void displayMenu()
{
    // Display the menu options
    cout << "Women's Clothing E-Commerce Reviews Data" << endl
         << "Options" << endl
         << "A) Display Data" << endl
         << "B) Find the Maximum, Minimum, and Average Rating by Item" << endl
         << "C) Quit" << endl
         << "Please select option (A-C)..." << endl;
}

// Function to process option A
void processOptionA(const vector<Review>& reviews)
{
    cout << "Item                       Age    Rating" << endl; //lazy mode
    cout << "Comment" << endl;
    cout << "*********************************************************" << endl;

    for (int i = 0; i < reviews.size(); i++)
    {
        cout << setw(25) << left << reviews[i].item << setw(5) << reviews[i].age << setw(5) << reviews[i].rating << endl;
        cout << reviews[i].comments << endl;
        cout << endl;
    }
}

// Function to process option B
void processOptionB(const vector<Review>& reviews)
{
    // Create a vector to store the item names
    vector<string> itemNames;

    // Create an array to store the maximum ratings for each item
    int* maxRatings = new int[reviews.size()];

    // Create an array to store the minimum ratings for each item
    int* minRatings = new int[reviews.size()];

    // Create an array to store the sum of ratings for each item
    int* sumRatings = new int[reviews.size()];

    // Create an array to store the count of ratings for each item
    int* countRatings = new int[reviews.size()];

    // Initialize the arrays
    for (int i = 0; i < reviews.size(); i++)
    {
        maxRatings[i] = 0;
        minRatings[i] = 0;
        sumRatings[i] = 0;
        countRatings[i] = 0;
    }

    // Loop through each review
    for (int i = 0; i < reviews.size(); i++)
    {
        bool found = false;

        // Check if the item is already in the vector
        for (int j = 0; j < itemNames.size(); j++)
        {
            if(itemNames[j] == reviews[i].item)
            {
                // Update the maximum rating
                if (reviews[i].rating > maxRatings[j])
                {
                    maxRatings[j] = reviews[i].rating;
                }

                // Update the minimum rating
                if (reviews[i].rating < minRatings[j])
                {
                    minRatings[j] = reviews[i].rating;
                }

                // Update the sum of ratings
                sumRatings[j] += reviews[i].rating;

                // Update the count of ratings
                countRatings[j]++;

                found = true;
                break;
            }
        }

        // If the item is not found, add it to the vector
        if (!found)
        {
            itemNames.push_back(reviews[i].item);
            maxRatings[itemNames.size() - 1] = reviews[i].rating;
            minRatings[itemNames.size() - 1] = reviews[i].rating;
            sumRatings[itemNames.size() - 1] = reviews[i].rating;
            countRatings[itemNames.size() - 1]++;
        }
    }

    // Bubble sort the vectors by item name in alphabetical order
    bool swapped;
    do
    {
        swapped = false;
        for (int i = 0; i < itemNames.size() - 1; i++)
        {
            if (itemNames[i] > itemNames[i + 1])
            {
                // Swap the elements
                string tempItem = itemNames[i];
                itemNames[i] = itemNames[i + 1];
                itemNames[i + 1] = tempItem;

                int tempMaxRating = maxRatings[i];
                maxRatings[i] = maxRatings[i + 1];
                maxRatings[i + 1] = tempMaxRating;

                int tempMinRating = minRatings[i];
                minRatings[i] = minRatings[i + 1];
                minRatings[i + 1] = tempMinRating;

                int tempSumRating = sumRatings[i];
                sumRatings[i] = sumRatings[i + 1];
                sumRatings[i + 1] = tempSumRating;

                int tempCountRating = countRatings[i];
                countRatings[i] = countRatings[i + 1];
                countRatings[i + 1] = tempCountRating;

                swapped = true;
            }
        }
    } while (swapped);

    // Display the maximum, minimum, and average rating for each item
    cout << "Item           Min  Max  Avg" << endl; //lazy mode
    for (int i = 0; i < itemNames.size(); i++)
    {
        double avgRating = static_cast<double>(sumRatings[i]) / countRatings[i];

        cout << setw(15) << left << itemNames[i] << setw(5) << minRatings[i] << setw(5) << maxRatings[i] << setw(5) << fixed << setprecision(2) << avgRating << endl;
    }

    // Delete the dynamically allocated arrays
    delete[] maxRatings;
    delete[] minRatings;
    delete[] sumRatings;
    delete[] countRatings;
}

// Function to process option C
void processOptionC()
{
    // Quit the program
    cout << "Goodbye!" << endl;
    exit(0);
}