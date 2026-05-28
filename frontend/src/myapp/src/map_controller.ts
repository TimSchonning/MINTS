import { get_all_sensor_types, get_all_stations, get_measurements_in_interval, Interval, Measurement, SensorType, Station } from "@my-app/database";
import { SvelteDate } from "svelte/reactivity";
import { verifySignedIn } from "../../../../database/src/database_connection";
import { TimeLapse } from "./timelapse";

/**
 * The date that should be shown on the heatmap.
 */
export const shown_date = new SvelteDate();

/**
 * The time resolution of the heatmap.
 */
export const time_resolution = 60;

/**
 * Maps the string name of the sensor types to the SensorType IDs.
 */
export const sensor_type_map: Map<string, SensorType> = await load_sensor_types();
export const timelapse_controller: TimeLapse = new TimeLapse();

/**
 * Loads an interval around a given time, used for the slider on the heatmap.
 * @param interval the time interval for which data should be loaded.
 * @returns A promise resolving to the list of stations with their measurements.
 */
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

/**
 * Retrieves all sensortypes.
 * @returns An array of all sensortypes.
 */
export function get_sensor_types(): SensorType[] {
    return sensor_type_map.values().toArray();
}

/**
 * A function that retrieves the sensortype id for a given sensortype.
 * @param sensor_type_id a string with the name of the sensortype
 * @returns the id of the sensortype
 */
export function get_sensor_type_info(sensor_type_id: string): SensorType | undefined {
    return sensor_type_map.get(sensor_type_id);
}

/**
 * Loads all sensor types and creates a mapping from their IDs to the sensor type objects.
 * @returns A promise resolving to a map of sensor type IDs to sensor type objects.
 */
export async function load_sensor_types() {
    await verifySignedIn();
    const sensor_types = await get_all_sensor_types();
    const map = new Map<string, SensorType>();
    sensor_types.forEach((sensor_type) => {
        map.set(sensor_type.sensor_id, sensor_type);
    })
    return map;
}