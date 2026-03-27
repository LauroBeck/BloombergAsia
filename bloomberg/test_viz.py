import pandas as pd
import mplfinance as mpf
import numpy as np
import os

# Create dummy data simulating Brent Crude spikes
dates = pd.date_range('2026-03-20', periods=7)
data = {
    'Open':  [101, 103, 105, 106, 106.66, 107.10, 106.80],
    'High':  [104, 105, 107, 108, 109.00, 108.50, 107.50],
    'Low':   [100, 102, 104, 105, 106.00, 106.50, 106.20],
    'Close': [103, 105, 106, 106.66, 107.10, 106.80, 106.66],
    'Volume': [1000, 1200, 1500, 1800, 2500, 2100, 1900]
}
df = pd.DataFrame(data, index=dates)

# Generate the candle chart
print("Generating Stargate Telemetry Image...")
mpf.plot(df, type='candle', style='charles', 
         title='Brent Crude - Hormuz Risk Monitor (March 2026)',
         ylabel='Price ($)',
         savefig='h_risk_report.png')

print(f"Success. Image saved to: {os.path.abspath('h_risk_report.png')}")
