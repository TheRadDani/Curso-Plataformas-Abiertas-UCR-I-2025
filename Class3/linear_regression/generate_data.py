import numpy as np
import pandas as pd
import os

np.random.seed(69)
X = np.linspace(1, 100, 100)
y = 2.5 * X + np.random.normal(0, 5 ,size=X.shape)

df = pd.DataFrame({"x": X, "y": y})
df.to_csv("data.tsv", sep="\t", index=False)

current_dir = os.getcwd()
files = os.listdir(current_dir)
print("Files in curretn dir: \n")
for file in files:
    print(file)