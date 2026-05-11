from datetime import datetime

class MeasurementGroup():
    readings = {}
    def __init__(self, station_id, pm1: float, pm25: float, noise: float):
        self.station_id = station_id
        self.readings["PM2.5"] = pm25
        self.readings["PM1"] = pm1
        self.readings["Noise"] = noise
        self.timestamp = datetime.now()
        