import firebase_admin
from firebase_admin import credentials, firestore
from datetime import datetime

from measurement import MeasurementGroup

cred = credentials.Certificate("secrets/firebase_config.json")
MEASUREMENT_COLLECTION = "Measurements"

class DbConnection():
    def __init__(self): 
        firebase_admin.initialize_app(cred)
        self.db = firestore.client()

    def save_measurements(self, measurements: MeasurementGroup):
        try:
            batch = self.db.batch()
            for sensor_type_id, value in measurements.readings.items():
                ref = self.db.collection(MEASUREMENT_COLLECTION).document()
                batch.set(ref, {
                    "measurement_id": ref.id,
                    "station_id": measurements.station_id,
                    "sensor_type_id": sensor_type_id,
                    "timestamp": measurements.timestamp,
                    "value": value,
                })
            batch.commit()
            print("Saving successful!")
        except Exception as e:
            print(f"Error saving measurements: {e}")
        

        