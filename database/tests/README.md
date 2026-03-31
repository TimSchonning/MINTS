# Database CRUD Tests

Comprehensive test suite for Firebase database CRUD operations.

## Setup

Install dependencies:
```bash
npm install
```

## Running Tests

**Run all tests:**
```bash
npm test
```

**Run tests with UI:**
```bash
npm run test:ui
```

**Run tests in watch mode:**
```bash
npm test -- --watch
```

**Run specific test file:**
```bash
npm test -- database_tests.ts
```

## Test Coverage

The test suite includes:

### Database Connection
- Successful Firebase connection
- Connection error handling

### Station CRUD Operations
- **Create**: Valid data insertion, error handling, timestamp verification
- **Read**: Successful position retrieval, null handling for non-existent stations, error handling
- **Update**: Position updates, timestamp tracking, error handling
- **Delete**: Successful deletion, error handling

### Measurement CRUD Operations
- **Create**: Data insertion with valid values, error handling
- **Read**: Data retrieval, null handling, error management
- **Update**: Value updates with timestamp tracking, error handling
- **Delete**: Successful deletion, error handling

### Measurement Type CRUD Operations
- **Create**: Type creation with threshold values, error handling
- **Read**: Type data retrieval, null handling, error management
- **Update**: Threshold value updates, error handling
- **Delete**: Successful deletion, error handling

## Mocking

Firebase operations are mocked using `vitest` mocks. This allows tests to run without requiring actual Firebase credentials or network access.

## Test Structure

Each CRUD operation is tested for:
1. **Success cases**: Valid data and expected behavior
2. **Error cases**: Exception handling and error propagation
3. **Data integrity**: Verification that correct data is passed to Firebase
4. **Timestamp handling**: Ensuring timestamps are properly created/updated
