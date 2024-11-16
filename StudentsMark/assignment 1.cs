using System;
using System.IO;
using System.Text.RegularExpressions;
using System.Linq;

class Person
{
   public string FirstName { get; set; }
   public string Surname { get; set; }
   public float[] HomeworkScores { get; set; }
   public float ExamScore { get; set; }
   public float FinalGrade { get; set; }

   public Person(string firstName, string surname, float[] homeworkScores, float examScore)
   {
       FirstName = firstName;
       Surname = surname;
       HomeworkScores = homeworkScores;
       ExamScore = examScore;
       CalculateFinalGrade();
   }

   public Person(Person other)
   {
       FirstName = other.FirstName;
       Surname = other.Surname;
       HomeworkScores = (float[])other.HomeworkScores.Clone();
       ExamScore = other.ExamScore;
       FinalGrade = other.FinalGrade;
   }

   public Person Assign(Person other)
   {
       if (this != other)
       {
           FirstName = other.FirstName;
           Surname = other.Surname;
           HomeworkScores = (float[])other.HomeworkScores.Clone();
           ExamScore = other.ExamScore;
           FinalGrade = other.FinalGrade;
       }
       return this;
   }

   ~Person() { }

   public static Person InputData(string inputLine)
   {
       string[] row = Regex.Split(inputLine, @"\s+");
       string firstName = row[0];
       string surname = row[1];
       float[] homeworkScores = row.Skip(2).Take(row.Length - 2).Select(float.Parse).ToArray();
       float examScore = float.Parse(row[row.Length - 1]);

       return new Person(firstName, surname, homeworkScores, examScore);
   }

   public void OutputData()
   {
       Console.WriteLine($"{FirstName,-15} {Surname,-15} {FinalGrade,15:F2}");
   }

   public void CalculateFinalGrade()
   {
       float homeworkAverage = HomeworkScores.Average();
       FinalGrade = (0.4f * homeworkAverage) + (0.6f * ExamScore);
   }
}

class Program
{
   static void Main(string[] args)
   {
       string filePath = "students10000.txt";
       string[] lines = File.ReadAllLines(filePath);
       Console.WriteLine("{0,-15} {1,-15} {2,-15}", "Name", "Family", "Final_Point (Aver.)");

       for (int i = 1; i < lines.Length; i++)
       {
           Person student = Person.InputData(lines[i]);
           student.OutputData();
       }
   }
}
