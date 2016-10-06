#include "hash.h"

#define P 7

using namespace std;

int HashTable::gethash(Key key, int capacity) const
{
    char * str = (char *)key.c_str();
    unsigned int result = 0;
    for (int i = 0; i < key.length(); ++i) 
        result = (result * 31) ^ str[i];
    return result%capacity;
   
}
HashTable::HashTable()
{
    size = 0;
    capacity = START_CAPACITY;
    table = new Table[capacity];
    for (int i = 0; i < capacity; ++i)
    {
        table[i].is_filled = false;
    }
}
HashTable::~HashTable()
{
    delete [] table;
    size = 0;
    capacity = 0;
}

// Вставка в контейнер. Возвращаемое значение - успешность вставки.
bool HashTable::insert(const Key& key, const Value& value)
{
    //cout << "INSERTING " << key << ' ' << value.age << ' ' << value.weight << endl;
    if (true == HashTable::search(key))
    {
        //cout << "FOUND" << endl;
        return false;
    }
    else
    {
        //cout << "NOT FOUND" << endl;
        if (size + 1 >= capacity / 2) // if rehashing is needed
        {
            //cout << "TRY " << size << ' ' << capacity << endl;
            Table * temp = new Table[size]; // creating temporary array of tables
            int current_ind = 0;

            for (int i = 0; i < capacity; ++i)
            {
                if (true == table[i].is_filled)
                {
                    //cout << "TRY1 " << i << endl;
                    temp[current_ind].key = table[i].key;
                    temp[current_ind].value.age = table[i].value.age;
                    temp[current_ind].value.weight = table[i].value.weight;
                    temp[current_ind].is_filled = true;
                    current_ind++;
                }
            }
            delete [] table; // deleting the old array of tables
            capacity *= 2;
            table = new Table[capacity];
            for (int i = 0; i < capacity; ++i)
            {
                table[i].is_filled = false;
            }
            int old_size = size;
            size = 0;
            //cout << "SIZE CHECKING " << size << endl;
            for (int i = 0; i < old_size; ++i)
            {
                HashTable::insert(temp[i].key, temp[i].value);
            }
            delete [] temp;
            //cout << "REHASHED" << endl;
        }
        size += 1;
        int hash = HashTable::gethash(key, capacity);
        //cout << "hah " << hash <<  endl;
        table[hash].key = key;
        table[hash].value.age = value.age;
        table[hash].value.weight = value.weight;
        table[hash].is_filled = true;
        //cout << "INSERTED" << endl;
        return true;
    }
}

// Проверка наличия значения по заданному ключу.
bool HashTable::search(const Key& key) const
{
    if (0 == size)
    {
        return false;
    }
    int hash = HashTable::gethash(key, capacity);
    int current_ind = hash;
    while (true)
    {
        if (false == table[current_ind].is_filled)
        {
            return false;
        }
        else
        {
            if (table[current_ind].key == key)
            {
                return true;
            }
            else
            {
                current_ind++;
            }
        }

    }
}

void HashTable::print()
{
    cout << "HashTable size : " << size <<  endl << "HashTable capacity : " << capacity << endl;
    for (int i = 0; i < capacity; ++i)
    {
        if (true == table[i].is_filled)
        {
            cout << "Table number " << i << ", name " << table[i].key << ", age " << table[i].value.age << ", weight " << table[i].value.weight << endl;
        }
    }
}

//HashTable::HashTable(const HashTable& b);

// Обменивает значения двух хэш-таблиц.
// Подумайте, зачем нужен этот метод, при наличии стандартной функции
// std::swap.
/*void HashTable::swap(HashTable& b);

HashTable& HashTable::operator=(const HashTable& b);
// Очищает контейнер.
void HashTable::clear();
// Удаляет элемент по заданному ключу.
bool HashTable::erase(const Key& k);




// Возвращает значение по ключу. Небезопасный метод.
// В случае отсутствия ключа в контейнереа следует вставить в контейнер
// значение, созданное конструктором по умолчанию и вернуть ссылку на него. 
Value& HashTable::operator[](const Key& k);

// Возвращает значение по ключу. Бросает исключение при неудаче.
Value& HashTable::at(const Key& k);
const Value& HashTable::at(const Key& k) const;

size_t HashTable::size() const;
bool HashTable::empty() const;

friend bool HashTable::operator==(const HashTable & a, const HashTable & b);
friend bool HashTable::operator!=(const HashTable & a, const HashTable & b);*/

void getkey(string str, Key& k)
{
    char * newstr = (char *)str.c_str();
    int i = 0;
    char * key = new char[100];
    while(' ' != newstr[i]) // getting the key
    {
        key[i] = newstr[i];
        ++i;
    }
    key[i] = '\0';
    k = key;
    delete [] key;

}
void getvalue(string str, Value& v)
{
    //cout << v.age << v.weight << "check << endl;"
    char * newstr = (char *)str.c_str();
    char * age = new char[100];
    char * weight = new char[100];
    int i = 0;
    int age_ind = 0;
    int weight_ind = 0;
    while(' ' != newstr[i]) 
    {
        ++i;
    }
    ++i;
    while(' ' != newstr[i]) 
    {
        age[age_ind] = newstr[i];
        ++age_ind;
        ++i;
    }
    ++i;
    while(' ' != newstr[i]) 
    {
        weight[weight_ind] = newstr[i];
        ++weight_ind;
        ++i;
    }
    int res_age = atoi(age);
    int res_weight = atoi(weight);
    delete [] newstr;
    delete [] age;
    delete [] weight;
    
    v.age = res_age;
   // cout << "ok" << endl;
    v.weight = res_weight;
}

