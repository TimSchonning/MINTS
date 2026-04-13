import { DocumentReference, QueryDocumentSnapshot, Timestamp } from "firebase/firestore";

export class Measurement {
    sensor_type: string;
    timestamp: Timestamp;
    value: number;
    station_id: string | undefined;

    constructor(sensor_type: string, value: number, timestamp: Timestamp) {
        this.sensor_type = sensor_type;
        this.value = value;
        this.timestamp = timestamp;
    }

    public static fromDocument(doc: QueryDocumentSnapshot): Measurement {
        const data = doc.data();
        let measurement = new Measurement(doc.id, data["value"], data["timestamp"]);
        measurement.station_id = data["station_id"];
        return measurement;
    }

    public toString(): string {
        return `M: ${this.sensor_type} - Value: ${this.value} - Timestamp: ${this.timestamp.toDate().toDateString()}`;
    }
}