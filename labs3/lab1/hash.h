#if !defined(HASH_H)
#define HASH_H
#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>

using namespace std;

typedef string Key;

typedef struct Value {
	unsigned int age;
	unsigned int weight;
} Value;

typedef struct Table {
  Key key;
  Value value;
  bool is_filled;
} Table;

#if !defined(START_CAPACITY)
#define START_CAPACITY 4
#endif
#if !defined(M)
#define M 50000
#endif
#if !defined(LOADFACTOR)
#define LOADFACTOR (float)(0.5)
#endif

typedef class HashTable
{
  private:
    int size;
    int capacity;
    Table * table;
    int gethash(Key key, int capacity) const;
  public:
    HashTable();
    ~HashTable();
    
    //HashTable(const HashTable& b);


    
    // Вставка в контейнер. Возвращаемое значение - успешность вставки.
    bool insert(const Key& k, const Value& v);

    // Проверка наличия значения по заданному ключу.
    bool search(const Key& key) const;
    void print();
    /*// Возвращает значение по ключу. Небезопасный метод.
    // В случае отсутствия ключа в контейнереа следует вставить в контейнер
    // значение, созданное конструктором по умолчанию и вернуть ссылку на него. 
    Value& operator[](const Key& k);

    // Возвращает значение по ключу. Бросает исключение при неудаче.
    Value& at(const Key& k);
    const Value& at(const Key& k) const;

    size_t size() const;
    bool empty() const;

    // Обменивает значения двух хэш-таблиц.
    // Подумайте, зачем нужен этот метод, при наличии стандартной функции
    // std::swap.
    void swap(HashTable& b);

    HashTable& operator=(const HashTable& b);


    // Очищает контейнер.
    void clear();
    // Удаляет элемент по заданному ключу.
    bool erase(const Key& k);

    friend bool operator==(const HashTable & a, const HashTable & b);
    friend bool operator!=(const HashTable & a, const HashTable & b);*/
 } HashTable;

void getkey(string str, Key& k);
void getvalue(string str, Value& v);

#endif