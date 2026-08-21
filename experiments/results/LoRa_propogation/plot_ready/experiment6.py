from lora_result import LoRaResult, ConfigResult, TResults
import numpy as np

# \begin{tabular}{c|ccccc}
#     Transmitter location & Mean RSSI (dBm) & Mean SNR (dB) & PL (\%) \\ \hline
# T1 & -117.34 & -7.92 & 0.00\\
# T2 & -120.04 & -8.14 & 44.00 \\
# T3 & NaN & NaN & 100.00 \\
# T4 & -115.12 & -7.99 & 0.00 \\
# T5 & -118.00 & -12.38 & 96.00 \\
# \end{tabular}
# \caption{Results from LoRa configured using a BW of 125 kHz and SF 8.}

exp6_bw125_sf8_result = ConfigResult(bw=125, 
                                   sf=8, 
                                   rows=[
                                       TResults(T_id=1, RSSI=-117.34, SNR=-7.92, PL=0.00), 
                                       TResults(T_id=2, RSSI=-120.04, SNR=-8.14, PL=44.00), 
                                       TResults(T_id=3, RSSI=np.nan, SNR=np.nan, PL=100.00),  
                                       TResults(T_id=4, RSSI=-115.12, SNR=-7.99, PL=0.00), 
                                       TResults(T_id=5, RSSI=-118.00, SNR=-12.38, PL=96.00), 
                                       ])

# \begin{tabular}{c|ccccc}
#     Transmitter location & Mean RSSI (dBm) & Mean SNR (dB) & PL (\%) \\ \hline
# T1 & -121.16 & -10.23 & 0.00\\
# T2 & -123.76 & -15.12 & 32.00 \\
# T3 & -121.53 & -13.27 & 2.00 \\
# T4 & -115.90 & -9.41 & 0.00 \\
# T5 & -121.06 & -14.02 & 0.00 \\
# \end{tabular}
# \caption{Results from LoRa configured using a BW of 125 kHz and SF 10.}

exp6_bw125_sf10_result = ConfigResult(bw=125, 
                                   sf=10, 
                                   rows=[
                                       TResults(T_id=1, RSSI=-121.16, SNR=-10.23, PL=0.00), 
                                       TResults(T_id=2, RSSI=-123.76, SNR=-15.12, PL=32.00), 
                                       TResults(T_id=3, RSSI=-121.53, SNR=-13.27, PL=2.00),  
                                       TResults(T_id=4, RSSI=-115.90, SNR=-9.41, PL=0.00), 
                                       TResults(T_id=5, RSSI=-121.06, SNR=-14.02, PL=0.00), 
                                       ])

# begin{tabular}{c|ccccc}
#     Transmitter location & Mean RSSI (dBm) & Mean SNR (dB) & PL (\%) \\ \hline
# T1 & -118.28 & -6.17 & 0.00\\
# T2 & -123.82 & -14.49 & 0.00 \\
# T3 & -118.90 & -11.58 & 8.00 \\
# T4 & -117.62 & -8.82 & 0.00 \\
# T5 & -123.44 & -15.30 & 0.00 \\
# \end{tabular}
# \caption{Results from LoRa configured using a BW of 125 kHz and SF 12.}

exp6_bw125_sf12_result = ConfigResult(bw=125, 
                                   sf=12, 
                                   rows=[
                                       TResults(T_id=1, RSSI=-118.28, SNR=-6.17, PL=0.00), 
                                       TResults(T_id=2, RSSI=-123.82, SNR=-14.49, PL=0.00), 
                                       TResults(T_id=3, RSSI=-118.90, SNR=-11.58, PL=8.00),  
                                       TResults(T_id=4, RSSI=-117.62, SNR=-8.82, PL=0.00), 
                                       TResults(T_id=5, RSSI=-123.44, SNR=-15.30, PL=0.00), 
                                       ])

# \begin{tabular}{c|ccccc}
#     Transmitter location & Mean RSSI (dBm) & Mean SNR (dB) & PL (\%) \\ \hline
# T1 & -116.09 & -9.71 & 10.00\\
# T2 & -117.19 & -10.94 & 46.00 \\
# T3 & NaN & NaN & 100.00 \\
# T4 & NaN & NaN & 100.00 \\
# T5 & NaN & NaN & 100.00 \\
# \end{tabular}
# \caption{Results from LoRa configured using a BW of 250 kHz and SF 8.}

exp6_bw250_sf8_result = ConfigResult(bw=250, 
                                   sf=8, 
                                   rows=[
                                       TResults(T_id=1, RSSI=-116.09, SNR=-9.71, PL=10.00), 
                                       TResults(T_id=2, RSSI=-117.19, SNR=-10.94, PL=46.00), 
                                       TResults(T_id=3, RSSI=np.nan, SNR=np.nan, PL=100.00),  
                                       TResults(T_id=4, RSSI=np.nan, SNR=np.nan, PL=100.00), 
                                       TResults(T_id=5, RSSI=np.nan, SNR=np.nan, PL=100.00), 
                                       ])

# \begin{tabular}{c|ccccc}
#     Transmitter location & Mean RSSI (dBm) & Mean SNR (dB) & PL (\%) \\ \hline
# T1 & -114.60 & -8.46 & 0.00\\
# T2 & -117.12 & -11.88 & 0.00 \\
# T3 & -121.37 & -17.34 & 68.00 \\
# T4 & -117.78 & -15.36 & 8.00 \\
# T5 & NaN & NaN & 100.00 \\
# \end{tabular}
# \caption{Results from LoRa configured using a BW of 250 kHz and SF 10.}

exp6_bw250_sf10_result = ConfigResult(bw=250, 
                                   sf=10, 
                                   rows=[
                                       TResults(T_id=1, RSSI=-114.60, SNR=-8.46, PL=0.00), 
                                       TResults(T_id=2, RSSI=-117.12, SNR=-11.88, PL=0.00), 
                                       TResults(T_id=3, RSSI=-121.37, SNR=-17.34, PL=68.00),  
                                       TResults(T_id=4, RSSI=-117.78, SNR=-15.36, PL=8.00), 
                                       TResults(T_id=5, RSSI=np.nan, SNR=np.nan, PL=100.00), 
                                       ])

# \begin{tabular}{c|ccccc}
#     Transmitter location & Mean RSSI (dBm) & Mean SNR (dB) & PL (\%) \\ \hline
# T1 & -118.47 & -13.08 & 22.00\\
# T2 & -118.28 & -12.26 & 0.00 \\
# T3 & -121.13 & -15.32 & 2.00 \\
# T4 & -117.74 & -13.20 & 0.00 \\
# T5 & -121.27 & -16.45 & 4.00 \\
# \end{tabular}
# \caption{Results from LoRa configured using a BW of 250 kHz and SF 12.}

exp6_bw250_sf12_result = ConfigResult(bw=250, 
                                   sf=12, 
                                   rows=[
                                       TResults(T_id=1, RSSI=-118.47, SNR=-13.08, PL=22.00), 
                                       TResults(T_id=2, RSSI=-118.28, SNR=-12.26, PL=0.00), 
                                       TResults(T_id=3, RSSI=-121.13, SNR=-15.32, PL=2.00),  
                                       TResults(T_id=4, RSSI=-117.74, SNR=-13.20, PL=0.00), 
                                       TResults(T_id=5, RSSI=-121.27, SNR=-16.45, PL=4.00), 
                                       ])





experiment6_bw125 = LoRaResult("Experiment 6 - Bandwidth 125 kHz", [exp6_bw125_sf8_result, exp6_bw125_sf10_result, exp6_bw125_sf12_result])
experiment6_bw250 = LoRaResult("Experiment 6 - Bandwidth 250 kHz", [exp6_bw250_sf8_result, exp6_bw250_sf10_result, exp6_bw250_sf12_result])

