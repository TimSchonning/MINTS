import { doc, writeBatch, GeoPoint, Timestamp, collection, query, where, getDocs, DocumentSnapshot } from "firebase/firestore";
import { auth, db, verifySignedIn } from "./database_connection";
import { Interval } from "./classes/interval";
import { get_all_sensor_types } from "./sensor_type_repository";
import { get_all_stations } from "./station_repository";
import { getAuth } from "firebase/auth";

/**
 * Adds N number of mock stations to Firestore in a single atomic batch.
 * @param n Number of mock stations to create
 */
async function create_mock_stations_batch(n: number) {
    await verifySignedIn();
    const batch = writeBatch(db);

    for (let i = 1; i <= n; i++) {
        const mock_id = "Mock " + i.toString();

        const lat = 59.85 + (Math.random() - 0.5) * 0.1;
        const lng = 17.63 + (Math.random() - 0.5) * 0.1;

        const stationRef = doc(db, "Stations", mock_id);

        batch.set(stationRef, {
            station_id: mock_id,
            position: new GeoPoint(lat, lng),
        });
    }

    console.log("ready to commit");
    try {
        await batch.commit();
        console.log(`Successfully committed ${n} mock stations.`);
    } catch (error) {
        console.error('Batch commit failed:', error);
        throw error;
    }
}

async function create_mock_measurements_batch(interval: Interval) {
    await verifySignedIn();
    const batch = writeBatch(db);

    let sensor_types = await get_all_sensor_types();
    let stations = await get_all_stations();

    let count = 0;

    for (let date = interval.start; date <= interval.end; date.setMinutes(date.getMinutes() + 60)) {

        stations.forEach((station) => {
            sensor_types.forEach((sensor_type) => {

                count++;
                let mock_id = "Mock " + count.toString();
                let mock_value = sensor_type.low + Math.random() * (sensor_type.high - sensor_type.low);

                const ref = doc(db, "Measurements", mock_id);
                batch.set(ref, {
                    station_id: station.id,
                    measurement_id: mock_id,
                    sensor_type_id: sensor_type.sensor_id,
                    timestamp: Timestamp.fromDate(date),
                    value: mock_value,
                });
            });
        });
    }

    try {
        await batch.commit();
        console.log(`Successfully committed ${count} mock measurements.`);
    } catch (error) {
        console.error('Batch commit failed:', error);
        throw error;
    }
}

async function changeMeasurementSensorTypeName(oldName: String, newName: String) {
    await verifySignedIn();

    const ref = collection(db, "Measurements");
    const q = query(ref, where("sensor_type_id", "==", oldName));
    const docs = await getDocs(q);
    if (docs.empty) {
        console.log("No docs with the given sensor_type_id found.")
        return;
    } else if (docs.size > 500) {
        console.log(`Attempting to update ${docs.size} documents.`);
        console.log("A batch has a limit of 500 operations, you must split it up.");
        return;
    }
    const batch = writeBatch(db); // Has a limit of 500 operations.
    docs.docs.forEach((doc: DocumentSnapshot) => {
        batch.update(doc.ref, { sensor_type_id: newName });
    });
    console.log(`Trying to update ${docs.size} measurements.`);
    await batch.commit();
    console.log(`Successfully updated ${docs.size} measurements.`);
}

//changeMeasurementSensorTypeName("PM5", "PM1");

//create_mock_stations_batch(10);
//create_mock_measurements_batch(new Interval(new Date(2026, 3, 19), new Date(2026, 3, 20)));