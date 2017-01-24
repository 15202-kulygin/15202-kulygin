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
Table * HashTable::get_data() const
{
    return table;
}
HashTable::HashTable()
{
    size = 0;
    capacity = START_CAPACITY;
    table = new Table[capacity];
    Table to_fill;
    to_fill.is_filled = false;
    to_fill.key = " ";
    to_fill.value.age = -1;
    to_fill.value.weight = -1;
    std::fill(table, table + capacity, to_fill); 
}

HashTable::HashTable(const HashTable& origin)
{
    size = origin.size;
    capacity = origin.capacity;
    table = new Table[capacity];
    std::copy(origin.table, origin.table + capacity, table);
}

HashTable::~HashTable()
{
    delete [] table;
}

// Вставка в контейнер. Возвращаемое значение - успешность вставки.
bool HashTable::insert(const Key& key, const Value& value)
{
    //cout << "INSERTING " << key << ' ' << value.age << ' ' << value.weight << endl;
    if (true == search(key))
    {
        //cout << "FOUND" << endl;
        return false;
    }
    else
    {
        //cout << "NOT FOUND" << endl;
        if (size + 1 >= capacity / 2) // if rehashing is needed
        {
            rehash();
        }
        size += 1;
        int hash = gethash(key);
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

void HashTable::rehash()
{
    Table * temp = new Table[capacity]; // creating temporary array of tables
    int current_ind = 0;
    std::copy(table, table + capacity, temp);
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
    
    for (int i = 0; i < old_size; ++i)
    {
        insert(temp[i].key, temp[i].value);
    }
    delete [] temp;
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

void HashTable::print() const
{
    if (0 == size)
    {
        std::cout << "Empty hashtable" << std::endl;
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
    HashTable & temp = origin;//???????????????????????
    origin = *this;
    *this = temp;
}

HashTable& HashTable::operator=(const HashTable& origin)
{
    if (this != &origin)
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
        /*Value * temp = new Value;
        temp->age = 0;
        temp->weight = 0;
        return *temp;*/ // ------------------ Hashtest "At" failed with this code
        throw -1;
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

const Value& HashTable::at(const Key& k) const
{
    if (false == HashTable::search(k))
    {
        /*Value * temp = new Value;
        temp->age = 0;
        temp->weight = 0;
        return *temp;*/
        throw -1;
    }
    else
    {
        int hash = HashTable::gethash(k);
        while (table[hash].key != k)
        {
            hash++;
            hash = hash % capacity;
        }
        const Value & result = table[hash].value;
        return result;
    }
}




