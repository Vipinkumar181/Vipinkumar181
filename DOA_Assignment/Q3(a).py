import time
import numpy as np
import matplotlib.pyplot as plt
import random
import sys
sys.setrecursionlimit(15000)

def partition(arr, low, high):
    pivot = arr[high]
    i = low - 1
    for j in range(low, high):
        if arr[j] < pivot:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]
    
    arr[i + 1], arr[high] = arr[high], arr[i + 1]
    return i + 1

def quick_sort(arr, low, high):
    if low < high:
        pi = partition(arr, low, high)
        quick_sort(arr, low, pi - 1)  
        quick_sort(arr, pi + 1, high)  

def measure_time(arr):
    start_time = time.time()
    quick_sort(arr, 0, len(arr) - 1)
    end_time = time.time()
    return end_time - start_time

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
    
    plt.title('Execution Time of Quick Sort (Without Randomization) on Different Data Types')
    plt.xlabel('Array Size')
    plt.ylabel('Time (seconds)')
    plt.legend()
    plt.grid(True)
    plt.show()

if __name__ == "__main__":
    test_sorting_and_plot()
