import { deleteDoc, doc, getDoc, setDoc, Timestamp, updateDoc } from "firebase/firestore";
import { db } from "./database_connection";

const SENSOR_TYPE_COLLECTION = 'SensorTypes';

export async function create_sensor_type(
    sensor_type_id: string,
    low_value: number,
    high_value: number
) {
    try {
        const typeRef = doc(db, SENSOR_TYPE_COLLECTION, sensor_type_id);
        await setDoc(typeRef, {
            sensor_type_id: sensor_type_id,
            low: low_value,
            high: high_value,
        });
        console.log('Sensor type created:', sensor_type_id);
    } catch (error) {
        console.error('Error creating sensor type:', error);
        throw error;
    }
}

export async function read_sensor_type_data(sensor_type_id: string) {
    try {
        const typeRef = doc(db, SENSOR_TYPE_COLLECTION, sensor_type_id);
        const typeSnap = await getDoc(typeRef);

        if (typeSnap.exists()) {
            return typeSnap.data();
        } else {
            console.warn('Sensor type not found:', sensor_type_id);
            return null;
        }
    } catch (error) {
        console.error('Error reading sensor type data:', error);
        throw error;
    }
}

export async function update_sensor_type_data(
    sensor_type_id: string,
    low_value: number,
    high_value: number
) {
    try {
        const typeRef = doc(db, SENSOR_TYPE_COLLECTION, sensor_type_id);
        await updateDoc(typeRef, {
            sensor_type_id: sensor_type_id,
            low: low_value,
            high: high_value,
        });
        console.log('Sensor type updated:', sensor_type_id);
    } catch (error) {
        console.error('Error updating sensor type data:', error);
        throw error;
    }
}

export async function delete_sensor_type(sensor_type_id: string) {
    try {
        const typeRef = doc(db, SENSOR_TYPE_COLLECTION, sensor_type_id);
        await deleteDoc(typeRef);
        console.log('Sensor type deleted:', sensor_type_id);
    } catch (error) {
        console.error('Error deleting sensor type:', error);
        throw error;
    }
}