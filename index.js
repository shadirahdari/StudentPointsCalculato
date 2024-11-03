const fs = require("fs");
const path = require("path");

class Person {
  constructor(firstName, surname) {
    this.firstName = firstName || "";
    this.surname = surname || "";
    this.homeworkResults = [];
    this.examResults = [];
  }

  addHomeworkResult(result) {
    this.homeworkResults.push(result);
  }

  addExamResult(result) {
    this.examResults.push(result);
  }

  calculateFinalGrade(method = "average") {
    const allResults = [...this.homeworkResults, ...this.examResults];
    if (allResults.length === 0) return 0;

    if (method === "average") {
      const sum = allResults.reduce((a, b) => a + b, 0);
      return (sum / allResults.length).toFixed(2);
    } else if (method === "median") {
      allResults.sort((a, b) => a - b);
      const mid = Math.floor(allResults.length / 2);
      return allResults.length % 2 !== 0
        ? allResults[mid].toFixed(2)
        : ((allResults[mid - 1] + allResults[mid]) / 2).toFixed(2);
    }
  }

  outputData() {
    const finalAvg = this.calculateFinalGrade("average");
    const finalMed = this.calculateFinalGrade("median");
    return `${this.firstName.padEnd(10)} ${this.surname.padEnd(
      10
    )} ${finalAvg.padStart(10)} | ${finalMed.padStart(10)}`;
  }
}

function readStudentsFromFile(filePath) {
  const data = fs.readFileSync(filePath, "utf8").trim().split("\n");
  const students = [];

  for (let i = 1; i < data.length; i++) {
    const line = data[i].trim();
    const parts = line.split(/\s+/);

    const firstName = parts[0];
    const surname = parts[1];
    const scores = parts.slice(2).map(Number);

    const person = new Person(firstName, surname);
    scores.slice(0, -1).forEach((score) => person.addHomeworkResult(score));
    person.addExamResult(scores[scores.length - 1]);

    students.push(person);
  }
  return students;
}

const filePath = path.join(__dirname, "students.txt");
const students = readStudentsFromFile(filePath);

console.log(`Name      Surname        Final (Avg.) | Final (Med.)`);
console.log(`----------------------------------------------------`);

students.forEach((student) => console.log(student.outputData()));
