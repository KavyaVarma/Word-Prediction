import pandas as pd
from math import ceil

data = pd.read_excel("C:/Users/kavyavarma/Documents/Projects/DS/wordFrequency.xlsx")
file = open("C:/Users/kavyavarma/Documents/Projects/DS/wordFreq.txt", "w")

word = []
freq = []

for a, row in data.iterrows():
    if row["Word"][3:].isalpha()==False:
        continue
    word.append(row["Word"][3:].lower())
    freq.append(row["Frequency"])

for i in range(0,len(word)):
    str1 = word[i]+" "+str(ceil((8-i/(5000/8)))+1)+"\n"
    file.write(str1)

file.close()
