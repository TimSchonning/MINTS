export class Interval {
    start: Date;
    end: Date;
    constructor(d1: Date, d2: Date) {
        if (d1 > d2) {
            // Ensure that d1 is always earlier than d2.
            this.start = d2;
            this.end = d1;
        } else {
            this.start = d1;
            this.end = d2;
        }
    }

    contains_date(date: Date): boolean {
        return this.start <= date && date <= this.end;
    }

    toString(): string {
        return `${this.start.toLocaleTimeString()} to ${this.end.toLocaleTimeString()}`
    }
}