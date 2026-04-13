import { collection, deleteDoc, doc, GeoPoint, getDoc, getDocs, query, setDoc, Timestamp, updateDoc } from "firebase/firestore";
import { db } from "./database_connection";
import { Station } from "./classes/station";

const STATION_COLLECTION = 'Stations';

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

export async function get_all_stations(): Promise<Station[]> {
    try {
        const snapshot = await getDocs(collection(db, STATION_COLLECTION))
        let stations = snapshot.docs.map((doc) => Station.fromDocument(doc));
        return stations;
    } catch (error) {
        console.error('Error fetchign all stations: ', error);
        throw error;
    }
}