import pandas as pd
import datetime

file = "data\\banknifty_5m\\bn_2021_oct_dec.csv"
df = pd.read_csv(file)
df.columns=['Date','Open','High','Low','Close','Volume']

def epoch_to_date_time(df1):
    length = len(df1)
    date = list(df1['Date'])
    date_time = [None] * length
    for line in range (0,length):
        date_time=datetime.datetime.fromtimestamp(date[line])
    return date_time

df['Date'] = epoch_to_date_time(df)
df.to_csv(file, index=False)


print("\n###   OPERATION COMPLETED  ###\n")

#####################  END  #################