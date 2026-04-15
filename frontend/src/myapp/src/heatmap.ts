// functions to edit heatmap
import { writable } from 'svelte/store';
import type { FeatureCollection, Point } from 'geojson';
import test from 'node:test';
import { get_sensor_type_info, load_interval, sensor_type_map, load_sensor_types, shown_date } from './map_controller';
import { TimeLapse } from './timelapse';

type Heatpoint = {
    lat: number;
    lng: number;
    intensity: number;
}

export function toGeoJSON(data: Heatpoint[]): FeatureCollection<Point> {
    return {
        type: 'FeatureCollection',
        features: data.map(point => ({
            type: 'Feature',
            geometry: {
                type: 'Point',
                coordinates: [point.lng, point.lat]
            },
            properties: {
                intensity: point.intensity
            }
        }))
    };
}

const timelapse_controller = new TimeLapse();
const sensors = await load_sensor_types();
const sens_types = Array.from(sensors.keys());

export const Data = writable<Heatpoint[]>([]);

export const testData = writable<Heatpoint[]>([
    //   { lat: 59.843905, lng: 17.635488, intensity: 1 },
    { lat: 59.844905, lng: 17.636488, intensity: 40 },
    { lat: 59.845905, lng: 17.637488, intensity: 60 },
    { lat: 59.846905, lng: 17.638488, intensity: 80 }
]);


function normalize_weight(intensity: number, lowval: number, highval: number): number {
    // returns value between 0-100, where 0 is low and 100 is high
    if (intensity <= lowval) {
        return 0;
    }
    else if (intensity >= highval) {
        return 100;
    }
    else {
        // min-max scaling normalization
        return ((intensity - lowval) / (highval - lowval)) * 100;
    }
}

function create_coordinates_heatmap(lat: number, lng: number, intensity: number): Heatpoint {
    return { lat, lng, intensity };
}

function add_extra_points(data: Heatpoint[]): Heatpoint[] {
    // add extra points around each point to make the heatmap smoother
    const extra_points: Heatpoint[] = [];
    const radius = 0.0005;
    data.forEach(point => {
        for (let i = 0; i < 8; i++) {
            const angle = (i / 8) * 2 * Math.PI;
            const new_lat = point.lat + radius * Math.sin(angle);
            const new_lng = point.lng + radius * Math.cos(angle);
            extra_points.push(create_coordinates_heatmap(new_lat, new_lng, (point.intensity) * 0.5));
        }
    });
    return [...data, ...extra_points];
}

export async function show_heatmap(date: Date): Promise<void> {
    // Process the stations and their measurements to create heatmap data
    const heatmapData: Heatpoint[] = [];
    const data_span = await timelapse_controller.get_measurement_data(date);
    data_span.forEach(station => {
        station.measurements.forEach(measurement => {
            const sensor_type = get_sensor_type_info(measurement.sensor_type);
            if (sensor_type == undefined) {
                console.warn(`Sensor type "${measurement.sensor_type}" is unknown.`);
            }

            if (sensor_type != undefined && sens_types.some(x => x == sensor_type.sensor_id)) {
                const intensity = normalize_weight(measurement.value, sensor_type.low, sensor_type.high);
                heatmapData.push(create_coordinates_heatmap(station.position.latitude, station.position.longitude, intensity));
            }
        });
    });
    const expanded_data = add_extra_points(heatmapData);
    console.log(heatmapData.length)
    Data.set(expanded_data);
}

export function addLayer(item: string): void {
    sens_types.push(item);
    show_heatmap(new Date());
}

export function removeLayer(item: string): void {
    sens_types.splice(sens_types.indexOf(item), 1);
    show_heatmap(new Date());
}

export function startAnimation(): void {
    // stub
}

export function pauseAnimation(): void {
    // stub
}

