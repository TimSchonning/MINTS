import { initializeApp, getApp, getApps } from "firebase/app";
import { Firestore, getFirestore } from "firebase/firestore";
import { Auth, getAuth, signInAnonymously } from "firebase/auth";

/*import 'dotenv/config';
const firebaseConfig = {
    // This check works in both Vite and Node
    apiKey: import.meta?.env?.VITE_FIREBASE_API_KEY || process.env.VITE_FIREBASE_API_KEY,
    authDomain: import.meta?.env?.VITE_FIREBASE_AUTH_DOMAIN || process.env.VITE_FIREBASE_AUTH_DOMAIN,
    projectId: import.meta?.env?.VITE_FIREBASE_PROJECT_ID || process.env.VITE_FIREBASE_PROJECT_ID,
    storageBucket: import.meta?.env?.VITE_FIREBASE_STORAGE_BUCKET || process.env.VITE_FIREBASE_STORAGE_BUCKET,
    messagingSenderId: import.meta?.env?.VITE_FIREBASE_MESSAGING_SENDER_ID || process.env.VITE_FIREBASE_MESSAGING_SENDER_ID,
    appId: import.meta?.env?.VITE_FIREBASE_APP_ID || process.env.VITE_FIREBASE_APP_ID
};*/

const firebaseConfig = {
    // Vite uses import.meta.env instead of process.env
    apiKey: import.meta.env.VITE_FIREBASE_API_KEY,
    authDomain: import.meta.env.VITE_FIREBASE_AUTH_DOMAIN,
    projectId: import.meta.env.VITE_FIREBASE_PROJECT_ID,
    storageBucket: import.meta.env.VITE_FIREBASE_STORAGE_BUCKET,
    messagingSenderId: import.meta.env.VITE_FIREBASE_MESSAGING_SENDER_ID,
    appId: import.meta.env.VITE_FIREBASE_APP_ID
};
const app = getApps().length == 0 ? initializeApp(firebaseConfig) : getApp();

export const db: Firestore = getFirestore(app);
export const auth: Auth = getAuth(app);

export async function verifySignedIn() {

    if (auth.currentUser == null) {
        await signInAnonymously(auth);
        console.log("Anonymous sign in complete!");
    }
}

verifySignedIn();