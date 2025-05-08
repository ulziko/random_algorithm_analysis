import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd

# Input sizes
input_sizes = ["5M", "10M", "20M", "50M"]
steps = [ 30.56 ,31.69, 32.28, 33.84  ]
steps2=[22.27 , 23.46, 23.86, 24.61 ]

df = pd.DataFrame({
    'n': input_sizes,
    's': steps
})
df2 = pd.DataFrame({
    'n': input_sizes,
    's': steps2
})

# Plot using Seaborn
sns.set(style="whitegrid")
plt.figure(figsize=(10, 6))
sns.lineplot(data=df, x='n', y='s', label="treap",marker='o')
sns.lineplot(data=df2, x='n', y='s',  label="skiplist",marker='o')
plt.title('Treap & skiplist average steps analysis', fontsize=16)
plt.xlabel('Input Size (n)', fontsize=12)
plt.ylabel('Steps (average)', fontsize=12)
plt.tight_layout()
plt.show()
