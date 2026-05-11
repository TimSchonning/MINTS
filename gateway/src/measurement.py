from datetime import datetime

class MeasurementGroup():
    readings = {}
    def __init__(self, station_id, pm1, pm25, noise):
        self.station_id = station_id
        self.readings["PM2.5"] = pm25
        self.readings["PM5"] = pm1
        self.readings["Noise"] = noise
        self.timestamp = datetime.now()
        