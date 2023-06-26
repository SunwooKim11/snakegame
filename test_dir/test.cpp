#include<fstream>

#include<sstream>

#include<iostream>

#include<vector>

#include<map>

#include<algorithm>


using std::cout; using std::cerr;

using std::endl; using std::string;

using std::ifstream; using std::ostringstream;

using std::istringstream;


string readFileIntoString(const string& path) 
    {    
        auto ss = ostringstream{};
        std::ifstream ifs;
        ifs.open ("normal.csv", std::ifstream::in); 

        // if (ifs.good()) {
        //     cerr << "Could not open the file - '"
        //          << path << "'" << endl;
        //     exit(EXIT_FAILURE);
        // }
        ss << ifs.rdbuf();
        return ss.str();
    }

int main(){
    int y, x;   
        string filename("normal.csv");
        string file_contents;
        char delimiter = ',';

        file_contents = readFileIntoString(filename);

        istringstream sstream(file_contents);
        std::vector<string> items;
        string record;

        int counter = 0;
        while (std::getline(sstream, record)) {
            istringstream line(record);
            while (std::getline(line, record, delimiter)) {
                record.erase(std::remove_if(record.begin(), record.end(), isspace), record.end());
                // std::cout << typeid(record).name();
                items.push_back(record);
            }
            y = std::stoi(items[0]);
            x = (int)std::stoi(items[1]);
            // addAt(y, x, 'O');
            std::cout << typeid(y).name() << ',' << typeid(x).name() << endl;
            std::cout << y << ',' << x << endl;
            items.clear();
        }
}