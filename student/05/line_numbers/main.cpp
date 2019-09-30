#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    string inp;
    string outp;
    cout << "Input file: ";
    cin >> inp;
    cout << "Output file: ";
    cin >> outp;
    ifstream tiedosto_in(inp);
        if ( not tiedosto_in ) {
            cout << "Error! The file " << inp << " cannot be opened." << endl;
            return EXIT_FAILURE;
        }
        else{
            ofstream tiedosto_out(outp);
            string rivi;
            int i = 1;
                    while ( getline(tiedosto_in, rivi) ) {
                        tiedosto_out << i << " " << rivi << endl;
                        ++i;
                    }
                    tiedosto_in.close();
                    tiedosto_out.close();
        }
}
