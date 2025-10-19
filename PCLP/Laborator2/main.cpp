// Laborator2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
//#include <vector>
#include <cmath>
#include <iomanip>
//#include <cstring>

using namespace std;

void an_bisect();
void modulo();
void mesaje();
void inegalitatea();
void parse_numeric_string();

int main()
{
    mesaje();
    cout << "\n";
    cout << "\n";
    modulo();
    cout << "\n";
    cout << "\n";
    an_bisect();
    cout << "\n";
    cout << "\n";
    inegalitatea();
    cout << "\n";
    cout << "\n";
    parse_numeric_string();
}

void modulo() {
    int a;
    int b;

    cout << "2. modulo\n" << "\tIntroduceti doua numere intregi. \na=";
    cin >> a;
    cout << "b=";
    cin >> b;

    cout << "restul impartirii lui " << a << " la " << b << " este: " << a % b;
}


void mesaje() {
    cout << "1. Program care afiseaza urmatoarele mesaje:\n";
    cout << "\tSirul \"Este dupa-amiaza\" este memorat pe: " << sizeof("Este dupa-amiaza") << " octeti.\n";
    cout << "\tO marime intreaga este memorata pe: " << sizeof(int) << " octeti.\n";
    cout << "\tO marime reala, in simpla precizie este memorata pe: " << sizeof(float) << " octeti.\n";
    cout << "\tO marime reala, in dubla precizie este memorata pe: " << sizeof(double) << " octeti.\n";
    cout << "\tConstanta caracter 'Q' este memorata pe: " << sizeof('Q') << " octeti.\n";
    cout << "\tSirul \"a\\n\\n\" este memorat pe: " << sizeof("a\n\n") << " octeti.\n";
    cout << "\tSirul \"\\n\" este memorat pe: " << sizeof('\n') * 8 << " biti.\n";
    cout << "\tCaracterul '\\' este memorat pe: " << sizeof('\\') * 8 << " biti.";
}

void an_bisect() {
    int an;
    bool is_bisect;
    cout << "3. An bisect\n" << "\tIntroduceti un an:";
    cin >> an;
    is_bisect = (an % 4 == 0) && (!(an % 100 == 0) || (an % 400 == 0));
    cout << "Anul " << an << (is_bisect ? " este" : " nu este") << " bisect";
}

void inegalitatea(){
    bool is_less_than;
    float n;
    float exp1;
    float exp2;
    float exp3;
    cout << "4. Introduceti un numar intreg pozitiv:";
    cin >> n;
    if ((n<=0)||!(n==floorf(n))){
        cout << "numarul nu corespunde criteriilor";
        return;
    }

    exp1=1/(n+1);
    exp2=log((n+1)/n);
    exp3=1/n;
    cout << setprecision(2) << exp1 <<";"<< exp2<<";"<< exp3 << "\n";
    is_less_than = (exp1 < exp2)&&(exp2 < exp3);
    cout << "expresia " << "1/("<<n<<"+1) < " << "ln(("<<n<<"+1)/"<<n<<") < " << "1/" << n << " este " << (is_less_than?"adevarata":"falsa");
}

void parse_numeric_string(){
    float nums[4];
    float rezultat;
    string num;
    int i=0;
    cout << "5. Introduceti un numar din 4 cifre:";
    cin >> num;

    for(char& d : num){
        nums[i]=d-'0';
        cout << i << ": " << nums[i] << " ";
        i++;
    }
    cout << "\n";
    cout << "rezultatul expresiei 4*" << nums[0]<< "+" << nums[1] << "/20-" << nums[2] << "+1/" << nums[3] << " este: " << 4*nums[0]+nums[1]/20-nums[2]+1/nums[3];
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
