import pandas as pd
import matplotlib.pyplot as plt
import plotly.graph_objects as go

file = "data\\banknifty_1m\\banknifty_2.csv"
df = pd.read_csv(file)
df.columns=['Date','Open','High','Low','Close','Volume']


def isLow(df,i):
  m = i
  for j in range(1,15):
    if(df['Low'][m] > df['Low'][m-j]):
        return 0
  for k in range(1,6):
    if(df['Low'][m] > df['Low'][m+k]):
        return 0
  return 1

def isHigh(df,i):
  m = i
  for j in range(1,15):
    if(df['High'][m] < df['High'][m-j]):# or ):
        return 0
  for k in range(1,6):
    if(df['High'][m] < df['High'][m+k]):
        return 0
  return 1

def slope(x1,x2,y1,y2):
    m = (y2-y1)/(x2-x1)
    c = y1 - m*x1
    return(m,c)

def distance(m, c, x, y):
    ch = y - m*x - c
    d = pow(1+m*m, 0.5)
    if( (abs(ch/d)) < 25 ):
        return True
    return False

is_l = []
is_h = []
start = 250+ 10
end = 350 #df.shape[0]-1

# past data
for i in range(20,start):
  if isLow(df,i-5):
    l = df['Low'][i-5]
    is_l.append((i-5,l-10))
  elif isHigh(df,i-5):
    l = df['High'][i-5]
    is_h.append((i-5,l+10))

# new data
for i in range(start,end):
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

#################### is_low  ########################

x1=is_l[len(is_l)-1][0]
x2=is_l[len(is_l)-2][0]
x3=is_l[len(is_l)-3][0]
y1=is_l[len(is_l)-1][1]
y2=is_l[len(is_l)-2][1]
y3=is_l[len(is_l)-3][1]

m1, c1 = slope(x3,x1,y3,y1)
m2, c2 = slope(x2,x1,y2,y1)
x_axis=[]
y_axis=[]

x_temp = 0
y_temp = 0

if(m1 > m2 ):
    x_axis.append(x3)
    y_axis.append(y3)
    for i in range(len(is_l)-4,0,-1):
        x_temp = is_l[i][0]
        y_temp = is_l[i][1]
        if(distance(m1,c1,x_temp,y_temp)):
            x_axis.pop()
            y_axis.pop()
            x_axis.append(x_temp)
            y_axis.append(y_temp)
        else:
            break

else:
    x_axis.append(x2)
    y_axis.append(y2)
    for i in range(len(is_l)-4,0,-1):
        x_temp = is_l[i][0]
        y_temp = is_l[i][1]
        if(distance(m2,c2,x_temp,y_temp)):
            x_axis.pop()
            y_axis.pop()
            x_axis.append(x_temp)
            y_axis.append(y_temp)
        else:
            break

x_axis.append(x1)
y_axis.append(y1)
x_axis.append(None)
y_axis.append(None)

################  is_low #################

x1=is_h[len(is_h)-1][0]
x2=is_h[len(is_h)-2][0]
x3=is_h[len(is_h)-3][0]
y1=is_h[len(is_h)-1][1]
y2=is_h[len(is_h)-2][1]
y3=is_h[len(is_h)-3][1]

m1, c1 = slope(x3,x1,y3,y1)
m2, c2 = slope(x2,x1,y2,y1)

if(m1 < m2):
    x_axis.append(x3)
    y_axis.append(y3)
    for i in range(len(is_h)-4,0,-1):
        x_temp = is_h[i][0]
        y_temp = is_h[i][1]
        if(distance(m1,c1,x_temp,y_temp)):
            x_axis.pop()
            y_axis.pop()
            x_axis.append(x_temp)
            y_axis.append(y_temp)
        else:
            break

else:
    x_axis.append(x2)
    y_axis.append(y2)
    for i in range(len(is_h)-4,0,-1):
        x_temp = is_h[i][0]
        y_temp = is_h[i][1]
        if(distance(m2,c2,x_temp,y_temp)):
            x_axis.pop()
            y_axis.pop()
            x_axis.append(x_temp)
            y_axis.append(y_temp)
        else:
            break

x_axis.append(x1)
y_axis.append(y1)

# for i in range(len(is_l)-1,len(is_l)-2,-1):
#     x_axis.append(is_l[i][0])
#     y_axis.append(is_l[i][1])

# for i in range(len(is_h)-1,len(is_h)-2,-1):
#     x_axis.append(is_h[i][0])
#     y_axis.append(is_h[i][1])

# fig.add_scatter(x=x_axis, y=y_axis, mode='markers',
#         marker=dict(size=5, color='MediumPurple'), name='pivot')
fig.add_trace(go.Scatter(x=x_axis, y=y_axis, name="linear",
                    line_shape='linear'))

fig.show()





