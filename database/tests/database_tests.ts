import { describe, it, expect, vi, beforeEach, afterEach } from 'vitest';
import * as db_connection from '../src/database_connection.ts'

import * as station_repo from '../src/station_repository.ts'
import * as measurement_repo from '../src/measurement_repository.ts'
import * as sensor_type_repo from '../src/sensor_type_repository.ts'
import { initializeApp } from 'firebase/app';
import {
  getFirestore,
  doc,
  setDoc,
  getDoc,
  updateDoc,
  deleteDoc,
  Timestamp,
  DocumentReference,
  GeoPoint
} from 'firebase/firestore';
import { AuthCredential, signInAnonymously } from 'firebase/auth';

// Mock Firebase
vi.mock('firebase/app');
vi.mock('firebase/firestore', () => ({
  GeoPoint: vi.fn().mockImplementation((lat, lng) => ({
    latitude: lat,
    longitude: lng,
  })),
  getFirestore: vi.fn(),
  doc: vi.fn(() => 0),
  setDoc: vi.fn(),
  getDoc: vi.fn(),
  updateDoc: vi.fn(),
  deleteDoc: vi.fn(),
  Timestamp: {
    now: vi.fn(),
    fromDate: vi.fn(),
  },
}));
vi.mock('firebase/app', () => ({
  getApp: vi.fn(),
  getApps: vi.fn(() => []),
  initializeApp: vi.fn(),
}));
vi.mock('firebase/auth', () => ({
  getAuth: vi.fn(() => ({
    currentUser: { uid: 'test-user-123' }
  })),
  signInAnonymously: vi.fn(),
}));

describe('Firebase Database CRUD Operations', () => {
  beforeEach(() => {
    vi.clearAllMocks();
  });

  describe('Station CRUD Operations', () => {
    const testStationId = (1).toString();
    const testGeoPoint = new GeoPoint(40.7128, -74.0060);
    const testPosition = { lat: testGeoPoint.latitude, lng: testGeoPoint.longitude };



    describe('Create Station', () => {
      it('should create a station with valid data', async () => {
        const mockSetDoc = vi.mocked(setDoc);

        await station_repo.create_station(testStationId, testPosition);

        expect(mockSetDoc).toHaveBeenCalledWith(
          expect.anything(),
          expect.objectContaining({
            station_id: testStationId,
            position: testGeoPoint,
          })
        );
      });

      it('should handle creation errors', async () => {
        const consoleSpy = vi.spyOn(console, 'error').mockImplementation(() => { });

        const mockSetDoc = vi.mocked(setDoc);
        mockSetDoc.mockRejectedValueOnce(new Error('Permission denied'));

        await expect(
          station_repo.create_station(testStationId, testPosition)
        ).rejects.toThrow('Permission denied');
        consoleSpy.mockRestore();
      });
    });

    describe('Read Station', () => {
      it('should read station position successfully', async () => {
        const mockGetDoc = vi.mocked(getDoc);

        mockGetDoc.mockResolvedValue({
          exists: () => true,
          data: () => ({ position: testPosition })
        } as any);

        const result = await station_repo.read_station_position(testStationId);

        expect(result).toEqual(testPosition);
      });

      it('should return null when station does not exist', async () => {
        const mockGetDoc = vi.mocked(getDoc);
        mockGetDoc.mockResolvedValue({
          exists: () => false,
          data: () => undefined
        } as any);

        const result = await station_repo.read_station_position(testStationId);

        expect(result).toBeNull();
      });

      it('should handle read errors', async () => {
        const consoleSpy = vi.spyOn(console, 'error').mockImplementation(() => { });

        const mockGetDoc = vi.mocked(getDoc);
        mockGetDoc.mockRejectedValueOnce(new Error('Network error'));

        await expect(
          station_repo.read_station_position(testStationId)
        ).rejects.toThrow('Network error');

        consoleSpy.mockRestore();
      });
    });

    describe('Update Station', () => {
      const updatedPosition = { lat: 34.0522, lng: -118.2437 };

      it('should update station position successfully', async () => {
        const mockUpdateDoc = vi.mocked(updateDoc);
        mockUpdateDoc.mockResolvedValue(undefined);

        await station_repo.update_station(testStationId, updatedPosition);

        expect(mockUpdateDoc).toHaveBeenCalledWith(
          expect.anything(),
          expect.objectContaining({
            position: updatedPosition
          })
        );
      });

      it('should include updated_at timestamp', async () => {
        const mockUpdateDoc = vi.mocked(updateDoc);
        mockUpdateDoc.mockResolvedValue(undefined);

        await station_repo.update_station(testStationId, updatedPosition);

        const callArgs = mockUpdateDoc.mock.calls[0][1];
        expect(callArgs).toHaveProperty('updated_at');
      });

      it('should handle update errors', async () => {
        const consoleSpy = vi.spyOn(console, 'error').mockImplementation(() => { });

        const mockUpdateDoc = vi.mocked(updateDoc);
        mockUpdateDoc.mockRejectedValueOnce(new Error('Document not found'));

        await expect(
          station_repo.update_station(testStationId, updatedPosition)
        ).rejects.toThrow('Document not found');
        consoleSpy.mockRestore();
      });
    });

    describe('Delete Station', () => {
      it('should delete station successfully', async () => {
        const mockDeleteDoc = vi.mocked(deleteDoc);
        mockDeleteDoc.mockResolvedValue(undefined);

        await station_repo.delete_station(testStationId);

        expect(mockDeleteDoc).toHaveBeenCalled();
      });

      it('should handle delete errors', async () => {
        const consoleSpy = vi.spyOn(console, 'error').mockImplementation(() => { });

        const mockDeleteDoc = vi.mocked(deleteDoc);
        mockDeleteDoc.mockRejectedValueOnce(new Error('Permission denied'));

        await expect(
          station_repo.delete_station(testStationId)
        ).rejects.toThrow('Permission denied');

        consoleSpy.mockRestore();
      });
    });
  });

  describe('Measurement CRUD Operations', () => {
    const testMeasurementId = (1).toString();
    const testStationId = (1).toString();
    const testValue = 2;
    const testTimestamp = new Date('2025-01-01T12:00:00Z');
    const testSensorTypeId = (1).toString();

    describe('Create Measurement', () => {
      it('should create a measurement with valid data', async () => {
        const mockSetDoc = vi.mocked(setDoc);
        mockSetDoc.mockResolvedValue(undefined);

        await measurement_repo.create_measurement(
          testMeasurementId,
          testStationId,
          testSensorTypeId,
          testValue,
          testTimestamp,
        );

        expect(mockSetDoc).toHaveBeenCalledWith(
          expect.anything(),
          expect.objectContaining({
            measurement_id: testMeasurementId,
            station_id: testStationId,
            value: testValue,
            sensor_type_id: testSensorTypeId
          })
        );
      });

      it('should handle creation errors', async () => {
        const consoleSpy = vi.spyOn(console, 'error').mockImplementation(() => { });

        const mockSetDoc = vi.mocked(setDoc);
        mockSetDoc.mockRejectedValueOnce(new Error('Invalid data'));

        await expect(
          measurement_repo.create_measurement(
            testMeasurementId,
            testStationId,
            testSensorTypeId,
            testValue,
            testTimestamp,
          )
        ).rejects.toThrow('Invalid data');

        consoleSpy.mockRestore();
      });
    });

    describe('Read Measurement', () => {
      it('should read measurement data successfully', async () => {
        const mockGetDoc = vi.mocked(getDoc);
        const mockData = {
          measurement_id: testMeasurementId,
          station_id: testStationId,
          value: testValue,
          sensor_type: testSensorTypeId
        };

        mockGetDoc.mockResolvedValue({
          exists: () => true,
          data: () => mockData
        } as any);

        const result = await measurement_repo.read_measurement_data(testMeasurementId);

        expect(result).toEqual(mockData);
      });

      it('should return null when measurement does not exist', async () => {
        const mockGetDoc = vi.mocked(getDoc);
        mockGetDoc.mockResolvedValue({
          exists: () => false,
          data: () => undefined
        } as any);

        const result = await measurement_repo.read_measurement_data(testMeasurementId);

        expect(result).toBeNull();
      });

      it('should handle read errors', async () => {
        const consoleSpy = vi.spyOn(console, 'error').mockImplementation(() => { });

        const mockGetDoc = vi.mocked(getDoc);
        mockGetDoc.mockRejectedValueOnce(new Error('Read failed'));

        await expect(
          measurement_repo.read_measurement_data(testMeasurementId)
        ).rejects.toThrow('Read failed');

        consoleSpy.mockRestore();
      });
    });

    describe('Update Measurement', () => {
      const updatedValue = 5.5;

      it('should update measurement data successfully', async () => {
        const mockUpdateDoc = vi.mocked(updateDoc);
        mockUpdateDoc.mockResolvedValue(undefined);

        await measurement_repo.update_measurement_data(
          testMeasurementId,
          testStationId,
          updatedValue,
          testTimestamp,
          testSensorTypeId
        );

        expect(mockUpdateDoc).toHaveBeenCalledWith(
          expect.anything(),
          expect.objectContaining({
            value: updatedValue,
            station_id: testStationId
          })
        );
      });

      it('should handle update errors', async () => {
        const consoleSpy = vi.spyOn(console, 'error').mockImplementation(() => { });

        const mockUpdateDoc = vi.mocked(updateDoc);
        mockUpdateDoc.mockRejectedValueOnce(new Error('Update failed'));

        await expect(
          measurement_repo.update_measurement_data(
            testMeasurementId,
            testStationId,
            updatedValue,
            testTimestamp,
            testSensorTypeId
          )
        ).rejects.toThrow('Update failed');
        consoleSpy.mockRestore();
      });
    });

    describe('Delete Measurement', () => {
      it('should delete measurement successfully', async () => {
        const mockDeleteDoc = vi.mocked(deleteDoc);
        mockDeleteDoc.mockResolvedValue(undefined);

        await measurement_repo.delete_measurement(testMeasurementId);

        expect(mockDeleteDoc).toHaveBeenCalled();
      });

      it('should handle delete errors', async () => {
        const consoleSpy = vi.spyOn(console, 'error').mockImplementation(() => { });

        const mockDeleteDoc = vi.mocked(deleteDoc);
        mockDeleteDoc.mockRejectedValueOnce(new Error('Delete failed'));

        await expect(
          measurement_repo.delete_measurement(testMeasurementId)
        ).rejects.toThrow('Delete failed');
        consoleSpy.mockRestore();
      });
    });
  });

  describe('Measurement Type CRUD Operations', () => {
    const testTypeId = 'PM5';
    const testValues = {
      low: 0,
      high: 100
    };

    describe('Create Measurement Type', () => {
      it('should create a measurement type with valid data', async () => {
        const mockSetDoc = vi.mocked(setDoc);
        mockSetDoc.mockResolvedValue(undefined);

        await sensor_type_repo.create_sensor_type(
          testTypeId,
          testValues.low,
          testValues.high
        );

        expect(mockSetDoc).toHaveBeenCalledWith(
          expect.anything(),
          expect.objectContaining({
            sensor_type_id: testTypeId,
            low: testValues.low,
            high: testValues.high
          })
        );
      });

      it('should handle creation errors', async () => {
        const consoleSpy = vi.spyOn(console, 'error').mockImplementation(() => { });

        const mockSetDoc = vi.mocked(setDoc);
        mockSetDoc.mockRejectedValueOnce(new Error('Invalid type'));

        await expect(
          sensor_type_repo.create_sensor_type(
            testTypeId,
            testValues.low,
            testValues.high
          )
        ).rejects.toThrow('Invalid type');

        consoleSpy.mockRestore();
      });
    });

    describe('Read Measurement Type', () => {
      it('should read measurement type data successfully', async () => {
        const mockGetDoc = vi.mocked(getDoc);
        const mockData = {
          sensor_type_id: testTypeId,
          low: testValues.low,
          high: testValues.high
        };

        mockGetDoc.mockResolvedValue({
          exists: () => true,
          data: () => mockData
        } as any);

        const result = await sensor_type_repo.read_sensor_type_data(testTypeId);

        expect(result).toEqual(mockData);
      });

      it('should return null when measurement type does not exist', async () => {
        const mockGetDoc = vi.mocked(getDoc);
        mockGetDoc.mockResolvedValue({
          exists: () => false,
          data: () => undefined
        } as any);

        const result = await sensor_type_repo.read_sensor_type_data(testTypeId);

        expect(result).toBeNull();
      });

      it('should handle read errors', async () => {
        const consoleSpy = vi.spyOn(console, 'error').mockImplementation(() => { });

        const mockGetDoc = vi.mocked(getDoc);
        mockGetDoc.mockRejectedValueOnce(new Error('Read failed'));

        await expect(
          sensor_type_repo.read_sensor_type_data(testTypeId)
        ).rejects.toThrow('Read failed');

        consoleSpy.mockRestore();
      });
    });

    describe('Update Measurement Type', () => {
      const updatedValues = {
        low: 10,
        high: 110
      };

      it('should update measurement type data successfully', async () => {
        const mockUpdateDoc = vi.mocked(updateDoc);
        mockUpdateDoc.mockResolvedValue(undefined);

        await sensor_type_repo.update_sensor_type_data(
          testTypeId,
          updatedValues.low,
          updatedValues.high
        );

        expect(mockUpdateDoc).toHaveBeenCalledWith(
          expect.anything(),
          expect.objectContaining({
            sensor_type_id: testTypeId,
            low: updatedValues.low,
            high: updatedValues.high
          })
        );
      });

      it('should handle update errors', async () => {
        const consoleSpy = vi.spyOn(console, 'error').mockImplementation(() => { });

        const mockUpdateDoc = vi.mocked(updateDoc);
        mockUpdateDoc.mockRejectedValueOnce(new Error('Update failed'));

        await expect(
          sensor_type_repo.update_sensor_type_data(
            testTypeId,
            updatedValues.low,
            updatedValues.high
          )
        ).rejects.toThrow('Update failed');

        consoleSpy.mockRestore();
      });
    });

    describe('Delete Measurement Type', () => {
      it('should delete measurement type successfully', async () => {
        const mockDeleteDoc = vi.mocked(deleteDoc);
        mockDeleteDoc.mockResolvedValue(undefined);

        await sensor_type_repo.delete_sensor_type(testTypeId);

        expect(mockDeleteDoc).toHaveBeenCalled();
      });

      it('should handle delete errors', async () => {
        const consoleSpy = vi.spyOn(console, 'error').mockImplementation(() => { });

        const mockDeleteDoc = vi.mocked(deleteDoc);
        mockDeleteDoc.mockRejectedValueOnce(new Error('Delete failed'));

        await expect(
          sensor_type_repo.delete_sensor_type(testTypeId)
        ).rejects.toThrow('Delete failed');

        consoleSpy.mockRestore();
      });
    });
  });
});

