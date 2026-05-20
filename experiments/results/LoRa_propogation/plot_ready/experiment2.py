from lora_result import LoRaResult, ConfigResult, TResults
import numpy as np

# \begin{tabular}{c|ccccc}
#     Transmitter location & Mean RSSI (dBm) & Mean SNR (dB) & PL (\%) \\ \hline
# T1 & -86.56 & 12.81 & 0.00\\
# T2 & -117.67 & -11.50 & 88.00 \\
# T3 & NaN & NaN & 100.00 \\
# \end{tabular}
# \caption{Results from LoRa configured using a BW of 125 kHz and SF 8.}

exp2_bw125_sf8_result = ConfigResult(bw=125, 
                                   sf=8, 
                                   rows=[
                                       TResults(T_id=1, RSSI=-86.56, SNR=12.81, PL=0.00), 
                                       TResults(T_id=2, RSSI=-117.67, SNR=-11.50, PL=88.00), 
                                       TResults(T_id=3, RSSI=np.nan, SNR=np.nan, PL=100.00), 
                                       ])

# \begin{tabular}{c|ccccc}
#     Transmitter location & Mean RSSI (dBm) & Mean SNR (dB) & PL (\%) \\ \hline
# T1 & -87.58 & 7.85 & 0.00\\
# T2 & -109.03 & -3.84 & 30.00 \\
# T3 & -120.83 & -14.87 & 18.00 \\
# \end{tabular}
# \caption{Results from LoRa configured using a BW of 125 kHz and SF 10.}

exp2_bw125_sf10_result = ConfigResult(bw=125, 
                                   sf=10, 
                                   rows=[
                                       TResults(T_id=1, RSSI=-87.58, SNR=7.85, PL=0.00), 
                                       TResults(T_id=2, RSSI=-109.03, SNR=-3.84, PL=30.00), 
                                       TResults(T_id=3, RSSI=-120.83, SNR=-14.87, PL=18.00), 
                                       ])

# \begin{tabular}{c|ccccc}
#     Transmitter location & Mean RSSI (dBm) & Mean SNR (dB) & PL (\%) \\ \hline
# T1 & -92.54 & 5.83 & 0.00\\
# T2 & -111.20 & -4.32 & 0.00 \\
# T3 & -121.10 & -14.21 & 0.00 \\
# \end{tabular}
# \caption{Results from LoRa configured using a BW of 125 kHz and SF 12.}

exp2_bw125_sf12_result = ConfigResult(bw=125, 
                                   sf=12, 
                                   rows=[
                                       TResults(T_id=1, RSSI=-92.54, SNR=5.83, PL=0.00), 
                                       TResults(T_id=2, RSSI=-111.20, SNR=-4.32, PL=0.00), 
                                       TResults(T_id=3, RSSI=-121.10, SNR=-14.21, PL=0.00), 
                                       ])

# \begin{tabular}{c|ccccc}
#     Transmitter location & Mean RSSI (dBm) & Mean SNR (dB) & PL (\%) \\ \hline
# T1 & -93.06 & 8.98 & 0.00\\
# T2 & -114.92 & -10.66 & 48.00 \\
# T3 & NaN & NaN & 100.00 \\
# \end{tabular}
# \caption{Results from LoRa configured using a BW of 250 kHz and SF 8.}

exp2_bw250_sf8_result = ConfigResult(bw=250, 
                                   sf=8, 
                                   rows=[
                                       TResults(T_id=1, RSSI=-93.06, SNR=8.98, PL=0.00), 
                                       TResults(T_id=2, RSSI=-114.92, SNR=-10.66, PL=48.00), 
                                       TResults(T_id=3, RSSI=np.nan, SNR=np.nan, PL=100.00),  
                                       ])

# \begin{tabular}{c|ccccc}
#     Transmitter location & Mean RSSI (dBm) & Mean SNR (dB) & PL (\%) \\ \hline
# T1 & -94.18 & 5.59 & 0.00\\
# T2 & -113.24 & -9.14 & 0.00 \\
# T3 & -119.87 & -15.92 & 52.00 \\
# \end{tabular}
# \caption{Results from LoRa configured using a BW of 250 kHz and SF 10.}

exp2_bw250_sf10_result = ConfigResult(bw=250, 
                                   sf=10, 
                                   rows=[
                                       TResults(T_id=1, RSSI=-94.18, SNR=5.59, PL=0.00), 
                                       TResults(T_id=2, RSSI=-113.24, SNR=-9.14, PL=0.00), 
                                       TResults(T_id=3, RSSI=-119.87, SNR=-15.92, PL=52.00),  
                                       ])

# \begin{tabular}{c|ccccc}
#     Transmitter location & Mean RSSI (dBm) & Mean SNR (dB) & PL (\%) \\ \hline
# T1 & -92.82  & 3.18 & 0.00\\
# T2 & -112.38 & -10.97 & 16.00 \\
# T3 & -120.02 & -16.35 & 8.00 \\
# \end{tabular}
# \caption{Results from LoRa configured using a BW of 250 kHz and SF 12.}

exp2_bw250_sf12_result = ConfigResult(bw=250, 
                                   sf=12, 
                                   rows=[
                                       TResults(T_id=1, RSSI=-92.82, SNR=3.18, PL=0.00), 
                                       TResults(T_id=2, RSSI=-112.38, SNR=-10.97, PL=16.00), 
                                       TResults(T_id=3, RSSI=-120.02, SNR=-16.35, PL=8.00),  
                                       ])



experiment2_bw125 = LoRaResult("Experiment 2 - Bandwidth 125 kHz", [exp2_bw125_sf8_result, exp2_bw125_sf10_result, exp2_bw125_sf12_result])
experiment2_bw250 = LoRaResult("Experiment 2 - Bandwidth 250 kHz", [exp2_bw250_sf8_result, exp2_bw250_sf10_result, exp2_bw250_sf12_result])

