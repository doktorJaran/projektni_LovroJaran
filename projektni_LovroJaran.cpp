#include <iostream>
#include <algorithm>
#include <numeric>
#include <string>
#include <fstream>

using namespace std;

void pause()
{
    cout << endl << "Pritisnite enter za nastavak...";
    string dummy;
    cin.ignore();
    getline(cin, dummy);
}

bool negSaldo(double saldo)
{
    if (saldo < 0)
        return true;
    return false;
}

bool jeNula(double saldo)
{
    if (saldo == 0)
        return true;
    return false;
}

bool veciOdJedanK(double saldo)
{
    if (saldo > 10000)
        return true;
    return false;
}

int main()
{
    fstream datoteka;
    datoteka.open("podaci.txt", ios::app);

    int izbor;
    int brKl = 0;
    unsigned long long int* brRacuna = new unsigned long long int[1000];
    string* prezIme = new string[1000];
    double* saldo = new double[1000];
    while (1)
    {
        system("clear"); // system("cls"); za Windows
        cout << "Dobrodošli u moju banku\n";
        cout << "1. unos novog raèuna" << endl;
        cout << "2. ispisi raèune" << endl;
        cout << "3. ispisi statistiku" << endl;
        cout << "4. pretraga prema prezimenu i imenu" << endl;
        cout << "5. brisanje raèuna" << endl;
        cout << "6. ispiši sortirano po prezimenu i imenu" << endl;
        cout << "7. izlaz iz programa" << endl;
        cout << "Vas odabir je: ";
        cin >> izbor;
        if (izbor == 1)
        {
            cout << "Unesite broj raèuna: ";
            cin >> brRacuna[brKl];
            cin.ignore();
            cout << endl << "Unesite vaše prezime i ime: ";
            getline(cin, prezIme[brKl]);
            cout << endl << "Unesite saldo: ";
            cin >> saldo[brKl];
            if (datoteka.is_open())
            {
                datoteka << "Broj raèuna: " << brRacuna[brKl] << endl;
                datoteka << "Prezime i ime: " << prezIme[brKl] << endl;
                datoteka << "Saldo: " << saldo[brKl] << endl;
            }
            brKl++;
        }
        else if (izbor == 2)
        {
            for (int i = 0; i < brKl; i++)
            {
                cout << endl << "Broj raèuna: " << brRacuna[i] << endl;
                cout << "\t\t" << prezIme[i] << endl;
                cout << "\t\t" << saldo[i] << endl;
            }
        }
        else if (izbor == 3)
        {
            cout << endl << "Suma svih stanja na raèunima: " << accumulate(saldo, saldo + brKl, 0.0);
            cout << endl << "Prezime i ime raèuna koji ima najveæi saldo: " << prezIme[max_element(saldo, saldo + brKl) - saldo];
            cout << endl << "Koliko raèuna imaju saldo jednak 0,00 €: " << count_if(saldo, saldo + brKl, jeNula);
            cout << endl << "Koliko raèuna ima negativni saldo: " << count_if(saldo, saldo + brKl, negSaldo);
            cout << endl << "Postoji li raèun sa saldom veæim od 10.000,00 €: ";
            if (any_of(saldo, saldo + brKl, veciOdJedanK))
                cout << "da" << endl;
            else
                cout << "ne" << endl;
        }
        else if (izbor == 4)
        {
            string input;
            cout << "Unesite toèno prezime i ime: ";
            cin.ignore();
            getline(cin, input);
            bool postoji = false;
            for (int i = 0; i < brKl; i++)
            {
                if (prezIme[i] == input)
                {
                    cout << endl << "\t\t" << "Broj raèuna: " << brRacuna[i] << endl << "\t\t" << "Saldo: " << saldo[i] << endl;
                    postoji = true;
                }
            }
            if (!postoji)
                cout << "Raèun ne postoji!" << endl;

            if (datoteka.is_open())
            {
                datoteka << "Pretraga po prezimenu i imenu:" << endl;
                datoteka << "Uneseno prezime i ime: " << input << endl;
                if (postoji)
                {
                    for (int i = 0; i < brKl; i++)
                    {
                        if (prezIme[i] == input)
                        {
                            datoteka << "Broj raèuna: " << brRacuna[i] << endl;
                            datoteka << "Saldo: " << saldo[i] << endl;
                        }
                    }
                }
                else
                {
                    datoteka << "Raèun ne postoji!" << endl;
                }
            }
        }
        else if (izbor == 5)
        {
            unsigned long long int unosRacuna;
            cout << "Unesite broj raèuna koji želite ukloniti: ";
            cin >> unosRacuna;
            int ind = find(brRacuna, brRacuna + brKl, unosRacuna) - brRacuna;
            if (ind == brKl)
                cout << "Broj raèuna ne postoji!" << endl;
            else
            {
                for (int i = ind; i < brKl - 1; i++)
                {
                    brRacuna[i] = brRacuna[i + 1];
                    prezIme[i] = prezIme[i + 1];
                    saldo[i] = saldo[i + 1];
                }
                brKl--;
            }
        }
        else if (izbor == 6)
        {
           
                sort(prezIme, prezIme + brKl);

                ofstream izlaznaDatoteka("sortirani_podaci.txt", ios::app);
                if (!izlaznaDatoteka)
                {
                    cout << "Nije moguæe otvoriti datoteku za pisanje!" << endl;
                    return 1;
                }

                for (int i = 0; i < brKl; i++)
                {
                    izlaznaDatoteka << endl << "Broj raèuna: " << brRacuna[i] << endl;
                    izlaznaDatoteka << "\t\t" << prezIme[i] << endl;
                    izlaznaDatoteka << "\t\t" << saldo[i] << endl;
                }

                izlaznaDatoteka.close();
                cout << "Sortirani podaci su uspešno upisani u datoteku." << endl;
                ifstream ulaznaDatoteka("sortirani_podaci.txt");
                if (!ulaznaDatoteka)
                {
                    cout << "Nije moguæe otvoriti datoteku za èitanje!" << endl;
                    return 1;
                }
                string linija;
                while (getline(ulaznaDatoteka, linija))
                {
                    cout << linija << endl;
                }

                ulaznaDatoteka.close();
            }
        else if (izbor == 7)
        {
            cout << "Izlaz iz programa!";
            break;
        }
        else
        {
            cout << "Krivi unos!" << endl;
        }
        pause();
    }

    delete[] brRacuna;
    delete[] prezIme;
    delete[] saldo;

    datoteka.close();

    return 0;
}