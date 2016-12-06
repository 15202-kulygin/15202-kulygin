#include "HashTable.h"

HashTable::HashTable()
{
    table = new ListItem * [table_size];

    std::fill(table, table + table_size, nullptr);
}

HashTable::~HashTable()
{
    this->clear();
    delete[] table;
}

HashTable::HashTable(const HashTable & b) : HashTable()
{
    for (int i = 0; i < table_size; i++)
    {
        if (b.table[i] == nullptr) continue;

        ListItem * itemB = b.table[i];

        ListItem * newItem = new ListItem(itemB->key, itemB->value, nullptr);

        table[i] = newItem;
        ListItem * lastItemA = newItem;

        itemB = itemB->next;

        while (itemB != nullptr)
        {
            newItem = new ListItem(itemB->key, itemB->value, nullptr);

            lastItemA->next = newItem;
            lastItemA = newItem;

            itemB = itemB->next;
        }
    }
}

HashTable::HashTable(HashTable && b)
{
    std::swap(table, b.table);
}

void HashTable::swap(HashTable & b)
{
    std::swap(table, b.table);
}

HashTable & HashTable::operator=(const HashTable & b)
{
    if (&b == this) return *this;

    this->clear();
    delete[] table;

    for (int i = 0; i < table_size; i++)
    {
        if (b.table[i] == nullptr)
        {
            table[i] = nullptr;
        }
        else
        {
            ListItem * itemB = b.table[i];

            ListItem * newItem = new ListItem(itemB->key, itemB->value, nullptr);

            table[i] = newItem;
            ListItem * lastItemA = newItem;

            itemB = itemB->next;

            while (itemB != nullptr)
            {
                newItem = new ListItem(itemB->key, itemB->value, nullptr);

                lastItemA->next = newItem;
                lastItemA = newItem;

                itemB = itemB->next;
            }
        }
    }

    return *this;
}

HashTable & HashTable::operator=(HashTable && b)
{
    std::swap(table, b.table);

    return *this;
}

void HashTable::clear()
{
    for (size_t i = 0; i < table_size; i++)
    {
        if (table[i] == nullptr) continue;

        ListItem * item = table[i];
        ListItem * nextItem;

        while (true)
        {
            nextItem = item->next;
            delete item;

            if (nextItem == nullptr) break;
            item = nextItem;
        }

        table[i] = nullptr;
    }
}

bool HashTable::erase(const Key & k)
{
    size_t keyHash = hash(k);

    if (table[keyHash] == nullptr)
    {
        return false;
    }
    else
    {
        if (table[keyHash]->key == k)
        {
            // It's first item in list
            ListItem * second = table[keyHash]->next;
            delete table[keyHash];
            table[keyHash] = second;
            return true;
        }
        else
        {
            if (table[keyHash]->next == nullptr) return false;

            ListItem * prevItem = table[keyHash];
            ListItem * item = prevItem->next;

            while (true)
            {
                if (item->key == k)
                {
                    ListItem * next = item->next;
                    delete item;
                    prevItem->next = next;
                    return true;
                }

                if (item->next == nullptr) return false;
                prevItem = item;
                item = item->next;
            }
        }
    }
}

bool HashTable::insert(const Key & k, const Value & v)
{
    ListItem * newItem = new ListItem(k, v, nullptr);

    size_t keyHash = hash(k);

    if (table[keyHash] == nullptr)
    {
        table[keyHash] = newItem;
    }
    else
    {
        size_t row_length = 0;

        ListItem * lastItem = table[keyHash];
        while (lastItem->next != nullptr)
        {
            lastItem = lastItem->next;
            row_length++;
        }

        lastItem->next = newItem;

        if(row_length >= this->row_length_limit) this->rehash();
    }

    return true;
}

bool HashTable::contains(const Key & k) const
{
    size_t keyHash = hash(k);

    if (table[keyHash] == nullptr)
    {
        return false;
    }
    else
    {
        ListItem * item = table[keyHash];

        while (true)
        {
            if (item->key == k) return true;

            if (item->next == nullptr) return false;
            item = item->next;
        }
    }
}

const Value & HashTable::operator[](const Key & k) const
{
    size_t keyHash = hash(k);

    if (table[keyHash] != nullptr)
    {
        ListItem * item = table[keyHash];

        while (true)
        {
            if (item->key == k) return item->value;

            if (item->next == nullptr)
            {
                throw "No such element";
            }
            item = item->next;
        }
    }
    else
    {
        throw "No such element";
    }
}

Value & HashTable::operator[](const Key & k)
{
    size_t keyHash = hash(k);

    if (table[keyHash] == nullptr)
    {
        ListItem * newItem = new ListItem(k, Value(), nullptr);

        table[keyHash] = newItem;
        return newItem->value;
    }
    else
    {
        ListItem * item = table[keyHash];

        while (true)
        {
            if (item->key == k) return item->value;

            if (item->next == nullptr)
            {
                ListItem * newItem = new ListItem(k, Value(), nullptr);

                item->next = newItem;
                return newItem->value;
            }
            item = item->next;
        }
    }
}

Value & HashTable::at(const Key & k)
{
    size_t keyHash = hash(k);

    if (table[keyHash] == nullptr)
    {
        throw "No such element";
    }
    else
    {
        ListItem * item = table[keyHash];

        while (true)
        {
            if (item->key == k) return item->value;

            if (item->next == nullptr) throw "No such element";
            item = item->next;
        }
    }
}

const Value & HashTable::at(const Key & k) const
{
    size_t keyHash = hash(k);

    if (table[keyHash] == nullptr)
    {
        throw "No such element";
    }
    else
    {
        ListItem * item = table[keyHash];

        while (true)
        {
            if (item->key == k) return item->value;

            if (item->next == nullptr) throw "No such element";
            item = item->next;
        }
    }
}

size_t HashTable::size() const
{
    size_t size = 0;

    for (int i = 0; i < table_size; i++)
    {
        ListItem * item = table[i];
        while (item != nullptr)
        {
            size++;
            item = item->next;
        }
    }

    return size;
}

bool HashTable::empty() const
{
    for (int i = 0; i < table_size; i++)
    {
        if (table[i] != nullptr)
        {
            return false;
        }
    }

    return true;
}

size_t HashTable::hash(const Key & key) const
{
    size_t result = 0;

    for (int i = 0; i < key.length(); i++)
    {
        result += (unsigned char)(key[i]);
        result -= (result << 13) | (result >> 19);
    }

    return result % table_size;
}

bool HashTable::operator==(const HashTable & other) const
{
    for (int i = 0; i < table_size; i++)
    {
        if (table[i] == nullptr && other.table[i] == nullptr)
        {
            continue;
        }
        if (table[i] == nullptr || other.table[i] == nullptr)
        {
            return false;
        }

        ListItem * item = table[i];

        while (item != nullptr)
        {
            ListItem * otherItem = other.table[i];

            while (!(otherItem == nullptr ||
                     (otherItem->value.age == item->value.age &&
                      otherItem->value.weight == item->value.weight)))
            {
                otherItem = otherItem->next;
            }
            if (otherItem == nullptr)
            {
                // item not found in other.table
                return false;
            }

            item = item->next;
        }
    }
    return true;
}

bool HashTable::operator!=(const HashTable & other) const
{
    return !(*this == other);
}

void HashTable::rehash()
{
    size_t old_size = table_size;
    ListItem ** old_table = table;

    table_size *= 2;  // const static int
    table = new ListItem * [table_size];
    std::fill(table, table + table_size, nullptr);

    for (int i = 0; i < old_size; i++)
    {
        if (old_table[i] == nullptr) continue;

        ListItem * item = old_table[i];

        while (item != nullptr)
        {
            this->operator[](item->key) = item->value;
            item = item->next;
        }
    }

    delete old_table;
}
