#include<iostream>
#include<fstream>
using namespace std;
class appointmentDetail
{
    string appointmentbyName;
    string appointmentbyId;
    string appointmenttoName;
    string appointmenttoId;
    string appointmentDay;

public:

    appointmentDetail()
    {
        appointmentbyName = " ";
        appointmentbyId = " ";
        appointmenttoName = " ";
        appointmenttoId = " ";
        appointmentDay = " ";
    }

    appointmentDetail(string byname, string byid, string toname, string toid, string day)
    {
        appointmentbyName = byname;
        appointmentbyId = byid;
        appointmenttoName = toname;
        appointmenttoId = toid;
        appointmentDay = day;
    }

    void setappointmentbyName(string name)
    {
        appointmentbyName = name;
    }
    void setappointmentbyId(string id)
    {
        appointmentbyId = id;
    }
    void setappointmenttoName(string name)
    {
        appointmenttoName = name;
    }
    void setappointmenttoId(string id)
    {
        appointmenttoId = id;
    }
    void setappointmentDay(string day)
    {
        appointmentDay = day;
    }

    string getappointmentbyName()
    {
        return appointmentbyName;
    }
    string getappointmentbyId()
    {
        return appointmentbyId;
    }
    string getappointmenttoName()
    {
        return appointmenttoName;
    }
    string getappointmenttoId()
    {
        return  appointmenttoId;
    }
    string getappointmentDay()
    {
        return  appointmentDay;
    }
};
class healthRecords
{
    string symptoms;
    string diagnosis;

public:
    healthRecords()
    {
        symptoms = " ";
        diagnosis = " ";

    }
    healthRecords(string symptom, string diagnose) : symptoms(symptom), diagnosis(diagnose)
    {

    }

    void setSymptoms(string symptom)
    {
        symptoms = symptom;
    }

    void setDiagnosis(string diagnose)
    {
        diagnosis = diagnose;
    }

    string getSymptoms()
    {
        return symptoms;
    }
    string getDiagnosis()
    {
        return diagnosis;
    }

};

class common_person
{
    string common_person_id;
    string common_person_name;
    int common_person_age;

public:

    common_person()
    {
        common_person_id = " ";
        common_person_name = " ";
        common_person_age = 0;
    }

    common_person(string id, string name, int age)
    {
        common_person_id = id;
        common_person_name = name;
        common_person_age = age;
    }

    common_person(common_person& p)
    {
        this->common_person_id = p.common_person_id;
        this->common_person_name = p.common_person_name;
        this->common_person_age = p.common_person_age;
    }

    void setcommonpersonID(string id)
    {
        common_person_id = id;
    }
    void setcommonpersonName(string name)
    {
        common_person_name = name;
    }
    void setcommonpersonAge(int age)
    {
        common_person_age = age;
    }

    string getcommonpersonID()
    {
        return common_person_id;
    }
    int getcommonpersonAge()
    {
        return common_person_age;
    }
    string getcommonpersonName()
    {
        return common_person_name;
    }

};
class doctor : virtual  public common_person
{
    string doctorType;
    string doctorStatus;
    int doctorFee;
    int doctorSalary;
    bool appointmentStatus;
    appointmentDetail* app_detail;

public:

    doctor()
    {
        doctorType = "General";
        doctorStatus = "free";
        doctorFee = 0;
        doctorSalary = 0;
        appointmentStatus = false;
        app_detail = NULL;
    }

    doctor(string id, string name, int age, string type, string status, int fee, int salary, bool app_status, appointmentDetail* ap) : common_person(id, name, age), doctorType(type), doctorStatus(status), doctorFee(fee), doctorSalary(salary), appointmentStatus(app_status), app_detail(ap)
    {

    }

    doctor(doctor& d)
    {
        this->setcommonpersonID(d.getcommonpersonID());
        this->setcommonpersonName(d.getcommonpersonName());
        this->setcommonpersonAge(d.getcommonpersonAge());
        this->doctorType = d.doctorType;
        this->doctorStatus = d.doctorStatus;
        this->doctorFee = d.doctorFee;
        this->doctorSalary = d.doctorSalary;
        this->appointmentStatus = d.appointmentStatus;
        this->app_detail = d.app_detail;
    }

    void setdoctorType(string type)
    {
        doctorType = type;
    }
    void setdoctorStatus(string status)
    {
        doctorStatus = status;
    }
    void setappointmentStatus(bool status)
    {
        appointmentStatus = status;
    }
    bool getappointmentStatus()
    {
        return appointmentStatus;
    }


    void setdoctorFee(int fee)
    {
        doctorFee = fee;
    }
    void setdoctorSalary(int Salary)
    {
        doctorSalary = Salary;
    }

    void setappointmentbyName(string name)
    {
        app_detail->setappointmentbyName(name);   // at the place where we have done doctor[i].setstatus("free") then we have to d0
    }                                             // doctor.getapp_detail()->setappointmentbyName(name) ; 
    void setappointmentbyId(string id)
    {
        app_detail->setappointmentbyId(id);
    }
    void setappointmenttoName(string name)
    {
        app_detail->setappointmenttoName(name);
    }
    void setappointmenttoId(string id)
    {
        app_detail->setappointmenttoId(id);
    }
    void setappointmentDay(string day)
    {
        app_detail->setappointmentDay(day);
    }

    void setapp_detail(appointmentDetail* ap)
    {
        app_detail = ap;
    }

    appointmentDetail* getapp_detail()
    {
        return app_detail;    // returns the pointer of the appointment 
    }
    string getappointmentbyName()
    {
        return app_detail->getappointmentbyName();
    }
    string getappointmentbyId()
    {
        return app_detail->getappointmentbyId();
    }
    string getappointmenttoName()
    {
        return app_detail->getappointmenttoName();
    }
    string getappointmenttoId()
    {
        return  app_detail->getappointmenttoId();
    }
    string getappointmentDay()
    {
        return  app_detail->getappointmentDay();
    }

    string getdoctorType()
    {
        return doctorType;
    }
    string getdoctorStatus()
    {
        return doctorStatus;
    }
    int getdoctorFee()
    {
        return doctorFee;
    }
    int getdoctorSalary()
    {
        return doctorSalary;
    }
};

class patient : public common_person
{
    string patientType;
    healthRecords record;

public:

    patient()
    {
        patientType = "General";
    }

    patient(string id, string name, int age, string type, string symptom, string diagnose) : common_person(id, name, age), patientType(type), record(symptom, diagnose)
    {

    }

    patient(patient& p)
    {
        this->setcommonpersonID(p.getcommonpersonID());
        this->setcommonpersonName(p.getcommonpersonName());
        this->setcommonpersonAge(p.getcommonpersonAge());
        this->patientType = p.patientType;
    }

    void setpatientType(string type)
    {
        patientType = type;
    }

    void setSymptoms(string symptom)
    {
        record.setSymptoms(symptom);
    }

    void setDiagnosis(string diagnose)
    {
        record.setDiagnosis(diagnose);
    }
    void setRecord(healthRecords& h)
    {
        record = h;
    }
    healthRecords& getRecord()
    {
        return record;
    }
    string getSymptoms()
    {
        return record.getSymptoms();
    }
    string getDiagnosis()
    {
        return record.getDiagnosis();
    }
    string getpatientType()
    {
        return patientType;
    }

    void display()
    {
        cout << "Patient Information" << endl;
        cout << "Patient name : " << this->getcommonpersonName() << endl;
        cout << "patient id : " << this->getcommonpersonID() << endl;
        cout << "Patient Age : " << this->getcommonpersonAge() << endl;
        cout << "Patient Type : " << patientType << endl;
        cout << "Pateint Health Record " << endl;
        cout << "Patient Symptoms : " << getSymptoms() << endl;
        cout << "Pateitn Diagnosis : " << getDiagnosis() << endl;

    }


};
class Room {
protected:
    int roomNumber;
    string roomType;
    bool isOccupied;

public:
    Room()
    {
        roomNumber = 0;
        roomType = "General";
        isOccupied = false;
    }

    Room(int number, string type, bool occupied = false)
    {
        roomNumber = number;
        roomType = type;
        isOccupied = occupied;
    }
    virtual ~Room() {
        cout << "Room destructor called" << endl;
    }

    void setNumber(int number)
    {
        roomNumber = number;
    }
    void setType(string type)
    {
        roomType = type;
    }
    string getType()
    {
        return roomType;
    }
    int getNumber()
    {
        return roomNumber;
    }
    void setIsOccupied(bool occupied)
    {
        isOccupied = occupied;
    }
    bool getIsOccupied()
    {
        return isOccupied;
    }

    virtual void bookRoom()
    {
        if (isOccupied)
            cout << "Room is already occupied" << endl;
        else {
            isOccupied = true;
            cout << "Room booked successfully" << endl;
        }
    }

    virtual void releaseRoom()
    {
        if (isOccupied)
        {
            isOccupied = false;
            cout << "Room released successfully" << endl;
        }
        else cout << "Room is already vacant" << endl;
    }
    virtual void displayRoomInfo()
    {
        cout << "Room Info" << endl;
        cout << "Room Number: " << roomNumber << endl;
        cout << "Room Type: " << roomType << endl;
        cout << "Is Occupied: " << (isOccupied ? "Yes" : "No") << endl;
    }

};
class ICURoom : public Room {
    const int capacity = 30;
    bool hasVentilator;
    int patientCount;
public:
    ICURoom() : Room() {
        hasVentilator = false;
        patientCount = 0;
    }
    ICURoom(int number, string type, bool occupied, bool ventilator) : Room(number, type, occupied) {
        hasVentilator = ventilator;
        patientCount = 0;
    }
    int getCapacity()
    {
        return capacity;
    }
    void setHasVentilator(bool ventilator) {
        hasVentilator = ventilator;
    }
    bool getHasVentilator() {
        return hasVentilator;
    }
    void bookRoom() override {
        if (patientCount < capacity)
        {
            patientCount++;
            setIsOccupied(true);
            cout << "Patient admitted to ICU Room successfully" << endl;
        }
        else
        {
            cout << "ICU Room is at full capacity" << endl;
        }
    }
};
class GeneralRoom : public Room {
private:
    const int capacity = 50;
    int patientCount;
public:
    GeneralRoom() : Room() {
        patientCount = 0;
    }
    GeneralRoom(int number, string type, bool occupied) : Room(number, type, occupied) {
        patientCount = 0;
    }
    int getCapacity()
    {
        return capacity;
    }
    void bookRoom() override
    {
        if (patientCount < capacity)
        {
            patientCount++;
            setIsOccupied(true);
            cout << "Patient admitted to General Room successfully" << endl;
        }
        else
        {
            cout << "General Room is at full capacity" << endl;
        }
    }

};
class EmergencyRoom : public Room {
private:
    const int capacity = 10;
    int patientCount;
public:
    EmergencyRoom() : Room() {
        patientCount = 0;
    }
    EmergencyRoom(int number, string type, bool occupied) : Room(number, type, occupied) {
        patientCount = 0;
    }
    int getCapacity()
    {
        return capacity;
    }
    void bookRoom() override
    {
        if (patientCount < capacity)
        {
            patientCount++;
            setIsOccupied(true);
            cout << "Patient admitted to Emergency Room successfully" << endl;
        }
        else
        {
            cout << "Emergency Room is at full capacity" << endl;
        }
    }

};
class medicine
{
    string medicineType;
    int medicineQuantity;
    string medicineTime;

public:
    medicine()
    {
        medicineType = "normal";
        medicineQuantity = 0;
        medicineTime = " ";
    }

    medicine(string type, int quantity, string time)
    {
        medicineType = type;
        medicineQuantity = quantity;
        medicineTime = time;
    }

    medicine(medicine& m)
    {
        this->medicineType = m.medicineType;
        this->medicineQuantity = m.medicineQuantity;
        this->medicineTime = m.medicineTime;
    }

    string getmedicineType()
    {
        return medicineType;
    }

    string getmedicineTime()
    {
        return medicineTime;
    }
    int getmedicineQuantity()
    {
        return medicineQuantity;
    }
    void setmedicineType(string type)
    {
        medicineType = type;
    }
    void setmedicineQuantity(int num)
    {
        medicineQuantity = num;
    }
    void setmedicineTime(string time)
    {
        medicineTime = time;
    }
};
class prescription
{
    doctor* docPtr;
    patient Patient;
    int numberofmedicines;
    medicine* medicinePtr;

public:

    prescription()
    {
        docPtr = NULL;
        numberofmedicines = 0;
        medicinePtr = NULL;
    }

    prescription(doctor* d, patient p, int num)
    {
        docPtr = d;
        Patient = p;
        numberofmedicines = num;
        if (num > 0)
        {
            medicinePtr = new medicine[num];
            fillMedicine(num);
        }
        else
            medicinePtr = NULL;
    }


    void display()
    {
        cout << "Medicine Prescription" << endl;
        if (docPtr != NULL)
        {
            cout << "Doctor name : " << this->docPtr->getcommonpersonName() << endl;
            cout << "Doctor id : " << this->docPtr->getcommonpersonID() << endl;
        }
        else
        {
            cout << "No doctor assigned " << endl;
        }
        cout << "Patient name : " << this->Patient.getcommonpersonName() << endl;
        cout << "Patient id : " << this->Patient.getcommonpersonID() << endl;
        cout << "Patient Age : " << this->Patient.getcommonpersonAge() << endl;
        cout << "Patient Diagnosis : " << this->Patient.getDiagnosis() << endl;
        if (medicinePtr != NULL)
        {
            for (int i = 0; i < numberofmedicines; i++)
            {
                cout << "Medicine : " << i + 1 << endl;
                cout << "Medicine Type : " << medicinePtr[i].getmedicineType() << endl;
                cout << "Medicine Quantity : " << medicinePtr[i].getmedicineQuantity() << endl;
                cout << "Medicine Time : " << medicinePtr[i].getmedicineTime() << endl;
            }

        }
        else
            cout << "No Medicine assigned " << endl;

    }

    void fillMedicine(int num)
    {
        int bufferint;
        string bufferstring;
        for (int i = 0; i < num; i++)
        {
            cout << "Enter medicine : " << i << endl;
            cout << "Enter medicine Type : ";
            cin >> bufferstring;
            medicinePtr[i].setmedicineType(bufferstring);
            cout << "Enter medicine quantity : ";
            cin >> bufferint;
            medicinePtr[i].setmedicineQuantity(bufferint);
            cout << "Enter medicine Time: ";
            cin >> bufferstring;
            medicinePtr[i].setmedicineTime(bufferstring);
        }
    }

    ~prescription()
    {
        delete[] medicinePtr;
    }
};
class appointmentScheduling {
    string appointmentDate;
    string appointmentTime;
    string doctorSpecialization;
    bool ifBooked;
    patient* currentPatient;
    doctor* selectedDoctor;

public:
    appointmentScheduling() {
        appointmentDate = "";
        appointmentTime = "";
        doctorSpecialization = " ";
        ifBooked = false;
        currentPatient = NULL;
        selectedDoctor = NULL;
    }

    void scheduleAppointment(patient& p, doctor Doctors[], int s) {
        cout << "Welcome: " << p.getcommonpersonName() << endl;
        cout << "Please book your appointment" << endl;
        cout << "Select doctor specialization: " << endl;
        cout << "1. General" << endl << "2. Surgeon" << endl << "3. Cardiologist" << endl;

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        string Byname = "";
        if (choice == 1)
        {
            Byname = "General";
        }
        else if (choice == 2)
        {
            Byname = "Surgeon";
        }
        else if (choice == 3)
        {
            Byname = "Cardiologist";
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
            return;
        }

        cout << "Available Doctors for " << Byname << ":" << endl;
        for (int i = 0; i < s; i++) {
            if (Doctors[i].getdoctorType() == Byname) {
                cout << "  " << Doctors[i].getcommonpersonName() << "  " << Doctors[i].getdoctorStatus() << " " << Doctors[i].getdoctorType() << " " << endl;
            }
        }
    }

    void scheduleByname(patient& p, doctor Doctors[], int s) {
        currentPatient = &p;
        cout << "Welcome: " << p.getcommonpersonName() << endl;
        cout << "Enter doctor name to schedule appointment: ";
        string name;
        cin >> name;

        for (int i = 0; i < s; i++) {
            if (Doctors[i].getcommonpersonName() == name)
            {
                if (Doctors[i].getdoctorStatus() == "free")
                {
                    Doctors[i].setdoctorStatus("busy");
                    Doctors[i].setappointmentStatus(true);
                    if (Doctors[i].getapp_detail() == NULL) {
                        Doctors[i].setapp_detail(new appointmentDetail());
                    }
                    Doctors[i].setappointmentbyName(p.getcommonpersonName());
                    Doctors[i].setappointmentbyId(p.getcommonpersonID());
                    Doctors[i].setappointmenttoName(Doctors[i].getcommonpersonName());
                    Doctors[i].setappointmenttoId(Doctors[i].getcommonpersonID());
                    Doctors[i].setappointmentDay("Monday");

                    this->selectedDoctor = &Doctors[i];
                    this->ifBooked = true;
                    this->doctorSpecialization = Doctors[i].getdoctorType();

                    cout << "Appointment booked successfully with Dr. " << Doctors[i].getcommonpersonName() << endl;
                    return;
                }
                else {
                    cout << "Dr. " << Doctors[i].getcommonpersonName() << " is currently busy." << endl;
                    return;
                }
            }
        }
        cout << "Doctor not found." << endl;
    }

    void successfulAppointment() {
        if (ifBooked && selectedDoctor != NULL && currentPatient != NULL) {
            cout << " Appointment Booked" << endl;
            cout << "Patient: " << currentPatient->getcommonpersonName() << endl;
            cout << "Doctor: " << selectedDoctor->getcommonpersonName() << endl;
            cout << "Specialization: " << doctorSpecialization << endl;
            cout << "Status: Confirmed" << endl;
        }
        else
        {
            cout << "No appointment has been booked yet." << endl;
        }
    }
};
void addDoctor(doctor*& Doctors, int& s, int& cap) {
    if (s >= cap) {
        cap = cap + 3;
        doctor* newArr = new doctor[cap];
        for (int i = 0; i < s; i++) {
            newArr[i] = Doctors[i];
        }
        delete[] Doctors;
        Doctors = newArr;
    }
    ofstream outFile("doctors.txt", ios::app);
    if (!outFile) {
        cout << "Error opening file." << endl;
        return;
    }
    else
    {
        cout << "Enter doctor ID: ";
        string id;
        cin >> id;
        cout << "Enter doctor name: ";
        string name;
        cin >> name;
        cout << "Enter doctor age: ";
        int age;
        cin >> age;
        cout << "Enter doctor specialization: ";
        string type;
        cin >> type;
        cout << "Enter doctor status: ";
        string status;
        cin >> status;
        cout << "Enter doctor fee: ";
        int fee;
        cin >> fee;
        cout << "Enter doctor salary: ";
        int salary;
        cin >> salary;
        Doctors[s] = doctor(id, name, age, type, status, fee, salary, false, NULL);
        outFile << "Name: " << name << ", ID: " << id << ", Age: " << age << ", Type: " << type << ", Fee: " << fee << ", Salary: " << salary << endl;
        s++;
        outFile.close();

    }

}
void viewDoctors(doctor Doctors[], int s)
{
    cout << "List of Doctors:" << endl;
    for (int i = 0; i < s; i++) {
        cout << "Name: " << Doctors[i].getcommonpersonName() << "  Specialization: " << Doctors[i].getdoctorType() << " Status: " << Doctors[i].getdoctorStatus() << endl;
    }
}
void removeDoctor(doctor Doctors[], int& s) {
    cout << "Enter doctor ID to remove: ";
    string id;
    cin >> id;

    for (int i = 0; i < s; i++) {
        if (Doctors[i].getcommonpersonID() == id) {
            for (int j = i; j < s - 1; j++) {
                Doctors[j] = Doctors[j + 1];
            }
            s--;
            ofstream outFile("doctors.txt");
            if (outFile) {
                for (int k = 0; k < s; k++) {
                    outFile << "Name: " << Doctors[k].getcommonpersonName() << " ID: " << Doctors[k].getcommonpersonID()<< " Age: " << Doctors[k].getcommonpersonAge()<< " Type: " << Doctors[k].getdoctorType() << " Fee: " << Doctors[k].getdoctorFee() << " Salary: " << Doctors[k].getdoctorSalary() << endl;
                }
                outFile.close();
            }
            cout << "Doctor removed successfully." << endl;
            return;
        }
    }
    cout << "Doctor not found." << endl;
}

void seePatientDetails(patient Patients[], int s) {
    cout << "List of Patients:" << endl;
    for (int i = 0; i < s; i++) {
        cout << "Name: " << Patients[i].getcommonpersonName() << "  Age: " << Patients[i].getcommonpersonAge() << " Type: " << Patients[i].getpatientType() << endl;
    }
}
void seeRoomDetails(Room* rooms[], int s) {
    cout << "List of Rooms:" << endl;
    for (int i = 0; i < s; i++) {
        rooms[i]->displayRoomInfo();
        cout << endl;
    }
}
void seeAppointmentDetails(appointmentScheduling& scheduler) {
    cout << "Appointment Details:" << endl;
    scheduler.successfulAppointment();
}
void editPatientDetails(patient Patients[], int s) {
    cout << "Enter patient name to edit: ";
    string name;
    cin >> name;

    for (int i = 0; i < s; i++) {
        if (Patients[i].getcommonpersonName() == name) {
            cout << "Editing details for " << name << endl;
            int age;
            string type;
            cout << "New Age: ";
            cin >> age;
            cout << "New Type: ";
            cin >> type;
            Patients[i].setcommonpersonAge(age);
            Patients[i].setpatientType(type);
            cout << "Patient details updated successfully." << endl;
            return;
        }
    }
    cout << "Patient not found." << endl;
}
void editDoctorDetails(doctor Doctors[], int s) {
    cout << "Enter doctor name to edit: ";
    string name;
    cin >> name;

    for (int i = 0; i < s; i++) {
        if (Doctors[i].getcommonpersonName() == name) {
            cout << "Editing details for Dr. " << name << endl;
            string type, status;
            int fee, salary;
            cout << "New Specialization: ";
            cin >> type;
            cout << "New Status: ";
            cin >> status;
            cout << "New Fee: ";
            cin >> fee;
            cout << "New Salary: ";
            cin >> salary;
            Doctors[i].setdoctorType(type);
            Doctors[i].setdoctorStatus(status);
            Doctors[i].setdoctorFee(fee);
            Doctors[i].setdoctorSalary(salary);
            cout << "Doctor details updated successfully." << endl;
            return;
        }
    }
    cout << "Doctor not found." << endl;
}
void editSpecialization(doctor Doctors[], int s) {
    cout << "Enter doctor name to edit specialization: ";
    string name;
    cin >> name;

    for (int i = 0; i < s; i++) {
        if (Doctors[i].getcommonpersonName() == name) {
            cout << "Editing specialization for Dr. " << name << endl;
            string type;
            cout << "New Specialization: ";
            cin >> type;
            Doctors[i].setdoctorType(type);
            cout << "Doctor specialization changed successfully." << endl;
            return;
        }
    }
    cout << "Doctor not found." << endl;
}
void editStatus(doctor Doctors[], int s) {
    cout << "Enter doctor name to edit status: ";
    string name;
    cin >> name;

    for (int i = 0; i < s; i++) {
        if (Doctors[i].getcommonpersonName() == name) {
            cout << "Editing status for Dr. " << name << endl;
            string status;
            cout << "New Status: ";
            cin >> status;
            Doctors[i].setdoctorStatus(status);
            cout << "Doctor status changed successfully." << endl;
            return;
        }
    }
    cout << "Doctor not found." << endl;
}
void editFee(doctor Doctors[], int s) {
    cout << "Enter doctor name to edit fee: ";
    string name;
    cin >> name;

    for (int i = 0; i < s; i++) {
        if (Doctors[i].getcommonpersonName() == name) {
            cout << "Editing fee for Dr. " << name << endl;
            int fee;
            cout << "New Fee: ";
            cin >> fee;
            Doctors[i].setdoctorFee(fee);
            cout << "Doctor fee changed successfully." << endl;
            return;
        }
    }
    cout << "Doctor not found." << endl;
}
void editSalary(doctor Doctors[], int s) {
    cout << "Enter doctor name to edit salary: ";
    string name;
    cin >> name;

    for (int i = 0; i < s; i++) {
        if (Doctors[i].getcommonpersonName() == name) {
            cout << "Editing salary for Dr. " << name << endl;
            int salary;
            cout << "New Salary: ";
            cin >> salary;
            Doctors[i].setdoctorSalary(salary);
            cout << "Doctor salary changed successfully." << endl;
            return;
        }
    }
    cout << "Doctor not found." << endl;
}


void adminPortal(doctor Doctors[], patient Patients[], Room* rooms[],int roomC, appointmentScheduling& scheduler, int &ds,int &dcap, int &ps, int &pcap) {
    cout << "Welcome to the Admin Portal" << endl;
    cout << "1. Add Doctor" << endl;
    cout << "2. View Doctors" << endl;
    cout << "3. Remove Doctor" << endl;
    cout << "4. see patient details" << endl;
    cout << "5. see room details" << endl;
    cout << "6. see appointment details" << endl;
    cout << "7. edit doctor details" << endl;
    cout << "8. edit patient details" << endl;
    cout << "9. exit" << endl;
    int choice;
    cout << "Enter your choice: ";
    cin >> choice;
    if (choice == 1) {
        cout << "Adding a new doctor" << endl;
        addDoctor(Doctors, ds, dcap);
    }
    else if (choice == 2)
    {
        cout << "Viewing all doctors" << endl;
        viewDoctors(Doctors, ds);
    }
    else if (choice == 3)
    {
        cout << "Removing a doctor" << endl;
        removeDoctor(Doctors, ds);
    }
    else if (choice == 4)
    {
        cout << "Viewing patient details" << endl;
        seePatientDetails(Patients, ps);
    }
    else if (choice == 5)
    {
        cout << "Viewing room details" << endl;
        seeRoomDetails(rooms,roomC);
    }
    else if (choice == 6)
    {
        cout << "Viewing appointment details" << endl;
        seeAppointmentDetails(scheduler);
    }
    else if (choice == 7)
    {
        cout << "Editing doctor details" << endl;
        cout << "What details do you want to edit?" << endl;
        cout << "1. Specialization" << endl;
        cout << "2. Status" << endl;
        cout << "3. Fee" << endl;
        cout << "4. Salary" << endl;
        cout << "5. All details" << endl;
        cout << "6.Exit" << endl;
        cout << "Enter your choice: ";
        int Choice;
        cin >> Choice;
        if (Choice == 1)
        {
            editSpecialization(Doctors, ds);
        }
        else if (Choice == 2)
        {
            editStatus(Doctors, ds);
        }
        else if (Choice == 3)
        {
            editFee(Doctors, ds);
        }
        else if (Choice == 4)
        {
            editSalary(Doctors, ds);
        }
        else if (Choice == 5)
        {
            editDoctorDetails(Doctors, ds);
        }
        else if (Choice == 6)
        {
            cout << "Exiting doctor details editing" << endl;
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
    else if (choice == 8)
    {
        cout << "Editing patient details" << endl;
        editPatientDetails(Patients, ps);
    }
    else
    {
        cout << "Invalid choice. Please try again." << endl;
    }
}
void viewAllpatients(patient Patients[], int s) {
    cout << "List of Patients:" << endl;
    for (int i = 0; i < s; i++) {
        cout << "Name: " << Patients[i].getcommonpersonName() << "  Age: " << Patients[i].getcommonpersonAge() << " Type: " << Patients[i].getpatientType() << endl;
    }
}
void viewHealthRecord(patient Patients[], int s) {
    cout << "Enter patient name to view health record: ";
    string name;
    cin >> name;

    for (int i = 0; i < s; i++) {
        if (Patients[i].getcommonpersonName() == name) {
            cout << "Health Record for " << name << endl;
            cout << "Symptoms: " << Patients[i].getSymptoms() << endl;
            cout << "Diagnosis: " << Patients[i].getDiagnosis() << endl;
            return;
        }
    }
    cout << "Patient not found." << endl;
}
void viewPrescription(patient Patients[], int s) {
    cout << "Enter patient name to view prescription: ";
    string name;
    cin >> name;

    for (int i = 0; i < s; i++) {
        if (Patients[i].getcommonpersonName() == name) {
            cout << "Prescription for " << name << endl;
            cout << "Patient Name: " << Patients[i].getcommonpersonName() << endl;
            cout << "Patient ID: " << Patients[i].getcommonpersonID() << endl;
            cout << "Patient Age: " << Patients[i].getcommonpersonAge() << endl;
            cout << "Patient Diagnosis: " << Patients[i].getDiagnosis() << endl;
            return;
        }
    }
    cout << "Patient not found." << endl;
}
void setStatus(doctor Doctors[], int s) {
    cout << "Enter doctor name to set status: ";
    string name;
    cin >> name;

    for (int i = 0; i < s; i++) {
        if (Doctors[i].getcommonpersonName() == name) {
            cout << "Setting status for Dr. " << name << endl;
            string status;
            cout << "New Status: ";
            cin >> status;
            Doctors[i].setdoctorStatus(status);
            cout << "Doctor status changed successfully." << endl;
            return;
        }
    }
    cout << "Doctor not found." << endl;
}
void setFee(doctor Doctors[], int s) {
    cout << "Enter doctor name to set fee: ";
    string name;
    cin >> name;

    for (int i = 0; i < s; i++) {
        if (Doctors[i].getcommonpersonName() == name) {
            cout << "Setting fee for Dr. " << name << endl;
            int fee;
            cout << "New Fee: ";
            cin >> fee;
            Doctors[i].setdoctorFee(fee);
            cout << "Doctor fee changed successfully." << endl;
            return;
        }
    }
    cout << "Doctor not found." << endl;
}
void seeAppointments(appointmentScheduling& scheduler) {
    cout << "Viewing appointments" << endl;
    scheduler.successfulAppointment();
}
void addPatient(patient*& Patients, int& s, int& capa) {
    if (s >= capa) {
        capa = capa + 3;
        patient* newArr = new patient[capa];
        for (int i = 0; i < s; i++) {
            newArr[i] = Patients[i];
        }
        delete[] Patients;
        Patients = newArr;
    }
    ofstream outFile("patients.txt", ios::app);
    if (!outFile) {
        cout << "Error opening file." << endl;
        return;
    }
    else
    {
        cout << "Enter patient ID" << endl;
        string id;
        cin >> id;
        cout << "Enter patient symptoms" << endl;
        string symptom;
        cin >> symptom;
        cout << "Enter the patient diagnosis" << endl;
        string diagnose;
        cin >> diagnose;
        cout << "Enter patient name: ";
        string name;
        cin >> name;
        cout << "Enter patient age: ";
        int age;
        cin >> age;
        cout << "Enter patient type: ";
        string type;
        cin >> type;

        Patients[s] = patient(id, name, age, type, symptom, diagnose);
        outFile << "Name: " << name << ", ID: " << id << ", Age: " << age << ", Type: " << type << ", Symptoms: " << symptom << ", Diagnosis: " << diagnose << endl;
        s++;
        outFile.close();
    }
}
void removePatient(patient*& Patients, int& s) {
    cout << "Enter patient name to remove: ";
    string name;
    cin >> name;

    for (int i = 0; i < s; i++) {
        if (Patients[i].getcommonpersonName() == name) {
            for (int j = i; j < s - 1; j++) {
                Patients[j] = Patients[j + 1];
            }
            s--;
            cout << "Patient " << name << " removed successfully." << endl;
            return;
        }
    }
    cout << "Patient not found." << endl;
}
void applyLeave(doctor Doctors[], int s) {
    cout << "Enter doctor name to apply for leave: ";
    string name;
    cin >> name;

    for (int i = 0; i < s; i++) {
        if (Doctors[i].getcommonpersonName() == name) {
            cout << "Applying for leave for Dr. " << name << endl;
            string status = "on leave";
            Doctors[i].setdoctorStatus(status);
            cout << "Doctor " << name << " is now on leave." << endl;
            return;
        }
    }
    cout << "Doctor not found." << endl;
}
void doctorPortal(doctor Doctors[], patient Patients[], Room* rooms[], appointmentScheduling& scheduler, int &ds,int &cap,int &ps, int &capa) {
    cout << "Welcome to the Doctor Portal" << endl;
    int choice = 0;
    while (choice != 10) {
        cout << "Press key to perform task " << endl;
        cout << "1. View all Patients" << endl;
        cout << "2. View Patient's Health Record" << endl;
        cout << "3. View Patient's Prescription" << endl;
        cout << "4. Set your Status" << endl;
        cout << "5. Set your Fee" << endl;
        cout << "6. See your appointments" << endl;
        cout << "7. Add Patient" << endl;
        cout << "8. Remove Patient" << endl;
        cout << "9. Apply for Leave" << endl;
        cout << "10. exit " << endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
            viewAllpatients(Patients, ps);
            break;
        case 2:
            viewHealthRecord(Patients, ps);
            break;
        case 3:
            viewPrescription(Patients, ps);
            break;
        case 4:
            setStatus(Doctors, ds);
            break;
        case 5:
            setFee(Doctors, ds);
            break;
        case 6:
            seeAppointments(scheduler);
            break;

        case 7:
            addPatient(Patients, ps, capa);
            break;
        case 8:
            removePatient(Patients, ps);
            break;
        case 9:
            applyLeave(Doctors, ds);
            break;
        default:
            cout << "work" << endl;
        }
    }
    cout << "Thanks you for visiting..." << endl;
}
int main() {

}
