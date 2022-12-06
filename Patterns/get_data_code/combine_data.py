import pandas as pd

# 01-01  04-30  07-31  10-31
# 03-31  06-30  09-30  12-31
# jan_mar  apr_jun  jul_sep  oct_dec

small_file = "data\\banknifty_5m\\bn_2022_jul_sep.csv"

big_file = "data\\banknifty_5m\\bn_2021_to_2022_sep.csv"

col = {}
##########  if big_file is empty   ############
# # creating new pandas DataFrame
# df_to_write = pd.DataFrame(list(col))

# # writing empty DataFrame to the new csv file
# df_to_write.to_csv(big_file)

# add column to file manually
# Date,Open,High,Low,Close,Volume

#####################

df_to_read = pd.read_csv(small_file)
df_to_read.columns=['Date','Open','High','Low','Close','Volume']

date = list(df_to_read['Date'])
open = list(df_to_read['Open'])
high = list(df_to_read['High'])
low = list(df_to_read['Low'])
close = list(df_to_read['Close'])
volume = list(df_to_read['Volume'])

data = {
    'Date': date,
    'Open': open,
    'High': high,
    'Low': low,
    'Close': close,
    'Volume': volume
}

# comment if big_file is empty
df_to_write = pd.read_csv(big_file)
df_to_write = pd.DataFrame(data)
df_to_write.to_csv(big_file, mode='a', index=False, header=False)

print("\n   ___OPERATION COMPLETED___   \n")