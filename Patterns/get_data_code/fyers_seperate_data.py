import pandas as pd

file_path = "data\\banknifty_5m\\bn_2021_oct_dec.txt"
file_path_csv = "data\\banknifty_5m\\bn_2021_oct_dec.csv"

my_file = open(file_path, "r")
data = my_file.read()
data_into_list = data.replace("{'s': 'ok', 'candles': [", "Date,Open,High,Low,Close,Volume")
my_file.close()
with open(file_path,'w') as f: 
    f.write(str(data_into_list))
my_file.close()


my_file = open(file_path, "r")
data = my_file.read()
data_into_list = data.replace("[", "\n")
my_file.close()
with open(file_path,'w') as f: 
    f.write(str(data_into_list))
my_file.close()


my_file = open(file_path, "r")
data = my_file.read()
data_into_list = data.replace("],", "")
my_file.close()
with open(file_path,'w') as f: 
    f.write(str(data_into_list))
my_file.close()


my_file = open(file_path, "r")
data = my_file.read()
data_into_list = data.replace("]]}", "")
my_file.close()
with open(file_path,'w') as f: 
    f.write(str(data_into_list))
my_file.close()

dataframe1 = pd.read_csv(file_path)
dataframe1.to_csv(file_path_csv, index = None)


print("\n###   OPERATION COMPLETED  ###\n")

