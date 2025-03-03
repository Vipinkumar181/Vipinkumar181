import time
import numpy as np
import matplotlib.pyplot as plt
import random
# import sys
# sys.setrecursionlimit(15000)

def counting_sort(arr, dig):
    n = len(arr)
    output = [0] * (n)
    count = [0] * (10)
    for i in range(0, n):
        index = arr[i] // dig
        count[index % 10] += 1

    for i in range(1, 10):
        count[i] += count[i - 1]

    i = n - 1
    while i >= 0:
        index = arr[i] // dig
        output[count[index % 10] - 1] = arr[i]
        count[index % 10] -= 1
        i -= 1

    i = 0
    for i in range(0, len(arr)):
        arr[i] = output[i]


def radix_sort(arr):
    max1 = max(arr)
    dig = 1
    while max1 / dig >= 1:
        counting_sort(arr, dig)
        dig *= 10


def measure_time(arr):
    start_time = time.time()
    radix_sort(arr)
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
    
    plt.title('Execution Time of Radix Sort on Different Data Types')
    plt.xlabel('Array Size')
    plt.ylabel('Time (seconds)')
    plt.legend()
    plt.grid(True)
    plt.show()
    

if __name__ == "__main__":
    test_sorting_and_plot()
   
