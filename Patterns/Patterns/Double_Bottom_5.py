import pandas as pd
import plotly.graph_objects as go
import numpy as np


file = "data\\banknifty_aug_03.csv"
df = pd.read_csv(file)
# df.columns=['Date','Open','High','Low','Close','Volume']
df.columns=['Date','Open','High','Low','Close','Adj Close','Volume']

# input_set = open("ML_data\\D_B\\input\\input_1.txt", 'w')
# output_set = open("output_1.txt", 'w')

def isLow(df,i):
  m = i
  for j in range(1,6):
    if(df['Low'][m] >= df['Low'][m-j]):
        return 0
  for k in range(1,6):
    if(df['Low'][m] >= df['Low'][m+k]):
        return 0
  return 1

def isHigh(df,i):
  for j in range(1,6):
    if(df['High'][i] < df['High'][i-j]):# or ):
        return 0
  return 1

def temp_high(df,i,y1,y2):
  if( (df['High'][i] - y1 < 30) or (df['High'][i] - y2 < 30) ):
    return 0
  return 1


is_l = []
for i in range(32,df.shape[0]-32):
  if isLow(df,i):
    l = df['Low'][i]
    is_l.append((i,l))

fig = go.Figure(data=go.Candlestick(x=df.index,
    open = df['Open'],
    high = df['High'],
    low = df['Low'],
    close = df['Close']
))

x_axis=[]
y_axis=[]
file_count = 1
flag = False
for i in range(len(is_l)-2):
  x1 = is_l[i][0]
  y1 = is_l[i][1]
  x2 = is_l[i+1][0]
  y2 = is_l[i+1][1]
  flag = False
  if(abs(y2 - y1) < 15 and (x2 - x1 > 7) and (x2 - x1 < 40) ):
    for j in range(x1,x2):
        if((temp_high(df,j,y1,y2))):
          for k in range(x1,x1-30,-1):
            if isHigh(df,k):
              l = df['High'][k]
              if( ((( l - y1 ) / (k - x1)) < -7) and (l - y1 > 50 )):
                x_axis.append(k)
                y_axis.append(l)
                x_axis.append(x1)
                y_axis.append(y1)
                x_axis.append(x2)
                y_axis.append(y2)
                x_axis.append(None)
                y_axis.append(None)
                input_set = open("ML_data\\D_B\\input\\input_" + str(file_count) + ".txt", 'w')
                
                input_set.write(str(df[k:x2]))
                file_count+=1
                input_set.close()
                flag = True
                break
          if(flag):
            break


fig.add_trace(go.Scatter(x=x_axis, y=y_axis, name="linear",
                    line_shape='linear'))

fig.show()




