from databaseConnection import DbConnection
from measurement import MeasurementGroup


db_connection = DbConnection()

station_id = "Mock 1"
pm10 = 10,
pm25 = 6,
noise = 420
measurement_group = MeasurementGroup(station_id, pm10, pm25, noise)

print(f"Attempting to save measurements for station ID: {station_id}, PM10: {pm10}, PM2.5: {pm25}, Noise: {noise}")
db_connection.save_measurements(measurement_group)

