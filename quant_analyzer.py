import yfinance as yf
import pandas as pd
import pandas_ta as ta
import time
import os
from datetime import datetime

# TIP: On Sundays, standard stocks like NVDA won't move. 
# Use ["NQ=F", "ES=F", "BTC-USD"] for live weekend testing.
TICKERS = ["NVDA", "AAPL", "MSFT", "TSLA", "AMD"]
CSV_FILE = "market_intelligence_log.csv"

def get_signals(df):
    df = df.copy()
    # Ensure we have enough data (BBands needs 20 periods)
    if len(df) < 20:
        return None
        
    df['RSI'] = ta.rsi(df['Close'], length=14)
    bbands = ta.bbands(df['Close'], length=20, std=2)
    df = pd.concat([df, bbands], axis=1)
    return df

def run_analysis():
    os.system('clear')
    print(f"QUANT ANALYZER | {datetime.now().strftime('%H:%M:%S')} | LOGGING: {CSV_FILE}")
    print("=" * 110)
    print(f"{'TICKER':<8} | {'PRICE':>10} | {'CHANGE %':>10} | {'RSI':>6} | {'BB-UPPER':>10} | {'BB-LOWER':>10} | {'SIGNAL'}")
    print("-" * 110)

    # Use 1h interval if 1m is empty (common on weekends/closed markets)
    data = yf.download(TICKERS, period="5d", interval="1m", group_by='ticker', progress=False, prepost=True)

    for ticker in TICKERS:
        try:
            ticker_df = data[ticker].dropna().copy()
            
            # If 1m data is empty (Weekend), try pulling 1h data for testing
            if ticker_df.empty or len(ticker_df) < 20:
                ticker_df = yf.download(ticker, period="5d", interval="60m", progress=False)

            analyzed_df = get_signals(ticker_df)
            if analyzed_df is None:
                print(f"{ticker:<8} | Insufficient Data for Technicals")
                continue

            last = analyzed_df.iloc[-1]
            price = last['Close']
            
            # Dynamic Column Lookup (fixes the 'BBU_20_2.0' vs 'BBU_20' issue)
            upper_col = [c for c in analyzed_df.columns if c.startswith('BBU')][0]
            lower_col = [c for c in analyzed_df.columns if c.startswith('BBL')][0]
            
            upper, lower = last[upper_col], last[lower_col]
            rsi = last['RSI'] if not pd.isna(last['RSI']) else 50.0
            
            pct_change = ((price - ticker_df['Open'].iloc[0]) / ticker_df['Open'].iloc[0]) * 100
            
            signal = "STABLE"
            if rsi > 70 or price > upper: signal = "⚡ OVERBOUGHT"
            elif rsi < 30 or price < lower: signal = "⚠️ OVERSOLD"

            color = "\033[92m" if pct_change >= 0 else "\033[91m"
            print(f"{ticker:<8} | {price:>10.2f} | {color}{pct_change:>9.2f}% \033[0m | {rsi:>6.1f} | {upper:>10.2f} | {lower:>10.2f} | {signal}")

        except Exception as e:
            print(f"{ticker:<8} | System Offline (Market Closed)")

    print("-" * 110)
    print("Re-scanning... (Ctrl+C to quit)")

if __name__ == "__main__":
    while True:
        run_analysis()
        time.sleep(60)
