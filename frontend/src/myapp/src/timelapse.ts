import { Interval, type Station } from "@my-app/database";
import { load_interval } from "./map_controller";

function add_hours(date: Date, hours: number): Date {
    return new Date(date.getTime() + hours * 60 * 60 * 1000);
}

function add_minutes(date: Date, minutes: number): Date {
    return new Date(date.getTime() - minutes * 60 * 1000);
}

export class TimeLapse {
    loaded_data: Station[] = [];
    loaded_interval: Interval | undefined;
    resolution: number;
    hours_to_preload: number;

    /**
     * A class used to preload measurements and quickly select the measurements at a specific time to be displayed on the map.
     * @param resolution the time resolution of loaded measurements in minutes. 
     * For example, if resolution is 15 minutes all measurements within a 15 minute timespan centered around the desired time will be given. 
     * @param hours_to_preload the number of hours of data to preload if the requested time is not already loaded. 
     * Loads data this number of hours both earlier and later than the requested time. 
     * For example, if hours_to_preload is 2 and measurements at 15 PM is requested, data between 13 and 17 PM will be loaded.
     */
    constructor(resolution: number = 15, hours_to_preload: number = 2) {
        this.resolution = resolution;
        this.hours_to_preload = hours_to_preload;
    }

    private calc_resolution_bounds(time: Date): Interval {
        const res_start = add_minutes(time, -this.resolution / 2);
        const res_end = add_minutes(time, this.resolution / 2);
        return new Interval(res_start, res_end);
    }

    private is_date_loaded(bounds: Interval): boolean {
        if (this.loaded_interval == undefined) {
            return false;
        }

        return this.loaded_interval.contains_date(bounds.d1) && this.loaded_interval.contains_date(bounds.d2);
    }

    async get_measurement_data(time: Date): Promise<Station[]> {
        const bounds = this.calc_resolution_bounds(time);
        if (!this.is_date_loaded(bounds)) {
            console.log("Requested time not preloaded, fetching from database.")
            // Preload from database.
            const interval_to_load = new Interval(
                add_hours(time, -this.hours_to_preload),
                add_hours(time, this.hours_to_preload));
            this.loaded_data = await load_interval(interval_to_load);
            this.loaded_interval = interval_to_load;
        }

        const requested_data: Station[] = [];
        this.loaded_data.forEach((station: Station) => {
            const new_station = station.copyWithoutMeasurements();
            station.measurements.forEach((measurement) => {
                if (bounds.contains_date(measurement.timestamp.toDate())) {
                    new_station.add_measurement(measurement);
                }
            });
            requested_data.push(new_station);
        });

        // TODO: Pickout measurements from the loaded data around the requested time.
        return requested_data;
    }
}