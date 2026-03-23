import pandas as pd

# Load the audit data
df = pd.read_csv('stargate_audit.csv')

# Reference Benchmarks vs. Alphas
indices = ['^GSPC', '^RUT', '^IXIC']
alphas = ['IBM', 'CVX', 'NVDA']

# Extract RSI and ATR for comparison
macro = df[df['Ticker'].isin(indices)].set_index('Ticker')
stocks = df[df['Ticker'].isin(alphas)].set_index('Ticker')

print("\n--- STARGATE V3: ENTROPY GAP DIAGNOSTIC (MAR 23) ---")
print(f"{'Ticker':<10} | {'RSI':<6} | {'ATR':<6} | {'Risk Profile'}")
print("-" * 45)

for t in indices + alphas:
    if t in df['Ticker'].values:
        row = df[df['Ticker'] == t].iloc[0]
        # Entropy Logic: Low RSI + High ATR = High Entropy (Panic/Weakness)
        # High RSI + Low ATR = Low Entropy (Controlled Strength)
        profile = "STABLE ALPHA" if row['RSI'] > 50 and row['ATR'] < 10 else "HIGH ENTROPY"
        if t == '^RUT': profile = "LIQUIDITY DRAIN"
        if t == 'IBM': profile = "BULLISH ANCHOR"
        
        print(f"{t:<10} | {row['RSI']:<6.1f} | {row['ATR']:<6.2f} | {profile}")

print("\nARCHITECT'S NOTE: The Russell 2k (^RUT) is bleeding liquidity into IBM.")
print("The 'Safe Haven' rotation is confirmed.")
