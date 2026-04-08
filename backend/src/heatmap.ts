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

export const testData = writable([
//   { lat: 59.843905, lng: 17.635488, intensity: 1 },
  { lat: 59.844905, lng: 17.636488, intensity: 40 },
  { lat: 59.845905, lng: 17.637488, intensity: 60 },
  { lat: 59.846905, lng: 17.638488, intensity: 1000 }
]);

// Array of exactly 1440 coordinates (one per minute in a 24-hour day)
type CoordForOneDay = Heatpoint[] & { readonly length: 1440 };
    
function create_coordinates_heatmap(): Heatpoint[] {
    return [];
}

function create_coordinates_for_one_day(): CoordForOneDay {
    return new Array(1440).fill({ lat: 0, lng: 0, intensity: 0 }) as CoordForOneDay;
}

function create_heatmap_layer(): void {
    // stub
}

export function addLayer(item: string): void {
    testData.set([{ lat: 59.843905, lng: 17.635488, intensity: 1 }])
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