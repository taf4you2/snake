#include <iostream>
#include <stdlib.h>
#include <memory>

using namespace std;

/* Klasa Cell */
class Cell {
public:
    size_t wiersz;
    size_t kolumna;
    shared_ptr<Cell> next; // WskaŸnik na nastêpny element w kolejce

    // Konstruktor
    Cell(size_t w, size_t k) : wiersz(w), kolumna(k), next(nullptr) {}

    // Konstruktor kopiuj¹cy
    Cell(const Cell& other) : wiersz(other.wiersz), kolumna(other.kolumna), next(other.next) {}

    // Operator przypisania
    Cell& operator=(const Cell& other) {
        if (this != &other) {
            wiersz = other.wiersz;
            kolumna = other.kolumna;
            next = other.next;
        }
        return *this;
    }
};

/* Klasa Queue */
class Queue {
private:
    shared_ptr<Cell> front; // WskaŸnik na pierwszy element kolejki
    shared_ptr<Cell> rear;  // WskaŸnik na ostatni element kolejki
    size_t size;            // Liczba elementów w kolejce

public:
    // Konstruktor
    Queue() : front(nullptr), rear(nullptr), size(0) {}

    // Sprawdza, czy kolejka jest pusta
    bool isEmpty() const{
        return size == 0;
    }

    // Inicjalizowanie pierwszego elementu kolejki
    void first_element(size_t wiersz, size_t kolumna){
        shared_ptr<Cell> newCell = make_shared<Cell>(wiersz, kolumna);
        rear = newCell;
        front = newCell;
        size = 1;
    }

    // Dodawanie elementu do kolejki
    void enqueue(size_t w, size_t k, bool foundApple){
        shared_ptr<Cell> newCell = make_shared<Cell>(w, k);

        if (rear == nullptr){
            front = rear = newCell; // Pierwszy element w kolejce
            size = 1;
        }
        else{
            rear->next = newCell; // Dodanie na koñcu
            rear = newCell;
            if (foundApple){
                size++; // Jeœli znaleziono jab³ko, zwiêkszamy d³ugoœæ kolejki
            }
            else{
                dequeue(); // Jeœli nie, usuwamy pierwszy element FIFO
            }
        }
    }

    void dequeue(){
        if (isEmpty()){
            cout << "Queue is empty, cannot remove an element!" << endl;
            return;
        }

        front = front->next; // Przesuwamy wskaŸnik na nastêpny element
        if (front == nullptr){
            rear = nullptr;
        }
    }

    // Wyœwietlenie kolejki
    void display() const{
        shared_ptr<Cell> temp = front;
        cout << "Queue (size = " << size << "): ";
        while (temp){
            cout << "(" << temp->wiersz << "," << temp->kolumna << ") -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    shared_ptr<Cell> getLastElement() const{
    return rear;
    }
    shared_ptr<Cell> getFirstElement() const{
    return front;
    }
};


/*
    zwykla kolejka (queue)
    musimy znac wporzedne glowy
    po nacisnieciu dodajemy to co mamy dodac do glowy i dodajemy to do kolejki
*/

//klasa queue bedzie dziedziczona przez klase game_luncher

void table_display(char table[10][10]){

for(int i = 0; i < 10; ++i){
    for(int j = 0; j < 10; ++j){
            cout << table[i][j];
    }
    cout<<endl;
}
}


int main(){
char table[10][10];

int wiersz = 5, kolumna = 5;
int jab_wiersz = 3, jab_kolumna = 3;


for(int i = 0; i < 10; ++i){
    for(int j = 0; j < 10; ++j)
        table[i][j] = '0';
}
table[jab_wiersz][jab_kolumna] = '?';

Queue kolejka;
kolejka.first_element(wiersz, kolumna);

shared_ptr<Cell> ostatnia_komorka = kolejka.getLastElement();

//ostatnia_komorka->wiersz;

table[ostatnia_komorka->wiersz][ostatnia_komorka->kolumna] = '-';

table_display(table);

while (true){
    shared_ptr<Cell> ost = kolejka.getLastElement();
    if (!ost) break; // Sprawdzenie czy kolejka nie jest pusta

    size_t new_wie = ost->wiersz;
    size_t new_kol = ost->kolumna;

    shared_ptr<Cell> fir = kolejka.getFirstElement();
    if (!fir) break; // Sprawdzenie czy kolejka nie jest pusta
    size_t old_wie = fir->wiersz;
    size_t old_kol = fir->kolumna;

    char a;
    cin >> a;
    if (a == 'w') new_wie--;
    else if (a == 'a') new_kol--;
    else if (a == 'd') new_kol++;
    else if (a == 's') new_wie++;
    else break;

    table[new_wie][new_kol] = '-';
    table[old_wie][old_kol] = '0';

    kolejka.enqueue(new_wie, new_kol, 0);

    system("cls");
    table_display(table);
}

return 0;

}

