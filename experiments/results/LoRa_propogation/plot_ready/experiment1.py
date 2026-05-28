from lora_result import LoRaResult, ConfigResult, TResults

# \begin{tabular}{c|ccccc}
#     Transmitter location & Mean RSSI (dBm) & Mean SNR (dB) & PL (\%) \\ \hline
# T1 & -81.98 & 13.77 & 0.00\\
# T2 & -98.44 & 3.34 & 4.00 \\
# T3 & -109.79 & -7.96 & 62.00 \\
# T4 & -111.57 & -7.76 & 16.00 \\
# \end{tabular}
# \caption{Results from LoRa configured using a BW of 125 kHz and SF 8.}

exp1_bw125_sf8_result = ConfigResult(bw=125, 
                                   sf=8, 
                                   rows=[
                                       TResults(T_id=1, RSSI=-81.98, SNR=13.77, PL=0.00), 
                                       TResults(T_id=2, RSSI=-98.44, SNR=3.34, PL=4.00), 
                                       TResults(T_id=3, RSSI=-109.79, SNR=-7.96, PL=62.00), 
                                       TResults(T_id=4, RSSI=-111.57, SNR=-7.76, PL=16.00)
                                       ])

# \begin{tabular}{c|ccccc}
#     Transmitter location & Mean RSSI (dBm) & Mean SNR (dB) & PL (\%) \\ \hline
# T1 & -85.74 & 8.22 & 0.00\\
# T2 & -102.62 & 1.50 & 6.00 \\
# T3 & -112.23 & -9.63 & 22.00 \\
# T4 & -113.20 & -9.40 & 0.00 \\
# \end{tabular}
# \caption{Results from LoRa configured using a BW of 125 kHz and SF 10.}

exp1_bw125_sf10_result = ConfigResult(bw=125, 
                                   sf=10, 
                                   rows=[
                                       TResults(T_id=1, RSSI=-85.74, SNR=8.22, PL=0.00), 
                                       TResults(T_id=2, RSSI=-102.62, SNR=1.50, PL=6.00), 
                                       TResults(T_id=3, RSSI=-112.23, SNR=-9.63, PL=22.00), 
                                       TResults(T_id=4, RSSI=-113.20, SNR=-9.40, PL=0.00)
                                       ])

# \begin{tabular}{c|ccccc}
#     Transmitter location & Mean RSSI (dBm) & Mean SNR (dB) & PL (\%) \\ \hline
# T1 & -85.58 & 6.78 & 0.00\\
# T2 & -98.60 & 4.40 & 0.00 \\
# T3 & -110.55 & -7.09 & 2.00 \\
# T4 & -111.12 & -6.89 & 0.00 \\
# \end{tabular}
# \caption{Results from LoRa configured using a BW of 125 kHz and SF 12.}

exp1_bw125_sf12_result = ConfigResult(bw=125, 
                                   sf=12, 
                                   rows=[
                                       TResults(T_id=1, RSSI=-85.58, SNR=6.78, PL=0.00), 
                                       TResults(T_id=2, RSSI=-98.60, SNR=4.40, PL=0.00), 
                                       TResults(T_id=3, RSSI=-110.55, SNR=-7.09, PL=2.00), 
                                       TResults(T_id=4, RSSI=-111.12, SNR=-6.89, PL=0.00)
                                       ])

# \begin{tabular}{c|ccccc}
#     Transmitter location & Mean RSSI (dBm) & Mean SNR (dB) & PL (\%) \\ \hline
# T1 & -90.88 & 6.72 & 0.00\\
# T2 & -93.18 & 7.72 & 0.00 \\
# T3 & -109.27 & -10.47 & 70.00 \\
# T4 & -108.86 & -8.23 & 0.00 \\
# \end{tabular}
# \caption{Results from LoRa configured using a BW of 250 kHz and SF 8.}

exp1_bw250_sf8_result = ConfigResult(bw=250, 
                                   sf=8, 
                                   rows=[
                                       TResults(T_id=1, RSSI=-90.88, SNR=6.72, PL=0.00), 
                                       TResults(T_id=2, RSSI=-93.18, SNR=7.72, PL=0.00), 
                                       TResults(T_id=3, RSSI=-109.27, SNR=-10.47, PL=70.00), 
                                       TResults(T_id=4, RSSI=-108.86, SNR=-8.23, PL=0.00)
                                       ])

# \begin{tabular}{c|ccccc}
#     Transmitter location & Mean RSSI (dBm) & Mean SNR (dB) & PL (\%) \\ \hline
# T1 & -90.35 & 5.51 & 2.00\\
# T2 & -91.26 & 7.01 & 0.00 \\
# T3 & -111.86 & -12.78 & 56.00 \\
# T4 & -111.88 & -10.34 & 0.00 \\
# \end{tabular}
# \caption{Results from LoRa configured using a BW of 250 kHz and SF 10.}

exp1_bw250_sf10_result = ConfigResult(bw=250, 
                                   sf=10, 
                                   rows=[
                                       TResults(T_id=1, RSSI=-90.35, SNR=5.51, PL=2.00), 
                                       TResults(T_id=2, RSSI=-91.26, SNR=7.01, PL=0.00), 
                                       TResults(T_id=3, RSSI=-111.86, SNR=-12.78, PL=56.00), 
                                       TResults(T_id=4, RSSI=-111.88, SNR=-10.34, PL=0.00)
                                       ])

# \begin{tabular}{c|ccccc}
#     Transmitter location & Mean RSSI (dBm) & Mean SNR (dB) & PL (\%) \\ \hline
# T1 & -92.14 & 3.62 & 0.00\\
# T2 & -98.80 & 2.14 & 0.00 \\
# T3 & -109.85 & -11.11 & 8.00 \\
# T4 & -113.26 & -12.49 & 0.00 \\
# \end{tabular}
# \caption{Results from LoRa configured using a BW of 250 kHz and SF 12.}

exp1_bw250_sf12_result = ConfigResult(bw=250, 
                                   sf=12, 
                                   rows=[
                                       TResults(T_id=1, RSSI=-92.14, SNR=3.62, PL=0.00), 
                                       TResults(T_id=2, RSSI=-98.80, SNR=2.14, PL=0.00), 
                                       TResults(T_id=3, RSSI=-109.85, SNR=-11.11, PL=8.00), 
                                       TResults(T_id=4, RSSI=-113.26, SNR=-12.49, PL=0.00)
                                       ])


experiment1_bw125 = LoRaResult("Experiment 1 - Bandwidth 125 kHz", [exp1_bw125_sf8_result, exp1_bw125_sf10_result, exp1_bw125_sf12_result])
experiment1_bw250 = LoRaResult("Experiment 1 - Bandwidth 250 kHz", [exp1_bw250_sf8_result, exp1_bw250_sf10_result, exp1_bw250_sf12_result])

