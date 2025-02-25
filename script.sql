CREATE TABLE Memberships (
    MembershipID INT PRIMARY KEY IDENTITY(1,1),
    MembershipType NVARCHAR(50) NOT NULL,
    DurationInMonths INT NOT NULL,
    Price DECIMAL(10, 2) NOT NULL,
    Benefits NVARCHAR(200)
);
CREATE TABLE Members (
    MemberID INT PRIMARY KEY IDENTITY(1,1),
    FirstName NVARCHAR(100) NOT NULL,
    LastName NVARCHAR(100) NOT NULL,
    Email NVARCHAR(100) UNIQUE NOT NULL,
    PhoneNumber NVARCHAR(15),
    DateOfBirth DATE,
    MembershipID INT,
    JoinDate DATE NOT NULL,
    CONSTRAINT FK_Members_Memberships FOREIGN KEY (MembershipID) 
        REFERENCES Memberships(MembershipID) 
        ON DELETE SET NULL
);
CREATE TABLE Trainers (
    TrainerID INT PRIMARY KEY IDENTITY(1,1),
    FirstName NVARCHAR(100) NOT NULL,
    LastName NVARCHAR(100) NOT NULL,
    Specialization NVARCHAR(100),
    Email NVARCHAR(100) UNIQUE NOT NULL,
    PhoneNumber NVARCHAR(15),
    HireDate DATE NOT NULL
);
CREATE TABLE Classes (
    ClassID INT PRIMARY KEY IDENTITY(1,1),
    ClassName NVARCHAR(100) NOT NULL,
    Description NVARCHAR(200),
    Schedule DATETIME NOT NULL,
    TrainerID INT,
    Capacity INT NOT NULL,
    CONSTRAINT FK_Classes_Trainers FOREIGN KEY (TrainerID) 
        REFERENCES Trainers(TrainerID) 
        ON DELETE SET NULL
);
CREATE TABLE Attendance (
    AttendanceID INT PRIMARY KEY IDENTITY(1,1),
    MemberID INT,
    ClassID INT,
    AttendanceDate DATETIME NOT NULL,
    Status NVARCHAR(10) CHECK (Status IN ('Present', 'Absent')) NOT NULL,
    CONSTRAINT FK_Attendance_Members FOREIGN KEY (MemberID) 
        REFERENCES Members(MemberID) 
        ON DELETE CASCADE,
    CONSTRAINT FK_Attendance_Classes FOREIGN KEY (ClassID) 
        REFERENCES Classes(ClassID) 
        ON DELETE CASCADE
);
INSERT INTO Memberships (MembershipType, DurationInMonths, Price, Benefits) VALUES
('Monthly', 1, 50.00, 'Access to gym facilities and group classes'),
('Quarterly', 3, 135.00, 'Access to gym, classes, and 2 personal training sessions'),
('Yearly', 12, 480.00, 'Unlimited access to all facilities and classes'),
('Student Monthly', 1, 40.00, 'Discounted monthly rate for students'),
('Premium Yearly', 12, 800.00, 'Access to VIP lounge, spa, and personal trainer');
INSERT INTO Members (FirstName, LastName, Email, PhoneNumber, DateOfBirth, MembershipID, JoinDate) VALUES
('John', 'Doe', 'john.doe@example.com', '555-1234', '1990-05-15', 1, '2025-01-01'),
('Jane', 'Smith', 'jane.smith@example.com', '555-5678', '1985-10-22', 3, '2025-01-15'),
('Michael', 'Johnson', 'michael.j@example.com', '555-8765', '2000-03-30', 4, '2025-02-10'),
('Emily', 'Davis', 'emily.davis@example.com', '555-3456', '1995-07-11', 2, '2025-01-20'),
('Chris', 'Brown', 'chris.brown@example.com', '555-2345', '1988-12-05', 5, '2025-02-01');
INSERT INTO Trainers (FirstName, LastName, Specialization, Email, PhoneNumber, HireDate) VALUES
('Alex', 'Miller', 'Strength Training', 'alex.miller@example.com', '555-1111', '2024-09-01'),
('Samantha', 'Taylor', 'Yoga Instructor', 'samantha.taylor@example.com', '555-2222', '2023-05-15'),
('David', 'Wilson', 'Cardio and HIIT', 'david.wilson@example.com', '555-3333', '2022-11-10'),
('Laura', 'Anderson', 'Pilates', 'laura.anderson@example.com', '555-4444', '2024-02-20'),
('Brian', 'Thomas', 'Personal Training', 'brian.thomas@example.com', '555-5555', '2025-01-05');
INSERT INTO Classes (ClassName, Description, Schedule, TrainerID, Capacity) VALUES
('Morning Yoga', 'Start your day with a relaxing yoga session.', '2025-02-15 08:00:00', 2, 20),
('HIIT Blast', 'High-intensity interval training for all fitness levels.', '2025-02-15 09:30:00', 3, 15),
('Strength Training', 'Full body workout to build strength.', '2025-02-16 18:00:00', 1, 25),
('Pilates Basics', 'Beginner-friendly Pilates class.', '2025-02-17 10:00:00', 4, 20),
('Personal Training Session', 'One-on-one personal training.', '2025-02-18 14:00:00', 5, 1);
INSERT INTO Attendance (MemberID, ClassID, AttendanceDate, Status) VALUES
(1, 1, '2025-02-15 08:00:00', 'Present'),
(2, 2, '2025-02-15 09:30:00', 'Present'),
(3, 3, '2025-02-16 18:00:00', 'Absent'),
(4, 4, '2025-02-17 10:00:00', 'Present'),
(5, 5, '2025-02-18 14:00:00', 'Present');
