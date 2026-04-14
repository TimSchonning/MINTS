import { Interval, type Station } from "@my-app/database";
import { load_interval } from "./map_controller";

function add_hours(date: Date, hours: number): Date {
    return new Date(date.getTime() + hours * 60 * 60 * 1000);
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

    private is_date_loaded(time: Date): boolean {
        if (this.loaded_interval == undefined) {
            return false;
        }
        return this.loaded_interval.contains_date(time); //TODO: Add checks that all date within resolution is also in the interval.
    }

    async get_measurement_data(time: Date): Promise<Station[]> {
        if (!this.is_date_loaded(time)) {
            // Preload from database.
            const interval_to_load = new Interval(
                add_hours(time, -this.hours_to_preload),
                add_hours(time, this.hours_to_preload));
            this.loaded_data = await load_interval(interval_to_load);
            this.loaded_interval = interval_to_load;
        }

        // TODO: Pickout measurements from the loaded data around the requested time.
        return [];
    }
}