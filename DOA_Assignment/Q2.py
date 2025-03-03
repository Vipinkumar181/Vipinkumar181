import time
import numpy as np
import matplotlib.pyplot as plt
import random

def merge(arr, left, mid, right):
    n1 = mid - left + 1
    n2 = right - mid

    L = [0] * n1
    R = [0] * n2

    for i in range(n1):
        L[i] = arr[left + i]
    for j in range(n2):
        R[j] = arr[mid + 1 + j]

    i = 0  
    j = 0  
    k = left  


    while i < n1 and j < n2:
        if L[i] <= R[j]:
            arr[k] = L[i]
            i += 1
        else:
            arr[k] = R[j]
            j += 1
        k += 1


    while i < n1:
        arr[k] = L[i]
        i += 1
        k += 1

    while j < n2:
        arr[k] = R[j]
        j += 1
        k += 1

def merge_sort(arr, left, right):
    if left < right:
        mid=left+(right-left)// 2

        merge_sort(arr, left, mid)
        merge_sort(arr, mid + 1, right)
        merge(arr, left, mid, right)

def measure_time(arr):
    start_time=time.time()
    merge_sort(arr,0,len(arr)-1)
    end_time=time.time()
    return end_time-start_time

def test_sorting_and_plot():
    sizes = [100, 1000, 10000]
    data_types = ['Random data', 'Already sorted', 'Reverse-sorted', 'Many duplicates']
    times = {data_type: [] for data_type in data_types}

    for size in sizes:
        arr = np.random.randint(0, 10000, size)
        times['Random data'].append(measure_time(arr.copy()))
        
        arr = np.arange(size)
        times['Already sorted'].append(measure_time(arr.copy()))
        
        arr = np.arange(size, 0, -1)
        times['Reverse-sorted'].append(measure_time(arr.copy()))
        
        arr = np.random.choice([1, 2, 3, 4, 5, 6, 7, 8, 9, 0], size)
        times['Many duplicates'].append(measure_time(arr.copy()))
    
    plt.figure(figsize=(10, 6))
    for data_type in data_types:
        plt.plot(sizes, times[data_type], label=data_type, marker='o')
    
    plt.title('Execution Time of Merge Sort on Different Data Types')
    plt.xlabel('Array Size')
    plt.ylabel('Time (seconds)')
    plt.legend()
    plt.grid(True)
    plt.show()

if __name__ == "__main__":
    test_sorting_and_plot()