from datetime import datetime

class MeasurementGroup():
    readings = {}
    def __init__(self, station_id, pm10, pm25, noise):
        self.station_id = station_id
        self.readings["PM2.5"] = pm25
        self.readings["PM5"] = pm10
        self.readings["Noise"] = noise
        self.timestamp = datetime.now()
        