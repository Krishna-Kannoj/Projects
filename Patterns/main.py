app_id = "SZGD59D9UR-100"
app_key = "USXY3C26N3"
redirect_url = "http://www.google.com/"

from fyers_api import fyersModel
from fyers_api import accessToken
import os
from datetime import date
import pandas as pd
from token import NEWLINE
today = date.today()
token_path = 'API\\data\\access_token_' + str(today) + '_.txt'


def get_access_token(): 
    if not os.path.exists(token_path):
        session=accessToken.SessionModel(client_id=app_id,
        secret_key=app_key,redirect_uri=redirect_url, 
        response_type="code", grant_type="authorization_code") 
        response = session.generate_authcode()
        print("Login URL: ", response) 
        auth_code = input("Enter Auth code: ")
        session.set_token(auth_code)
        access_token = session.generate_token()["access_token"]
        with open(token_path,"w") as f:
            f.write(access_token) 
    else:
        with open(token_path,"r") as f:
            access_token = f.read() 
    return access_token

fyers = fyersModel.FyersModel(client_id=app_id, token=get_access_token(), log_path="")

# data = {"symbol": "NSE:NIFTYBANK-INDEX", "resolution": "1", "date_format": "1", "range_from": "2022-07-26", "range_to": "2022-07-27", "cont_flag": "1"}

print("############   YES   ##################")
# b_n = []
# b_n = (fyers.history(data)) 

# with open("API\\data\\banknifty_1.txt","w") as data: 
#     data.write(str(b_n))

# eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJpc3MiOiJhcGkubG9naW4uZnllcnMuaW4iLCJpYXQiOjE2NjIzNzA4MTYsImV4cCI6MTY2MjQwMDgxNiwibmJmIjoxNjYyMzcwMjE2LCJhdWQiOiJbXCJ4OjBcIiwgXCJ4OjFcIiwgXCJ4OjJcIiwgXCJkOjFcIiwgXCJkOjJcIiwgXCJ4OjFcIiwgXCJ4OjBcIl0iLCJzdWIiOiJhdXRoX2NvZGUiLCJkaXNwbGF5X25hbWUiOiJYSzE3NzY3Iiwibm9uY2UiOiIiLCJhcHBfaWQiOiJTWkdENTlEOVVSIiwidXVpZCI6IjcwN2YxMGZjZDFiZDQ5N2ViMzAyZmQyNzM3NDYwYjhjIiwiaXBBZGRyIjoiMC4wLjAuMCIsInNjb3BlIjoiIn0.DnwanzGts3U4sT_XDAoDNtKbVeDWfq22DOk4Gg20LT0
    
        
