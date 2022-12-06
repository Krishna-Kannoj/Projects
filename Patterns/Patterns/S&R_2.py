import pandas as pd
import plotly.graph_objects as go
import numpy as np


file = "data\\banknifty_1m\\banknifty_2.csv"
df = pd.read_csv(file)
df.columns=['Date','Open','High','Low','Close','Volume']

def isLow(df,i):
  m = i
  for j in range(1,20):
    if(df['Low'][m] >= df['Low'][m-j]):
        return 0
  for k in range(1,20):
    if(df['Low'][m] >= df['Low'][m+k]):
        return 0
  return 1

def isHigh(df,i):
  m = i
  for j in range(1,15):
    if(df['High'][m] < df['High'][m-j]):# or ):
        return 0
  for k in range(1,15):
    if(df['High'][m] < df['High'][m+k]):
        return 0
  return 1

s =  np.mean(df['High'] - df['Low'])

def isFarFromLevel(l):
   return np.sum([abs(l-x) < s  for x in is_l]) == 0

is_l = []
is_h = []
for i in range(100,df.shape[0]-100):
# for i in range(250,300):
  if isLow(df,i):
    l = df['Low'][i]
    # if isFarFromLevel(l):
    is_l.append((i,l))
  elif isHigh(df,i):
    l = df['High'][i]
    # if isFarFromLevel(l):
    is_h.append((i,l))

fig = go.Figure(data=go.Candlestick(x=df.index,
    open = df['Open'],
    high = df['High'],
    low = df['Low'],
    close = df['Close']
))

x_axis=[]
y_axis=[]

for i in range(len(is_l)):
      x_axis.append(is_l[i][0])
      y_axis.append(is_l[i][1])
      x_axis.append(df.shape[0]-15)
      y_axis.append(is_l[i][1])
      x_axis.append(None)
      y_axis.append(None)

for i in range(len(is_h)):
      x_axis.append(is_h[i][0])
      y_axis.append(is_h[i][1])
      x_axis.append(df.shape[0]-15)
      y_axis.append(is_h[i][1])
      x_axis.append(None)
      y_axis.append(None)

# for i in range(len(is_h)):
#     fig.add_hline(y=is_h[i][1])

fig.add_trace(go.Scatter(x=x_axis, y=y_axis, name="linear",
                    line_shape='linear'))

fig.show()




