import { GeoPoint, QueryDocumentSnapshot } from "firebase/firestore";
import { Measurement } from "./measurement";


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

    public copyWithoutMeasurements(): Station {
        return new Station(this.id, this.position);
    }
}