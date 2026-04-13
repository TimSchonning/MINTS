export class Interval {
    d1: Date;
    d2: Date;
    constructor(d1: Date, d2: Date) {
        if (d1 > d2) {
            // Ensure that d1 is always earlier than d2.
            this.d1 = d2;
            this.d2 = d1;
        }
        this.d1 = d1;
        this.d2 = d2;
    }
}