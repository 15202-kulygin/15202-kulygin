#pragma once

#include <string>

typedef std::string Key;

struct Value
{
    unsigned age;
    unsigned weight;
};

struct ListItem
{
    Key key;
    Value value;
    ListItem * next;

    ListItem(Key key, Value value, ListItem * next)
    {
        this->key = key;
        this->value = value;
        this->next = next;
    }
};

class HashTable
{
public:
    HashTable();

    ~HashTable();

    // Copy constructor
    HashTable(const HashTable & b);

    // Move constructor
    HashTable(HashTable && b);


    // Обменивает значения двух хэш-таблиц.
    // Подумайте, зачем нужен этот метод, при наличии стандартной функции
    // std::swap.
    void swap(HashTable & b);

    HashTable & operator=(const HashTable & b);

    HashTable & operator=(HashTable && b);


    // Очищает контейнер.
    void clear();

    // Удаляет элемент по заданному ключу.
    bool erase(const Key & k);

    // Вставка в контейнер. Возвращаемое значение - успешность вставки.
    bool insert(const Key & k, const Value & v);

    // Проверка наличия значения по заданному ключу.
    bool contains(const Key & k) const;

    // Возвращает значение по ключу. Небезопасный метод.
    // В случае отсутствия ключа в контейнера следует вставить в контейнер
    // значение, созданное конструктором по умолчанию и вернуть ссылку на него.
    const Value & operator[](const Key & k) const;

    Value & operator[](const Key & k);

    // Возвращает значение по ключу. Бросает исключение при неудаче.
    Value & at(const Key & k);

    const Value & at(const Key & k) const;

    size_t size() const;

    bool empty() const;

    bool operator==(const HashTable & other) const;

    bool operator!=(const HashTable & other) const;

private:
    size_t table_size = 256;
    ListItem ** table;

    size_t hash(const Key & key) const;

    void rehash();

    const size_t row_length_limit = 12;
};
