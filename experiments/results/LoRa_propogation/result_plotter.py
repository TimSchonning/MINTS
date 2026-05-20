import matplotlib.pyplot as plt
import numpy as np
from lora_result import LoRaResult, TResults
from plot_ready.experiment1 import *
from plot_ready.experiment2 import *
from plot_ready.experiment3 import *

value_plot_configs = {
    "PL": {
        "label": "Packet loss (%)",
        "y_lim": [0, 100],
    },
    "RSSI": {
        "label": "Mean RSSI (dBm)",
        "y_lim": [0, 100],
    },
    "SNR": {
        "label": "Mean SNR (dB)",
        "y_lim": [0, 100],
    },
}


data: LoRaResult = experiment3_bw250
plot_settings = value_plot_configs["PL"]

def main():
    fig, ax = plt.subplots(figsize=(8, 8))
    fig.tight_layout()
    plt.title(data.exp_name, fontsize=18)

    ax.set_xlabel("Transmitter location", fontsize=20)
    ax.set_ylabel(plot_settings["label"], fontsize=20)
    ax.set_ylim(ymin=plot_settings["y_lim"][0], ymax=plot_settings["y_lim"][1])
    ax.grid()
    
    t_labels = data.t_labels
    t_values = np.array(data.t_ids)

    ax.set_xticks(t_values)
    ax.set_xticklabels(t_labels, fontsize=18)
    ax.tick_params(axis='y', labelsize=18)

    bar_width = 0.2
    for i, config in enumerate(data.config_results):
        config: ConfigResult
        y_values = np.array([row.PL for row in config.rows])
        ax.bar(
        t_values + (i + 0.5) * (bar_width),
        y_values,
        width=bar_width,
        label=config.to_string()
    )
        
    ax.legend(fontsize=18, loc="upper left")
    fig.show()
    print("Type 'y' to save the figure: ")
    should_save = input()
    if should_save.lower().strip() == "y":
        img_path = f"plots/{data.exp_name}.png"
        plt.savefig(img_path, dpi=300, bbox_inches="tight")

        print(f"Saved figure as '{img_path}'")


if __name__ == "__main__":
    main()