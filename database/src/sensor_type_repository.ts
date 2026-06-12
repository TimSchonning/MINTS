import { collection, deleteDoc, doc, getDoc, getDocs, setDoc, Timestamp, updateDoc } from "firebase/firestore";
import { db } from "./database_connection";
import { SensorType } from "./classes/sensor_type";

const SENSOR_TYPE_COLLECTION = 'SensorTypes'; // The name of the collection in firebase containing sensor type information.

/**
 * IMPORTANT: This function can not be used from the web application as Firebase rules does not allow creation of documents
 * from the web application. In the case that the rules are changed this function can be used to create a sensor type.
 * @param sensor_type_id - the id of the new sensor type.
 * @param low_value - the low threshold for the sensor type.
 * @param high_value - the high threshold for the sensor type.
 */
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

/**
 * Reads a sensor type from the database.
 * @param sensor_type_id - the id of the sensor type to read.
 * @returns the found firebase document data or null.
 */
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

/**
 * IMPORTANT: This function can not be used from the web application as Firebase rules does not allow creation of documents
 * from the web application. In the case that the rules are changed this function can be used to update a sensor type.
 * @param sensor_type_id - the id of the sensor type.
 * @param low_value - the low threshold for the sensor type.
 * @param high_value - the high threshold for the sensor type.
 */
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

/**
 * IMPORTANT: This function can not be used from the web application as Firebase rules does not allow deleting of documents
 * from the web application. In the case that the rules are changed this function can be used to delete a sensor type.
 * @param sensor_type_id - the id of the sensor type.
 */
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

/**
 * Gets a list of all sensor types stored in the database, this function should generally be used once at the start
 * of the web application.
 * @returns a promise of an array of sensor types.
 */
export async function get_all_sensor_types(): Promise<SensorType[]> {
    try {
        const snapshot = await getDocs(collection(db, SENSOR_TYPE_COLLECTION))
        let sensor_types = snapshot.docs.map((doc) => SensorType.fromDocument(doc));
        return sensor_types;
    } catch (error) {
        console.error('Error fetching all sensor types: ', error);
        throw error;
    }
}