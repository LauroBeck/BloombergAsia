import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# 1. Load Data
try:
    df = pd.read_csv('stargate_audit.csv')
    
    # Get the latest snapshot per ticker
    latest = df.sort_values('Timestamp').groupby('Ticker').tail(1)
    
    # 2. Pivot for Heatmap (RSI vs ATR)
    # We use Price/ATR ratio to normalize the risk
    latest['Risk_Intensity'] = (latest['ATR'] / latest['Price']) * 100
    plot_data = latest.set_index('Ticker')[['RSI', 'Risk_Intensity']]

    # 3. Setup Dark Theme
    plt.style.use('dark_background')
    plt.figure(figsize=(10, 6))
    
    # 4. Create Heatmap
    ax = sns.heatmap(plot_data, annot=True, cmap='magma', cbar_kws={'label': 'Magnitude'})
    
    plt.title("STARGATE CLUSTER | RISK ENTROPY HEATMAP | MAR 23 EOD", color='#00FFCC', pad=15)
    plt.tight_layout()
    
    # 5. Save Asset
    plt.savefig('stargate_heatmap.png')
    print("ARCHITECT LOG: Heatmap 'stargate_heatmap.png' generated.")

except Exception as e:
    print(f"ERROR: {e}")
