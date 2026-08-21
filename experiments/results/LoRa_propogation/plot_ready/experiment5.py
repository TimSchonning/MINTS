from lora_result import LoRaResult, ConfigResult, TResults
import numpy as np

# \begin{tabular}{c|ccccc}
#     Transmitter location & Mean RSSI (dBm) & Mean SNR (dB) & PL (\%) \\ \hline
# T1 & -113.64 & -6.20 & 0.00\\
# T2 & -117.38 & -9.47 & 16.00 \\
# T3 & NaN & NaN & 100.00 \\
# T4 & -112.64 & -3.52 & 0.00 \\
# \end{tabular}
# \caption{Results from LoRa configured using a BW of 125 kHz and SF 8.}

exp5_bw125_sf8_result = ConfigResult(bw=125, 
                                   sf=8, 
                                   rows=[
                                       TResults(T_id=1, RSSI=-113.64, SNR=-6.20, PL=0.00), 
                                       TResults(T_id=2, RSSI=-117.38, SNR=-9.47, PL=16.00), 
                                       TResults(T_id=3, RSSI=np.nan, SNR=np.nan, PL=100.00),  
                                       TResults(T_id=4, RSSI=-112.64, SNR=-3.52, PL=0.00), 
                                       ])

# \begin{tabular}{c|ccccc}
#     Transmitter location & Mean RSSI (dBm) & Mean SNR (dB) & PL (\%) \\ \hline
# T1 & -119.10 & -10.15 & 0.00\\
# T2 & -118.56 & -11.04 & 14.00 \\
# T3 & NaN & NaN & 100.00 \\
# T4 & -113.30 & -3.05 & 0.00 \\
# \end{tabular}
# \caption{Results from LoRa configured using a BW of 125 kHz and SF 10.}

exp5_bw125_sf10_result = ConfigResult(bw=125, 
                                   sf=10, 
                                   rows=[
                                       TResults(T_id=1, RSSI=-119.10, SNR=-10.15, PL=0.00), 
                                       TResults(T_id=2, RSSI=-118.56, SNR=-11.04, PL=14.00), 
                                       TResults(T_id=3, RSSI=np.nan, SNR=np.nan, PL=100.00),  
                                       TResults(T_id=4, RSSI=-113.30, SNR=-3.05, PL=0.00), 
                                       ])

# \begin{tabular}{c|ccccc}
#     Transmitter location & Mean RSSI (dBm) & Mean SNR (dB) & PL (\%) \\ \hline
# T1 & -122.32 & -15.11 & 28.00\\
# T2 & NaN & NaN & 100.00 \\
# T3 & NaN & NaN & 100.00 \\
# T4 & -111.70 & -1.04 & 0.00 \\
# \end{tabular}
# \caption{Results from LoRa configured using a BW of 125 kHz and SF 12.}

exp5_bw125_sf12_result = ConfigResult(bw=125, 
                                   sf=12, 
                                   rows=[
                                       TResults(T_id=1, RSSI=-122.32, SNR=-15.11, PL=28.00), 
                                       TResults(T_id=2, RSSI=np.nan, SNR=np.nan, PL=100.00), 
                                       TResults(T_id=3, RSSI=np.nan, SNR=np.nan, PL=100.00),  
                                       TResults(T_id=4, RSSI=-111.70, SNR=-1.04, PL=0.00), 
                                       ])

# \begin{tabular}{c|ccccc}
#     Transmitter location & Mean RSSI (dBm) & Mean SNR (dB) & PL (\%) \\ \hline
# T1 & NaN & NaN & 100.00\\
# T2 & NaN & NaN & 100.00 \\
# T3 & NaN & NaN & 100.00 \\
# T4 & -109.96 & -2.79 & 0.00 \\
# \end{tabular}
# \caption{Results from LoRa configured using a BW of 250 kHz and SF 8.}

exp5_bw250_sf8_result = ConfigResult(bw=250, 
                                   sf=8, 
                                   rows=[
                                       TResults(T_id=1, RSSI=np.nan, SNR=np.nan, PL=100.00), 
                                       TResults(T_id=2, RSSI=np.nan, SNR=np.nan, PL=100.00), 
                                       TResults(T_id=3, RSSI=np.nan, SNR=np.nan, PL=100.00),  
                                       TResults(T_id=4, RSSI=-109.96, SNR=-2.79, PL=0.00), 
                                       ])

# \begin{tabular}{c|ccccc}
#     Transmitter location & Mean RSSI (dBm) & Mean SNR (dB) & PL (\%) \\ \hline
# T1 & NaN & NaN & 100.00\\
# T2 & NaN & NaN & 100.00 \\
# T3 & NaN & NaN & 100.00 \\
# T4 & -112.84 & -5.74 & 0.00 \\
# \end{tabular}
# \caption{Results from LoRa configured using a BW of 250 kHz and SF 10.}

exp5_bw250_sf10_result = ConfigResult(bw=250, 
                                   sf=10, 
                                   rows=[
                                       TResults(T_id=1, RSSI=np.nan, SNR=np.nan, PL=100.00), 
                                       TResults(T_id=2, RSSI=np.nan, SNR=np.nan, PL=100.00), 
                                       TResults(T_id=3, RSSI=np.nan, SNR=np.nan, PL=100.00),  
                                       TResults(T_id=4, RSSI=-112.84, SNR=-5.74, PL=0.00), 
                                       ])

# \begin{tabular}{c|ccccc}
#     Transmitter location & Mean RSSI (dBm) & Mean SNR (dB) & PL (\%) \\ \hline
# T1 & -119.27 & -16.86 & 10.00\\
# T2 & NaN & NaN & 100.00 \\
# T3 & NaN & NaN & 100.00 \\
# T4 & -111.22 & -4.09 & 0.00 \\
# \end{tabular}
# \caption{Results from LoRa configured using a BW of 250 kHz and SF 12.}

exp5_bw250_sf12_result = ConfigResult(bw=250, 
                                   sf=12, 
                                   rows=[
                                       TResults(T_id=1, RSSI=-119.27, SNR=-16.86, PL=100.00), 
                                       TResults(T_id=2, RSSI=np.nan, SNR=np.nan, PL=100.00), 
                                       TResults(T_id=3, RSSI=np.nan, SNR=np.nan, PL=100.00),  
                                       TResults(T_id=4, RSSI=-111.22, SNR=-4.09, PL=0.00), 
                                       ])


experiment5_bw125 = LoRaResult("Experiment 5 - Bandwidth 125 kHz", [exp5_bw125_sf8_result, exp5_bw125_sf10_result, exp5_bw125_sf12_result])
experiment5_bw250 = LoRaResult("Experiment 5 - Bandwidth 250 kHz", [exp5_bw250_sf8_result, exp5_bw250_sf10_result, exp5_bw250_sf12_result])

