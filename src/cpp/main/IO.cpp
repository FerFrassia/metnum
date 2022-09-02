#include "IO.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

namespace IO {
    void writeOutResult(const vector<double> &v, double p, string file) {
        ostringstream streamObj;
        streamObj << fixed;
        streamObj << setprecision(2);
        ofstream myfile;
        myfile.open(file);
        streamObj << p;
        myfile << streamObj.str() + "\n";
        for (double element: v) {
            myfile << to_string(element) + "\n";
        }
        myfile.close();
    }
}