#include <iostream>
#include <string>

#include <sstream>
#include <iomanip>
using namespace std;

string caesar_proses(string text, int key);
void caesar();

string railfence_enkripsi(string text, int key);
string railfence_dekripsi(string text, int key);
void railfence();

string stream_cipher(string text, string key);
void stream();

string block_cipher_encrypt(string text, string key);
string block_cipher_decrypt(string text, string key);
void block();

void super_enkripsi();

int main(){
    int pilih;
    char ulang;

    START:
    cout << ".:: Program Enkripsi dan Dekripsi Pesan ::." << endl;
    cout << "1. nama kelompok 1" << endl;
    cout << "2. nama kelompok 2" << endl;
    cout << "3. nama kelompok 3" << endl;
    cout << "4. nama kelompok 4" << endl << endl;

    cout << "Algoritma:" << endl;
    cout << "1. Caesar Cipher" << endl;
    cout << "2. Rail Fence Cipher" << endl;
    cout << "3. Stream Cipher (XOR)" << endl;
    cout << "4. Block Cipher (Sederhana)" << endl;
    cout << "5. Super Enkripsi (Gabungan)" << endl;
    cout << "0. Keluar" << endl;
    cout << "Pilih: "; cin >> pilih;
    cout << endl;

    cin.ignore();  // Mengabaikan newline dari input sebelumnya

    if (pilih == 1){
        caesar();
    }
    else if (pilih == 2){
        railfence();
    }
    else if (pilih == 3){
        stream();
    }
    else if (pilih == 4){
        block();
    }
    else if (pilih == 5){
        super_enkripsi();
    }
    else if (pilih == 0){
        return 0;
    }
    else{
        cout << "Masukan tidak valid." << endl;
        system("pause");
        system("cls");
        goto START;
    }

    cout << endl << endl;
    cout << "Masukkan 'y' untuk mengulang program: "; cin >> ulang;
    if (ulang == 'y' || ulang == 'Y'){
        system("cls");
        goto START;
    }
    else{
        return 0;
    }

    return 0;
}

// Caesar Cipher
string caesar_proses(string text, int key){
    string result = "";

    for (int i = 0; i < text.length(); i++){
        if (isupper(text[i]))
            result += char(int(text[i] + key - 65) % 26 + 65);
        else if (islower(text[i]))
            result += char(int(text[i] + key - 97) % 26 + 97);
        else
            result += text[i];  // Tidak memodifikasi karakter selain huruf
    }
    return result;
}

void caesar(){
    int pilih;
    string teks; int kunci;

    cout << ".:: Caesar Cipher ::." << endl;
    cout << "1. Enkripsi" << endl;
    cout << "2. Dekripsi" << endl;
    cout << "Pilih: "; cin >> pilih;
    cout << endl;

    cin.ignore();  // Mengabaikan newline dari input sebelumnya

    if (pilih == 1){
        cout << ".:: Enkripsi ::." << endl;
        cout << "Plainteks\t: "; getline(cin, teks);
        cout << "Kunci (angka)\t: "; cin >> kunci;

        string cipherteks = caesar_proses(teks, kunci);
        cout << "Hasil enkripsi\t: " << cipherteks;
    }
    else if (pilih == 2){
        cout << ".:: Dekripsi ::." << endl;
        cout << "Cipherteks\t: "; getline(cin, teks);
        cout << "Kunci (angka)\t: "; cin >> kunci;

        kunci = kunci % 26; // Ensuring that key lies between 0-25
        string plainteks = caesar_proses(teks, 26 - kunci);
        cout << "Hasil dekripsi\t: " << plainteks;
    }
    else{
        cout << "Masukan tidak valid." << endl;
        system("pause");
        system("cls");
        main();
    }
}

// Rail Fence Cipher
string railfence_enkripsi(string text, int key){
    char rail[key][(text.length())];

    for (int i = 0; i < key; i++)
        for (int j = 0; j < text.length(); j++)
            rail[i][j] = '\n';

    bool dir_down = false;
    int row = 0, col = 0;

    for (int i = 0; i < text.length(); i++){
        if (row == 0 || row == key - 1)
            dir_down = !dir_down;

        rail[row][col++] = text[i];
        dir_down ? row++ : row--;
    }

    string result;
    for (int i = 0; i < key; i++)
        for (int j = 0; j < text.length(); j++)
            if (rail[i][j] != '\n')
                result.push_back(rail[i][j]);

    return result;
}

string railfence_dekripsi(string cipher, int key){
    char rail[key][cipher.length()];

    for (int i = 0; i < key; i++)
        for (int j = 0; j < cipher.length(); j++)
            rail[i][j] = '\n';

    bool dir_down;
    int row = 0, col = 0;

    for (int i = 0; i < cipher.length(); i++){
        if (row == 0)
            dir_down = true;
        if (row == key - 1)
            dir_down = false;

        rail[row][col++] = '*';
        dir_down ? row++ : row--;
    }

    int index = 0;
    for (int i = 0; i < key; i++)
        for (int j = 0; j < cipher.length(); j++)
            if (rail[i][j] == '*' && index < cipher.length())
                rail[i][j] = cipher[index++];

    string result;
    row = 0, col = 0;
    for (int i = 0; i < cipher.length(); i++){
        if (row == 0)
            dir_down = true;
        if (row == key - 1)
            dir_down = false;

        if (rail[row][col] != '*')
            result.push_back(rail[row][col++]);

        dir_down ? row++ : row--;
    }
    return result;
}

void railfence(){
    int pilih;
    string teks; int kunci;

    cout << ".:: Rail Fence Cipher ::." << endl;
    cout << "1. Enkripsi" << endl;
    cout << "2. Dekripsi" << endl;
    cout << "Pilih: "; cin >> pilih;
    cout << endl;

    cin.ignore();  // Mengabaikan newline dari input sebelumnya

    if (pilih == 1){
        cout << ".:: Enkripsi ::." << endl;
        cout << "Plainteks\t: "; getline(cin, teks);
        cout << "Kunci (angka)\t: "; cin >> kunci;

        string cipherteks = railfence_enkripsi(teks, kunci);
        cout << "Hasil enkripsi\t: " << cipherteks;
    }
    else if (pilih == 2){
        cout << ".:: Dekripsi ::." << endl;
        cout << "Cipherteks\t: "; getline(cin, teks);
        cout << "Kunci (angka)\t: "; cin >> kunci;

        string plainteks = railfence_dekripsi(teks, kunci);
        cout << "Hasil dekripsi\t: " << plainteks;
    }
    else{
        cout << "Masukan tidak valid." << endl;
        system("pause");
        system("cls");
        main();
    }
}

string stream_cipher(string text, string key) {
    string result = text;

    for (int i = 0; i < text.length(); i++) {
        result[i] = text[i] ^ key[i % key.length()];  // XOR operation
    }
    return result;
}

// Fungsi untuk mengonversi string ke format hex
string to_hex_chiper(const string &input) {
    static const char *hex_digits = "0123456789ABCDEF";
    string output;
    for (unsigned char c : input) {
        output.push_back(hex_digits[c >> 4]);
        output.push_back(hex_digits[c & 0x0F]);
    }
    return output;
}

// Fungsi untuk mengonversi kembali dari hex ke string
string from_hex_chiper(const string &input) {
    string output;
    if (input.length() % 2 != 0) {
        throw invalid_argument("Invalid hex string length.");
    }

    for (size_t i = 0; i < input.length(); i += 2) {
        unsigned char byte = (unsigned char)stoi(input.substr(i, 2), nullptr, 16);
        output.push_back(static_cast<char>(byte));
    }

    return output;
}

void stream() {
    int pilih;
    string teks, kunci;
    bool valid = false;

    while (!valid) {
        cout << ".:: Stream Cipher (XOR) ::." << endl;
        cout << "1. Enkripsi" << endl;
        cout << "2. Dekripsi" << endl;
        cout << "Pilih: "; cin >> pilih;
        cout << endl;

        cin.ignore();  // Mengabaikan newline dari input sebelumnya

        if (pilih == 1 || pilih == 2) {
            valid = true;
            if (pilih == 1) {
                cout << ".:: Enkripsi ::." << endl;
                cout << "Plainteks\t: "; getline(cin, teks);
                cout << "Kunci (teks)\t: "; getline(cin, kunci);

                if (kunci.length() == 0) {
                    cout << "Kunci tidak boleh kosong." << endl;
                    return;
                }

                string cipherteks = stream_cipher(teks, kunci);
                cout << "Hasil enkripsi (hex)\t: " << to_hex_chiper(cipherteks) << endl;
            } else if (pilih == 2) {
                cout << ".:: Dekripsi ::." << endl;
                cout << "Cipherteks (hex)\t: "; getline(cin, teks);
                cout << "Kunci (teks)\t: "; getline(cin, kunci);

                if (kunci.length() == 0) {
                    cout << "Kunci tidak boleh kosong." << endl;
                    return;
                }

                try {
                    // Konversi dari hex ke teks sebelum didekripsi
                    string cipherteks = from_hex_chiper(teks);
                    string plainteks = stream_cipher(cipherteks, kunci);
                    cout << "Hasil dekripsi\t: " << plainteks << endl;
                } catch (const invalid_argument &e) {
                    cout << "Format hex tidak valid: " << e.what() << endl;
                }
            }
        } else {
            cout << "Masukan tidak valid. Coba lagi." << endl;
        }
    }
}



// Fungsi untuk enkripsi block cipher sederhana
string block_cipher_encrypt(string text, string key) {
    string result = text;
    for (int i = 0; i < text.length(); i++) {
        result[i] = (text[i] + key[i % key.length()]) % 256;  // Penjumlahan dengan kunci
    }
    return result;
}

// Fungsi untuk dekripsi block cipher sederhana
string block_cipher_decrypt(string text, string key) {
    string result = text;
    for (int i = 0; i < text.length(); i++) {
        result[i] = (text[i] - key[i % key.length()] + 256) % 256;  // Pengurangan dengan kunci
    }
    return result;
}

// Fungsi untuk mengubah string ke format heksadesimal
string to_hex(const string& input) {
    stringstream ss;
    for (unsigned char c : input) {
        ss << hex << setw(2) << setfill('0') << (int)c;  // Menampilkan sebagai 2 digit hex
    }
    return ss.str();
}

// Fungsi untuk mengubah string heksadesimal ke string asli
string from_hex(const string& hex_input) {
    string result;
    for (size_t i = 0; i < hex_input.length(); i += 2) {
        string byte = hex_input.substr(i, 2);  // Mengambil 2 karakter hex
        char chr = (char)(int)strtol(byte.c_str(), nullptr, 16);  // Konversi hex ke char
        result.push_back(chr);
    }
    return result;
}

void block() {
    int pilih;
    string teks, kunci;

    cout << ".:: Block Cipher (Sederhana) ::." << endl;
    cout << "1. Enkripsi" << endl;
    cout << "2. Dekripsi" << endl;
    cout << "Pilih: "; cin >> pilih;
    cout << endl;

    cin.ignore();  // Mengabaikan newline dari input sebelumnya

    if (pilih == 1) {
        // Proses enkripsi
        cout << ".:: Enkripsi ::." << endl;
        cout << "Plainteks\t: "; getline(cin, teks);
        cout << "Kunci (teks)\t: "; getline(cin, kunci);

        if (teks.empty() || kunci.empty()) {
            cout << "Plainteks dan kunci tidak boleh kosong." << endl;
            return;
        }

        string cipherteks = block_cipher_encrypt(teks, kunci);
        cout << "Hasil enkripsi dalam hex\t: " << to_hex(cipherteks) << endl;  // Tampilkan dalam hex
    }
    else if (pilih == 2) {
        // Proses dekripsi
        cout << ".:: Dekripsi ::." << endl;
        cout << "Cipherteks (hex)\t: "; getline(cin, teks);  // Cipherteks dalam bentuk hex
        cout << "Kunci (teks)\t: "; getline(cin, kunci);

        if (teks.empty() || kunci.empty()) {
            cout << "Cipherteks dan kunci tidak boleh kosong." << endl;
            return;
        }

        string cipher_binary = from_hex(teks);  // Ubah hex kembali ke string biner
        string plainteks = block_cipher_decrypt(cipher_binary, kunci);
        cout << "Hasil dekripsi\t: " << plainteks << endl;
    }
    else {
        cout << "Masukan tidak valid." << endl;
    }
}

// Super Enkripsi (Gabungan)
void super_enkripsi() {
    int pilih;
    cout << ".:: Super Enkripsi (Gabungan) ::." << endl;
    cout << "1. Enkripsi" << endl;
    cout << "2. Dekripsi" << endl;
    cout << "Pilih: "; cin >> pilih;
    cin.ignore();  // Mengabaikan newline dari input sebelumnya

    string teks, kunci_stream, kunci_block;
    int kunci_caesar, kunci_railfence;

    if (pilih == 1) {
        // Proses Enkripsi
        cout << ".:: Enkripsi ::." << endl;
        cout << "Masukkan teks: "; getline(cin, teks);
        cout << "Kunci Caesar (angka): "; cin >> kunci_caesar;
        cout << "Kunci Rail Fence (angka): "; cin >> kunci_railfence;
        cin.ignore();  // Mengabaikan newline dari input sebelumnya
        cout << "Kunci Stream (teks): "; getline(cin, kunci_stream);
        cout << "Kunci Block (teks): "; getline(cin, kunci_block);

        // Caesar Cipher
        string caesar_enkrip = caesar_proses(teks, kunci_caesar);
        cout << "Hasil Caesar\t\t: " << caesar_enkrip << endl;

        // Rail Fence Cipher
        string railfence_enkrip = railfence_enkripsi(caesar_enkrip, kunci_railfence);
        cout << "Hasil Rail Fence\t: " << railfence_enkrip << endl;

        // Stream Cipher (XOR)
        string stream_enkrip = stream_cipher(railfence_enkrip, kunci_stream);
        cout << "Hasil Stream Cipher\t: " << to_hex_chiper(stream_enkrip) << endl;  // Ditampilkan dalam format hex

        // Block Cipher
        string block_enkrip = block_cipher_encrypt(stream_enkrip, kunci_block);
        cout << "Hasil Block Cipher\t: " << to_hex(block_enkrip) << endl;  // Ditampilkan dalam format hex

        // Hasil akhir gabungan dari 4 metode enkripsi
        cout << "Hasil Gabungan Enkripsi\t: " << to_hex(block_enkrip) << endl;  // Ditampilkan dalam format hex

    } else if (pilih == 2) {
        // Proses Dekripsi
        cout << ".:: Dekripsi ::." << endl;
        cout << "Masukkan teks (hex): "; getline(cin, teks);  // Teks dalam format hex
        cout << "Kunci Caesar (angka): "; cin >> kunci_caesar;
        cout << "Kunci Rail Fence (angka): "; cin >> kunci_railfence;
        cin.ignore();  // Mengabaikan newline dari input sebelumnya
        cout << "Kunci Stream (teks): "; getline(cin, kunci_stream);
        cout << "Kunci Block (teks): "; getline(cin, kunci_block);

        // Block Cipher Dekripsi
        string cipher_binary = from_hex(teks);  // Ubah hex kembali ke string biner
        string block_dekrip = block_cipher_decrypt(cipher_binary, kunci_block);
        cout << "Hasil Block Cipher Dekripsi\t: " << block_dekrip << endl;

        // Stream Cipher Dekripsi
        string stream_dekrip = stream_cipher(block_dekrip, kunci_stream);
        cout << "Hasil Stream Cipher Dekripsi\t: " << stream_dekrip << endl;

        // Rail Fence Cipher Dekripsi
        string railfence_dekrip = railfence_dekripsi(stream_dekrip, kunci_railfence);
        cout << "Hasil Rail Fence Dekripsi\t: " << railfence_dekrip << endl;

        // Caesar Cipher Dekripsi
        string caesar_dekrip = caesar_proses(railfence_dekrip, 26 - kunci_caesar);
        cout << "Hasil Caesar Dekripsi\t\t: " << caesar_dekrip << endl;

        // Hasil akhir gabungan dari 4 metode dekripsi
        cout << "Hasil Gabungan Dekripsi\t\t: " << caesar_dekrip << endl;

    } else {
        cout << "Pilihan tidak valid." << endl;
    }
}
