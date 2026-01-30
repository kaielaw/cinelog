# CINELOG (CINEMA LOG)

## Deskripsi Program
Cinelog merupakan suatu program yang berisi personal watching list, di mana program tersebut dapat menampilkan film yang telah ditonton dan review yang diberikan, mengurutkan film berdasarkan judul; rating; atau tahun rilis, memilah film berdasarkan rate atau genre, memberikan rekomendasi film, mencari film berdasarkan aktor, serta membuat review singkat. Dengan membuat program ini, user dapat melihat journal film yang telah ditonton dan user akan mudah untuk menonton kembali film sesuai genre atau rating. Pada program ini, terdapat struct movies yang berisi judul film, rating, genre, tahun rilisnya film, pemain atau aktor, dan review singkat di mana data-data tersebut akan disimpan ke dalam file.

## Algoritma yang Digunakan

### 1. Sorting
Memilah film berdasarkan rating, tahun rilis, atau judul film yang diinput oleh user. Rating dan tahun rilis akan dibagi dengan rentang nilai 0 hingga 5. Lalu, program akan sorting berdasarkan rate tertinggi atau terendah. Jika dipilih sort rate tertinggi, program akan menampilkan dari rate 5 sampai 0, begitupun sebaliknya. Judul film akan diurutkan berdasarkan ascending (a sampai z) atau descending (z sampai a) sesuai input user.

### 2. Filtering
Mengakses data film dan membandingkan setiap data berdasarkan input user. Apabila ditemukan data yang sama, program menampilkan film apa saja dengan genre atau rate tersebut. Apabila tidak ditemukan data yang sama, program akan menampilkan pesan bahwa tidak ada film dengan genre atau rate tersebut. 

### 3. Recommendations
Program akan menampilkan judul film, genre, dan aktor rekomendasi berdasarkan film-film yang belum pernah ditonton atau direview oleh user.

### 4. Searching
User dapat mencari film yang ada di list berdasarkan aktor yang bermain di film tersebut. Program akan meminta user untuk menginput nama aktor dan program akan menampilkan judul film, genre, tahun rilis, dan aktor sesuai dengan yang ada di list.

## Potongan Kode Penting

    1. Sorting
    void sortNum(vector<Film>& daftarPersonal, int pilihan, bool ascending){
    int n = daftarPersonal.size();

    for (int i = 0; i < n - 1; i++) {
        int idx = i; 

        for (int j = i + 1; j < n; j++) {
            if (pilihan == 2) {
                if (ascending) {
                    if (daftarPersonal[j].rating < daftarPersonal[idx].rating)
                        idx = j;
                } else {
                    if (daftarPersonal[j].rating > daftarPersonal[idx].rating)
                        idx = j;
                }
            }

            else if (pilihan == 3) {
                if (ascending) {
                    if (daftarPersonal[j].year < daftarPersonal[idx].year)
                        idx = j;
                } else {
                    if (daftarPersonal[j].year > daftarPersonal[idx].year)
                        idx = j;
                }
            }

        }

    void sortTitle(vector<Film>& daftarPersonal, bool ascending){
    int n = (int)daftarPersonal.size();

    for (int i = 0; i < n - 1; i++) {
        int idx = i; 

        for (int j = i + 1; j < n; j++) {
            char a;
            char b;

            if (daftarPersonal[j].judul.empty()){
                a = '0'; 
            } else {
                a = daftarPersonal[j].judul[0];
                if (a >= 'A' && a <= 'Z'){
                    a = a + 32;
                }
            }

            if (daftarPersonal[idx].judul.empty()){
                b = '0';
            } else {
                b = daftarPersonal[idx].judul[0];
                if (b >= 'A' && b <= 'Z'){
                    b = b + 32;
                }
            }
            
            if (ascending) {
                if (a < b) idx = j;
            } else {
                if (a > b) idx = j;
            }
        }
    
    2. Filtering
    void filteredByRate(vector<Film> daftarMvs, vector<Film> daftarPersonal, int &jumlahMvs, int &jumlahPersonal)
    {
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
        
    void filteredByGenre(vector<Film> daftarMvs, vector<Film> daftarPersonal, int &jumlahMvs, int &jumlahPersonal) // tampilin message gaada
    {
    int count = 1;
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
         }
        }
    }
    
    3. Recommendation
    srand(time(0));
    int randNum = rand() % jumlahMvs;
    int check = 0;
    for (int i = 0; i < jumlahPersonal; i++)
    {
        if (daftarPersonal[i].judul == daftarMvs[randNum].judul)
        {
            check++; // gausah ada check, lgsg panggil function
        }
    }
    
    4. Searching
    bool found = false;
    for (int i = 0; i < jumlahMvs; i++){

        for (int j = 0; j < 2; j++){
            string actor = daftarMvs[i].actors[j];
            string newActor = actor;
            transform(newActor.begin(), newActor.end(), newActor.begin(), ::tolower);

            if (newActor == srcActor){
                found = true;

                cout << "\nActor found!\n";
                cout << "Movie      : " << daftarMvs[i].judul << endl;
                cout << "Genre      : " << daftarMvs[i].genre << endl;
                cout << "Year       : " << daftarMvs[i].year  << endl;
                cout << "Actor 1    : " << daftarMvs[i].actors[0] << endl;
                cout << "Actor 2    : " << daftarMvs[i].actors[1] << endl;
                cout << endl;

                return; 
            }
        }
    } if (!found){
        cout << "Actor not found.\n" << endl;
    }
    
## Pembagian Tugas Anggota

|         Nama          |     NPM      |           Tugas                       |
|-----------------------|--------------|---------------------------------------|
| Kayla Hessa Ferdinan  | 140810250023 | Filtering, Recommendation, Add Review |
| Azahwa Ezarmei Narita | 140810250044 |    Sorting, Searching                 |

## Cara Menjalankan Program
Masukkan menu yang ingin dipilih (tampilkan semua film, tampilkan semua review, tampilkan berdasarkan genre, tampilkan berdasarkan rating atau tahun rilis (tertinggi/terendah), tampilkan berdasarkan judul (ascending/descending), rekomendasi, mencari film, menambahkan review film, atau exit).
1. Tampilkan semua
   - Langsung menampilkan semua data film.
2. Tampilkan semua review
   - Langsung memnampilkan semua review yang pernah diinput oleh user.
3. Tampilkan berdasarkan judul film
   - Meminta user untuk memilih untuk mensorting judul film secara ascending atau descending.
   - Menampilkan judul film sesuai input user.
4. Tampilkan berdasarkan genre
   - Meminta user untuk memilih genre.
   - Menampilkan film dengan genre tersebut (bila ada) atau menampilkan pesan.
5. Tampilkan berdasarkan rating atau tahun rilis
   - Meminta user untuk memilih antara dimulai dari tertinggi atau terendah.
   - Menampilka film berdasarkan tertinggi atau terendah.
6. Rekomendasi
   - Menampilkan rekomendasi film untuk user berdasarkan film yang belum pernah ditonton atau direview.
7. Mencari berdasarkan aktor film
   - User dapat mencari film dengan menginput aktor yang ingin dicari.
   - Program menampilkan judul film, genre, tahun rilis, dan aktor berdasarkan input user.
8. Menambahkan film
   - Meminta user untuk menambahkan judul film, rate film, genre, dan review singkat.
   - Menyimpan data ke dalam file.

## Struktur Folder
    project-folder/
    ├── main.cpp
    ├── data.txt
    └── README.md
