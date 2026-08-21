import { and, collection, deleteDoc, doc, getDoc, getDocs, query, setDoc, Timestamp, updateDoc, where } from "firebase/firestore";
import { db } from "./database_connection";
import { Interval } from "./classes/interval";
import { Station } from "./classes/station";
import { Measurement } from "./classes/measurement";

const MEASUREMENT_COLLECTION = 'Measurements'; // The name of the firebase collection containing measurements.

/**
 * IMPORTANT: This function can not be used from the web application as Firebase rules does not allow creation of documents
 * from the web application. In the case that the rules are changed this function can be used to create a measurement.
 * @param measurement_id - the id of the new measurement.
 * @param station_id - the id of the station the measurement was taken by.
 * @param sensor_type_id - the id of the type of measurement type.
 * @param value - the measurement value.
 * @param date - the time the measurement was taken.
 */
export async function create_measurement(
    measurement_id: string,
    station_id: string,
    sensor_type_id: string,
    value: number,
    date: Date,
) {
    try {
        const measurementRef = doc(db, MEASUREMENT_COLLECTION, measurement_id);
        await setDoc(measurementRef, {
            measurement_id: measurement_id,
            station_id: station_id,
            sensor_type_id: sensor_type_id,
            timestamp: Timestamp.fromDate(date),
            value: value,
        });
        console.log('Measurement created:', measurement_id);
    } catch (error) {
        console.error('Error creating measurement:', error);
        throw error;
    }
}

/**
 * Can be used from the web application. Gets the document for a specific measurement id.
 * @param measurement_id - the measurement id to read.
 * @returns promise the firebase document.
 */
export async function read_measurement_data(measurement_id: string) {
    try {
        const measurementRef = doc(db, MEASUREMENT_COLLECTION, measurement_id);
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

/**
 * IMPORTANT: This function can not be used from the web application as Firebase rules does not allow updating of documents
 * from the web application. In the case that the rules are changed this function can be used to update a measurement.
 * @param measurement_id - the id of the measurement to update.
 * @param station_id - the id of the station the measurement was taken by.
 * @param sensor_type_id - the id of the type of measurement type.
 * @param value - the measurement value.
 * @param date - the time the measurement was taken.
 */
export async function update_measurement_data(
    measurement_id: string,
    station_id: string,
    value: number,
    timestamp: Date,
    sensor_type_id: string,
) {
    try {
        const measurementRef = doc(db, MEASUREMENT_COLLECTION, measurement_id);
        await updateDoc(measurementRef, {
            station_id,
            value,
            timestamp: Timestamp.fromDate(timestamp),
            sensor_type_id,
        });
        console.log('Measurement updated:', measurement_id);
    } catch (error) {
        console.error('Error updating measurement data:', error);
        throw error;
    }
}

/**
 * IMPORTANT: This function can not be used from the web application as Firebase rules does not allow deletion of documents
 * from the web application. In the case that the rules are changed this function can be used to delete a measurement.
 * @param measurement_id - the id of the measurement to delete.
 */
export async function delete_measurement(measurement_id: string) {
    try {
        const measurementRef = doc(db, MEASUREMENT_COLLECTION, measurement_id);
        await deleteDoc(measurementRef);
        console.log('Measurement deleted:', measurement_id);
    } catch (error) {
        console.error('Error deleting measurement:', error);
        throw error;
    }
}

/**
 * Gets an array containing all measurements in the database that are within the given time interval.
 * @param interval - the time interval.
 * @returns promise of an array of measurements.
 */
export async function get_measurements_in_interval(interval: Interval): Promise<Measurement[]> {
    try {
        const q = query(collection(db, MEASUREMENT_COLLECTION),
            where("timestamp", ">=", interval.start),
            where("timestamp", "<=", interval.end));
        const snapshot = await getDocs(q);
        let measurements = snapshot.docs.map((doc) => Measurement.fromDocument(doc));
        return measurements;
    } catch (error) {
        console.error('Error fetching measurements in an interval: ', error);
        throw error;
    }
}