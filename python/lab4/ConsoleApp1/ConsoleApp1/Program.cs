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
        Status status;
        School school;
        public Student(string name, int group, School school)
        {
            Name = name;
            Group = group;
            this.school = school;
            status = Status.atHome;
        }
        public void GoToSchool()
        {
            school.AddStudent(this);
        }
        public void GoToLesson()
        {

        }
        public void GoHome()
        {
        }
    }
    class School
    {
        static School Instance;
        Dictionary<int, Schedule> program;
        List<Room> Rooms;
        List<Student> Students;
        DateTime Time = new DateTime(2022,11,10,7,0,0);
        int CurLesson = 0;
        event Action<bool> signal;
        Dictionary<DateTime, Func<int, int, bool>> SignalOrder = new Dictionary<DateTime, Action<int, bool>>()
        {
            [new DateTime(2022, 11, 10, 8, 0, 0)] = Signal(1,false)
        };
        void Update()
        {
            Time.AddMinutes(1);
        }
        static int Signal(int lesson, bool isBreake)
        {
            Instance.CurLesson = lesson;
            Instance.signal.Invoke(isBreake);
            return 1;
        }
        School()
        {

        }
        public static School GetInstance()
        {
            if (Instance!=null) return Instance;
            else Instance=new School();
            return Instance;
        }
        public void AddStudent(Student student)
        {
            Students.Add(student);
        }
        public void GetLesson()
        {
            if(Time>8 && Time<)
        }
        public int FindRoom(int group)
        {
            Schedule schedule = program[group];
            return 
        }
    }
    class Room
    {
        List<Student> tables;
    }
    struct Schedule
    {

    }
    enum Status
    {
        atHome,
        ill,
        relax,
        studying,
        shirker
    }
}
