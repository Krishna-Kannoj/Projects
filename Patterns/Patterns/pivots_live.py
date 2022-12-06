import pandas as pd
import matplotlib.pyplot as plt
import plotly.graph_objects as go

file = "data\\banknifty_2.csv"
df = pd.read_csv(file)
df.columns=['Date','Open','High','Low','Close','Volume']


def isLow(df,i):
  m = i
  for j in range(1,10):
    if(df['Low'][m] > df['Low'][m-j]):
        return 0
  for k in range(1,6):
    if(df['Low'][m] > df['Low'][m+k]):
        return 0
  return 1

def isHigh(df,i):
  m = i
  for j in range(1,10):
    if(df['High'][m] < df['High'][m-j]):# or ):
        return 0
  for k in range(1,6):
    if(df['High'][m] < df['High'][m+k]):
        return 0
  return 1

is_l = []
is_h = []
start = 130+ 10
end = 280  #df.shape[0]-1

# past data
for i in range(20,len(df)-30):
  if isLow(df,i-5):
    l = df['Low'][i-5]
    is_l.append((i-5,l-10))
  elif isHigh(df,i-5):
    l = df['High'][i-5]
    is_h.append((i-5,l+10))


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





