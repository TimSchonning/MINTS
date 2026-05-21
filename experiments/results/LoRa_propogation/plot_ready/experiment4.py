from lora_result import LoRaResult, ConfigResult, TResults
import numpy as np

# \begin{tabular}{c|ccccc}
#     Transmitter location & Mean RSSI (dBm) & Mean SNR (dB) & PL (\%) \\ \hline
# T1 & -107.42  & 1.24 & 0.00\\
# T2 & -117.20 & -8.13 & 10.00 \\
# T3 & -119.67 & -12.39 & 82.00 \\
# T4 & -119.00 & -11.75 & 98.00 \\
# \end{tabular}
# \caption{Results from LoRa configured using a BW of 125 kHz and SF 8.}

exp4_bw125_sf8_result = ConfigResult(bw=125, 
                                   sf=8, 
                                   rows=[
                                       TResults(T_id=1, RSSI=-107.42, SNR=1.24, PL=0.00), 
                                       TResults(T_id=2, RSSI=-117.20, SNR=-8.13, PL=10.00), 
                                       TResults(T_id=3, RSSI=-119.67, SNR=-12.39, PL=82.00), 
                                       TResults(T_id=4, RSSI=-119.00, SNR=-11.75, PL=98.00), 
                                       ])

# \begin{tabular}{c|ccccc}
#     Transmitter location & Mean RSSI (dBm) & Mean SNR (dB) & PL (\%) \\ \hline
# T1 & -105.64  & 1.33 & 0.00\\
# T2 & -114.86 & -4.88 & 0.00 \\
# T3 & -119.89 & -14.58 & 12.00 \\
# T4 & -123.61 & -15.10 & 38.00 \\
# \end{tabular}
# \caption{Results from LoRa configured using a BW of 125 kHz and SF 10.}

exp4_bw125_sf10_result = ConfigResult(bw=125, 
                                   sf=10, 
                                   rows=[
                                       TResults(T_id=1, RSSI=-105.64, SNR=1.33, PL=0.00), 
                                       TResults(T_id=2, RSSI=-114.86, SNR=-4.88, PL=0.00), 
                                       TResults(T_id=3, RSSI=-119.89, SNR=-14.58, PL=12.00), 
                                       TResults(T_id=4, RSSI=-123.61, SNR=-15.10, PL=38.00), 
                                       ])

# \begin{tabular}{c|ccccc}
#     Transmitter location & Mean RSSI (dBm) & Mean SNR (dB) & PL (\%) \\ \hline
# T1 & -105.30  & 1.14 & 0.00\\
# T2 & -113.48 & -3.57 & 0.00 \\
# T3 & -125.75 & -19.05 & 20.00 \\
# T4 & -126.52 & -16.98 & 42.00 \\
# \end{tabular}
# \caption{Results from LoRa configured using a BW of 125 kHz and SF 12.}

exp4_bw125_sf12_result = ConfigResult(bw=125, 
                                   sf=12, 
                                   rows=[
                                       TResults(T_id=1, RSSI=-105.30, SNR=1.14, PL=0.00), 
                                       TResults(T_id=2, RSSI=-113.48, SNR=-3.57, PL=0.00), 
                                       TResults(T_id=3, RSSI=-125.75, SNR=-19.05, PL=20.00), 
                                       TResults(T_id=4, RSSI=-126.52, SNR=-16.98, PL=42.00), 
                                       ])

# \begin{tabular}{c|ccccc}
#     Transmitter location & Mean RSSI (dBm) & Mean SNR (dB) & PL (\%) \\ \hline
# T1 & -102.48  & 2.55 & 0.00\\
# T2 & -114.46 & -8.81 & 8.00 \\
# T3 & NaN & NaN & 100.00 \\
# T4 & NaN & NaN & 100.00 \\
# \end{tabular}
# \caption{Results from LoRa configured using a BW of 250 kHz and SF 8.}

exp4_bw250_sf8_result = ConfigResult(bw=250, 
                                   sf=8, 
                                   rows=[
                                       TResults(T_id=1, RSSI=-102.48, SNR=2.55, PL=0.00), 
                                       TResults(T_id=2, RSSI=-114.46, SNR=-8.81, PL=8.00), 
                                       TResults(T_id=3, RSSI=np.nan, SNR=np.nan, PL=100.00),  
                                       TResults(T_id=4, RSSI=np.nan, SNR=np.nan, PL=100.00),  
                                       ])

# \begin{tabular}{c|ccccc}
#     Transmitter location & Mean RSSI (dBm) & Mean SNR (dB) & PL (\%) \\ \hline
# T1 & -104.32  & -1.67 & 0.00\\
# T2 & -114.50 & -8.08 & 0.00 \\
# T3 & -119.81 & -16.72 & 68.00 \\
# T4 & -120.87 & -16.30 & 68.00 \\
# \end{tabular}
# \caption{Results from LoRa configured using a BW of 250 kHz and SF 10.}

exp4_bw250_sf10_result = ConfigResult(bw=250, 
                                   sf=10, 
                                   rows=[
                                       TResults(T_id=1, RSSI=-104.32, SNR=-1.67, PL=0.00), 
                                       TResults(T_id=2, RSSI=-114.50, SNR=-8.08, PL=0.00), 
                                       TResults(T_id=3, RSSI=-119.81, SNR=-16.72, PL=68.00),  
                                       TResults(T_id=4, RSSI=-120.87, SNR=-16.30, PL=68.00),  
                                       ])

# \begin{tabular}{c|ccccc}
#     Transmitter location & Mean RSSI (dBm) & Mean SNR (dB) & PL (\%) \\ \hline
# T1 & -108.92  & -2.51 & 0.00\\
# T2 & -115.48 & -8.69 & 0.00 \\
# T3 & -122.93 & -20.07 & 44.00 \\
# T4 & -124.22 & -18.86 & 46.00 \\
# \end{tabular}
# \caption{Results from LoRa configured using a BW of 250 kHz and SF 12.}

exp4_bw250_sf12_result = ConfigResult(bw=250, 
                                   sf=12, 
                                   rows=[
                                       TResults(T_id=1, RSSI=-108.92, SNR=-2.51, PL=0.00), 
                                       TResults(T_id=2, RSSI=-115.48, SNR=-8.69, PL=0.00), 
                                       TResults(T_id=3, RSSI=-122.93, SNR=-20.07, PL=44.00),  
                                       TResults(T_id=4, RSSI=-124.22, SNR=-18.86, PL=46.00),  
                                       ])



experiment4_bw125 = LoRaResult("Experiment 4 - Bandwidth 125 kHz", [exp4_bw125_sf8_result, exp4_bw125_sf10_result, exp4_bw125_sf12_result])
experiment4_bw250 = LoRaResult("Experiment 4 - Bandwidth 250 kHz", [exp4_bw250_sf8_result, exp4_bw250_sf10_result, exp4_bw250_sf12_result])

