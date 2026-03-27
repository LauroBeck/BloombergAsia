import pandas as pd
import matplotlib.pyplot as plt

# Data Source: Screenshot 2026-03-26 20:13:35
data = {
    'Timestamp': pd.date_range(start='2026-03-26 09:00', periods=6, freq='h'),
    'VIX_Index': [25.1, 25.8, 26.5, 27.2, 27.44, 27.44],
    'HSI_Index': [25200, 25100, 24950, 24856, 24856, 24856]
}
df = pd.DataFrame(data)

plt.style.use('dark_background')
fig, ax1 = plt.subplots(figsize=(12, 6))

ax1.set_ylabel('VIX (Fear Gauge)', color='#ff4444', fontweight='bold')
ax1.plot(df['Timestamp'], df['VIX_Index'], color='#ff4444', lw=2, marker='o')
ax1.tick_params(axis='y', labelcolor='#ff4444')

ax2 = ax1.twinx()
ax2.set_ylabel('Hang Seng Index', color='#00f2ff', fontweight='bold')
ax2.plot(df['Timestamp'], df['HSI_Index'], color='#00f2ff', lw=2, marker='s')
ax2.tick_params(axis='y', labelcolor='#00f2ff')

plt.title('STARGATE v12.6: HSI CAPITULATION vs. GLOBAL VOLATILITY')
plt.savefig('stargate_hsi_vix_report.png')
print("Mission Report Generated: stargate_hsi_vix_report.png")
