#include <iostream>
#include <string>
//#include <bits/stdc++.h>

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
    int problema_len = (sizeof(problema)/sizeof(*problema));
    int subpct_num;
    for (size_t i = 0; i < N; ++i) {
        problema[i](sub++);
        subpct_num = i+1;
        cout << "\n" << string(sep_size, sep_symbol) << ((subpct_num!=problema_len)?"\n\n":string(sep_size, sep_symbol)); // branching intr-un loop!! Functia asta are complexitatea unui adolescent emo.
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
    [](auto sub){
        REZULTAT(
                    sub,
                    "double a=9.7; double b=5.2; int c=(a+6<b)++;cout << c << '\\n'; --> eroare",
                    "nu se poate incrementa rezultatul expresiei (a+6<b) pentru ca nu este continut intr-o variabila (este rvalue)",
                    //double a=9.7; double b=5.2; int c=(a+6<b)++;cout << c << '\n';
                    );
    },
    [](auto sub){
        REZULTAT(
                    sub,
                    "double a=7/5; double c=a*5++; cout << c << '\\n'; --> eroare",
                    "la fel ca la subpunctul anterior",
                    //double a=7/5; double c=a*5++; cout << c << '\n';
                    );
    },
    [](auto sub){
        REZULTAT(
                    sub,
                    "double a=9.7; double b=5.2; int c=(a%6<b)++;cout << c << '\\n'; --> eroare",
                    "a este o valoare de tip (double) iar (6<b) este o valoare de tip (int). Nu se poate efectua operatia de impartire cu rest.",
                    //double a=9.7; double b=5.2; int c=(a%6<b)++;cout << c << '\n';
                    );
    },
    [](auto sub){
        REZULTAT(
                    sub,
                    "double a=5.6, b=7.45; cout<<++ (a+5>b) <<'\\n'; --> eroare",
                    "valoarea de tip rvalue nu se poate incrementa.",
                    //double a=5.6; double b=7.45; cout<<++ (a+5>b) <<' \n';
                    );
    },
    [](auto sub){
        REZULTAT(
                    sub,
                    "double a=9.8; double b=9.7; cout<<a%b<<'\\n'; --> eroare",
                    "nu se poate efectua operatia de impartire cu rest intre doua valori de tip (double)",
                    //double a=9.8; double b=9.7; cout<<a%b<<'\n';
                    );
    },
    [](auto sub){
        REZULTAT(
                    sub,
                    "cout<<& (a+8)<<'\\n'; --> eroare",
                    "a nu a fost declarat.",
                    //cout<<& (a+8)<<'\n';
                    );
    },
    [](auto sub){
        REZULTAT(
                    sub,
                    "int I=8; cout<<(I+10) ++<<'\\n'; --> eroare",
                    "valoarea de tip rvalue nu se poate incrementa.",
                    //int I=8; cout<<(I+10) ++<<'\n';
                    );
    },
    [](auto sub){
        REZULTAT(
                    sub,
                    "double a=8.7; A=(a+8)/56; cout<<A<<'\\n'; --> eroare",
                    "A nu a fost declarat.",
                    //double a=8.7; A=(a+8)/56; cout<<A<<'\n';
                    );
    },
    [](auto sub){
        REZULTAT(
                    sub,
                    "int x=3/5; int y=x++; char x='J'; cout<<\"y=\"<<y<<'\\n'; --> eroare",
                    "x este declarat de doua ori",
                    //int x=3/5; int y=x++; char x='J'; cout<<"y="<<y<<'\n';
                    );
    },
    [](auto sub){
        REZULTAT(
                    sub,
                    "char a='X';const int b=89; b+=8; cout<<\"b=\"<<b<<\" a=\"<<a<<'\\n';; --> eroare",
                    "variabila de tip (const int) b nu poate fi modificata dupa initializare",
                    // char a='X';const int b=89; b+=8; cout<<"b="<<b<<" a="<<a<<'\n';
                    );
    },
    [](auto sub){
        REZULTAT(
                    sub,
                    "const x=34; int g=56; x+=h; cout<<\"g=\"<<g<<\"x=\"<<x<<'\\n';; --> eroare",
                    "simbolul (const) nu este suficient pentru declararea unei variabile. El trebuie folosit impreuna cu un simbol care sa indice tipul variabilei.",
                    //const x=34; int g=56; x+=h; cout<<"g="<<g<<"x="<<x<<'\n';
                    );
    },
    [](auto sub){
        REZULTAT(
                    sub,
                    "double y=9.8; int a=(y<<7); cout<<\"a=\"<<a<<\"y=\"<<y<<'\\n'; --> eroare",
                    "(y<<7) -> nu se poate face bitshift pe o variabila cu virgula flotanta.",
                    //double y=9.8; int a=(y<<7); cout<<"a="<<a<<"y="<<y<<'\n';
                    );
    },
    [](auto sub){
        REZULTAT(
                    sub,
                    "cout<<(5++-3)--<<'\\n';; --> eroare",
                    "incrementare pe rvalue",
                    //cout<<(5++-3)--<<'\n';
                    );
    },
    [](auto sub){
        REZULTAT(
                    sub,
                    "int a=9; cout<<(a!=9)<<'\\n'; cout<<(++a!=9); cout<< (a++!=9);",
                    "Se compileaza si se executa fara erori. La primul cout a=10, pre-incrementat, deci expresia este adevarata. La al doilea cout a=10, expresia este evaluata ca fiind adevarata, apoi a este post-incrementat.",
                    int a=9; cout<<(a!=9)<<'\n'; cout<<(++a!=9); cout<< (a++!=9);
                    );
    },
    [](auto sub){
        REZULTAT(
                    sub,
                    "int a=9; cout<<(a!=9) <<'\\n'; cout<< (a++!=9); cout<< (++a!=9);",
                    "Se compileaza si se executa fara erori. La primul cout a=9, post-incrementat, deci expresia este falsa. La al doilea cout a=11, expresia este evaluata ca fiind adevarata.",
                    int a=9; cout<<(a!=9) <<'\n'; cout<< (a++!=9); cout<< (++a!=9);
                    );
    },
    [](auto sub){
        REZULTAT(
                    sub,
                    "int a=9; cout<<(a++-2*5);",
                    "Se compileaza si se executa fara erori. (a=9)-2*5=-1, apoi a este incrementat",
                    int a=9; cout<<(a++-2*5);
                    );
    },
    [](auto sub){
        REZULTAT(
                    sub,
                    "cout<<(sizeof('A') <=1) <<'\\n';",
                    "Se compileaza si se executa fara erori. Valorile de tip char sunt stocate pe 1 octet. Functia sizeof() returneaza dimensiunea unei variabile in octeti, deci expresia este adevarata",
                    cout<<(sizeof('A') <=1) <<'\n';
                    );
    },
    [](auto sub){
        REZULTAT(
                    sub,
                    "cout<<(int)'A';",
                    "Se compileaza si se executa fara erori. Afiseaza valoarea caracterului A in tabelul ASCII.",
                    cout<<(int)'A';
                    );
    },
    [](auto sub){
        REZULTAT(
                    sub,
                    "double x; int y=8.5; x=y%3; cout<<\"x=\"<<x<<\" y=\"<<y<<'\\n';",
                    "Se compileaza si se executa fara erori. y este declarat ca int, deci se pastreaza doar partea intreaga a valorii.",
                    double x; int y=8.5; x=y%3; cout<<"x="<<x<<" y="<<y<<'\n';
                    );
    },
    [](auto sub){
        REZULTAT(
                    sub,
                    "double x; int y=8; x=y%3; cout<<\"x=\"<<x<<\" y=\"<<y<<'\\n';",
                    "Se compileaza si se executa fara erori.",
                    double x; int y=8; x=y/3; cout<<"x="<<x<<" y="<<y<<'\n';
                    );
    },
    [](auto sub){
        REZULTAT(
                    sub,
                    "double w=2.5; cout<<(!w); cout<< ((!w)++); cout<<(!w+2) ++;",
                    "incrementare pe rvalue",
                    //double w=2.5; cout<<(!w); cout<< ((!w)++); cout<<(!w+2) ++;
                    );
    },
    [](auto sub){
        REZULTAT(
                    sub,
                    "cout<<sizeof (\"ab9*\")<<'\\t'<<sizeof(\"a\\nb\";",
                    "Se compileaza si se executa fara erori.",
                    cout<<sizeof ("ab9*")<<'\t'<<sizeof("a\nb");
                    );
    },
    [](auto sub){
        REZULTAT(
                    sub,
                    "double x=3; double y=(x<7)?1:0; cout<<y<<\"\\n\";",
                    "Se compileaza si se executa fara erori.",
                    double x=3; double y=(x<7)?1:0; cout<<y<<"\n";
                    );
    },
    [](auto sub){
        REZULTAT(
                    sub,
                    "int m=2, n=5, p=10; p=(m=n, n<20); cout<<\"p=\"<<p<<'\\n';",
                    "In atribuirea unei variabile o evaluare a unei insiruiri de expresii separate cu virgula, se atribuie valoarea ultimei expresii.",
                    int m=2; int n=5; int p=10; p=(m=n, n<20); cout<<"p="<<p<<'\n';
                    );
    },
    [](auto sub){
        REZULTAT(
                    sub,
                    "int x=3; double y=25.2, z; x=y; cout<<x<<'\n';",
                    "Se compileaza si se executa fara erori. (int) x devine jumatatea intreaga a lui (double) y. Romantic.",
                    int x=3; double y=25.2; double z; x=y; cout<<x<<'\n';
                    );
    },
};

int main()
{
    iterare_subpuncte(1, problema1);
    cout << "\n\n";
    iterare_subpuncte(2, problema2);
    return 0;
}


