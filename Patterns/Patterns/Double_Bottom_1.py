import pandas as pd
import plotly.graph_objects as go


file = "data\\banknifty_aug_22.csv"
df = pd.read_csv(file)
# df.columns=['Date','Open','High','Low','Close','Volume']
df.columns=['Date','Open','High','Low','Close','Adj Close','Volume']

def isLow(df,i):
  m = i
  for j in range(1,7):
    if(df['Low'][m] >= df['Low'][m-j]):
        return 0
  for k in range(1,7):
    if(df['Low'][m] >= df['Low'][m+k]):
        return 0
  return 1

is_l = []
for i in range(25,df.shape[0]-25):
# for i in range(250,300):
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
i = len(is_l)-2
for i in range(len(is_l)-2):
  t = i
  x1 = is_l[i][0]
  y1 = is_l[i][1]
  x2 = is_l[i+1][0]
  y2 = is_l[i+1][1]
  if(abs(y2 - y1) < 15 and (x2 - x1 > 7) and (x2 - x1 < 40) ):
    x_axis.append(is_l[i][0])
    y_axis.append(is_l[i][1])
    x_axis.append(is_l[i+1][0])
    y_axis.append(is_l[i+1][1])
    x_axis.append(None)
    y_axis.append(None)

fig.add_trace(go.Scatter(x=x_axis, y=y_axis, name="linear",
                    line_shape='linear'))

fig.show()




