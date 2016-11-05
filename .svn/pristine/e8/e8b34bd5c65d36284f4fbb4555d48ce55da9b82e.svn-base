#include "hash.h"

using namespace std;

int HashTable::gethash(Key key) const
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
        table[i].key = " ";
        table[i].value.age = -1;
        table[i].value.weight = -1;
    }
}

HashTable::HashTable(const HashTable& origin)
{
    size = origin.size;
    capacity = origin.capacity;
    table = new Table[capacity];
    for (int i = 0; i < capacity; ++i)
    {
        if (true == origin.table[i].is_filled)
        {
            table[i].is_filled = true;
            table[i].key = origin.table[i].key;
            table[i].value.age = origin.table[i].value.age;
            table[i].value.weight = origin.table[i].value.weight;
        }
        else
        {
            table[i].is_filled = false;
            table[i].key = " ";
            table[i].value.age = -1;
            table[i].value.weight = -1;
        }
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
                table[i].key = " ";
                table[i].value.age = -1;
                table[i].value.weight = -1;
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
        int hash = HashTable::gethash(key);
        while (true == table[hash%capacity].is_filled)
        {
            hash++;
        }
        hash = hash%capacity;
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
    int hash = HashTable::gethash(key);
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
                current_ind = current_ind%capacity;
            }
        }

    }
}

void HashTable::print()
{
    if (0 == size)
    {
        return;
    }
    cout << "HashTable size : " << size <<  endl << "HashTable capacity : " << capacity << endl;
    for (int i = 0; i < capacity; ++i)
    {
        if (true == table[i].is_filled)
        {
            cout << "Table number " << i << ", name " << table[i].key << ", age " << table[i].value.age << ", weight " << table[i].value.weight << endl;
        }
    }
    cout << endl << endl;
}

// Обменивает значения двух хэш-таблиц.
// Подумайте, зачем нужен этот метод, при наличии стандартной функции
// std::swap.
void HashTable::swap(HashTable& origin)
{
    HashTable * temp = new HashTable(origin);
    delete [] origin.table;
    origin.size = size;
    origin.capacity = capacity;
    origin.table = new Table[origin.capacity];
    for (int i = 0; i < origin.capacity; ++i)
    {
        if (true == table[i].is_filled)
        {
            origin.table[i].key = table[i].key;
            origin.table[i].value.age = table[i].value.age;
            origin.table[i].value.weight = table[i].value.weight;
            origin.table[i].is_filled = true;
        }
        else
        {
            origin.table[i].key = " ";
            origin.table[i].value.age = -1;
            origin.table[i].value.weight = -1;
            origin.table[i].is_filled = false;
        }
    }
    delete [] table;
    size = temp->size;
    capacity = temp->capacity;
    table = new Table[capacity];
    for (int i = 0; i < capacity; ++i)
    {
        if (true == temp->table[i].is_filled)
        {
            table[i].key = temp->table[i].key;
            table[i].value.age = temp->table[i].value.age;
            table[i].value.weight = temp->table[i].value.weight;
            table[i].is_filled = true;
        }
        else
        {
            table[i].key = " ";
            table[i].value.age = -1;
            table[i].value.weight = -1;
            table[i].is_filled = false;
        }
    }
    delete temp;
}

HashTable& HashTable::operator=(const HashTable& origin)
{
    if (*this != origin)
    {
        size = origin.size;
        capacity = origin.capacity;
        delete [] table;
        //table = new Table[capacity];
        table = new Table[capacity];
        for (int i = 0; i < capacity; ++i)
        {
            if (true == origin.table[i].is_filled)
            {
                table[i].key = origin.table[i].key;
                table[i].value.age = origin.table[i].value.age;
                table[i].value.weight = origin.table[i].value.weight;
                table[i].is_filled = true;
            }
            else
            {
                table[i].key = " ";
                table[i].value.age = -1;
                table[i].value.weight = -1;
                table[i].is_filled = false;
            }
        }

    }
    return *this;
}

// Очищает контейнер.
void HashTable::clear()
{
    for (int i = 0; i < capacity; ++i)
    {
        if (true == table[i].is_filled)
        {
            table[i].is_filled = false;
            table[i].key = " ";
            table[i].value.age = -1;
            table[i].value.weight = -1;
        }
    }
    size = 0;
    capacity = START_CAPACITY;
}

// Удаляет элемент по заданному ключу.
bool HashTable::erase(const Key& k)
{
    int i = HashTable::gethash(k);
    while (true == table[i].is_filled)
    {
        if (k == table[i].key)
        {
            size--;
            table[i].key = " ";
            table[i].value.age = -1;
            table[i].value.weight = -1;
            table[i].is_filled = false;
            return true;
        }
        ++i;
        i = i%capacity;
    }
    return false;
}

int HashTable::getsize() const
{
    return size;
}

int HashTable::getcapacity() const
{
    return capacity;
}

bool HashTable::empty() const
{
    for (int i = 0; i < capacity; ++i)
    {
        if (true == table[i].is_filled)
        {
            return false;
        }
    }
    return true;
}

// Возвращает значение по ключу. Бросает исключение при неудаче.
Value& HashTable::at(const Key& k)
{
    if (false == HashTable::search(k))
    {
        throw 0;
    }
    else
    {
        int hash = HashTable::gethash(k);
        while (table[hash].key != k)
        {
            hash++;
            hash = hash % capacity;
        }
        Value & result = table[hash].value;
        return result;
    }
}

// Возвращает значение по ключу. Небезопасный метод.
// В случае отсутствия ключа в контейнере следует вставить в контейнер
// значение, созданное конструктором по умолчанию и вернуть ссылку на него. 
Value& HashTable::operator[](const Key& k)
{
    if (false == HashTable::search(k))
    {
        int i = 0;
        while (true == table[i].is_filled)
        {
            ++i;
            i = i % capacity;
        }
        table[i].value.age = -1;
        table[i].value.weight = -1;
        Value & result = table[i].value;
        return result;
    }
    else
    {
        int hash = HashTable::gethash(k);
        while (table[hash].key != k)
        {
            hash++;
            hash = hash % capacity;
        }
        Value & result = table[hash].value;
        return result;
    }
}


/*

const Value& HashTable::at(const Key& k) const;

*/

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
    while('\0' != newstr[i]) 
    {
        weight[weight_ind] = newstr[i];
        ++weight_ind;
        ++i;
    }
    int res_age = atoi(age);
    int res_weight = atoi(weight);
    delete [] age;
    delete [] weight;
    
    v.age = res_age;
   // cout << "ok" << endl;
    v.weight = res_weight;
}

