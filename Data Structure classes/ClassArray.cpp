#include <iostream>
#include <initializer_list>

using namespace std;

class Array
{
private:
    int *arr;
    int size;
    int length;

public:
    Array()
    {
        size = 0;
        length = 0;
        arr = nullptr;
    }
    Array(int s)
    {
        size = s;
        length = 0;
        arr = new int[size];
    }



    // The RULE OF 3
        // Copy Constructo
        // COpy assignment operator
        // Destructor



    Array(const Array &other)       //Copy Constructor
    {
        size = other.size;
        length = other.length;
        arr = new int[size];
        for (int i = 0; i < length; i++)
        {
            arr[i] = other.arr[i];
        }
    }

    Array &operator=(const Array &other){       //COpy Assigment operator overloading for 'ASSIGNING EXISTING OBJECT"
        if(this == &other) return *this;

        delete[] arr;

        size = other.size;
        length = other.length;
        arr = new int[size];
        for(int i=0; i<size; i++)
            arr[i] = other.arr[i];
        
        return *this;
    }

    ~Array()                        // Destructor
    {
        delete[] arr;
    }
    void display_info()
    {
        cout << "Size:" << size << " Length: " << length;
    }
    void display_values()
    {

        cout << "Elements are: " << endl;
        for (int i = 0; i < length; i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    void swap(int &a, int &b)
    {
        int temp = a;
        a = b;
        b = temp;
    }

    void initial_values()
    {
        if (size == 0)
        {
            cout << "Enter size of Array: ";
            cin >> size;
        }
        cout << "Enter array elements : ";
        for (int i = 0; i < size; i++)
        {
            cin >> arr[i];
            length++;
        }
    }

    void append(int value)
    {
        arr[length] = value;
        length++;
    }

    void insert(int value, int index)
    {
        for (int i = length - 1; i != index; i++)
            arr[i] = arr[i - 1];
        arr[index] = value;
        length++;
    }

    void delete_value(int idx)
    {
        for (int i = idx; i < length; i++)
        {
            arr[i] = arr[i + 1];
        }
        length--;
    }

    int lin_srch(int key)
    {
        for (int i = 0; i < length; i++)
        {
            if (arr[i] == key)
                return i;
        }
        return -1;
    }

    int bin_srch(int key)
    {
        int l = 0, h = length - 1, mid = (l + h) / 2;
        while (l <= h)
        {
            if (arr[mid] == key)
                return mid;
            else if (arr[mid] < key)
                h = mid - 1;
            else
                l = mid + 1;
        }
        return -1;
    }

    int get(int idx)
    {
        if (idx >= 0 && idx < length)
            return arr[idx];
    }

    void set(int idx, int key)
    {
        if (idx >= 0 && idx < length)
            arr[idx] = key;
    }

    int max()
    {
        int max = INT16_MIN;
        for (int i = 0; i < length; i++)
            if (arr[i] > max)
                max = arr[i];

        return max;
    }

    int min()
    {
        int min = INT16_MAX;
        for (int i = 0; i < length; i++)
            if (arr[i] < min)
                min = arr[i];

        return min;
    }

    int sum()
    {
        int total = 0;
        for (int i = 0; i < length; i++)
        {
            total += arr[i];
        }
        return total;
    }

    int avg()
    {
        int total = 0;
        for (int i = 0; i < length; i++)
        {
            total += arr[i];
        }
        return total / length;
    }

    void reverse_1()
    {
        int *brr = new int[size];
        for (int i = length - 1, j = 0; i >= 0; i--, j++)
        {
            brr[j] = arr[i];
        }

        delete[] arr;
        arr = brr;
    }

    void reverse_2()
    {
        for (int i = 0, j = length - 1; i < j; i++, j--)
        {
            swap(arr[i], arr[j]);
        }
    }

    void left_shift()
    {
        int temp = arr[0];
        for (int i = 0; i < length; i++)
        {
            arr[i] = arr[i + 1];
        }
        arr[length - 1] = temp;
    }

    void right_shift()
    {
        int temp = arr[length - 1];
        for (int i = length - 1; i > 0; i--)
        {
            arr[i] = arr[i - 1];
        }
        arr[0] = temp;
    }

    void insertInSorted(int key)
    {
        int i = length - 1;
        while (arr[i] > key)
        {
            arr[i] = arr[i - 1];
            i--;
        }
        arr[i + 1] = key;
    }

    bool isSorted()
    {
        for (int i = 0; i < length; i++)
        {
            if (arr[i] > arr[i + 1])
                return false;
        }
        return true;
    }

    void shift_negatives()
    {
        int i = 0, j = length - 1;
        while (i < j)
        {
            while (arr[i] < 0)
            {
                i++;
            }
            while (arr[j] >= 0)
            {
                j--;
            }
            swap(arr[i], arr[j]);
        }
    }

    void resize(int newSize)
    {
        int *brr = new int[newSize];
        int elementsToCopy = (newSize < length) ? newSize : length;
        for (int i = 0; i < elementsToCopy; i++)
            brr[i] = arr[i];

        delete[] arr;
        arr = brr;
        size = newSize;
        length = elementsToCopy;
    }

    Array merge(Array &A) // Merging Arrays
    {
        int i = 0, j = 0, k = 0;
        Array C((this->length + A.length));
        while ((i < this->length) && (j < A.length))
        {
            if ((this->arr[i]) < (A.arr[j]))
                C.arr[k++] = this->arr[i++];
            else
                C.arr[k++] = A.arr[j++];
        }
        for (; i < this->length; i++)
            C.arr[k++] = this->arr[i];
        for (; j < A.length; j++)
            C.arr[k++] = A.arr[j];
        C.length = k;
        return C;
    }

    Array &operator=(initializer_list<int> list) // Overloading '=' for original array type intializatin
    {
        delete[] arr;
        size = list.size();
        length = size;
        arr = new int[size];
        int i = 0;
        for (int x : list)
            arr[i++] = x;

        return *this;
    }

    // Overloading cout and cin
};

int main()
{

    Array A, B;
    A = {2, 3, 4, 5};
    B = {1, 7, 8, 9};
    B.display_values();

    A = A.merge(B);
    A.display_values();

    return 0;
}