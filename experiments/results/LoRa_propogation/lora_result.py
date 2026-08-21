# \begin{tabular}{c|ccccc}
#     Transmitter location & Mean RSSI (dBm) & Mean SNR (dB) & PL (\%) \\ \hline
# T1 & -81.98 & 13.77 & 0.00\\
# T2 & -98.44 & 3.34 & 4.00 \\
# T3 & -109.79 & -7.96 & 62.00 \\
# T4 & -111.57 & -7.76 & 16.00 \\
# \end{tabular}

import numpy as np

class TResults():
    def __init__(self, T_id: int, RSSI: float, SNR: float, PL: float):
        self.T_id = T_id
        self.RSSI = RSSI
        self.SNR = SNR
        self.PL = PL


class ConfigResult():
    def __init__(self, bw: int, sf: int, rows: list[TResults]):
        self.bw = bw
        self.sf = sf
        self.rows = np.array(rows)

    def add_row(self, t_results: TResults):
        np.append(self.rows, t_results)
    
    def to_string(self):
        return f"Spreading factor {self.sf}"

class LoRaResult():
    def __init__(self, exp_name: str, config_results: list[ConfigResult]):
        self.exp_name = exp_name
        self.t_labels = [f"T{row.T_id}" for row in config_results[0].rows]
        self.t_ids = [row.T_id for row in config_results[0].rows]
        self.config_results = np.array(config_results)