import { deleteDoc, doc, getDoc, setDoc, Timestamp, updateDoc } from "firebase/firestore";
import { db } from "./database_connection";

export async function create_measurementType(
    measurementType_id: number,
    measurement_type: any,
    low_value: number,
    medium_value: number,
    high_value: number
) {
    try {
        const typeRef = doc(db, 'measurement_types', measurementType_id.toString());
        await setDoc(typeRef, {
            measurementType_id,
            measurement_type,
            low_value,
            medium_value,
            high_value,
            created_at: Timestamp.now()
        });
        console.log('Measurement type created:', measurementType_id);
    } catch (error) {
        console.error('Error creating measurement type:', error);
        throw error;
    }
}

export async function read_measurementType_data(measurementType_id: number) {
    try {
        const typeRef = doc(db, 'measurement_types', measurementType_id.toString());
        const typeSnap = await getDoc(typeRef);

        if (typeSnap.exists()) {
            return typeSnap.data();
        } else {
            console.warn('Measurement type not found:', measurementType_id);
            return null;
        }
    } catch (error) {
        console.error('Error reading measurement type data:', error);
        throw error;
    }
}

export async function update_measurementType_data(
    measurementType_id: number,
    measurement_type: any,
    low_value: number,
    medium_value: number,
    high_value: number
) {
    try {
        const typeRef = doc(db, 'measurement_types', measurementType_id.toString());
        await updateDoc(typeRef, {
            measurement_type,
            low_value,
            medium_value,
            high_value,
            updated_at: Timestamp.now()
        });
        console.log('Measurement type updated:', measurementType_id);
    } catch (error) {
        console.error('Error updating measurement type data:', error);
        throw error;
    }
}

export async function delete_measurementType(measurementType_id: number) {
    try {
        const typeRef = doc(db, 'measurement_types', measurementType_id.toString());
        await deleteDoc(typeRef);
        console.log('Measurement type deleted:', measurementType_id);
    } catch (error) {
        console.error('Error deleting measurement type:', error);
        throw error;
    }
}