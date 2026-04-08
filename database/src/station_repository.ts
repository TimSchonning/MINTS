import { deleteDoc, doc, getDoc, setDoc, Timestamp, updateDoc } from "firebase/firestore";
import { db } from "./database_connection";

export async function create_station(station_id: number, position: { lat: number; lng: number }) {
    try {
        const stationRef = doc(db, 'stations', station_id.toString());
        await setDoc(stationRef, {
            station_id,
            position,
            created_at: Timestamp.now()
        });
        console.log('Station created:', station_id);
    } catch (error) {
        console.error('Error creating station:', error);
        throw error;
    }
}

export async function read_station_position(station_id: number) {
    try {
        const stationRef = doc(db, 'stations', station_id.toString());
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

export async function update_station(station_id: number, position: { lat: number; lng: number }) {
    try {
        const stationRef = doc(db, 'stations', station_id.toString());
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

export async function delete_station(station_id: number) {
    try {
        const stationRef = doc(db, 'stations', station_id.toString());
        await deleteDoc(stationRef);
        console.log('Station deleted:', station_id);
    } catch (error) {
        console.error('Error deleting station:', error);
        throw error;
    }
}