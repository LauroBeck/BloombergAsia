import yfinance as yf
import pandas as pd
import time
import os
from datetime import datetime

# Targeting Sunday night active instruments (Futures & Forex)
WATCHLIST = {
    "NQ=F": "Nasdaq 100 Futures",
    "ES=F": "S&P 500 Futures",
    "YM=F": "Dow Futures",
    "GC=F": "Gold Futures",
    "BTC-USD": "Bitcoin",
    "USDJPY=X": "USD/JPY"
}

def render():
    os.system('clear')
    now = datetime.now().strftime('%H:%M:%S')
    print(f"STARGATE CLUSTER | SUNDAY NIGHT LIVE FEED | {now}")
    print(f"STATUS: FUTURES/GLOBAL MARKET ACTIVE")
    print("=" * 80)
    print(f"{'SYMBOL':<10} | {'NAME':<20} | {'PRICE':>10} | {'CHANGE %':>10} | {'VOL'}")
    print("-" * 80)

    # Note: 'prepost=True' is key for seeing moves outside 9:30-4:00
    data = yf.download(list(WATCHLIST.keys()), period="1d", interval="1m", group_by='ticker', progress=False, prepost=True)

    for symbol, name in WATCHLIST.items():
        try:
            df = data[symbol].dropna()
            if df.empty: continue
            
            last = df.iloc[-1]
            prev_close = df['Close'].iloc[0]
            price = last['Close']
            pct = ((price - prev_close) / prev_close) * 100
            
            color = "\033[92m" if pct >= 0 else "\033[91m"
            reset = "\033[0m"
            
            print(f"{symbol:<10} | {name:<20} | {price:>10.2f} | {color}{pct:>9.2f}%{reset} | {int(last['Volume']):,}")
        except:
            continue
    print("-" * 80)
    print("Watching for Sunday night gaps. Ctrl+C to stop.")

if __name__ == "__main__":
    while True:
        render()
        time.sleep(20)
