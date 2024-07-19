#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Structure to hold the data
struct Review {
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
        cout << "Error opening file!" << endl;
        return;
    }

    string line;

    // Read the file line by line
    while (getline(infile, line))
    {
        // Extract data from the line
        string tempItem, tempAge, tempRating;
        int tabCount = 0;

        for (int i = 0; i < line.length(); i++)
        {
            // Check if the current character is a tab
            if (line[i] == '\t')
            {
                tabCount++;
            } else if (tabCount == 0)
            {
                // If we haven't reached the first tab yet, add the character to the item name
                tempItem += line[i];
            } else if (tabCount == 1)
            {
                // If we've reached the first tab, add the character to the age
                tempAge += line[i];
            } else if (tabCount == 2)
            {
                // If we've reached the second tab, add the character to the rating
                tempRating += line[i];
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
    // Display the data for each review
    for (const Review& review : reviews)
    {
        cout << "Item: " << review.item << endl
             << "Age: " << review.age << endl
             << "Rating: " << review.rating << endl
             << "Comments: " << review.comments << endl
             << "------------------------" << endl;
    }
}

// Function to process option B
void processOptionB(const vector<Review>& reviews)
{
    // Create a vector to store the aggregate values for each item
    vector<pair<string, vector<int>>> itemRatings;

    // Loop through each review
    for (const Review& review : reviews)
    {
        // Check if the item is already in the vector
        bool found = false;
        for (auto& item : itemRatings)
        {
            if (item.first == review.item)
            {
                item.second.push_back(review.rating);
                found = true;
                break;
            }
        }

        // If the item is not in the vector, add it
        if (!found)
        {
            vector<int> ratings;
            ratings.push_back(review.rating);
            itemRatings.push_back(make_pair(review.item, ratings));
        }
    }

    // Sort the vector by item name
    sort(itemRatings.begin(), itemRatings.end(), [](const pair<string, vector<int>>& a, const pair<string, vector<int>>& b) {
        return a.first < b.first;
    });

    // Display the aggregate values for each item
    for (const auto& item : itemRatings)
    {
        int sum = 0;
        int count = 0;
        int minRating = INT_MAX;
        int maxRating = INT_MIN;

        // Compute the sum, count, min, and max for the item
        for (int rating : item.second)
        {
            sum += rating;
            count++;
            minRating = min(minRating, rating);
            maxRating = max(maxRating, rating);
        }

        // Display the aggregate values
        cout << "Item: " << item.first << endl
             << "Number of Reviews: " << count << endl
             << "Sum of Ratings: " << sum << endl
             << "Average Rating: " << static_cast<double>(sum) / count << endl
             << "Minimum Rating: " << minRating << endl
             << "Maximum Rating: " << maxRating << endl
             << "------------------------" << endl;
    }
}

// Function to process option C
void processOptionC()
{
    // Quit the program
    exit(0);
}