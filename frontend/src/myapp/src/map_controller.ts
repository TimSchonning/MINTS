import { get_all_stations, get_measurements_in_interval, Interval, Measurement } from "@my-app/database";
import type { Station } from "../../../../database/src/classes/station";

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
            console.warn("Measurement found for unknown station id: ${station_id}")
            return;
        }

        station.add_measurement(measurement);
    });
    return stations;
}