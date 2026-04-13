import { DocumentReference } from "firebase/firestore";

export class Measurement {
    sensor_type: string;
    value: number;

    constructor(sensor_type: string, value: number) {
        this.sensor_type = sensor_type;
        this.value = value;
    }
}