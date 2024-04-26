#This file was written with the help of ChatGPT
import sys
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

df = pd.read_csv(sys.argv[1])
grouped = df.groupby('test_name')

#df['sqrt_n'] = np.sqrt(df['n'])

plt.figure(figsize=(10, 6))
for name, group in grouped:
    plt.plot(group['n'], group['t_avg'], marker='x', label=name)

plt.xscale('log')
plt.ylabel('Average Operation Time (ms)')
plt.xlabel('Number of Operations')
plt.legend(title='test_name', loc='best')
plt.title('Average Operation Time vs N')
plt.savefig("BigO.png")

