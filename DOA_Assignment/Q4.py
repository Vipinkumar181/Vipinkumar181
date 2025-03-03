import time
import numpy as np
import matplotlib.pyplot as plt
import random
# import sys
# sys.setrecursionlimit(15000)

def insertion_sort(bucket):
    for i in range(1, len(bucket)):
        key = bucket[i]
        j = i - 1
        while j >= 0 and bucket[j] > key:
            bucket[j + 1] = bucket[j]
            j -= 1
        bucket[j + 1] = key


def bucket_sort(arr):
    n = len(arr)
    buckets = [[] for _ in range(n)]
    if n == 0:
        return
    
    min_val = min(arr)
    max_val = max(arr)
        
    for num in arr:
        bi = int((num - min_val) / (max_val - min_val) * (n - 1))
        buckets[bi].append(num)
    print(buckets)

    for bucket in buckets:
        insertion_sort(bucket)



    index = 0
    for bucket in buckets:
        for num in bucket:
            arr[index] = num
            index += 1


def measure_time(arr):
    start_time = time.time()
    bucket_sort(arr)
    end_time = time.time()
    return end_time - start_time

def test_sorting_and_plot():
    sizes = [100, 1000, 10000]
    data_types = ['Random data', 'Already sorted', 'Reverse-sorted', 'Many duplicates']
    times = {data_type: [] for data_type in data_types}

    for size in sizes:
        arr = np.random.rand(size)  
        times['Random data'].append(measure_time(arr.copy()))
        
        arr = np.linspace(0, 1, size)  
        times['Already sorted'].append(measure_time(arr.copy()))
        
        arr = np.linspace(1, 0, size)  
        times['Reverse-sorted'].append(measure_time(arr.copy()))
        
        arr = np.random.choice([0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9], size)  
        times['Many duplicates'].append(measure_time(arr.copy()))
    
    plt.figure(figsize=(10, 6))
    for data_type in data_types:
        plt.plot(sizes, times[data_type], label=data_type, marker='o')
    
    plt.title('Execution Time of Bucket Sort on Different Data Types')
    plt.xlabel('Array Size')
    plt.ylabel('Time (seconds)')
    plt.legend()
    plt.grid(True)
    plt.show()

if __name__ == "__main__":
    test_sorting_and_plot()
