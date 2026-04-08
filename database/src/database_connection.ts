import { initializeApp } from "firebase/app";
import { Firestore, getFirestore } from "firebase/firestore";

const firebaseConfig = {
    apiKey: process.env.FIREBASE_API_KEY,
    authDomain: process.env.FIREBASE_AUTH_DOMAIN,
    projectId: process.env.FIREBASE_PROJECT_ID,
    storageBucket: process.env.FIREBASE_STORAGE_BUCKET,
    messagingSenderId: process.env.FIREBASE_MESSAGING_SENDER_ID,
    appId: process.env.FIREBASE_APP_ID
};

export let db: Firestore;

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
