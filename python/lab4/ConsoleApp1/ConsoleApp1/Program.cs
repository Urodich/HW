using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    internal class Program
    {
        static void Main(string[] args)
        {
        }
    }
    class Director
    {
        public void CreateProgram()
        {

        }
    }
    class Teacher
    {
           
    }
    class Student
    {
        public int Group;
        public string Name;
    }
    class Shcool
    {
        Dictionary<int, Schedule> program;
        List<Room> Rooms;
    }
    class Room
    {
        Student[,] tables;
    }
    struct Schedule
    {

    }
}
