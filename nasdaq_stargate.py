import yfinance as yf
import pandas as pd
import time
import os
from datetime import datetime

# Configuration - Professional Tech & Index Watchlist
WATCHLIST = {
    "^IXIC": "Nasdaq Composite",
    "^NDX": "Nasdaq 100",
    "NVDA": "NVIDIA Corp",
    "AAPL": "Apple Inc",
    "MSFT": "Microsoft Corp",
    "GOOGL": "Alphabet Cl A",
    "AVGO": "Broadcom Inc"
}

def get_market_status():
    now = datetime.now()
    # Basic check for Market Hours (EST: 9:30 - 16:00)
    # Note: Adjust for your local time as needed
    return "OPEN" if 9 <= now.hour < 17 else "CLOSED/POST"

def render_dashboard():
    tickers = list(WATCHLIST.keys())
    
    # Clear terminal for that "Live Dashboard" feel
    os.system('clear')
    
    print(f"STARGATE CLUSTER | SOVEREIGN INTELLIGENCE STACK | {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    print(f"MARKET STATUS: {get_market_status()} | FEED: YAHOO FINANCE (1m)")
    print("=" * 85)
    print(f"{'SYMBOL':<10} | {'NAME':<18} | {'PRICE':>10} | {'CHANGE %':>10} | {'5m SMA':>10} | {'VOL'}")
    print("-" * 85)

    try:
        # Bulk download for efficiency
        data = yf.download(tickers, period="1d", interval="1m", group_by='ticker', progress=False)
        
        for symbol, name in WATCHLIST.items():
            df = data[symbol].dropna()
            if df.empty: continue
            
            last_row = df.iloc[-1]
            open_price = df['Open'].iloc[0]
            current_price = last_row['Close']
            
            # Analytics
            pct_change = ((current_price - open_price) / open_price) * 100
            sma_5 = df['Close'].rolling(window=5).mean().iloc[-1]
            volume = int(last_row['Volume'])
            
            # Color logic (ANSI Escape Codes)
            color = "\033[92m" if pct_change >= 0 else "\033[91m"
            reset = "\033[0m"
            trend = "▲" if current_price >= sma_5 else "▼"

            print(f"{symbol:<10} | {name[:18]:<18} | {current_price:>10.2f} | {color}{pct_change:>9.2f}%{reset} | {sma_5:>9.2f} {trend} | {volume:,}")
            
    except Exception as e:
        print(f"\n[!] DATA ERROR: {e}")
    
    print("-" * 85)
    print("Press Ctrl+C to exit and return to bash.")

if __name__ == "__main__":
    try:
        while True:
            render_dashboard()
            time.sleep(30) # 30s update cycle for balanced precision/rate-limit
    except KeyboardInterrupt:
        print("\n[STARGATE] Shutdown complete.")
