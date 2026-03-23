import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from datetime import datetime

# 1. Load the Sovereign Audit Data
try:
    df = pd.read_csv('stargate_audit.csv')
    df['Timestamp'] = pd.to_datetime(df['Timestamp'])
    
    # 2. Setup Plot Aesthetics (Dark Mode for the Cluster)
    plt.style.use('dark_background')
    fig, ax1 = plt.subplots(figsize=(14, 8))
    ax2 = ax1.twinx()

    # 3. Plot Price Trends (Primary Axis)
    # We normalize to % change to compare IBM ($248) vs Nasdaq ($21k)
    for ticker in df['Ticker'].unique():
        data = df[df['Ticker'] == ticker].sort_values('Timestamp')
        initial_price = data['Price'].iloc[0]
        data['Price_Pct'] = (data['Price'] / initial_price - 1) * 100
        
        line, = ax1.plot(data['Timestamp'], data['Price_Pct'], label=f"{ticker} Price %", linewidth=2)
        
        # 4. Plot ATR/Volatility (Secondary Axis - Dotted Lines)
        ax2.plot(data['Timestamp'], data['RSI'], linestyle='--', alpha=0.4, color=line.get_color())

    # 5. Annotations & Branding
    ax1.set_title(f"STARGATE CLUSTER | MAR 23, 2026 | PERFORMANCE & MOMENTUM", fontsize=16, pad=20, color='#00FFCC')
    ax1.set_ylabel("Price Performance (%)", fontsize=12, color='white')
    ax2.set_ylabel("RSI (Momentum)", fontsize=12, color='gray')
    
    # Add the RSI "Danger Zones"
    ax2.axhline(70, color='red', linestyle=':', alpha=0.3)
    ax2.axhline(30, color='green', linestyle=':', alpha=0.3)

    ax1.legend(loc='upper left', frameon=False)
    plt.tight_layout()
    
    # 6. Save for the 2026 Portfolio
    output_name = f"stargate_analysis_{datetime.now().strftime('%H%M')}.png"
    plt.savefig(output_name)
    print(f"ARCHITECT LOG: Graphic generated as {output_name}")

except Exception as e:
    print(f"ERROR: Could not generate graphics. {e}")
