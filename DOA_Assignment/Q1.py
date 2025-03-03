import time
import numpy as np
import matplotlib.pyplot as plt
import random


def insertion_sort(arr):
    for i in range(1,len(arr)):
        key=arr[i]
        j=i-1
        while j>=0 and arr[j]>key:
            arr[j+1]=arr[j]
            j-=1
            arr[j+1]=key
    
def printArr(arr):
    for i in range(len(arr)):
      print(arr[i],end=" ")
    print()

def measure_time(arr):
    start_time=time.time()
    insertion_sort(arr)
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
    
    plt.title('Execution Time of Insertion Sort on Different Data Types')
    plt.xlabel('Array Size')
    plt.ylabel('Time (seconds)')
    plt.legend()
    plt.grid(True)
    plt.show()

if __name__ == "__main__":
    test_sorting_and_plot()

  
