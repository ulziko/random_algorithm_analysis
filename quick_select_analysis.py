import time
import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd

# Input sizes
input_sizes = ["10M", "20M", "40M", "80M", "160M"]
times = [ 0.193181 , 0.429518,0.878970, 1.456931 , 3.524980 ]
times2=[2.031544 , 4.399049, 10.588542 , 24.830965, 42.582846 ]

df = pd.DataFrame({
    'n': input_sizes,
    's': times
})
df2 = pd.DataFrame({
    'n': input_sizes,
    's': times2
})

# Plot using Seaborn
sns.set(style="whitegrid")
plt.figure(figsize=(10, 6))
sns.lineplot(data=df, x='n', y='s', label="Quickselect",marker='o')
sns.lineplot(data=df2, x='n', y='s',  label="Quicksort",marker='o')
plt.title('EQuickselect running time analysis', fontsize=16)
plt.xlabel('Input Size (n)', fontsize=12)
plt.ylabel('Time (seconds)', fontsize=12)
plt.tight_layout()
plt.show()
