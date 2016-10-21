#if !defined(HASH_H)
#define HASH_H

#include <iostream>
#include <string>
#include <cstdlib>

typedef std::string Key;

typedef struct Value {
	unsigned int age;
	unsigned int weight;
} Value;

typedef struct Table {
  Key key;
  Value value;
  bool is_filled;
} Table;

/*#if !defined(START_CAPACITY)
#define START_CAPACITY 4
#endif*/

typedef class HashTable
{
  private:
    static const int START_CAPACITY = 4;
    int size;
    int capacity;
    Table * table;
    
  public:
    HashTable();
    HashTable(const HashTable& origin);
    ~HashTable();
    
    int gethash(Key key) const;

    // Вставка в контейнер. Возвращаемое значение - успешность вставки.
    bool insert(const Key& k, const Value& v);

    // Проверка наличия значения по заданному ключу.
    bool search(const Key& key) const;
    
    void print();
    
    void swap(HashTable& origin);
    
    HashTable& operator=(const HashTable& origin);
    
    // Очищает контейнер.
    void clear();

     // Удаляет элемент по заданному ключу.
    bool erase(const Key& k);

    int getsize() const;
    int getcapacity() const;

    bool empty() const;

    friend bool operator==(const HashTable & a, const HashTable & b)
    {
      if (a.size == b.size)
      {
        for (int i = 0; i < a.capacity; ++i)
        {
          if (true == a.table[i].is_filled)
          {
            if (false == b.search(a.table[i].key))
            {
              return false;
            }
          }
          return true;
        }
      }
      return false;
    }

    friend bool operator!=(const HashTable & a, const HashTable & b)
    {
      if (a == b)
      {
        return false;
      }
      else
      {
        return true;
      }
    }
    // Возвращает значение по ключу. Бросает исключение при неудаче.
    Value& at(const Key& k);

    // Возвращает значение по ключу. Небезопасный метод.
    // В случае отсутствия ключа в контейнереа следует вставить в контейнер
    // значение, созданное конструктором по умолчанию и вернуть ссылку на него. 
    Value& operator[](const Key& k);

    /*  ?????? ? ? ?? ?
    const Value& at(const Key& k) const;
    */
} HashTable;


/// /??? ? ? ? ? ? ? ? ? ? ? ? ?  ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ?
void getkey(std::string str, Key& k);
void getvalue(std::string str, Value& v);

#endif