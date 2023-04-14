#include <iostream>
#include <fstream>

using namespace std;

// Function Prototypes
void initFiles(ifstream& infile, ofstream& outfile, int argc, char* argv[]);

int main(int argc, char** argv) {
    // Variable defs
    ifstream infile; ofstream outfile;
    string line;
    int numLines = 1, fallIndex, currFall, nextFall;
    auto nextFallIndex = [](int fallIndex, string line) {
        // Accumulate index of first space and consume it until nextFall
        // is greater than fallIndex or the line is consumed entirely.
        int nextFall = -1, edge = line.size();
        while (nextFall < fallIndex && nextFall < edge) {
            if (line.find(' ') != string::npos)
                nextFall += line.find(' ') + 1;
            else
                nextFall += line.size() + 1;
            line.erase(0, line.find(' ') + 1);
        }
        return nextFall;
    };

    initFiles(infile, outfile, argc, argv);

    while (numLines > 0) {
        getline(infile, line);
        numLines = stoi(line);
        fallIndex = 0; // If the first space is a whitespace or there is nothing, fall immediately

        for (int i = 0; i < numLines; i++) {
            getline(infile, line);
            currFall = nextFallIndex(fallIndex, line); // Index of where the first space after fallIndex
                                                       // or the index of the end of the line (current line)
            if (i < numLines - 1) { // Read a second line unless current line is the last line
                getline(infile, line);
                i++;
            }
            nextFall = nextFallIndex(currFall, line); // Index of where the first space after fallIndex
                                                              // or the index of the end of the line (next line)
            if (fallIndex < currFall) fallIndex = currFall;
            if (fallIndex < nextFall) fallIndex = nextFall;
        }

        if (numLines > 0) outfile << ++fallIndex << endl; // Increment fallIndex because problem uses base 1 counting
    }

    return 0;
}

/*
 *  This function receives user arguments and assigns them to the ifstream and ofstream objects which manage I/O
 *  for the program. If the user supplies no arguments, this function tries to resolve the issue.
 *
 *  If the user has no input file available to pass, then they must enter ## when prompted to exit the program.
 */
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
