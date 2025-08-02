
#include <iostream>
 
/* fstream header file for ifstream, ofstream, 
  fstream classes */
#include <fstream>
 
 
void run()
{
    // Creation of ofstream class object
    std::ofstream fout;
 
    std::string line;
 
    fout.open("data.txt", std::ios::app);
 
    // Execute a loop If file successfully opened
    while (fout) {
 
        // Read a Line from standard input
        std::getline(std::cin, line);
 
        // Press -1 to exit
        if (line == "-1")
            break;
 
        // Write line in file
        fout << line << std::endl;
    }
 
    // Close the File
    fout.close();
 
    // Creation of ifstream class object to read the file
    std::ifstream fin;
 
    // by default open mode = ios::in mode
    fin.open("sample.txt");
 
    // Execute a loop until EOF (End of File)
    while (std::getline(fin, line)) {
       
        // Print line (read from file) in Console
        std::cout << line << std::endl;
    }
    // Close the file
    fin.close();
}
