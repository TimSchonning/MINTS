import { get_all_sensor_types, get_all_stations, get_measurements_in_interval, Interval, Measurement, SensorType, Station } from "@my-app/database";

export const sensor_type_map: Map<string, SensorType> = await load_sensor_types();

export async function load_interval(interval: Interval): Promise<Station[]> {
    const [stations, measurements] = await Promise.all([
        get_all_stations(),
        get_measurements_in_interval(interval)
    ]);

    let station_map = new Map<string, Station>();
    stations.forEach((station: Station) => {
        station_map.set(station.id, station);
    });

    measurements.forEach((measurement: Measurement) => {
        let station_id = measurement.station_id;
        if (station_id == undefined) {
            return;
        }
        let station = station_map.get(station_id);
        if (station == undefined) {
            console.warn(`Measurement found for unknown station id: ${station_id}`)
            return;
        }

        station.add_measurement(measurement);
    });
    return stations;
}

export function get_sensor_type_info(sensor_type_id: string): SensorType | undefined {
    return sensor_type_map.get(sensor_type_id);
}

async function load_sensor_types() {
    const sensor_types = await get_all_sensor_types();
    const map = new Map<string, SensorType>();
    sensor_types.forEach((sensor_type) => {
        map.set(sensor_type.sensor_id, sensor_type);
    })
    return map;
}