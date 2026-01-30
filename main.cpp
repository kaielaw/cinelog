#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <algorithm>
#include <windows.h>
using namespace std;

const string listMvs = "listMovies.txt";
const string listPersonal = "personalWatchlist.txt";

struct Film
{
    string judul;
    float rating;
    string genre;
    int year;
    string actors[2];
    string review;
};

void loadData(vector<Film> &daftarMvs, vector<Film> &daftarPersonal, int &jumlahMvs, int &jumlahPersonal);      // kay don
void menuPage(vector<Film> &daftarMvs, vector<Film> &daftarPersonal, int &jumlahMvs, int &jumlahPersonal);      // kay don
void showMovies(vector<Film> &daftarMvs, vector<Film> &daftarPersonal, int &jumlahMvs, int &jumlahPersonal);    // kay don
void showReviews(vector<Film> &daftarMvs, vector<Film> &daftarPersonal, int &jumlahMvs, int &jumlahPersonal);   // kay don
void swapFilm(Film &a, Film &b);                                                                                // jawa don
void sortNum(vector<Film> &daftarPersonal, int pilihan, bool ascending);                                        // jawa don
void sortTitle(vector<Film> &daftarPersonal, bool ascending);                                                   // jawa don
void sorted(vector<Film> &daftarMvs, vector<Film> &daftarPersonal, int &jumlahMvs, int &jumlahPersonal);        // jawa don -> sort by title, rating, date release -> ascending/descending
void filtered(vector<Film> daftarMvs, vector<Film> daftarPersonal, int &jumlahMvs, int &jumlahPersonal);        // kay don -> filter by rate tapi range, genre
void filteredByRate(vector<Film> daftarMvs, vector<Film> daftarPersonal, int &jumlahMvs, int &jumlahPersonal);  // kay don
void filteredByGenre(vector<Film> daftarMvs, vector<Film> daftarPersonal, int &jumlahMvs, int &jumlahPersonal); // kay don
void recommendations(vector<Film> daftarMvs, vector<Film> daftarPersonal, int &jumlahMvs, int &jumlahPersonal); // kay don
void search(vector<Film> daftarMvs, vector<Film> daftarPersonal, int &jumlahMvs, int &jumlahPersonal);          // jawa don -> search by actor
void addReview(vector<Film> &daftarMvs, vector<Film> &daftarPersonal, int &jumlahMvs, int &jumlahPersonal);     // kay don
void saveData(vector<Film> &daftarMvs, vector<Film> &daftarPersonal, int &jumlahMvs, int &jumlahPersonal);      // jawa don

int main()
{
    vector<Film> daftarMvs;
    vector<Film> daftarPersonal;
    int jumlahMvs = 0, jumlahPersonal = 0;
    loadData(daftarMvs, daftarPersonal, jumlahMvs, jumlahPersonal);
    menuPage(daftarMvs, daftarPersonal, jumlahMvs, jumlahPersonal);

    return 0;
}

void loadData(vector<Film> &daftarMvs, vector<Film> &daftarPersonal, int &jumlahMvs, int &jumlahPersonal)
{
    ifstream file1(listPersonal);
    ifstream file2(listMvs);
    Film f;

    if (file1.is_open())
    {
        file1 >> jumlahPersonal;
    }
    else
    {
        jumlahPersonal = 0;
    }

    file1.ignore();

    for (int i = 0; i < jumlahPersonal; i++)
    {
        getline(file1, f.judul);
        file1 >> f.rating;
        file1.ignore();
        getline(file1, f.genre);
        file1 >> f.year;
        file1.ignore();
        getline(file1, f.actors[0]);
        getline(file1, f.actors[1]);
        getline(file1, f.review);
        daftarPersonal.push_back(f);
    }

    file1.close();

    if (file2.is_open())
    {
        file2 >> jumlahMvs;
    }
    else
    {
        jumlahMvs = 0;
    }

    file2.ignore();

    for (int i = 0; i < jumlahMvs; i++)
    {
        getline(file2, f.judul);
        getline(file2, f.genre);
        file2 >> f.year;
        file2.ignore();
        getline(file2, f.actors[0]);
        getline(file2, f.actors[1]);
        daftarMvs.push_back(f);
    }

    file2.close();
}

void menuPage(vector<Film> &daftarMvs, vector<Film> &daftarPersonal, int &jumlahMvs, int &jumlahPersonal)
{
    system("cls");
    system("Color 8F");
    cout << " ================================================================ " << endl
         << "|\t\t\tCINELOG\t\t\t\t\t |" << endl
         << " ================================================================ " << endl
         << "|\t\t\tPAGE MENU\t\t\t\t |" << endl
         << " ================================================================ " << endl
         << "| 1. Show All Movies\t\t\t\t\t\t |" << endl
         << "| 2. Show All Reviews\t\t\t\t\t\t |" << endl
         << "| 3. Sort\t\t\t\t\t\t\t |" << endl
         << "| 4. Filter\t\t\t\t\t\t\t |" << endl
         << "| 5. Recommendations\t\t\t\t\t\t |" << endl
         << "| 6. Search\t\t\t\t\t\t\t |" << endl
         << "| 7. Add Reviews\t\t\t\t\t\t |" << endl
         << "| 8. Exit\t\t\t\t\t\t\t |" << endl
         << " ================================================================ " << endl
         << "-> ";

    int input;
    cin >> input;

    switch (input)
    {
    case 1:
        showMovies(daftarMvs, daftarPersonal, jumlahMvs, jumlahPersonal);
        break;

    case 2:
        showReviews(daftarMvs, daftarPersonal, jumlahMvs, jumlahPersonal);
        break;

    case 3:
        sorted(daftarMvs, daftarPersonal, jumlahMvs, jumlahPersonal);
        break;

    case 4:
        filtered(daftarMvs, daftarPersonal, jumlahMvs, jumlahPersonal);
        break;

    case 5:
        recommendations(daftarMvs, daftarPersonal, jumlahMvs, jumlahPersonal);
        break;

    case 6:
        search(daftarMvs, daftarPersonal, jumlahMvs, jumlahPersonal);
        break;
    case 7:
        addReview(daftarMvs, daftarPersonal, jumlahMvs, jumlahPersonal);

    default:
        saveData(daftarMvs, daftarPersonal, jumlahMvs, jumlahPersonal);
        break;
    }
}

void showMovies(vector<Film> &daftarMvs, vector<Film> &daftarPersonal, int &jumlahMvs, int &jumlahPersonal)
{
    system("cls");
    system("Color 04");
    cout << " ================================================================ " << endl
         << "|\t\t\tLIST OF ALL MOVIES\t\t\t |" << endl
         << " ================================================================ " << endl;

    for (int i = 0; i < jumlahMvs; i++)
    {
        cout << "|| " << i + 1 << ".\t" << daftarMvs[i].judul << " (" << daftarMvs[i].year << ")" << endl
             << "||\tGenre\t: " << daftarMvs[i].genre << endl
             << "||\tActors\t: " << daftarMvs[i].actors[0] << ", " << daftarMvs[i].actors[1] << endl;
    }

    cout << " ================================================================ " << endl
         << "| 1. Back to Menu\t\t\t\t\t\t|" << endl
         << "| 2. Exit\t\t\t\t\t\t\t|" << endl
         << " ================================================================ " << endl
         << "-> ";

    int input;
    cin >> input;

    switch (input)
    {
    case 1:
        menuPage(daftarMvs, daftarPersonal, jumlahMvs, jumlahPersonal);
        break;

    default:
        saveData(daftarMvs, daftarPersonal, jumlahMvs, jumlahPersonal);
        break;
    }
}

void showReviews(vector<Film> &daftarMvs, vector<Film> &daftarPersonal, int &jumlahMvs, int &jumlahPersonal)
{
    system("cls");
    system("Color 04");
    int count = 1;
    cout << " ================================================================ " << endl
         << "|\t\t\tLIST OF ALL REVIEWS\t\t\t |" << endl
         << " ================================================================ " << endl;

    for (auto &pr : daftarPersonal)
    {
        cout << "|| " << count << ".\t" << pr.judul << " (" << pr.year << ")" << endl
             << "||\tRate\t: " << pr.rating << "/5" << endl
             << "||\tGenre\t: " << pr.genre << endl
             << "||\tActors\t: " << pr.actors[0] << ", " << pr.actors[1] << endl
             << "||\tReview\t: " << pr.review << endl;
        count++;
    }

    cout << " ================================================================ " << endl
         << "| 1. Back to Menu\t\t\t\t\t\t|" << endl
         << "| 2. Exit\t\t\t\t\t\t\t|" << endl
         << " ================================================================ " << endl
         << "-> ";

    int input;
    cin >> input;

    switch (input)
    {
    case 1:
        menuPage(daftarMvs, daftarPersonal, jumlahMvs, jumlahPersonal);
        break;

    default:
        saveData(daftarMvs, daftarPersonal, jumlahMvs, jumlahPersonal);
        break;
    }
}

void swapFilm(Film &a, Film &b)
{
    Film temp = a;
    a = b;
    b = temp;
}

void sortNum(vector<Film> &daftarPersonal, int pilihan, bool ascending)
{
    int n = daftarPersonal.size();

    for (int i = 0; i < n - 1; i++)
    {
        int idx = i;

        for (int j = i + 1; j < n; j++)
        {
            if (pilihan == 2)
            {
                if (ascending)
                {
                    if (daftarPersonal[j].rating < daftarPersonal[idx].rating)
                        idx = j;
                }
                else
                {
                    if (daftarPersonal[j].rating > daftarPersonal[idx].rating)
                        idx = j;
                }
            }

            else if (pilihan == 3)
            {
                if (ascending)
                {
                    if (daftarPersonal[j].year < daftarPersonal[idx].year)
                        idx = j;
                }
                else
                {
                    if (daftarPersonal[j].year > daftarPersonal[idx].year)
                        idx = j;
                }
            }
        }
        if (idx != i)
        {
            swapFilm(daftarPersonal[i], daftarPersonal[idx]);
        }
    }
}

void sortTitle(vector<Film> &daftarPersonal, bool ascending)
{
    int n = (int)daftarPersonal.size();

    for (int i = 0; i < n - 1; i++)
    {
        int idx = i;

        for (int j = i + 1; j < n; j++)
        {
            char a;
            char b;

            if (daftarPersonal[j].judul.empty())
            {
                break;
            }
            else
            {
                a = daftarPersonal[j].judul[0];
                if (a >= 'A' && a <= 'Z')
                {
                    a = a + 32;
                }
            }

            if (daftarPersonal[idx].judul.empty())
            {
                break;
            }
            else
            {
                b = daftarPersonal[idx].judul[0];
                if (b >= 'A' && b <= 'Z')
                {
                    b = b + 32;
                }
            }

            if (ascending)
            {
                if (a < b)
                    idx = j;
            }
            else
            {
                if (a > b)
                    idx = j;
            }
        }

        if (idx != i)
        {
            swapFilm(daftarPersonal[i], daftarPersonal[idx]);
        }
    }
}

void sorted(vector<Film> &daftarMvs, vector<Film> &daftarPersonal, int &jumlahMvs, int &jumlahPersonal)
{
    system("cls");
    cout << " ================================================================ " << endl
         << "|\t\t\tCINELOG\t\t\t\t\t |" << endl
         << " ================================================================ " << endl
         << "|\t\t\tSORT OPTION\t\t\t\t |" << endl
         << " ================================================================ " << endl
         << "| 1. Title\t\t\t\t\t\t\t |" << endl
         << "| 2. Rating\t\t\t\t\t\t\t |" << endl
         << "| 3. Date Release\t\t\t\t\t\t |" << endl
         << " ================================================================ " << endl
         << "-> ";

    int pilihOpsi;
    cin >> pilihOpsi;
    cin.ignore();

    cout << " ================================================================ " << endl
         << "|\t\t\tCHOOSE SORTING MODE\t\t\t|" << endl
         << " ================================================================ " << endl
         << "| 1. Ascending\t\t\t\t\t\t\t|" << endl
         << "| 2. Descending\t\t\t\t\t\t\t|" << endl
         << " ================================================================ " << endl
         << "-> ";

    int pilihMode;
    cin >> pilihMode;
    cin.ignore();

    bool ascending;
    if (pilihMode == 1)
    {
        ascending = true;
    }
    else
    {
        ascending = false;
    }

    if (pilihOpsi == 1)
    {
        sortTitle(daftarPersonal, ascending);
    }
    else if (pilihOpsi == 2 || pilihOpsi == 3)
    {
        sortNum(daftarPersonal, pilihOpsi, ascending);
    }
    showReviews(daftarMvs, daftarPersonal, jumlahMvs, jumlahPersonal);
}

void filtered(vector<Film> daftarMvs, vector<Film> daftarPersonal, int &jumlahMvs, int &jumlahPersonal)
{
    system("cls");
    cout << " ================================================================ " << endl
         << "|\t\t\tCINELOG\t\t\t\t\t |" << endl
         << " ================================================================ " << endl
         << "|\t\t\tFILTERED BY\t\t\t\t |" << endl
         << " ================================================================ " << endl
         << "| 1. Rate\t\t\t\t\t\t\t |" << endl
         << "| 2. Genre\t\t\t\t\t\t\t |" << endl
         << "| 3. Back to Menu\t\t\t\t\t\t |" << endl
         << "| 4. Exit\t\t\t\t\t\t\t |" << endl
         << " ================================================================ " << endl
         << "-> ";

    int input;
    cin >> input;

    switch (input)
    {
    case 1:
        filteredByRate(daftarMvs, daftarPersonal, jumlahMvs, jumlahPersonal);
        break;

    case 2:
        filteredByGenre(daftarMvs, daftarPersonal, jumlahMvs, jumlahPersonal);
        break;

    case 3:
        menuPage(daftarMvs, daftarPersonal, jumlahMvs, jumlahPersonal);
        break;

    default:
        saveData(daftarMvs, daftarPersonal, jumlahMvs, jumlahPersonal);
        break;
    }
}

void filteredByRate(vector<Film> daftarMvs, vector<Film> daftarPersonal, int &jumlahMvs, int &jumlahPersonal)
{
    system("cls");
    cout << " ================================================================ " << endl
         << "|\t\t\tFILTERED BY RATE\t\t\t |" << endl
         << " ================================================================ " << endl
         << "| 1. 0 - 3\t\t\t\t\t\t\t |" << endl
         << "| 2. 3 - 4\t\t\t\t\t\t\t |" << endl
         << "| 3. 4+\t\t\t\t\t\t\t\t |" << endl
         << "| 4. Back to Menu\t\t\t\t\t\t |" << endl
         << "| 5. Exit\t\t\t\t\t\t\t |" << endl
         << " ================================================================ " << endl
         << "-> ";

    int input;
    do
    {
        cin >> input;
    } while (input < 1 || input > 5);

    if (input == 5)
    {
        saveData(daftarMvs, daftarPersonal, jumlahMvs, jumlahPersonal);
    }
    else if (input == 4)
    {
        menuPage(daftarMvs, daftarPersonal, jumlahMvs, jumlahPersonal);
    }
    else
    {
        float minVal, maxVal;
        if (input == 1)
        {
            minVal = 0;
            maxVal = 3;
        }
        else if (input == 2)
        {
            minVal = 3;
            maxVal = 4;
        }
        else
        {
            minVal = 4;
            maxVal = 5;
        }

        system("cls");
        cout << " ================================================================ " << endl
             << "|\t\t\tRATE " << minVal << " - " << maxVal << " \t\t\t\t |" << endl
             << " ================================================================ " << endl;

        int count = 1;
        int found = 0;
        for (int i = 0; i < jumlahPersonal; i++)
        {
            if (minVal != 0)
            {
                if (daftarPersonal[i].rating > minVal && daftarPersonal[i].rating <= maxVal)
                {
                    cout << "|| " << count << ".\t" << daftarPersonal[i].judul << " (" << daftarPersonal[i].year << ")" << endl
                         << "||\tRate\t: " << daftarPersonal[i].rating << "/5" << endl
                         << "||\tGenre\t: " << daftarPersonal[i].genre << endl
                         << "||\tActors\t: " << daftarPersonal[i].actors[0] << ", " << daftarPersonal[i].actors[1] << endl
                         << "||\tReview\t: " << daftarPersonal[i].review << endl;
                    count++;
                    found++;
                }
            }
            else
            {
                if (daftarPersonal[i].rating >= minVal && daftarPersonal[i].rating <= maxVal)
                {
                    cout << "|| " << count << ".\t" << daftarPersonal[i].judul << " (" << daftarPersonal[i].year << ")" << endl
                         << "||\tRate\t: " << daftarPersonal[i].rating << "/5" << endl
                         << "||\tGenre\t: " << daftarPersonal[i].genre << endl
                         << "||\tActors\t: " << daftarPersonal[i].actors[0] << ", " << daftarPersonal[i].actors[1] << endl
                         << "||\tReview\t: " << daftarPersonal[i].review << endl;
                    count++;
                    found++;
                }
            }
        }

        if (found == 0)
        {
            cout << "|| There's no movie with this rate" << endl;
        }

        cout << " ================================================================ " << endl
             << "| 1. Back to Menu\t\t\t\t\t\t|" << endl
             << "| 2. Exit\t\t\t\t\t\t\t|" << endl
             << " ================================================================ " << endl
             << "-> ";

        int input;
        cin >> input;

        switch (input)
        {
        case 1:
            menuPage(daftarMvs, daftarPersonal, jumlahMvs, jumlahPersonal);
            break;

        default:
            saveData(daftarMvs, daftarPersonal, jumlahMvs, jumlahPersonal);
            break;
        }
    }
}

void filteredByGenre(vector<Film> daftarMvs, vector<Film> daftarPersonal, int &jumlahMvs, int &jumlahPersonal)
{
    system("cls");
    cout << " ================================================================ " << endl
         << "|\t\t\tFILTERED BY GENRE\t\t\t |" << endl
         << " ================================================================ " << endl
         << "| 1. Action\t\t\t\t\t\t\t |" << endl
         << "| 2. Animation\t\t\t\t\t\t\t |" << endl
         << "| 3. Crime\t\t\t\t\t\t\t |" << endl
         << "| 4. Documenter\t\t\t\t\t\t\t |" << endl
         << "| 5. Drama\t\t\t\t\t\t\t |" << endl
         << "| 6. History\t\t\t\t\t\t\t |" << endl
         << "| 7. Horror\t\t\t\t\t\t\t |" << endl
         << "| 8. Romance\t\t\t\t\t\t\t |" << endl
         << "| 9. Thriller\t\t\t\t\t\t\t |" << endl
         << "| 10. Back to Menu\t\t\t\t\t\t |" << endl
         << "| 11. Exit\t\t\t\t\t\t\t |" << endl
         << " ================================================================ " << endl
         << "-> ";

    int input;
    cin >> input;

    string filter;
    switch (input)
    {
    case 1:
        filter = "action";
        break;

    case 2:
        filter = "animation";
        break;

    case 3:
        filter = "crime";
        break;

    case 4:
        filter = "documenter";
        break;

    case 5:
        filter = "drama";
        break;

    case 6:
        filter = "history";
        break;

    case 7:
        filter = "horror";
        break;

    case 8:
        filter = "romance";
        break;

    case 9:
        filter = "thriller";
        break;

    case 10:
        menuPage(daftarMvs, daftarPersonal, jumlahMvs, jumlahPersonal);
        break;

    default:
        saveData(daftarMvs, daftarPersonal, jumlahMvs, jumlahPersonal);
        break;
    }

    system("cls");
    cout << " ================================================================ " << endl
         << "|\t\t\tFILTERED BY GENRE\t\t\t |" << endl
         << " ================================================================ " << endl;

    int count = 1;
    bool found = false;
    for (int i = 0; i < jumlahMvs; i++)
    {
        string low = daftarMvs[i].genre;
        transform(low.begin(), low.end(), low.begin(), ::tolower);
        if (low == filter)
        {
            cout << "|| " << count << ".\t" << daftarMvs[i].judul << " (" << daftarMvs[i].year << ")" << endl
                 << "||\tGenre\t: " << daftarMvs[i].genre << endl
                 << "||\tActors\t: " << daftarMvs[i].actors[0] << ", " << daftarMvs[i].actors[1] << endl;
            count++;
            found = true;
        }
    }

    if (!found)
    {
        cout << "|| There's no movies with this genre" << endl;
    }

    cout << " ================================================================ " << endl
         << "| 1. Back to Menu\t\t\t\t\t\t|" << endl
         << "| 2. Exit\t\t\t\t\t\t\t|" << endl
         << " ================================================================ " << endl
         << "-> ";

    cin >> input;

    switch (input)
    {
    case 1:
        menuPage(daftarMvs, daftarPersonal, jumlahMvs, jumlahPersonal);
        break;

    default:
        saveData(daftarMvs, daftarPersonal, jumlahMvs, jumlahPersonal);
        break;
    }
}

void recommendations(vector<Film> daftarMvs, vector<Film> daftarPersonal, int &jumlahMvs, int &jumlahPersonal)
{
    system("Color 46");
    srand(time(0));
    int randNum = rand() % jumlahMvs;
    int check = 0;
    for (int i = 0; i < jumlahPersonal; i++)
    {
        if (daftarPersonal[i].judul == daftarMvs[randNum].judul)
        {
            check++;
            break;
        }
    }

    if (check == 0)
    {
        system("cls");
        cout << " ================================================================ " << endl
             << "|\t\t\tRECOMMENDATION TO WATCH\t\t\t |" << endl
             << " ================================================================ " << endl
             << "|| " << daftarMvs[randNum].judul << " (" << daftarMvs[randNum].year << ")" << endl
             << "|| Genre\t: " << daftarMvs[randNum].genre << endl
             << "|| Actors\t: " << daftarMvs[randNum].actors[0] << ", " << daftarMvs[randNum].actors[1] << endl
             << " ================================================================ " << endl
             << "| 1. Back to Menu\t\t\t\t\t\t|" << endl
             << "| 2. Exit\t\t\t\t\t\t\t|" << endl
             << " ================================================================ " << endl
             << "-> ";

        int input;
        cin >> input;

        switch (input)
        {
        case 1:
            menuPage(daftarMvs, daftarPersonal, jumlahMvs, jumlahPersonal);
            break;

        default:
            saveData(daftarMvs, daftarPersonal, jumlahMvs, jumlahPersonal);
            break;
        }
    }
    else
    {
        recommendations(daftarMvs, daftarPersonal, jumlahMvs, jumlahPersonal);
    }
}

void search(vector<Film> daftarMvs, vector<Film> daftarPersonal, int &jumlahMvs, int &jumlahPersonal)
{
    system("cls");
    cout << " ================================================================ " << endl
         << "|\t\t\tCINELOG\t\t\t\t\t |" << endl
         << " ================================================================ " << endl
         << "|\t\t\tSEARCH OPTION\t\t\t\t |" << endl
         << " ================================================================ " << endl
         << "| Write down the actor you want to search!\t\t\t |" << endl
         << " ================================================================ " << endl
         << "-> ";

    cin.ignore();

    string srcActor;
    getline(cin, srcActor);
    transform(srcActor.begin(), srcActor.end(), srcActor.begin(), ::tolower);

    bool found = false;
    for (int i = 0; i < jumlahMvs; i++)
    {

        for (int j = 0; j < 2; j++)
        {
            string newActor = daftarMvs[i].actors[j];
            transform(newActor.begin(), newActor.end(), newActor.begin(), ::tolower);

            if (newActor == srcActor)
            {
                found = true;

                cout << "\nActor found!\n";
                cout << "Movie      : " << daftarMvs[i].judul << endl;
                cout << "Genre      : " << daftarMvs[i].genre << endl;
                cout << "Year       : " << daftarMvs[i].year << endl;
                cout << "Actor 1    : " << daftarMvs[i].actors[0] << endl;
                cout << "Actor 2    : " << daftarMvs[i].actors[1] << endl;
                cout << endl;
            }
        }
    }

    if (!found)
    {
        cout << "Actor not found.\n"
             << endl;
    }
    cout << " ================================================================ " << endl
         << "| 1. Back to Menu\t\t\t\t\t\t|" << endl
         << "| 2. Exit\t\t\t\t\t\t\t|" << endl
         << " ================================================================ " << endl
         << "-> ";

    int input;
    cin >> input;

    switch (input)
    {
    case 1:
        menuPage(daftarMvs, daftarPersonal, jumlahMvs, jumlahPersonal);
        break;

    default:
        saveData(daftarMvs, daftarPersonal, jumlahMvs, jumlahPersonal);
        break;
    }
}

void addReview(vector<Film> &daftarMvs, vector<Film> &daftarPersonal, int &jumlahMvs, int &jumlahPersonal)
{
    system("cls");
    cout << " ================================================================ " << endl
         << "|\t\t\tADD REVIEW\t\t\t\t |" << endl
         << " ================================================================ " << endl;

    Film pr;
    cout << "|| Title\t: ";
    cin.ignore();
    getline(cin, pr.judul);
    string title = pr.judul;
    transform(title.begin(), title.end(), title.begin(), ::tolower);

    for (int i = 0; i < jumlahPersonal; i++)
    {
        string temp = daftarPersonal[i].judul;
        transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
        if (title == temp)
        {
            cout << "|| You already reviewed this movie " << endl;
            _sleep(2000);
            addReview(daftarMvs, daftarPersonal, jumlahMvs, jumlahPersonal);
            break;
        }
    }

    bool sama = false;
    for (int i = 0; i < jumlahMvs; i++)
    {
        string temp = daftarMvs[i].judul;
        transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
        if (title == temp)
        {
            cout << "|| Year\t\t: " << daftarMvs[i].year << endl;
            pr.year = daftarMvs[i].year;
            cout << "|| Genre\t: " << daftarMvs[i].genre << endl;
            pr.genre = daftarMvs[i].genre;
            cout << "|| Actor 1\t: " << daftarMvs[i].actors[0] << endl;
            pr.actors[0] = daftarMvs[i].actors[0];
            cout << "|| Actor 2\t: " << daftarMvs[i].actors[1] << endl;
            pr.actors[1] = daftarMvs[i].actors[1];
            cout << "|| Rate\t\t: ";
            cin >> pr.rating;
            cin.ignore();
            cout << "|| Review\t: ";
            getline(cin, pr.review);
            sama = true;
        }
    }

    if (!sama)
    {
        daftarMvs[jumlahMvs].judul = pr.judul;
        cout << "|| Year\t\t: ";
        cin >> pr.year;
        cin.ignore();
        daftarMvs[jumlahMvs].year = pr.year;
        cout << "|| Rate\t\t: ";
        cin >> pr.rating;
        cin.ignore();

        bool check = false;
        do
        {
            cout << "|| Genre\t: ";
            getline(cin, pr.genre);
            daftarMvs[jumlahMvs].genre = pr.genre;
            string temp = pr.genre;
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
            if (temp == "action" || temp == "animation" || temp == "crime" || temp == "documenter" || temp == "drama" || temp == "history" || temp == "horror" || temp == "romance" || temp == "thriller")
            {
                check = true;
            }
            else
            {
                cout << "|| Pick genre between action, animation, crime, documenter, drama, history, horror, romance, thriller" << endl;
            }
        } while (check == false);

        cout << "|| Actor 1\t: ";
        getline(cin, pr.actors[0]);
        daftarMvs[jumlahMvs].actors[0] = pr.actors[0];
        cout << "|| Actor 2\t: ";
        getline(cin, pr.actors[1]);
        daftarMvs[jumlahMvs].actors[1] = pr.actors[1];
        cout << "|| Review\t: ";
        getline(cin, pr.review);
        jumlahMvs++;
    }

    jumlahPersonal++;
    daftarPersonal.push_back(pr);

    cout << " ================================================================ " << endl
         << "| 1. Back to Menu\t\t\t\t\t\t|" << endl
         << "| 2. Exit\t\t\t\t\t\t\t|" << endl
         << " ================================================================ " << endl
         << "-> ";

    int input;
    cin >> input;

    switch (input)
    {
    case 1:
        menuPage(daftarMvs, daftarPersonal, jumlahMvs, jumlahPersonal);
        break;

    default:
        saveData(daftarMvs, daftarPersonal, jumlahMvs, jumlahPersonal);
        break;
    }
}

void saveData(vector<Film> &daftarMvs, vector<Film> &daftarPersonal, int &jumlahMvs, int &jumlahPersonal)
{
    ofstream file1(listPersonal);
    if (!file1.is_open())
    {
        return;
    }
    file1 << jumlahPersonal << endl;
    for (int i = 0; i < jumlahPersonal; i++)
    {
        file1 << daftarPersonal[i].judul << endl;
        file1 << daftarPersonal[i].rating << endl;
        file1 << daftarPersonal[i].genre << endl;
        file1 << daftarPersonal[i].year << endl;
        file1 << daftarPersonal[i].actors[0] << endl;
        file1 << daftarPersonal[i].actors[1] << endl;
        file1 << daftarPersonal[i].review << endl;
    }
    file1.close();

    ofstream file2(listMvs);
    if (!file2.is_open())
    {
        return;
    }
    file2 << jumlahMvs << endl;
    for (int i = 0; i < jumlahMvs; i++)
    {
        file2 << daftarMvs[i].judul << endl;
        file2 << daftarMvs[i].genre << endl;
        file2 << daftarMvs[i].year << endl;
        file2 << daftarMvs[i].actors[0] << endl;
        file2 << daftarMvs[i].actors[1] << endl;
    }
    file2.close();
}