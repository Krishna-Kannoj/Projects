app_id = "SZGD59D9UR-100"
app_key = "USXY3C26N3"
redirect_url = "http://www.google.com/"

from fyers_api import fyersModel
from fyers_api import accessToken
import os
import pandas as pd
from token import NEWLINE

def get_access_token(): 
    if not os.path.exists("API\\access_token\\access_token.txt"):
        session=accessToken.SessionModel(client_id=app_id,
        secret_key=app_key,redirect_uri=redirect_url, 
        response_type="code", grant_type="authorization_code") 
        response = session.generate_authcode()
        print("Login URL: ", response) 
        auth_code = input("Enter Auth code: ")
        session.set_token(auth_code)
        access_token = session.generate_token()["access_token"]
        with open("API\\access_token\\access_token.txt","w") as f:
            f.write(access_token) 
    else:
        with open("API\\access_token\\access_token.txt","r") as f:
            access_token = f.read() 
    return access_token

fyers = fyersModel.FyersModel(client_id=app_id, token=get_access_token(), log_path="")

symbol = "NSE:NIFTYBANK-INDEX"
data = {"symbol": symbol, "resolution": "1", "date_format": "1", "range_from": "2022-07-26", "range_to": "2022-07-27", "cont_flag": "1"}

b_n = []
b_n = (fyers.history(data)) 

with open("API\\access_token\\banknifty_1.txt","w") as data: 
    data.write(str(b_n))

    
        
