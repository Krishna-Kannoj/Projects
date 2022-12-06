import pandas as pd
import plotly.graph_objects as go

# file = "ML\\ORB\\data\\bn_2021_to_2022_sep.csv"
file = "data\\banknifty_1m\\banknifty_aug_03.csv"
df = pd.read_csv(file)
df.columns=['Date','Open','High','Low','Close','Adj Close','Volume']
# Datetime,Open,High,Low,Close,Adj Close,Volume

def isLow(df,i):
  for j in range(1,10):
    if(df['Low'][i] > df['Low'][i-j]):
        return 0
  for k in range(1,10):
    if(df['Low'][i] > df['Low'][i+k]):
        return 0
  return 1

def isHigh(df,i):
  for j in range(1,10):
    if(df['High'][i] < df['High'][i-j]):# or ):
        return 0
  for k in range(1,10):
    if(df['High'][i] < df['High'][i+k]):
        return 0
  return 1

is_l = []
is_h = []
start = 130+ 10
end = 280  #df.shape[0]-1

# past data
for i in range(20,len(df)-30):
  if isLow(df,i):
    l = df['Low'][i]
    is_l.append((i,l-10))
  elif isHigh(df,i):
    l = df['High'][i]
    is_h.append((i,l+10))


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

for i in range(len(is_h)-1):
    x_axis.append(is_h[i][0])
    y_axis.append(is_h[i][1])

fig.add_scatter(x=x_axis, y=y_axis, mode='markers',
        marker=dict(size=5, color='MediumPurple'), name='pivot')

fig.show()





