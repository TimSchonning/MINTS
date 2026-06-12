import { collection, deleteDoc, doc, GeoPoint, getDoc, getDocs, query, setDoc, Timestamp, updateDoc } from "firebase/firestore";
import { db } from "./database_connection";
import { Station } from "./classes/station";

const STATION_COLLECTION = 'Stations'; // The name of the collection in firebase containing station information.

/**
 * IMPORTANT: This function can not be used from the web application as Firebase rules does not allow creation of documents
 * from the web application. In the case that the rules are changed this function can be used to create a station.
 * @param station_id - the id of the new station.
 * @param position - the position of the station in latitude and longitude.
 */
export async function create_station(station_id: string, position: { lat: number; lng: number }) {
    try {
        const stationRef = doc(db, STATION_COLLECTION, station_id);
        console.log("try create");
        await setDoc(stationRef, {
            station_id: station_id,
            position: new GeoPoint(position.lat, position.lng),
        });
        console.log('Station created:', station_id);
    } catch (error) {
        console.error('Error creating station:', error);
        throw error;
    }
}

/**
 * Reads a station from the database.
 * @param station_id - the id of the station to read.
 * @returns the found firebase document data or null.
 */
export async function read_station_position(station_id: string) {
    try {
        const stationRef = doc(db, STATION_COLLECTION, station_id);
        const stationSnap = await getDoc(stationRef);

        if (stationSnap.exists()) {
            return stationSnap.data().position;
        } else {
            console.warn('Station not found:', station_id);
            return null;
        }
    } catch (error) {
        console.error('Error reading station position:', error);
        throw error;
    }
}

/**
 * IMPORTANT: This function can not be used from the web application as Firebase rules does not allow creation of documents
 * from the web application. In the case that the rules are changed this function can be used to update a station.
 * @param station_id - id of the targeted station
 * @param position - the new position in latitude and longitude.
 */
export async function update_station(station_id: string, position: { lat: number; lng: number }) {
    try {
        const stationRef = doc(db, STATION_COLLECTION, station_id);
        await updateDoc(stationRef, {
            position,
            updated_at: Timestamp.now()
        });
        console.log('Station updated:', station_id);
    } catch (error) {
        console.error('Error updating station:', error);
        throw error;
    }
}

/**
 * IMPORTANT: This function can not be used from the web application as Firebase rules does not allow deletion of documents
 * from the web application. In the case that the rules are changed this function can be used to delete a station.
 * @param station_id - the id of the station to delete.
 */
export async function delete_station(station_id: string) {
    try {
        const stationRef = doc(db, STATION_COLLECTION, station_id);
        await deleteDoc(stationRef);
        console.log('Station deleted:', station_id);
    } catch (error) {
        console.error('Error deleting station:', error);
        throw error;
    }
}

/**
 * Gets all stations stored in the database.
 * @returns a promise of an array of stations.
 */
export async function get_all_stations(): Promise<Station[]> {
    try {
        const snapshot = await getDocs(collection(db, STATION_COLLECTION))
        let stations = snapshot.docs.map((doc) => Station.fromDocument(doc));
        return stations;
    } catch (error) {
        console.error('Error fetching all stations: ', error);
        throw error;
    }
}