const fs = require('fs');
const path = require('path');

class Person {
    constructor(firstName, surname) {
        this.firstName = firstName || '';
        this.surname = surname || '';
        this.homeworkResults = [];
        this.examResults = [];
    }

    addHomeworkResult(result) {
        this.homeworkResults.push(result);
    }

    addExamResult(result) {
        this.examResults.push(result);
    }

    calculateFinalGrade() {
        const allResults = [...this.homeworkResults, ...this.examResults];
        if (allResults.length === 0) return 0;

        const sum = allResults.reduce((a, b) => a + b, 0);
        return (sum / allResults.length).toFixed(2);
    }

    outputData() {
        const finalAvg = this.calculateFinalGrade();
        return `${this.firstName.padEnd(10)} ${this.surname.padEnd(10)} ${finalAvg.padStart(10)}`;
    }
}

function readStudentsFromFile(filePath) {
    const data = fs.readFileSync(filePath, 'utf8').trim().split('\n');
    const students = [];

    for (let i = 1; i < data.length; i++) {
        const line = data[i].trim();
        const parts = line.split(/\s+/);

        const firstName = parts[0];
        const surname = parts[1];
        const scores = parts.slice(2).map(Number);

        const person = new Person(firstName, surname);
        scores.slice(0, -1).forEach(score => person.addHomeworkResult(score));
        person.addExamResult(scores[scores.length - 1]);

        students.push(person);
    }
    return students;
}

const filePath = path.join(__dirname, 'students.txt');
const students = readStudentsFromFile(filePath);

console.log(`Name       Surname       Final_Point(Aver.)`);
console.log(`-------------------------------------------`);

students.forEach(student => console.log(student.outputData()));
