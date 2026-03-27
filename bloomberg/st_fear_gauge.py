import pandas as pd
import matplotlib.pyplot as plt

# Session Data: 2026-03-26 (Closing Snapshot)
# Source: Bloomberg Asia / KOSPI Telemetry
data = {
    'Timestamp': pd.date_range(start='2026-03-26 09:00', periods=6, freq='h'),
    'VIX_Index': [25.33, 26.49, 27.84, 27.10, 26.99, 27.45],  # VIX Surge
    'Samsung_KS': [180100, 178500, 176200, 174100, 173600, 173600] # Tech Sell-off
}
df = pd.DataFrame(data)

plt.style.use('dark_background')
fig, ax1 = plt.subplots(figsize=(12, 7))

# Plot VIX (Fear Gauge)
ax1.set_xlabel('HK/Seoul Session (March 26, 2026)', fontsize=10, color='gray')
ax1.set_ylabel('VIX Volatility Index', color='#ff3333', fontsize=12, fontweight='bold')
ax1.plot(df['Timestamp'], df['VIX_Index'], color='#ff3333', lw=3, marker='o', label='VIX (Global Fear)')
ax1.fill_between(df['Timestamp'], df['VIX_Index'], 20, color='#ff3333', alpha=0.1)
ax1.tick_params(axis='y', labelcolor='#ff3333')

# Plot Samsung (Semiconductor Proxy)
ax2 = ax1.twinx()
ax2.set_ylabel('Samsung Electronics (KRW)', color='#00d4ff', fontsize=12, fontweight='bold')
ax2.plot(df['Timestamp'], df['Samsung_KS'], color='#00d4ff', lw=3, linestyle='--', marker='s', label='Samsung (Tech Liquidity)')
ax2.tick_params(axis='y', labelcolor='#00d4ff')

# Formatting for BloombergAsia Repo
plt.title('STARGATE v12.6 | GLOBAL FEAR GAUGE vs. TECH LIQUIDITY', fontsize=14, pad=25)
ax1.grid(True, which='both', linestyle='--', alpha=0.2)
fig.tight_layout()

output_name = 'stargate_fear_gauge_v12_6.png'
plt.savefig(output_name)
print(f"\033[1;32m[SUCCESS]\033[0m Fear Gauge produced: {output_name}")
