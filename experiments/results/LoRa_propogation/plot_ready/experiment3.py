from lora_result import LoRaResult, ConfigResult, TResults
import numpy as np

# \begin{tabular}{c|ccccc}
#     Transmitter location & Mean RSSI (dBm) & Mean SNR (dB) & PL (\%) \\ \hline
# T1 & -107.64  & -0.81 & 0.00\\
# T2 & -112.94 & -7.86 & 0.00 \\
# T3 & -116.53 & -11.34 & 66.00 \\
# \end{tabular}
# \caption{Results from LoRa configured using a BW of 125 kHz and SF 8.}

exp3_bw125_sf8_result = ConfigResult(bw=125, 
                                   sf=8, 
                                   rows=[
                                       TResults(T_id=1, RSSI=-107.64, SNR=-0.81, PL=0.00), 
                                       TResults(T_id=2, RSSI=-112.94, SNR=-7.86, PL=0.00), 
                                       TResults(T_id=3, RSSI=-116.53, SNR=-11.34, PL=66.00), 
                                       ])

# \begin{tabular}{c|ccccc}
#     Transmitter location & Mean RSSI (dBm) & Mean SNR (dB) & PL (\%) \\ \hline
# T1 & -105.34  & -0.10 & 0.00\\
# T2 & -112.76 & -7.32 & 0.00 \\
# T3 & -115.90 & -10.23 & 0.00 \\
# \end{tabular}
# \caption{Results from LoRa configured using a BW of 125 kHz and SF 10.}

exp3_bw125_sf10_result = ConfigResult(bw=125, 
                                   sf=10, 
                                   rows=[
                                       TResults(T_id=1, RSSI=-105.34, SNR=-0.10, PL=0.00), 
                                       TResults(T_id=2, RSSI=-112.76, SNR=-7.32, PL=0.00), 
                                       TResults(T_id=3, RSSI=-115.90, SNR=-10.23, PL=0.00), 
                                       ])

# \begin{tabular}{c|ccccc}
#     Transmitter location & Mean RSSI (dBm) & Mean SNR (dB) & PL (\%) \\ \hline
# T1 & -107.34 & -1.48 & 0.00\\
# T2 & -113.98 & -8.18 & 0.00 \\
# T3 & -119.88 & -10.38 & 0.00 \\
# \end{tabular}
# \caption{Results from LoRa configured using a BW of 125 kHz and SF 12.}

exp3_bw125_sf12_result = ConfigResult(bw=125, 
                                   sf=12, 
                                   rows=[
                                       TResults(T_id=1, RSSI=-107.34, SNR=-1.48, PL=0.00), 
                                       TResults(T_id=2, RSSI=-113.98, SNR=-8.18, PL=0.00), 
                                       TResults(T_id=3, RSSI=-119.88, SNR=-10.38, PL=0.00), 
                                       ])

# \begin{tabular}{c|ccccc}
#     Transmitter location & Mean RSSI (dBm) & Mean SNR (dB) & PL (\%) \\ \hline
# T1 & -111.00 & -8.30 & 6.00\\
# T2 & -114.00 & -12.25 & 98.00 \\
# T3 & NaN & NaN & 100.00 \\
# \end{tabular}
# \caption{Results from LoRa configured using a BW of 250 kHz and SF 8.}

exp3_bw250_sf8_result = ConfigResult(bw=250, 
                                   sf=8, 
                                   rows=[
                                       TResults(T_id=1, RSSI=-111.00, SNR=-8.30, PL=6.00), 
                                       TResults(T_id=2, RSSI=-114.00, SNR=-12.25, PL=98.00), 
                                       TResults(T_id=3, RSSI=np.nan, SNR=np.nan, PL=100.00),  
                                       ])

# \begin{tabular}{c|ccccc}
#     Transmitter location & Mean RSSI (dBm) & Mean SNR (dB) & PL (\%) \\ \hline
# T1 & -105.46 & -3.72 & 0.00\\
# T2 & -114.20 & -13.10 & 2.00 \\
# T3 & NaN & NaN & 100.00 \\
# \end{tabular}
# \caption{Results from LoRa configured using a BW of 250 kHz and SF 10.}

exp3_bw250_sf10_result = ConfigResult(bw=250, 
                                   sf=10, 
                                   rows=[
                                       TResults(T_id=1, RSSI=-105.46, SNR=-3.72, PL=0.00), 
                                       TResults(T_id=2, RSSI=-114.20, SNR=-13.10, PL=2.00), 
                                       TResults(T_id=3, RSSI=np.nan, SNR=np.nan, PL=100.00),  
                                       ])

# \begin{tabular}{c|ccccc}
#     Transmitter location & Mean RSSI (dBm) & Mean SNR (dB) & PL (\%) \\ \hline
# T1 & -102.08 & -1.84 & 2.00\\
# T2 & -114.02 & -12.31 & 6.00 \\
# T3 & -125.03 & -19.29 & 64.00 \\
# \end{tabular}
# \caption{Results from LoRa configured using a BW of 250 kHz and SF 12.}

exp3_bw250_sf12_result = ConfigResult(bw=250, 
                                   sf=12, 
                                   rows=[
                                       TResults(T_id=1, RSSI=-102.08, SNR=-1.84, PL=2.00), 
                                       TResults(T_id=2, RSSI=-114.02, SNR=-12.31, PL=6.00), 
                                       TResults(T_id=3, RSSI=-125.03, SNR=-19.29, PL=64.00),  
                                       ])


experiment3_bw125 = LoRaResult("Experiment 3 - Bandwidth 125 kHz", [exp3_bw125_sf8_result, exp3_bw125_sf10_result, exp3_bw125_sf12_result])
experiment3_bw250 = LoRaResult("Experiment 3 - Bandwidth 250 kHz", [exp3_bw250_sf8_result, exp3_bw250_sf10_result, exp3_bw250_sf12_result])

