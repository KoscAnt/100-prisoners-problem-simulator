#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <fstream>

using namespace std;

// Initializes a 10x10 matrix with sequential numbers from 1 to 100
void number_boxes(int box[10][10]) {
    int number = 1;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            box[i][j] = number;
            number++;
        }
    }
}

// Generates a random permutation of numbers 1-100 in a 10x10 matrix
void matrix_generate(int matrix[10][10]) {
    vector<int> numbers;
    for (int i = 1; i <= 100; i++) {
        numbers.push_back(i);
    }

    // Shuffle using Mersenne Twister engine
    random_device rd;
    mt19937 gen(rd());
    shuffle(numbers.begin(), numbers.end(), gen);

    // Transfer shuffled numbers to matrix
    int vec = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            matrix[i][j] = numbers[vec];
            vec++;
        }
    }
}

// Prints the current state of the matrix (for debugging/visualization).
void matrix_print(int matrix[10][10]) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << endl;
}

// Finds the starting number for a prisoner's search chain
int find_first_number(int matrix[10][10], int box[10][10], int prisoner_number) {
    int next_number = 0;
    
    // Search for the prisoner's starting box
    do {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (box[i][j] == prisoner_number) {
                    next_number = matrix[i][j];
                }
            }
        }
    } while (next_number == 0);

    return next_number;
}

// Runs the main simulation for 100 prisoners
void sent_prisoners(int matrix[10][10], int box[10][10]) {
    int prisoner_number = 1;
    int next_number;
    bool found;
    bool next;
    int eror = 0;

    ofstream myfile("results.txt");

    do {
        next_number = find_first_number(matrix, box, prisoner_number);
        found = false;
        myfile << endl;
        myfile << "Prisoner " << prisoner_number << ". started with box " << prisoner_number << ". " << endl;
        myfile << "Chain";

        // Each prisoner gets up to 50 attempts
        for (int x = 1; x < 50; x++) {
            next = false;

            // Search through all boxes
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    if (box[i][j] == next_number) {
                        if (matrix[i][j] != prisoner_number) {
                            next_number = matrix[i][j];
                            myfile << " -> " << next_number;
                            next = true;
                        }
                        else {
                            found = true;
                            myfile << " -> Prisoner found the number" << endl;
                        }
                    }
                    if (next || found) break;
                }
                if (next || found) break;
            }

            if (found) break;
            if (x == 49 && !found) {
                myfile << " -> Prisoner did not find the number" << endl;
                eror++;
            }
        }

        if (eror > 0) {
            myfile << endl << "Prisoners failed." << endl;
            break;
        }

        prisoner_number++;
    } while (prisoner_number <= 100);

    if (eror == 0) {
        myfile << "Prisoners succeeded." << endl;
    }

    myfile.close();
}


// Similar to the previous function, but used only to calculate whether the prisoners succeeded (for statistics).
int sent_prisoners_for_stats(int matrix[10][10], int box[10][10]) {
    int result = 0;
    int prisoner_number = 1;
    int next_number;
    bool found;
    bool next;
    int eror = 0;

    do {
        next_number = find_first_number(matrix, box, prisoner_number);
        found = false;

        for (int x = 1; x < 50; x++) {
            next = false;

            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    if (box[i][j] == next_number) {
                        if (matrix[i][j] != prisoner_number) {
                            next_number = matrix[i][j];
                            next = true;
                        }
                        else {
                            found = true;
                        }
                    }
                    if (next || found) break;
                }
                if (next || found) break;
            }

            if (found) break;
            if (x == 49 && !found) {
                eror++;
            }
        }

        if (eror > 0) break;

        prisoner_number++;
    } while (prisoner_number <= 100);

    if (eror == 0) {
        result = 1;
    }

    return result;
}

// Simulates 100 runs and counts how many times the prisoners succeed.
int stats() {
    int box[10][10];
    int matrix[10][10];
    number_boxes(box);
    int count = 0;
    int percent = 0;
    int result;

    // Runs 100 simulations of the prisoner scenario and calculates success rate
    do {
        count++;
        matrix_generate(matrix);
        result = sent_prisoners_for_stats(matrix, box);

        if (result == 1) {
            percent++;
        }

    } while (count < 100);

    return percent;
}

// Repeats the stats function 100 times and calculates average success.
int stats_hundrets_times() {
    int count = 0;
    int percent;
    int number = 0;
    int average;

    // Performs 100 batches of simulations (10,000 total trials) and records statisti (writes results to statistics.txt)
    ofstream myfile("statistics.txt");
    myfile << "Simulating one hundred simulations of the 100 prisoners dilemma:" << endl << endl;

    do {
        count++;
        percent = stats();
        myfile << "Number of successful simulations in one hundred: " << percent << endl;
        number += percent;
    } while (count < 100);

    myfile.close();

    average = number / 100;

    return average;
}


// Simulates the prisoner problem with 4 prisoners and 4 boxes (2x2 matrix) - 2 attempts by one prisoner

void customSimulation4(int matrix[2][2]) {
    cout << endl;
    cout << "In this 4-box simulation, each prisoner has 2 attempts to find their number. If any prisoner fails, all 4 prisoners fail." << endl << endl;

    int box[2][2];
    int number = 1;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            box[i][j] = number++;
        }
    }

    vector<int> numbers = { 1, 2, 3, 4 };
    random_device rd;
    mt19937 gen(rd());
    shuffle(numbers.begin(), numbers.end(), gen);

    int vec = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            matrix[i][j] = numbers[vec++];
        }
    }

    int prisonerNumber = 1;

    while (prisonerNumber <= 4) {
        int attempts = 0;
        int currentBox;

        cout << "Prisoner " << prisonerNumber << " turn (2 attempts max):" << endl;

        while (attempts < 2) {
            cout << "Choose a box to open (1-4): ";
            cin >> currentBox;

            bool found = false;
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 2; j++) {
                    if (box[i][j] == currentBox) {
                        cout << "Opened box " << currentBox << " -> found number: " << matrix[i][j] << endl;

                        if (matrix[i][j] == prisonerNumber) {
                            cout << "Prisoner " << prisonerNumber << " found their number!" << endl << endl;
                            found = true;
                        }
                    }
                }
            }

            attempts++;

            if (found) break;
            if (attempts == 2) {
                cout << "Prisoner " << prisonerNumber << " failed to find their number in 2 attempts." << endl;
                cout << "All prisoners have failed." << endl;
                return;
            }
        }

        prisonerNumber++;
    }

    cout << "All prisoners found their numbers. Success!" << endl;
}


// Simulates the prisoner problem with 9 prisoners and 9 boxes (3x3 matrix) - 4 attempts by one prisoner

void customSimulation9(int matrix[3][3]) {

    cout << endl;
    cout << "In this 9-box simulation, each prisoner has 4 attempts to find their number. If any prisoner fails, all 9 prisoners fail." << endl << endl;

    int box[3][3];
    int number = 1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            box[i][j] = number++;
        }
    }

    vector<int> numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    random_device rd;
    mt19937 gen(rd());
    shuffle(numbers.begin(), numbers.end(), gen);

    int vec = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrix[i][j] = numbers[vec++];
        }
    }

    int prisonerNumber = 1;

    while (prisonerNumber <= 9) {
        int attempts = 0;
        int currentBox;

        cout << "Prisoner " << prisonerNumber << " turn (4 attempts max):" << endl;

        while (attempts < 3) {
            cout << "Choose a box to open (1-9): ";
            cin >> currentBox;

            bool found = false;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (box[i][j] == currentBox) {
                        cout << "Opened box " << currentBox << " -> found number: " << matrix[i][j] << endl;

                        if (matrix[i][j] == prisonerNumber) {
                            cout << "Prisoner " << prisonerNumber << " found their number!" << endl << endl;
                            found = true;
                        }
                    }
                }
            }

            attempts++;

            if (found) break;
            if (attempts == 4) {
                cout << "Prisoner " << prisonerNumber << " failed to find their number in 4 attempts." << endl;
                cout << "All prisoners have failed." << endl;
                return;
            }
        }

        prisonerNumber++;
    }

    cout << "All prisoners found their numbers. Success!" << endl;



}

// Simulates the prisoner problem with 16 prisoners and 16 boxes (4x4 matrix) - 8 attempts by one prisoner

void customSimulation16(int matrix[4][4]) {

    cout << endl;
    cout << "In this 16-box simulation, each prisoner has 8 attempts to find their number. If any prisoner fails, all 16 prisoners fail." << endl << endl;

    int box[4][4];
    int number = 1;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            box[i][j] = number++;
        }
    }

    vector<int> numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    random_device rd;
    mt19937 gen(rd());
    shuffle(numbers.begin(), numbers.end(), gen);

    int vec = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = numbers[vec++];
        }
    }

    int prisonerNumber = 1;

    while (prisonerNumber <= 16) {
        int attempts = 0;
        int currentBox;

        cout << "Prisoner " << prisonerNumber << " turn (4 attempts max):" << endl;

        while (attempts < 8) {
            cout << "Choose a box to open (1-16): ";
            cin >> currentBox;

            bool found = false;
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (box[i][j] == currentBox) {
                        cout << "Opened box " << currentBox << " -> found number: " << matrix[i][j] << endl;

                        if (matrix[i][j] == prisonerNumber) {
                            cout << "Prisoner " << prisonerNumber << " found their number!" << endl << endl;
                            found = true;
                        }
                    }
                }
            }

            attempts++;

            if (found) break;
            if (attempts == 8) {
                cout << "Prisoner " << prisonerNumber << " failed to find their number in 4 attempts." << endl;
                cout << "All prisoners have failed." << endl;
                return;
            }
        }

        prisonerNumber++;
    }

    cout << "All prisoners found their numbers. Success!" << endl;


}

// Simulates the prisoner problem with 36 prisoners and 36 boxes (6x6 matrix) - 18 attempts by one prisoner

void customSimulation36(int matrix[6][6]) {

    cout << endl;
    cout << "In this 36-box simulation, each prisoner has 18 attempts to find their number. If any prisoner fails, all 36 prisoners fail." << endl << endl;

    int box[6][6];
    int number = 1;

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            box[i][j] = number++;
        }
    }

    vector<int> numbers;
    for (int i = 1; i <= 36; i++) {
        numbers.push_back(i);
    }

    random_device rd;
    mt19937 gen(rd());
    shuffle(numbers.begin(), numbers.end(), gen);

    int vec = 0;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = numbers[vec++];
        }
    }

    int prisonerNumber = 1;

    while (prisonerNumber <= 36) {
        int attempts = 0;
        int currentBox;

        cout << "Prisoner " << prisonerNumber << " turn (18 attempts max):" << endl;

        while (attempts < 18) {
            cout << "Choose a box to open (1-36): ";
            cin >> currentBox;

            bool found = false;
            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 6; j++) {
                    if (box[i][j] == currentBox) {
                        cout << "Opened box " << currentBox << " -> found number: " << matrix[i][j] << endl;

                        if (matrix[i][j] == prisonerNumber) {
                            cout << "Prisoner " << prisonerNumber << " found their number!" << endl << endl;
                            found = true;
                        }
                    }
                }
            }

            attempts++;

            if (found) break;
            if (attempts == 18) {
                cout << "Prisoner " << prisonerNumber << " failed to find their number in 18 attempts." << endl;
                cout << "All prisoners have failed." << endl;
                return;
            }
        }

        prisonerNumber++;
    }

    cout << "All prisoners found their numbers. Success!" << endl;


}

// Simulates the prisoner problem with 64 prisoners and 64 boxes (8x8 matrix) - 32 attempts by one prisoner

void customSimulation64(int matrix[8][8]) {

    cout << endl;
    cout << "In this 64-box simulation, each prisoner has 32 attempts to find their number. If any prisoner fails, all 64 prisoners fail." << endl << endl;

    int box[8][8];
    int number = 1;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            box[i][j] = number++;
        }
    }

    vector<int> numbers;
    for (int i = 1; i <= 64; i++) {
        numbers.push_back(i);
    }

    random_device rd;
    mt19937 gen(rd());
    shuffle(numbers.begin(), numbers.end(), gen);

    int vec = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            matrix[i][j] = numbers[vec++];
        }
    }

    int prisonerNumber = 1;

    while (prisonerNumber <= 64) {
        int attempts = 0;
        int currentBox;

        cout << "Prisoner " << prisonerNumber << " turn (32 attempts max):" << endl;

        while (attempts < 32) {
            cout << "Choose a box to open (1-64): ";
            cin >> currentBox;

            bool found = false;
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    if (box[i][j] == currentBox) {
                        cout << "Opened box " << currentBox << " -> found number: " << matrix[i][j] << endl;

                        if (matrix[i][j] == prisonerNumber) {
                            cout << "Prisoner " << prisonerNumber << " found their number!" << endl << endl;
                            found = true;
                        }
                    }
                }
            }

            attempts++;

            if (found) break;
            if (attempts == 32) {
                cout << "Prisoner " << prisonerNumber << " failed to find their number in 32 attempts." << endl;
                cout << "All prisoners have failed." << endl;
                return;
            }
        }

        prisonerNumber++;
    }

    cout << "All prisoners found their numbers. Success!" << endl;

}

// Simulates the prisoner problem with 100 prisoners and 100 boxes (10x10 matrix) - 50 attempts by one prisoner

void customSimulation100(int matrix[10][10]) {

    cout << endl;
    cout << "In this 100-box simulation, each prisoner has 50 attempts to find their number. If any prisoner fails, all 100 prisoners fail." << endl << endl;

    int box[10][10];
    int number = 1;

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            box[i][j] = number++;
        }
    }

    vector<int> numbers;
    for (int i = 1; i <= 100; i++) {
        numbers.push_back(i);
    }

    random_device rd;
    mt19937 gen(rd());
    shuffle(numbers.begin(), numbers.end(), gen);

    int vec = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            matrix[i][j] = numbers[vec++];
        }
    }

    int prisonerNumber = 1;

    while (prisonerNumber <= 100) {
        int attempts = 0;
        int currentBox;

        cout << "Prisoner " << prisonerNumber << " turn (50 attempts max):" << endl;

        while (attempts < 50) {
            cout << "Choose a box to open (1-100): ";
            cin >> currentBox;

            bool found = false;
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    if (box[i][j] == currentBox) {
                        cout << "Opened box " << currentBox << " -> found number: " << matrix[i][j] << endl;

                        if (matrix[i][j] == prisonerNumber) {
                            cout << "Prisoner " << prisonerNumber << " found their number!" << endl << endl;
                            found = true;
                        }
                    }
                }
            }

            attempts++;

            if (found) break;
            if (attempts == 50) {
                cout << "Prisoner " << prisonerNumber << " failed to find their number in 50 attempts." << endl;
                cout << "All prisoners have failed." << endl;
                return;
            }
        }

        prisonerNumber++;
    }

    cout << "All prisoners found their numbers. Success!" << endl;



}

int main() {

    // Initialize simulation matrices

    int matrix[10][10];
    int box[10][10];
    number_boxes(box);      // Fill boxes with sequential numbers
    matrix_generate(matrix);     // Create random number arrangement

    // Print program header and rules

    cout << "This is a simulation of the 100 Prisoners Dilemma in C++." << endl;
    cout << "-------------------------------------------------------------" << endl;
    cout << "RULES:" << endl;
    cout << "- There are 100 prisoners and 100 boxes, each containing a unique number from 1 to 100." << endl;
    cout << "- Each prisoner may open up to 50 boxes in an attempt to find their own number." << endl;
    cout << "- If even one prisoner fails to find their number, all prisoners lose." << endl;
    cout << endl;
    cout << "STRATEGY USED:" << endl;
    cout << "- Each prisoner starts by opening the box with the same number as their own." << endl;
    cout << "  For example, prisoner 1 opens box 1." << endl;
    cout << "- Inside is a number (e.g., 57), so they next open box 57." << endl;
    cout << "- This continues until they either:" << endl;
    cout << "  a) find their number within 50 attempts (success), or" << endl;
    cout << "  b) exceed 50 attempts (failure for all)." << endl;
    cout << endl;
    cout << "The program runs this simulation and can also calculate the success rate" << endl;
    cout << "across multiple runs." << endl;
    cout << endl;


    // Main menu interface

    int choice;

    cout << "Please choose an option:" << endl;
    cout << "1. Try a custom simulation (2x2 to 10x10 matrix, 4 to 100 prisoners), where you define the rules and see how the prisoners behave." << endl;
    cout << "2. Run a full simulation with 100 prisoners using the above described strategy." << endl;
    cout << "3. Run 10,000 simulations to calculate the average success rate of described strategy." << endl;
    cout << "Enter your choice (1-3): ";
    
    cin >> choice;

    switch (choice) {
    case 1: 

        // Custom simulation menu

        int num;
        cout << "Choose from the offered numbers. These numbers represent the number of prisoners in the simulation." << endl;
        cout << "a) 4 " << endl;
        cout << "b) 9 " << endl;
        cout << "c) 16 " << endl;
        cout << "d) 36 " << endl;
        cout << "e) 64 " << endl;
        cout << "f) 100 " << endl;
        cout << endl;
        cout << "Input the number (example '64'):" << endl;
        cin >> num;  

        // Run custom simulation selection

        switch (num) {
        case 4:  
            int matrix01[2][2];
            customSimulation4(matrix01); 
            break;
        case 9: 
            int matrix02[3][3];
            customSimulation9(matrix02);  
            break;
        case 16:  
            int matrix03[4][4];
            customSimulation16(matrix03);  
            break;
        case 36:  
            int matrix04[6][6];
            customSimulation36(matrix04); 
            break;
        case 64: 
            int matrix05[8][8];
            customSimulation64(matrix05);  
            break;
        case 100: 
            int matrix06[10][10];
            customSimulation100(matrix06); 
            break;
        default:
            cout << "Invalid number selection!" << endl;  
            break;
        }
        break;  

    case 2: 

        int times;

        cout << "This is a simulation of prisoner problem solved with the method above (1. prisoner chooses first box, the number in the box is the next box.)" << endl;
        cout << endl;
        cout << endl;

        // User chooses how many simulations
        cout << "Choose how many times you want to generate the simulation: " << endl;
        cout << "From 1 do 100 times (type in the number): " << endl;
        cout << endl;

        cin >> times;

        if (times > 100) {
            cout << "Incorrect number" << endl;

        }else if(times == 1) {

            // Single run with detailed output option

            cout << endl;

            string yesNo = "";

            string line;
            string lastLine;

            ifstream myfile("results.txt");

            while (getline(myfile, line)) {
                lastLine = line;
            }

            if (!lastLine.empty()) {
                cout << lastLine << endl;
            }

            myfile.close();

            cout << endl;
            cout << "Do you want to see the simulation in detaile? (answer with yes or no)" << endl;
            cin >> yesNo;

            if (yesNo == "yes" || yesNo == "Yes") {

                cout << endl;
                cout << "The prisoners in the simulation: " << endl;
                cout << endl;

                ifstream myfileAgain("results.txt");

                while (getline(myfileAgain, line)) {
                    cout << line << endl;
                    cout << endl;
                }

                myfileAgain.close();
            }

        }
        else if (times < 100 && times != 1) {

            int box[10][10];
            int matrix[10][10];
            number_boxes(box);
            int count = 0;
            int percent = 0;
            int result;

            do {
                count++;
                matrix_generate(matrix);
                result = sent_prisoners_for_stats(matrix, box);

                if (result == 1) {
                    percent++;
                }

            } while (count < times);

            cout << "In " << times << " simulations " << percent << " were successful" << endl;
            cout << "The " << times << " simulations had a succes rate of " << ((float)percent / times) * 100 << " %." << endl;

        }
       
        break;

    case 3:  
        // 10000 runs of the simulation
        cout << endl;
        cout << "Runing 10000 simulations of 100 prisoner problem solved by the above explained methode: " << endl;
        cout << endl;
        cout << "There was a " << stats_hundrets_times() << "% succes rate." << endl;
        cout << endl;
        break;

    default:  
        cout << "Invalid choice!" << endl;
        break;
    }


    return 0;
}
