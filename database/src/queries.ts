// Firebase database queries
/*import { initializeApp } from 'firebase/app';
import {
    getFirestore,
    Firestore,
    doc,
    setDoc,
    getDoc,
    updateDoc,
    deleteDoc,
    collection,
    query,
    where,
    getDocs,
    Timestamp
} from 'firebase/firestore';

let db: Firestore;

// Initialize Firebase (make sure to set these in your environment variables)
const firebaseConfig = {
    apiKey: process.env.FIREBASE_API_KEY,
    authDomain: process.env.FIREBASE_AUTH_DOMAIN,
    projectId: process.env.FIREBASE_PROJECT_ID,
    storageBucket: process.env.FIREBASE_STORAGE_BUCKET,
    messagingSenderId: process.env.FIREBASE_MESSAGING_SENDER_ID,
    appId: process.env.FIREBASE_APP_ID
};

export async function connect_to_db() {
    try {
        initializeApp(firebaseConfig);
        db = getFirestore();
        console.log('Connected to Firebase');
    } catch (error) {
        console.error('Error connecting to Firebase:', error);
        throw error;
    }
}

// CRUD operations for stations
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

// CRUD operations for measurement data
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

// CRUD operations for measurements type data
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
}*/