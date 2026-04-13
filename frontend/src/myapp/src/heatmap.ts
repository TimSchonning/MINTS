// functions to edit heatmap
import { writable } from 'svelte/store';
import type { FeatureCollection, Point } from 'geojson';

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

export const Data = writable([]);

export const testData = writable([
//   { lat: 59.843905, lng: 17.635488, intensity: 1 },
  { lat: 59.844905, lng: 17.636488, intensity: 40 },
  { lat: 59.845905, lng: 17.637488, intensity: 60 },
  { lat: 59.846905, lng: 17.638488, intensity: 80 }
]);

// Array of exactly 1440 coordinates (one per minute in a 24-hour day)
type CoordForOneDay = Heatpoint[] & { readonly length: 1440 };

function normalize_weight(intensity: number, lowval: number, medval: number, highval: number): number {
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

function create_coordinates_for_one_day(): CoordForOneDay {
    return new Array(1440).fill({ lat: 0, lng: 0, intensity: 0 }) as CoordForOneDay;
}

function create_heatmap_layer(): void {
    // stub
}

export function addLayer(item: string): void {
    // testData.update(data => [...data, { lat: 59.843905, lng: 17.635488, intensity: 1 }]);
    testData.update(data => [...data, create_coordinates_heatmap(59.843905, 17.635488, 1)]);
}

export function removeLayer(item: string): void {
    // stub
}

export function startAnimation(): void {
    // stub
}

export function pauseAnimation(): void {
    // stub
}