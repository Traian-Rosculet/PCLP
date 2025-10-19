#include <iostream>
#include <string>
#include <bits/stdc++.h>

using namespace std;


// Constructia do { ... } while(0) face ca macro-ul sa se comporte ca o singura instructiune C++,
// astfel incat sa poata fi folosit in siguranta in if/else, cu sau fara acolade.
#define REZULTAT(sub, EXPRESIA, CONCLUZIA, CODE) do { \
    cout << sub << ')';\
    cout << "\n" << (EXPRESIA) << "\nAFISEAZA:"; \
    CODE; \
    cout<< "\n\n"; \
    cout<<"CONCLUZIA: " << (CONCLUZIA) << "\n"; \
} while(0)

using F = void(*)(char); // alias de tip pentru functii lambda care primesc un argument de tip (double) si returneaza (void).
template <size_t N> void iterare_subpuncte(int nr_problema, const F (&problema)[N]){
    int sep_size=120;
    char sep_symbol='_';
    cout<<"Problema "<<nr_problema<<":";
    cout << "\n\n" ;
    char sub = 'a';
    for (size_t i = 0; i < N; ++i) {
        problema[i](sub++);
        std::cout << "\n" << std::string(120, '_') << "\n\n";
    }
};


F problema1[] = { // vector de functii pentru evitarea repetitiei la apelare
    [](auto sub){ // Functie de tip lambda, pentru izolarea scope-ului intre subpuncte
        double a=9/2; // = 4.0 pentru ca cifrele 9 si 2 sunt de tip int
        REZULTAT(
                    sub,
                    "double a=9/2; cout << a*5 << '\\n';",
                    "a=9/2=4.0 pentru ca cifrele 9 si 2 sunt de tip int.",
                    cout << a*5 << '\n';
                    );
    },

    [](auto sub){
        double a=9.7, b=5.6;
        REZULTAT(
                sub,
                "double a=9.7, b=5.6; cout<<(a+6<b)<<'\\n';",
                "se evalueaza (a+6)<b.",
                cout<<(a+6<b)<<'\n';
                );
    },
    [](auto sub){
        double a=9/4;
        REZULTAT(
                sub,
                "double a=9/4; cout<<(a*6)<<'\\n';",
                "a=9/4=2.0 pentru ca cifrele 9 si 2 sunt de tip int.",
                cout<<(a*6)<<'\n'
                );
    },
    [](auto sub){
        double x=3; int y=++x+5;
        REZULTAT(
                sub,
                "double x=3; int y=++x+5; cout<<y<<'\\n';",
                "++x se evalueaza ca x+1=4 inainte sa se evalueze restul expresiei, "
                "deci y=4+5=9",
                cout<<y<<'\n';
                );
    },
    [](auto sub){
        double a=7;
        REZULTAT(
                sub,
                "double a=7; cout<<(!a)<<'\\n';",
                "negarea oricarei valori diferita de 0 va da rezultatul 0. Reciproca este valabila.",
                cout<<(!a)<<'\n';
                );
    },
    [](auto sub){
        int a=10.5;
        REZULTAT(
                sub,
                "int a=10.5;cout<<a++<<'\\n';cout<<a<<'\\n';",
                "primul cout afiseaza valoarea lui a (convertit in int la declarare) inainte de incrementare, al doilea post-incrementare.",
                cout<<a++<<'\n';cout<<a<<'\n';
                );
    },
    [](auto sub){
        int a=7;
        REZULTAT(
                sub,
                "int a=7;cout<<++a<<'\\n';cout<<a<<'\\n';",
                "primul cout afiseaza valoarea lui a dupa incrementare, la al doilea cout valoarea lui a e neschimbata.",
                cout<<++a<<'\n';cout<<a<<'\n';
                );
    },
    [](auto sub){
        int a=10;
        REZULTAT(
                sub,
                "int a=10;cout<<a++<<'\\n';cout<<a<<'\\n';",
                "primul cout afiseaza valoarea lui a inainte de incrementare, al doilea post-incrementare.",
                cout<<a++<<'\n';cout<<a<<'\n';
                );
    },
    [](auto sub){
        double a=7/2;
        REZULTAT(
                sub,
                "double a=7/2; cout<<a<<'\\n';",
                "7/2 se evalueaza ca int, deci pierdem zecimalele.",
                cout<<a<<'\n';
                );
    },
    [](auto sub){
        int x=3; int y=x++-2;
        REZULTAT(
                sub,
                "int x=3; int y=x++-2;cout<<y<<'\\n';",
                "3-2=1, pentru ca x este incrementat DUPA evaluarea expresiei.",
                cout<<y<<'\n';
                );
    },
    [](auto sub){
        int x=3; int y=++x+5;
        REZULTAT(
                sub,
                "int x=3; int y=++x+5;cout<<y<<'\\n';",
                "4+5=9, pentru ca x este incrementat INAINTE de evaluarea expresiei.",
                cout<<y<<'\n';
                );
    },
    [](auto sub){
        double a=5.6, b=7.45;
        REZULTAT(
                sub,
                "double a=5.6, b=7.45;cout<<(a>b)<<'\\n';",
                "5.6 nu este mai mare decat 7.45, deci rezultatul este 0",
                cout<<(a>b)<<'\n';
                );
    },
};

F problema2[] = { // vector de functii pentru evitarea repetitiei la apelare
    [](auto sub){ // Functie de tip lambda, pentru izolarea scope-ului intre subpuncte
        REZULTAT(
                    sub,
                    "double a=9.7; double b=5.2; int c=(a+6<b)++;cout << c << '\\n'; --> eroare",
                    "nu se poate incrementa rezultatul expresiei (a+6<b) pentru ca nu este continut intr-o variabila (este rvalue)",
                    //double a=9.7; double b=5.2; int c=(a+6<b)++;cout << c << '\n';
                    );
    },
    [](auto sub){ // Functie de tip lambda, pentru izolarea scope-ului intre subpuncte
        REZULTAT(
                    sub,
                    "double a=7/5; double c=a*5++; cout << c << '\\n'; --> eroare",
                    "la fel ca la subpunctul anterior",
                    //double a=7/5; double c=a*5++; cout << c << '\n';
                    );
    },
    [](auto sub){ // Functie de tip lambda, pentru izolarea scope-ului intre subpuncte
        REZULTAT(
                    sub,
                    "double a=9.7; double b=5.2; int c=(a%6<b)++;cout << c << '\\n'; --> eroare",
                    "a este o valoare de tip (double) iar (6<b) este o valoare de tip (int). Nu se poate efectua operatia de impartire cu rest.",
                    //double a=9.7; double b=5.2; int c=(a%6<b)++;cout << c << '\n';
                    );
    },
    [](auto sub){ // Functie de tip lambda, pentru izolarea scope-ului intre subpuncte
        REZULTAT(
                    sub,
                    "double a=5.6, b=7.45; cout<<++ (a+5>b) <<'\\n'; --> eroare",
                    "valoarea de tip rvalue nu se poate incrementa.",
                    //double a=5.6; double b=7.45; cout<<++ (a+5>b) <<' \n';
                    );
    },
    [](auto sub){ // Functie de tip lambda, pentru izolarea scope-ului intre subpuncte
        REZULTAT(
                    sub,
                    "double a=9.8; double b=9.7; cout<<a%b<<'\\n'; --> eroare",
                    "nu se poate efectua operatia de impartire cu rest intre doua valori de tip (double)",
                    //double a=9.8; double b=9.7; cout<<a%b<<'\n';
                    );
    },
    [](auto sub){ // Functie de tip lambda, pentru izolarea scope-ului intre subpuncte
        REZULTAT(
                    sub,
                    "cout<<& (a+8)<<'\\n'; --> eroare",
                    "a nu a fost declarat.",
                    //cout<<& (a+8)<<'\n';
                    );
    },
    [](auto sub){ // Functie de tip lambda, pentru izolarea scope-ului intre subpuncte
        REZULTAT(
                    sub,
                    "int I=8; cout<<(I+10) ++<<'\\n'; --> eroare",
                    "valoarea de tip rvalue nu se poate incrementa.",
                    //int I=8; cout<<(I+10) ++<<'\n';
                    );
    },
    [](auto sub){ // Functie de tip lambda, pentru izolarea scope-ului intre subpuncte
        REZULTAT(
                    sub,
                    "double a=8.7; A=(a+8)/56; cout<<A<<'\\n'; --> eroare",
                    "A nu a fost declarat.",
                    //double a=8.7; A=(a+8)/56; cout<<A<<'\n';
                    );
    },
    [](auto sub){ // Functie de tip lambda, pentru izolarea scope-ului intre subpuncte
        REZULTAT(
                    sub,
                    "int x=3/5; int y=x++; char x='J'; cout<<\"y=\"<<y<<'\\n'; --> eroare",
                    "x este declarat de doua ori",
                    //int x=3/5; int y=x++; char x='J'; cout<<"y="<<y<<'\n';
                    );
    },
};

int main()
{
    iterare_subpuncte(1, problema1);
    iterare_subpuncte(2, problema2);
    return 0;
}


