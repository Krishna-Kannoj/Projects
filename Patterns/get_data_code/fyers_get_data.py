app_id = "SZGD59D9UR-100"
app_key = "USXY3C26N3"
redirect_url = "http://www.google.com/"
from fyers_api import fyersModel
from fyers_api import accessToken
import os
from datetime import date
today = date.today()
token_path = 'API\\access_token\\access_token_' + str(today) + '_.txt'

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

# The range cannot be more than 100 days for 5 min resolution
symbol = "NSE:NIFTYBANK-INDEX"
start_date = "2021-10-31"   # 01-01  04-30  07-31  10-31
end_date =   "2021-12-31"   # 03-31  06-30  09-30  12-31

file_to_store = "data\\banknifty_5m\\bn_2021_oct_dec.txt"
# jan_mar  apr_jun  jul_sep  oct_dec
data = {"symbol": symbol, "resolution": "5", "date_format": "1", "range_from": start_date, "range_to": end_date, "cont_flag": "1"}

b_n = []
b_n = (fyers.history(data)) 

with open(file_to_store,"w") as data: 
    data.write(str(b_n))

print("\n###   OPERATION COMPLETED  ###\n")



    
        
