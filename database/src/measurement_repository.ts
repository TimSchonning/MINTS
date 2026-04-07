import { deleteDoc, doc, getDoc, setDoc, Timestamp, updateDoc } from "firebase/firestore";
import { db } from "./database_connection";

export async function create_measurement(
    measurement_id: number,
    station_id: number,
    value: any,
    timestamp: Date,
    measurement_type: any
) {
    try {
        const measurementRef = doc(db, 'measurements', measurement_id.toString());
        await setDoc(measurementRef, {
            measurement_id,
            station_id,
            value,
            timestamp: Timestamp.fromDate(timestamp),
            measurement_type,
            created_at: Timestamp.now()
        });
        console.log('Measurement created:', measurement_id);
    } catch (error) {
        console.error('Error creating measurement:', error);
        throw error;
    }
}

export async function read_measurement_data(measurement_id: number) {
    try {
        const measurementRef = doc(db, 'measurements', measurement_id.toString());
        const measurementSnap = await getDoc(measurementRef);

        if (measurementSnap.exists()) {
            return measurementSnap.data();
        } else {
            console.warn('Measurement not found:', measurement_id);
            return null;
        }
    } catch (error) {
        console.error('Error reading measurement data:', error);
        throw error;
    }
}

export async function update_measurement_data(
    measurement_id: number,
    station_id: number,
    value: any,
    timestamp: Date,
    measurement_type: any
) {
    try {
        const measurementRef = doc(db, 'measurements', measurement_id.toString());
        await updateDoc(measurementRef, {
            station_id,
            value,
            timestamp: Timestamp.fromDate(timestamp),
            measurement_type,
            updated_at: Timestamp.now()
        });
        console.log('Measurement updated:', measurement_id);
    } catch (error) {
        console.error('Error updating measurement data:', error);
        throw error;
    }
}

export async function delete_measurement(measurement_id: number) {
    try {
        const measurementRef = doc(db, 'measurements', measurement_id.toString());
        await deleteDoc(measurementRef);
        console.log('Measurement deleted:', measurement_id);
    } catch (error) {
        console.error('Error deleting measurement:', error);
        throw error;
    }
}