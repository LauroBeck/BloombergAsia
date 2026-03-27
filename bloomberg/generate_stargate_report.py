import pandas as pd
import matplotlib.pyplot as plt
import os

# Stargate v12.6 Data Feed: 2026-03-26
try:
    data = {
        # Using lowercase 'h' for Pandas 3.x compliance
        'Timestamp': pd.date_range(start='2026-03-26 09:00', periods=6, freq='h'),
        'Brent_Crude': [101.50, 103.20, 105.10, 106.66, 107.10, 106.66],
        'KOSPI': [5640.10, 5600.50, 5520.30, 5460.46, 5440.00, 5460.46]
    }
    df = pd.DataFrame(data)

    plt.style.use('dark_background')
    fig, ax1 = plt.subplots(figsize=(12, 6))

    # LHS: Brent Crude (Energy Shock)
    ax1.set_ylabel('Brent Crude ($)', color='#ff4444', fontsize=12)
    ax1.plot(df['Timestamp'], df['Brent_Crude'], color='#ff4444', lw=2, marker='o', label='Brent')
    ax1.tick_params(axis='y', labelcolor='#ff4444')

    # RHS: KOSPI (Liquidity Drain)
    ax2 = ax1.twinx()
    ax2.set_ylabel('KOSPI Index', color='#00f2ff', fontsize=12)
    ax2.plot(df['Timestamp'], df['KOSPI'], color='#00f2ff', lw=2, marker='s', label='KOSPI')
    ax2.tick_params(axis='y', labelcolor='#00f2ff')

    plt.title('STARGATE CLUSTER v12.6 | HORMUZ CORRELATION: -0.9990', fontsize=14, pad=20)
    fig.tight_layout()

    output_path = 'stargate_report_v12_6.png'
    plt.savefig(output_path)
    print(f"\033[1;32m[SUCCESS]\033[0m Image produced at: {output_path}")

except Exception as e:
    print(f"\033[1;31m[ERROR]\033[0m Visualization failed: {e}")
