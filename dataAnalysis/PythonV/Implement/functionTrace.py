from pandas_cub_final import DataFrame
import numpy as np

a8 = np.array(['b', 'a', 'a', 'a', 'b', 'a', 'a', 'b'])
b8 = np.array(['B', 'A', 'A', 'A', 'B', 'B', 'B', 'A'])
c8 = np.array([1, 2, 3, 4, 5, 6, 7, 8])
df8 = DataFrame({'a': a8, 'b': b8, 'c': c8})

def process():
    result = df8.pivot_table(rows = 'a', columns='b', values='c', aggfunc='sum')
    return result

if __name__ == "__main__":
    process()