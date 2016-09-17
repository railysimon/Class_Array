#include <iostream>
#include <cstdlib>

using namespace std;


template <class T>
class Array
{
private:
        int size;
        T *ptr_array;
public:
        Array(int data_size) : size(data_size) { ptr_array = new T[size]; }
        Array(int data_size, T value);
        ~Array() { delete [] ptr_array; }

        void Set_Array_Data();
        void Get_Array_Data();

        void Insert(int position, T value);
        void Erase(int delete_position);
        int Size() const { return size; }
        void Sort() const;
        void Reverse();
        friend int Compare(const void *a, const void *b);

        template <typename F>
        friend ostream &operator << (ostream &stream, Array<F> &object);
        template <typename F>
        friend istream &operator >> (istream &stream, Array<F> &object);
        bool operator <(Array<T> &object);
        bool operator > (Array<T> &object);
        bool operator == (Array<T> &object);
        bool operator != (Array<T> &object);
        Array<T> &operator + (Array<T> &object);
        Array<T> &operator =(Array<T> &object);
        T operator [] (int i) { return ptr_array[i]; }
};

template <class T>
Array<T>::Array(int data_size, T value)
{
    size = data_size;
    ptr_array = new T[size];

    for(int i=0; i<size; i++)
    {
        ptr_array[i] = value;
    }
}

template <class T>
void Array<T>::Set_Array_Data()
{
    cout << "Input data: " << endl;
    for(int i=0; i<size; i++)
    {
        cout << "[" << i+1 << "]: ";
        cin >> ptr_array[i];
    }
}

template <class T>
void Array<T>::Get_Array_Data()
{
    cout << "Output data: ";
    cout << *this;
    cout << endl;
}

template <class T>
void Array<T>::Insert(int position, T value)
{

    T temp1 = ptr_array[position], temp2;

    for(int i=size-1; i>=position+1;i--)
    {
        temp2 = ptr_array[i];
        ptr_array[i] = ptr_array[i-1];
        ptr_array[i-1] = temp2;
    }

    ptr_array[position] = value;
    ptr_array[position+1] = temp1;
}

template <class T>
void Array<T>::Erase(int delete_position)
{
    T *buffer = new T[size-1];

    for(int i=0; i<delete_position; i++)
    {
        buffer[i] = ptr_array[i];
    }

    for(int i=delete_position+1; i<size; i++)
    {
        buffer[i-1] = ptr_array[i];
    }

    delete [] ptr_array;
    size--;
    ptr_array = new T[size];

    for(int i=0; i<size; i++)
    {
        ptr_array[i] = buffer[i];
    }

    delete [] buffer;

}

int Compare(const void *a, const void *b)
{
    return *(int*)a - *(int*)b; // Change a and b for Hight-Low
}

template <class T>
void Array<T>::Sort() const
{
    qsort(ptr_array, size, sizeof(T), Compare);
}

template <class T>
void Array<T>::Reverse()
{
    T *buffer = new T[size];

    for(int i=0; i<size; i++)
    {
        buffer[i] = ptr_array[(size-1)-i];
    }

    for(int i=0; i<size; i++)
    {
        ptr_array[i] = buffer[i];
    }

    delete [] buffer;
}

template <typename F>
ostream &operator << (ostream &stream, Array<F> &object)
{
    for(int i=0; i<object.size; i++)
    {
        stream << object.ptr_array[i] << " ";
    }
    return stream;
}

template <typename F>
istream &operator >> (istream &stream, Array<F> &object)
{
    for(int i=0; i<object.size; i++)
    {
        stream >> object.ptr_array[i];
    }
    return stream;
}

template <class T>
bool Array<T>::operator <(Array<T> &object)
{
    return true ? (this->size < object.size) : false;
}

template <class T>
bool Array<T>::operator > (Array<T> &object)
{
    return true ? (this->size > object.size) : false;
}

template <class T>
bool Array<T>::operator == (Array<T> &object)
{
    return true ? (this->size == object.size) : false;
}

template <class T>
bool Array<T>::operator != (Array<T> &object)
{
    return true ? (this->size != object.size) : false;
}

template <class T>
Array<T> &Array<T>::operator +(Array<T> &object)
{
    T *temp_array = new T[size];
    int temp_size = size;

    for(int i=0; i<size; i++)
    {
        temp_array[i] = ptr_array[i];
    }

    size += object.size;
    delete [] ptr_array;
    ptr_array = new T[size];

    int i;
    for(i=0; i<temp_size; i++)
    {
        ptr_array[i] = temp_array[i];
    }

    for(int j=i; j<size; j++)
    {
        ptr_array[j] = object.ptr_array[j-i];
    }

    delete [] temp_array;
    return *this;
}

template <class T>
Array<T> &Array<T>::operator =(Array<T> &object)
{
    if (size != object.size)
    {
        delete [] ptr_array;
        ptr_array = new T[object.size];
        size = object.size;
    }

    for(int i=0; i<size; i++)
    {
        ptr_array[i] = object.ptr_array[i];
    }

    return *this;

}

int main()
{
    Array<int> ob1(5), ob2(ob1);
    ob1.Set_Array_Data();
    ob1.Get_Array_Data();
    ob2.Get_Array_Data();
    return 0;
}
