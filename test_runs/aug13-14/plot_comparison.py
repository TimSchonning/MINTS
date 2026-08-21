from matplotlib import dates
import matplotlib.pyplot as plt
import pandas as pd

def load_data():
    official_data = pd.read_csv(
        "official_data.csv",
        skiprows=2,
        names=["time", "pm2_5"]
    )
    official_data["time"] = pd.to_datetime(official_data["time"])
    data = pd.read_csv("our_raw_data.csv")
    data["time"] = pd.to_datetime(data["time"])

    return official_data, data

def clean_data(data):
    return data[data["pm2_5"] != 254]

def plot_data(official_data, hourly_avg):
    # Start of our measurement
    start_time = hourly_avg.index[0]

    # Shift official data so that its first measurement
    # starts at the same time as our data
    official_time = (
        official_data["time"]
        - official_data["time"].iloc[0]
        + start_time
    )

    plt.figure(figsize=(10, 5))

    plt.plot(
        official_time,
        official_data["pm2_5"],
        label="Kungsgatan mätstation"
    )

    plt.plot(
        hourly_avg.index,
        hourly_avg.values,
        label="MINTS"
    )

    plt.xlabel("Time")
    plt.ylabel("PM2.5 (µg/m³)")
    plt.title("Hourly average PM2.5")

    # Format datetime axis
    plt.gca().xaxis.set_major_locator(
        dates.HourLocator(interval=1)
    )

    plt.gca().xaxis.set_major_formatter(
        dates.DateFormatter("%H:%M")
    )

    plt.xticks(rotation=45)

    plt.legend()
    plt.tight_layout()
    plt.show()



def main():
    official_data, raw_data = load_data()
    cleaned_data = clean_data(raw_data)

    hourly = cleaned_data.groupby(cleaned_data["time"].dt.floor("h"))
    hourly_avg = hourly["pm2_5"].mean()

    plot_data(official_data, hourly_avg)

    


if __name__ == "__main__":
    main()

