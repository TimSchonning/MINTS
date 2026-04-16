import { Interval, type Station } from "@my-app/database";
import { load_interval, time_resolution } from "./map_controller";

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

    private loading_promise: Promise<void> | null = null;

    /**
     * A class used to preload measurements and quickly select the measurements at a specific time to be displayed on the map.
     * @param resolution the time resolution of loaded measurements in minutes. 
     * For example, if resolution is 15 minutes all measurements within a 15 minute timespan centered around the desired time will be given. 
     * @param hours_to_preload the number of hours of data to preload if the requested time is not already loaded. 
     * Loads data this number of hours both earlier and later than the requested time. 
     * For example, if hours_to_preload is 2 and measurements at 15 PM is requested, data between 13 and 17 PM will be loaded.
     */
    constructor(resolution: number = time_resolution, hours_to_preload: number = 5) {
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

        return this.loaded_interval.contains_date(bounds.start) && this.loaded_interval.contains_date(bounds.end);
    }

    private is_loading_data(): boolean {
        return this.loading_promise != null;
    }

    /**
     * Uses the this.loaded_data field to compile a list to display in the map by selecting only the measurements belonging to the shown time interval.
     * @param shown_interval the interval from where measurements are shown in each station. Calculated in get_measurement_data.
     * @returns the list of all stations and all their measurements in the shown interval.
     */
    private prepare_data(shown_interval: Interval): Station[] {
        const prepared_data: Station[] = [];
        this.loaded_data.forEach((station: Station) => {
            const new_station = station.copy_without_measurements();
            station.measurements.forEach((measurement) => {
                if (shown_interval.contains_date(measurement.timestamp.toDate())) {
                    new_station.add_measurement(measurement);
                }
            });
            prepared_data.push(new_station);
        });
        return prepared_data;
    }

    /**
     * This is the function to use in order to fetch the measurements and stations to be displayed on the map. 
     * If this is the first time fetching data the desired data and a time span around it (determined by the Timelapse's "hours_to_preload") is fetched and cached. 
     * When this function is used it first checks if the requested data for a specific time is already cached and if so returns it quickly,
     * otherwise it is fetched from the database.
     * @param time the time around which to fetch and preload data.
     * @returns a list ready for use in the map. It is a list of stations that 
     * each have a list of measurements that should be displayed for the given time.
     */
    async get_measurement_data(time: Date): Promise<Station[]> {
        const bounds = this.calc_resolution_bounds(time);
        if (!this.is_date_loaded(bounds) && !this.is_loading_data()) {
            // Check if a load is currently in progress.
            console.log(`Requested time: ${time.toLocaleTimeString()} not preloaded, fetching from database.`)
            // Preload from database.
            const interval_to_load = new Interval(
                add_hours(time, -this.hours_to_preload),
                add_hours(time, this.hours_to_preload));
            let load_task = async () => {
                try {
                    console.log(`Preloading new interval: ${interval_to_load.toString()}`);
                    this.loaded_data = await load_interval(interval_to_load);
                    this.loaded_interval = interval_to_load;
                } catch (e) {
                    console.log("Error preloading interval", e);
                } finally {
                    this.loading_promise = null;
                }
            };
            this.loading_promise = load_task();
            await this.loading_promise;
        }
        return this.prepare_data(bounds);
    }
}