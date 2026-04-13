import { QueryDocumentSnapshot } from "firebase/firestore";

export class SensorType {
    sensor_id: string;
    low: number;
    high: number;
    constructor(sensor_id: string, low: number, high: number) {
        this.sensor_id = sensor_id;
        if (low > high) {
            this.low = high;
            this.high = low;
        } else {
            this.low = low;
            this.high = high;
        }
    }

    public static fromDocument(doc: QueryDocumentSnapshot) {
        const data = doc.data();
        return new SensorType(doc.id, data['low'], data['high']);
    }

    public toString() {
        return `Sensor type: ${this.sensor_id} [${this.low}-${this.high}]`;
    }
}