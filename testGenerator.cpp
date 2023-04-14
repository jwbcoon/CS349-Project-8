//
// Created by Ethan Edwards on 4/14/2023.
//

#include <iostream>
#include <fstream>
#include <random>

using namespace std;

// Function Prototypes
void initFiles(ifstream& infile, ofstream& outfile, int argc, char* argv[]);

int main(int argc, char **argv) {
    ifstream infile; ofstream outfile;
    initFiles(infile, outfile, argc, argv); // We aren't going to be using infile but I'm lazy lmao
    int numTests = stoi(argv[3]);
    string line;
    // RNG
    static default_random_engine rng;
    // Input files
    ifstream dictionary; dictionary.open("dictionary.txt");
    for (int i = 0; i < numTests; i++){
        // Determine the number of lines in the test
        uniform_real_distribution<float> dist1(1, 100);
        int numLines = dist1(rng);
        outfile << numLines << endl; // Write the number of lines at the start of the test
        for (int j = 0; j < numLines; j++){
            // Determine the number of words in the line
            uniform_real_distribution<float> dist2(0, 10);
            int numWords = dist2(rng);
            for (int k = 0; k < numWords; k++){
                // Get a random word from dictionary
                dictionary.seekg(ios::beg);
                uniform_real_distribution<float> dist3(0, 466550);
                int numSkips = dist3(rng);
                for (int l = 0; l < numSkips; l++){
                    getline(dictionary, line);
                }
                getline(dictionary, line);
                // Write the word to the output file
                outfile << line << " ";
            }
            outfile << endl; // End the line
        }
    }
    return 0;
}

void initFiles(ifstream& infile, ofstream& outfile, int argc, char* argv[]){
    char confirm = 'n';
    string fname;
    // Check for inputs
    if (argc == 3){
        infile.open(argv[1]);
        outfile.open(argv[2]);
    }
    else if (argc == 2) {
        fname = argv[1];
        cout << "Found " << fname << " for input file. Continue using " << fname << " as input? (y/n) ";
        cin >> confirm;
        if (confirm == 'n') {
            cout << "Enter the new input filename: \n";
            cin >> fname;
        }
        infile.open(fname);
    }
    else if (argc == 4){
        outfile.open(argv[2]);
        return;
    }
    else {
        cout << "No input or output filename entered. Please run the program as ./ShipPather.out <input file> <output file>\n";
        exit( EXIT_FAILURE);
    }

    // Confirm that the files are actually open & ask for reentry if not valid
    while (!outfile.is_open()){
        cout << "Please provide an existing filename to overwrite, or a new filename to create: ";
        cin >> fname;
        outfile = ofstream(fname, ios::out);
    }
    while (!infile.is_open() && fname != "##"){
        cout << "No input file found. Please provide a relative path and filename for an input file or enter ## to close the program: ";
        cin >> fname;
        infile.open(fname);
    }
}