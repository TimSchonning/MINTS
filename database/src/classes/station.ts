import { GeoPoint, QueryDocumentSnapshot } from "firebase/firestore";
import { Measurement } from "./measurement";

interface AvgAccumulator {
    count: number;
    sum: number;
}

export class Station {
    id: string;
    measurements: Measurement[] = [];
    position: GeoPoint;
    constructor(id: string, position: GeoPoint) {
        this.id = id;
        this.position = position;
    }

    public static fromDocument(doc: QueryDocumentSnapshot): Station {
        const data = doc.data();
        let station = new Station(doc.id, data["position"]);
        return station;
    }

    add_measurement(new_measurement: Measurement) {
        this.measurements.push(new_measurement);
    }

    public toString(): String {
        return `Station Id: ${this.id} Lat: ${this.position.latitude} Lng: ${this.position.longitude} Num_Measurements: ${this.measurements.length}`;
    }

    public copy_without_measurements(): Station {
        return new Station(this.id, this.position);
    }

    public calc_avg_measurements(): Map<string, number> {
        const accumulator: Map<string, AvgAccumulator> = new Map();

        this.measurements.forEach((measurement) => {
            let entry = accumulator.get(measurement.sensor_type);

            if (!entry) {
                accumulator.set(measurement.sensor_type, {
                    count: 1,
                    sum: measurement.value
                });
            } else {
                entry.count += 1;
                entry.sum += measurement.value;
            }
        });

        const resultMap: Map<string, number> = new Map();
        accumulator.forEach((data, sensorType) => {
            resultMap.set(sensorType, data.sum / data.count);
        });

        return resultMap;
    }
}