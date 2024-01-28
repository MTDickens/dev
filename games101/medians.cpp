#include <iostream>

using namespace std;

// for array containing multiplications, 
// we should use three-way-quick-sort-like method
int find_medium(int *arr, int length)
{
    int pivot;
    int final_index;
    int left = 0, right = length - 1;
    do
    {
        int pivot_index = left + rand() % (right - left + 1);
        pivot = arr[pivot_index];
        cout << "Pivot is: " << pivot;
        
        swap(arr[left], arr[pivot_index]); // make pivot the first
        // always (i.e. in any time) guarantee that
        // [left-i] <= pivot
        // [j-right] > pivot
        int i = left; // since arr[left] is pivot, it's bound to satisfy arr[left] <= pivot
        int j = right + 1;

        while (i+1 != j) {
            while (j >= 1 && arr[j-1] > pivot) {
                --j;
            }
            while (i <= length - 2 && arr[i+1] <= pivot) {
                ++i;
            }
            if (i+1 != j) {
                swap(arr[j-1], arr[i+1]);
                --j, ++i;
            }
        }
        
        swap(arr[left], arr[i]); // make the pivot stay at where it ought to be

        final_index = i;
        cout << "  Index is: " << final_index;
        if (final_index < length / 2) {
            left = final_index;
        }
        else if (final_index > length / 2) {
            right = final_index;
        }
        cout << "  Array is: ";
        for (int k = 0; k != length; ++k)
            cout << arr[k] << ' ';
        cout << '\n';
    } while (final_index != length / 2);

    return arr[final_index];
}

int main() {
    int test[10]{5, 6, 8, 1, 2, 3, 9, 4, 7, 0};
    cout << find_medium(test, 10) << '\n';
    return 0;
}