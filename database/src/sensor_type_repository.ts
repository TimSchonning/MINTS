import { deleteDoc, doc, getDoc, setDoc, Timestamp, updateDoc } from "firebase/firestore";
import { db } from "./database_connection";

export async function create_sensor_type(
    sensor_type_id: number,
    sensor_type: any,
    low_value: number,
    medium_value: number,
    high_value: number
) {
    try {
        const typeRef = doc(db, 'sensor_types', sensor_type_id.toString());
        await setDoc(typeRef, {
            sensor_type_id,
            sensor_type,
            low_value,
            medium_value,
            high_value,
            created_at: Timestamp.now()
        });
        console.log('Measurement type created:', sensor_type_id);
    } catch (error) {
        console.error('Error creating measurement type:', error);
        throw error;
    }
}

export async function read_sensor_type_data(sensor_type_id: number) {
    try {
        const typeRef = doc(db, 'sensor_types', sensor_type_id.toString());
        const typeSnap = await getDoc(typeRef);

        if (typeSnap.exists()) {
            return typeSnap.data();
        } else {
            console.warn('Measurement type not found:', sensor_type_id);
            return null;
        }
    } catch (error) {
        console.error('Error reading measurement type data:', error);
        throw error;
    }
}

export async function update_sensor_type_data(
    sensor_type_id: number,
    sensor_type: any,
    low_value: number,
    medium_value: number,
    high_value: number
) {
    try {
        const typeRef = doc(db, 'sensor_types', sensor_type_id.toString());
        await updateDoc(typeRef, {
            sensor_type,
            low_value,
            medium_value,
            high_value,
            updated_at: Timestamp.now()
        });
        console.log('Measurement type updated:', sensor_type_id);
    } catch (error) {
        console.error('Error updating measurement type data:', error);
        throw error;
    }
}

export async function delete_sensor_type(sensor_type_id: number) {
    try {
        const typeRef = doc(db, 'sensor_types', sensor_type_id.toString());
        await deleteDoc(typeRef);
        console.log('Measurement type deleted:', sensor_type_id);
    } catch (error) {
        console.error('Error deleting measurement type:', error);
        throw error;
    }
}