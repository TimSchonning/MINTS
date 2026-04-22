import firebase_admin
from firebase_admin import credentials, firestore
from datetime import datetime

cred = credentials.Certificate("path/to/serviceAccountKey.json")
firebase_admin.initialize_app(cred)

db = firestore.client()

MEASUREMENT_COLLECTION = "Measurements"

def create_measurement(
    measurement_id: str,
    station_id: str,
    sensor_type_id: str,
    value: float,
    date: datetime,
):
    try:
        measurement_ref = db.collection(MEASUREMENT_COLLECTION).document(measurement_id)
        measurement_ref.set({
            "measurement_id": measurement_id,
            "station_id": station_id,
            "sensor_type_id": sensor_type_id,
            "timestamp": date,
            "value": value,
        })
        print(f"Measurement created: {measurement_id}")
    except Exception as error:
        print("Error creating measurement:", error)
        raise