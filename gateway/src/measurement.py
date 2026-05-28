from datetime import datetime
from datetime import timedelta
import zoneinfo

NODE_SAMPLE_WINDOW_S = 600

time_zone = zoneinfo.ZoneInfo("Europe/Stockholm")

class MeasurementGroup():
    readings = {}
    def __init__(self, batch_nr, station_id, pm1, pm25, noise):
        self.station_id = station_id
        self.readings["PM2.5"] = pm25
        self.readings["PM1"] = pm1
        self.readings["Noise"] = noise
        self.timestamp = (datetime.now(time_zone) - timedelta(seconds=(int(batch_nr) * NODE_SAMPLE_WINDOW_S))).replace(second=0, microsecond=0)
        