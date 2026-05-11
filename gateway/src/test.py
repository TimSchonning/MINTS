from databaseConnection import DbConnection
from measurement import MeasurementGroup


db_connection = DbConnection()

station_id = "Mock 1"
pm1 = 10,
pm25 = 6,
noise = 420
measurement_group = MeasurementGroup(station_id, pm1, pm25, noise)

print(f"Attempting to save measurements for station ID: {station_id}, PM1: {pm1}, PM2.5: {pm25}, Noise: {noise}")
db_connection.save_measurements(measurement_group)

