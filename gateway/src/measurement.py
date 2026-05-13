from datetime import datetime
from datetime import timedelta

NODE_SAMPLE_WINDOW_S = 900

class MeasurementGroup():
    readings = {}
    def __init__(self, batch_nr, station_id, pm10, pm25, noise):
        self.station_id = station_id
        self.readings["PM2.5"] = pm25
        self.readings["PM1"] = pm1
        self.readings["Noise"] = noise
        self.timestamp = (datetime.now() - timedelta(seconds=(int(batch_nr) * NODE_SAMPLE_WINDOW_S))).replace(second=0, microsecond=0)
        